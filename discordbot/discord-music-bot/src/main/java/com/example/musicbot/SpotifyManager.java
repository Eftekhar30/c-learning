package com.example.musicbot;

import se.michaelthelin.spotify.SpotifyApi;
import se.michaelthelin.spotify.exceptions.SpotifyWebApiException;
import se.michaelthelin.spotify.model_objects.credentials.ClientCredentials;
import se.michaelthelin.spotify.model_objects.specification.Track;
import se.michaelthelin.spotify.model_objects.specification.PlaylistTrack;
import se.michaelthelin.spotify.model_objects.specification.Playlist;
import se.michaelthelin.spotify.requests.authorization.client_credentials.ClientCredentialsRequest;
import se.michaelthelin.spotify.requests.data.playlists.GetPlaylistRequest;
import se.michaelthelin.spotify.requests.data.playlists.GetPlaylistsItemsRequest;
import se.michaelthelin.spotify.requests.data.tracks.GetTrackRequest;
import org.apache.hc.core5.http.ParseException;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SpotifyManager {
    private final SpotifyApi spotifyApi;
    private String accessToken;
    private long tokenExpiry;

    private static final String CLIENT_ID = "841a06dab0e344dc82dc148a9ee6293d";
    private static final String CLIENT_SECRET = "717cc77e5e604d0cb171be5fde02d027";

    public SpotifyManager() {
        this.spotifyApi = new SpotifyApi.Builder()
                .setClientId(CLIENT_ID)
                .setClientSecret(CLIENT_SECRET)
                .build();

        refreshAccessToken();
    }

    private void refreshAccessToken() {
        try {
            ClientCredentialsRequest clientCredentialsRequest = spotifyApi.clientCredentials().build();
            ClientCredentials clientCredentials = clientCredentialsRequest.execute();

            this.accessToken = clientCredentials.getAccessToken();
            this.tokenExpiry = System.currentTimeMillis() + (clientCredentials.getExpiresIn() * 1000);

            spotifyApi.setAccessToken(accessToken);
            System.out.println("Spotify access token refreshed for large playlist support");
        } catch (IOException | SpotifyWebApiException | ParseException e) {
            System.err.println("Error refreshing Spotify token: " + e.getMessage());
        }
    }

    private void checkAndRefreshToken() {
        if (System.currentTimeMillis() >= tokenExpiry - 60000) {
            refreshAccessToken();
        }
    }

    public boolean isSpotifyUrl(String url) {
        return url.contains("spotify.com/") || url.contains("open.spotify.com/");
    }

    public String extractSpotifyId(String url) {
        Pattern pattern = Pattern.compile("(track|playlist|album)/([a-zA-Z0-9]+)");
        Matcher matcher = pattern.matcher(url);
        if (matcher.find()) {
            return matcher.group(2);
        }
        return null;
    }

    public String getSpotifyType(String url) {
        if (url.contains("/track/")) return "track";
        if (url.contains("/playlist/")) return "playlist";
        if (url.contains("/album/")) return "album";
        return null;
    }

    public SpotifyTrackInfo getTrackInfo(String trackId) {
        checkAndRefreshToken();

        try {
            GetTrackRequest getTrackRequest = spotifyApi.getTrack(trackId).build();
            Track track = getTrackRequest.execute();

            String title = track.getName();
            String artist = track.getArtists()[0].getName();
            long duration = track.getDurationMs();

            return new SpotifyTrackInfo(title, artist, duration);
        } catch (IOException | SpotifyWebApiException | ParseException e) {
            System.err.println("Error getting Spotify track: " + e.getMessage());
            return null;
        }
    }


    public List<SpotifyTrackInfo> getAllPlaylistTracks(String playlistId) {
        checkAndRefreshToken();

        List<SpotifyTrackInfo> allTracks = new ArrayList<>();
        int offset = 0;
        final int limit = 100;
        boolean hasMore = true;

        System.out.println("🔍 Fetching large Spotify playlist with pagination...");

        try {
            while (hasMore) {
                GetPlaylistsItemsRequest getPlaylistItemsRequest = spotifyApi
                        .getPlaylistsItems(playlistId)
                        .limit(limit)
                        .offset(offset)
                        .build();

                PlaylistTrack[] playlistTracks = getPlaylistItemsRequest.execute().getItems();

                if (playlistTracks.length == 0) {
                    hasMore = false;
                    break;
                }

                for (PlaylistTrack playlistTrack : playlistTracks) {
                    if (playlistTrack.getTrack() instanceof Track) {
                        Track track = (Track) playlistTrack.getTrack();
                        String title = track.getName();
                        String artist = track.getArtists()[0].getName();
                        long duration = track.getDurationMs();

                        allTracks.add(new SpotifyTrackInfo(title, artist, duration));
                    }
                }

                offset += limit;
                hasMore = playlistTracks.length == limit;

                System.out.println("📥 Fetched " + allTracks.size() + " tracks so far...");

                Thread.sleep(50);
            }
        } catch (IOException | SpotifyWebApiException | ParseException | InterruptedException e) {
            System.err.println("Error getting large Spotify playlist: " + e.getMessage());
        }

        System.out.println("✅ Successfully fetched " + allTracks.size() + " tracks from Spotify playlist");
        return allTracks;
    }

    public List<SpotifyTrackInfo> getPlaylistTracks(String playlistId) {
        checkAndRefreshToken();

        List<SpotifyTrackInfo> tracks = new ArrayList<>();

        try {
            GetPlaylistRequest getPlaylistRequest = spotifyApi.getPlaylist(playlistId).build();
            Playlist playlist = getPlaylistRequest.execute();

            GetPlaylistsItemsRequest getPlaylistItemsRequest = spotifyApi
                    .getPlaylistsItems(playlistId)
                    .limit(50)
                    .build();

            PlaylistTrack[] playlistTracks = getPlaylistItemsRequest.execute().getItems();

            for (PlaylistTrack playlistTrack : playlistTracks) {
                if (playlistTrack.getTrack() instanceof Track) {
                    Track track = (Track) playlistTrack.getTrack();
                    String title = track.getName();
                    String artist = track.getArtists()[0].getName();
                    long duration = track.getDurationMs();

                    tracks.add(new SpotifyTrackInfo(title, artist, duration));
                }
            }
        } catch (IOException | SpotifyWebApiException | ParseException e) {
            System.err.println("Error getting Spotify playlist: " + e.getMessage());
        }

        return tracks;
    }

    public static class SpotifyTrackInfo {
        private final String title;
        private final String artist;
        private final long duration;

        public SpotifyTrackInfo(String title, String artist, long duration) {
            this.title = title;
            this.artist = artist;
            this.duration = duration;
        }

        public String getTitle() { return title; }
        public String getArtist() { return artist; }
        public long getDuration() { return duration; }

        public String getSearchQuery() {
            return artist + " " + title;
        }

        public String getDisplayName() {
            return title + " by " + artist;
        }
    }
}