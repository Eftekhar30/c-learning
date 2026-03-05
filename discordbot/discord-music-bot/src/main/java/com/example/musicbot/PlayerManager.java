package com.example.musicbot;

import com.sedmelluq.discord.lavaplayer.player.AudioLoadResultHandler;
import com.sedmelluq.discord.lavaplayer.player.AudioPlayerManager;
import com.sedmelluq.discord.lavaplayer.player.DefaultAudioPlayerManager;
import com.sedmelluq.discord.lavaplayer.source.AudioSourceManagers;
import com.sedmelluq.discord.lavaplayer.tools.FriendlyException;
import com.sedmelluq.discord.lavaplayer.track.AudioPlaylist;
import com.sedmelluq.discord.lavaplayer.track.AudioTrack;
import net.dv8tion.jda.api.EmbedBuilder;
import net.dv8tion.jda.api.entities.Message;
import net.dv8tion.jda.api.entities.channel.concrete.TextChannel;

import java.awt.Color;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.atomic.AtomicInteger;

public class PlayerManager {
    private final AudioPlayerManager audioPlayerManager;

    public PlayerManager() {
        this.audioPlayerManager = new DefaultAudioPlayerManager();

        configureProfessionalAudio();

        AudioSourceManagers.registerRemoteSources(audioPlayerManager);
        AudioSourceManagers.registerLocalSource(audioPlayerManager);

        System.out.println("🎵 Professional Audio System initialized!");
        System.out.println("✅ High-quality resampling enabled");
        System.out.println("✅ Maximum Opus quality (10/10)");
        System.out.println("✅ Professional audio processing");
        System.out.println("✅ Compact playlist loading ready");
    }

    private void configureProfessionalAudio() {
        audioPlayerManager.getConfiguration().setFilterHotSwapEnabled(true);

        audioPlayerManager.getConfiguration().setResamplingQuality(
                com.sedmelluq.discord.lavaplayer.player.AudioConfiguration.ResamplingQuality.HIGH
        );

        audioPlayerManager.getConfiguration().setOpusEncodingQuality(10);

        audioPlayerManager.getConfiguration().setOutputFormat(
                com.sedmelluq.discord.lavaplayer.format.StandardAudioDataFormats.DISCORD_OPUS
        );

        System.out.println("🎛️ Professional audio configuration applied - studio-grade quality enabled");
    }

    public AudioPlayerManager getAudioPlayerManager() {
        return audioPlayerManager;
    }

    public void loadAndPlay(TextChannel channel, String trackUrl, GuildMusicManager musicManager) {
        System.out.println("=== LOADING PROFESSIONAL QUALITY TRACK ===");
        System.out.println("URL: " + trackUrl);

        audioPlayerManager.loadItem(trackUrl, new AudioLoadResultHandler() {
            @Override
            public void trackLoaded(AudioTrack track) {
                System.out.println("✅ SUCCESS: Professional quality track loaded - " + track.getInfo().title);

                EmbedBuilder embed = new EmbedBuilder()
                        .setColor(Color.GREEN)
                        .setTitle("✅ Added to Queue")
                        .setDescription("**" + track.getInfo().title + "**\nby " + track.getInfo().author)
                        .addField("Duration", formatDuration(track.getDuration()), true)
                        .addField("Position in Queue", String.valueOf(musicManager.scheduler.getQueue().size() + 1), true)
                        .addField("🎵 Audio Quality", getProfessionalQualityInfo(trackUrl), true)
                        .setFooter("Professional Audio Processing | Medium volume set for comfort")
                        .setTimestamp(Instant.now());

                channel.sendMessageEmbeds(embed.build()).queue();
                musicManager.scheduler.queue(track);
            }

            @Override
            public void playlistLoaded(AudioPlaylist playlist) {
                System.out.println("✅ SUCCESS: Professional quality playlist loaded");

                if (playlist.getSelectedTrack() != null) {
                    AudioTrack track = playlist.getSelectedTrack();

                    EmbedBuilder embed = new EmbedBuilder()
                            .setColor(Color.GREEN)
                            .setTitle("✅ Added to Queue")
                            .setDescription("**" + track.getInfo().title + "**\nby " + track.getInfo().author)
                            .addField("Source", getProfessionalSourceName(trackUrl), true)
                            .addField("Duration", formatDuration(track.getDuration()), true)
                            .addField("🎵 Audio Quality", getProfessionalQualityInfo(trackUrl), true)
                            .setFooter("Professional Audio Processing")
                            .setTimestamp(Instant.now());

                    channel.sendMessageEmbeds(embed.build()).queue();
                    musicManager.scheduler.queue(track);

                } else if (playlist.isSearchResult()) {
                    AudioTrack track = playlist.getTracks().get(0);
                    System.out.println("✅ SUCCESS: Professional search result - " + track.getInfo().title);

                    EmbedBuilder embed = new EmbedBuilder()
                            .setColor(Color.GREEN)
                            .setTitle("🔍 Found and Added")
                            .setDescription("**" + track.getInfo().title + "**\nby " + track.getInfo().author)
                            .addField("Source", getProfessionalSourceName(trackUrl), true)
                            .addField("Duration", formatDuration(track.getDuration()), true)
                            .addField("🎵 Audio Quality", getProfessionalQualityInfo(trackUrl), true)
                            .addField("Queue Position", String.valueOf(musicManager.scheduler.getQueue().size() + 1), true)
                            .setFooter("Professional Audio | Use player buttons for bass boost")
                            .setTimestamp(Instant.now());

                    channel.sendMessageEmbeds(embed.build()).queue();
                    musicManager.scheduler.queue(track);

                } else {
                    EmbedBuilder embed = new EmbedBuilder()
                            .setColor(Color.GREEN)
                            .setTitle("✅ Playlist Added")
                            .setDescription("**" + playlist.getName() + "**")
                            .addField("Tracks Added", String.valueOf(playlist.getTracks().size()), true)
                            .addField("Source", getProfessionalSourceName(trackUrl), true)
                            .addField("🎵 Audio Quality", "Professional Processing", true)
                            .addField("📋 Browse Queue", "Use the **Queue** button on the player to browse tracks", false)
                            .setFooter("Compact loading • Professional audio • Use player buttons for control")
                            .setTimestamp(Instant.now());

                    channel.sendMessageEmbeds(embed.build()).queue();

                    for (AudioTrack track : playlist.getTracks()) {
                        musicManager.scheduler.queue(track);
                    }
                }
            }

            @Override
            public void noMatches() {
                System.out.println("❌ NO MATCHES for: " + trackUrl);

                EmbedBuilder embed = new EmbedBuilder()
                        .setColor(Color.RED)
                        .setTitle("❌ No Results Found")
                        .setDescription("No matches found for your search")
                        .addField("Search Query", trackUrl, false)
                        .addField("💡 Try Professional Sources:", "• `scsearch:` for SoundCloud (Studio Quality)\n• `ytsearch:` for YouTube\n• Direct FLAC/MP3 URLs (Lossless)\n• Spotify playlists (Auto-convert)", false)
                        .setFooter("SoundCloud recommended for professional audio quality!")
                        .setTimestamp(Instant.now());

                channel.sendMessageEmbeds(embed.build()).queue();
            }

            @Override
            public void loadFailed(FriendlyException exception) {
                System.err.println("=== PROFESSIONAL AUDIO LOAD FAILED ===");
                System.err.println("Track URL: " + trackUrl);
                System.err.println("Exception: " + exception.getMessage());

                EmbedBuilder embed = new EmbedBuilder()
                        .setColor(Color.RED)
                        .setTitle("❌ Failed to Load Professional Track")
                        .setTimestamp(Instant.now());

                String errorMsg = exception.getMessage().toLowerCase();
                if (errorMsg.contains("sign in") || errorMsg.contains("bot") || errorMsg.contains("404") || errorMsg.contains("400")) {
                    embed.setDescription("**Service Blocked Bot Access**")
                            .addField("💡 Try Studio-Grade Alternatives:", "• `!play scsearch:song name` (Professional SoundCloud)\n• `!play https://direct-url.flac` (Lossless Quality)\n• Spotify playlists (Auto-converted to SoundCloud)", false)
                            .setFooter("YouTube blocks bots - SoundCloud provides superior audio quality!")
                            .setColor(Color.ORANGE);
                } else if (errorMsg.contains("unavailable") || errorMsg.contains("private")) {
                    embed.setDescription("**Content Not Available**")
                            .addField("Reason", "Content is private, deleted, or region-locked", false)
                            .setFooter("Try searching for a professional-quality version on SoundCloud");
                } else if (errorMsg.contains("age")) {
                    embed.setDescription("**Age-Restricted Content**")
                            .addField("Reason", "This content cannot be played by bots", false)
                            .setFooter("Try searching for an all-ages version with professional quality");
                } else if (errorMsg.contains("format")) {
                    embed.setDescription("**Unsupported Format**")
                            .addField("✅ Supported Professional Formats", "FLAC (Lossless), MP3 (320kbps), OGG, M4A, WebM", false)
                            .setFooter("Use high-quality formats for best professional audio experience");
                } else {
                    embed.setDescription("**Audio Loading Error**")
                            .addField("Error Details", exception.getMessage(), false)
                            .setFooter("Try a different professional audio source");
                }

                channel.sendMessageEmbeds(embed.build()).queue();
                System.err.println("=== END PROFESSIONAL DEBUG ===");
            }
        });
    }

    public void loadSpotifyPlaylistBatch(List<SpotifyManager.SpotifyTrackInfo> spotifyTracks,
                                         GuildMusicManager musicManager,
                                         Message loadingMessage) {

        List<PlaylistResult> successfulTracks = new ArrayList<>();
        List<PlaylistResult> failedTracks = new ArrayList<>();
        AtomicInteger processedCount = new AtomicInteger(0);

        System.out.println("=== PROFESSIONAL BATCH LOADING " + spotifyTracks.size() + " SPOTIFY TRACKS ===");

        for (SpotifyManager.SpotifyTrackInfo spotifyTrack : spotifyTracks) {
            String searchQuery = "scsearch:" + spotifyTrack.getSearchQuery();

            CompletableFuture<Void> future = CompletableFuture.runAsync(() -> {
                audioPlayerManager.loadItem(searchQuery, new AudioLoadResultHandler() {
                    @Override
                    public void trackLoaded(AudioTrack track) {
                        successfulTracks.add(new PlaylistResult(spotifyTrack, track, true));
                        musicManager.scheduler.queue(track);
                        System.out.println("✅ PROFESSIONAL BATCH SUCCESS: " + track.getInfo().title);

                        int processed = processedCount.incrementAndGet();
                        if (processed == spotifyTracks.size()) {
                            showCompactConsolidatedResults(loadingMessage, successfulTracks, failedTracks, spotifyTracks.size());
                        }
                    }

                    @Override
                    public void playlistLoaded(AudioPlaylist playlist) {
                        if (playlist.isSearchResult() && !playlist.getTracks().isEmpty()) {
                            AudioTrack track = playlist.getTracks().get(0);
                            successfulTracks.add(new PlaylistResult(spotifyTrack, track, true));
                            musicManager.scheduler.queue(track);
                            System.out.println("✅ PROFESSIONAL BATCH SUCCESS: " + track.getInfo().title);
                        } else {
                            failedTracks.add(new PlaylistResult(spotifyTrack, null, false));
                            System.out.println("❌ PROFESSIONAL BATCH FAIL: No results for " + spotifyTrack.getDisplayName());
                        }

                        int processed = processedCount.incrementAndGet();
                        if (processed == spotifyTracks.size()) {
                            showCompactConsolidatedResults(loadingMessage, successfulTracks, failedTracks, spotifyTracks.size());
                        }
                    }

                    @Override
                    public void noMatches() {
                        failedTracks.add(new PlaylistResult(spotifyTrack, null, false));
                        System.out.println("❌ PROFESSIONAL BATCH FAIL: No matches for " + spotifyTrack.getDisplayName());

                        int processed = processedCount.incrementAndGet();
                        if (processed == spotifyTracks.size()) {
                            showCompactConsolidatedResults(loadingMessage, successfulTracks, failedTracks, spotifyTracks.size());
                        }
                    }

                    @Override
                    public void loadFailed(FriendlyException exception) {
                        failedTracks.add(new PlaylistResult(spotifyTrack, null, false));
                        System.out.println("❌ PROFESSIONAL BATCH FAIL: " + spotifyTrack.getDisplayName() + " - " + exception.getMessage());

                        int processed = processedCount.incrementAndGet();
                        if (processed == spotifyTracks.size()) {
                            showCompactConsolidatedResults(loadingMessage, successfulTracks, failedTracks, spotifyTracks.size());
                        }
                    }
                });
            });

            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }

    private void showCompactConsolidatedResults(Message loadingMessage,
                                                List<PlaylistResult> successfulTracks,
                                                List<PlaylistResult> failedTracks,
                                                int totalTracks) {

        int successPercentage = (int) Math.round(((double) successfulTracks.size() / totalTracks) * 100);

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.decode("#1DB954"))
                .setTitle("🎵 Professional Playlist Processing Complete")
                .setTimestamp(Instant.now());

        StringBuilder summary = new StringBuilder();
        summary.append("**").append(successfulTracks.size()).append("** tracks successfully added to queue\n");

        if (failedTracks.size() > 0) {
            summary.append("**").append(failedTracks.size()).append("** tracks couldn't be found\n");
        }

        summary.append("\n🎵 **Professional Audio Processing Applied**\n");
        summary.append("📋 Use **Queue** button on player to browse tracks\n");
        summary.append("🔊 Use **Bass Boost** buttons for enhanced sound");

        embed.setDescription(summary.toString());

        embed.addField("📊 Success Rate", successPercentage + "% (" + successfulTracks.size() + "/" + totalTracks + ")", true);
        embed.addField("🎵 Audio Quality", "Studio-Grade Processing", true);
        embed.addField("📋 Queue Control", "Interactive Player Ready", true);

        embed.setFooter("Professional audio ready • Use player buttons for bass boost and EQ • Source: Spotify → SoundCloud");

        loadingMessage.editMessageEmbeds(embed.build()).queue();

        System.out.println("=== PROFESSIONAL BATCH LOADING COMPLETE ===");
        System.out.println("Success Rate: " + successPercentage + "% (" + successfulTracks.size() + "/" + totalTracks + ")");
        System.out.println("Professional audio processing applied to all successful tracks");
    }

    public void loadAndPlaySilent(TextChannel channel, String trackUrl, GuildMusicManager musicManager, SpotifyManager.SpotifyTrackInfo spotifyInfo) {
        audioPlayerManager.loadItem(trackUrl, new AudioLoadResultHandler() {
            @Override
            public void trackLoaded(AudioTrack track) {
                System.out.println("✅ PROFESSIONAL SILENT SUCCESS: " + track.getInfo().title + " (from Spotify: " + spotifyInfo.getDisplayName() + ")");
                musicManager.scheduler.queue(track);
            }

            @Override
            public void playlistLoaded(AudioPlaylist playlist) {
                if (playlist.isSearchResult() && !playlist.getTracks().isEmpty()) {
                    AudioTrack track = playlist.getTracks().get(0);
                    System.out.println("✅ PROFESSIONAL SILENT SUCCESS: " + track.getInfo().title + " (from Spotify: " + spotifyInfo.getDisplayName() + ")");
                    musicManager.scheduler.queue(track);
                }
            }

            @Override
            public void noMatches() {
                System.out.println("❌ PROFESSIONAL SILENT FAIL: No SoundCloud match for " + spotifyInfo.getDisplayName());
            }

            @Override
            public void loadFailed(FriendlyException exception) {
                System.out.println("❌ PROFESSIONAL SILENT FAIL: " + spotifyInfo.getDisplayName() + " - " + exception.getMessage());
            }
        });
    }

    private static class PlaylistResult {
        public final SpotifyManager.SpotifyTrackInfo spotifyTrack;
        public final AudioTrack loadedTrack;
        public final boolean success;

        public PlaylistResult(SpotifyManager.SpotifyTrackInfo spotifyTrack, AudioTrack loadedTrack, boolean success) {
            this.spotifyTrack = spotifyTrack;
            this.loadedTrack = loadedTrack;
            this.success = success;
        }
    }

    private String formatDuration(long durationMs) {
        if (durationMs == 0) return "Unknown";

        long seconds = durationMs / 1000;
        long minutes = seconds / 60;
        seconds = seconds % 60;

        if (minutes >= 60) {
            long hours = minutes / 60;
            minutes = minutes % 60;
            return String.format("%d:%02d:%02d", hours, minutes, seconds);
        }
        return String.format("%d:%02d", minutes, seconds);
    }

    private String getProfessionalQualityInfo(String trackUrl) {
        if (trackUrl.contains("scsearch:")) return "🔊 Studio Quality";
        if (trackUrl.contains("soundcloud.com")) return "🔊 Studio Quality";
        if (trackUrl.contains(".flac")) return "🎵 Lossless (FLAC)";
        if (trackUrl.contains(".mp3")) return "🎵 High Quality (MP3)";
        if (trackUrl.contains("ytsearch:")) return "📺 Standard (YouTube)";
        if (trackUrl.contains("youtube.com")) return "📺 Direct (YouTube)";
        if (trackUrl.contains("bandcamp.com")) return "🎵 Studio Quality";
        return "🎵 Professional";
    }

    private String getProfessionalSourceName(String trackUrl) {
        if (trackUrl.contains("scsearch:")) return "SoundCloud Search (Studio)";
        if (trackUrl.contains("ytsearch:") || trackUrl.contains("ytmsearch:")) return "YouTube Search";
        if (trackUrl.contains("soundcloud.com")) return "SoundCloud Direct (Studio)";
        if (trackUrl.contains("youtube.com") || trackUrl.contains("youtu.be")) return "YouTube Direct";
        if (trackUrl.contains("spotify.com")) return "Spotify";
        if (trackUrl.contains("bandcamp.com")) return "Bandcamp (Studio)";
        if (trackUrl.contains("archive.org")) return "Internet Archive";
        if (trackUrl.contains(".flac")) return "FLAC (Lossless)";
        if (trackUrl.contains(".mp3")) return "MP3 (Studio Quality)";
        if (trackUrl.contains("http")) return "Direct Audio URL";
        return "Professional Source";
    }
}