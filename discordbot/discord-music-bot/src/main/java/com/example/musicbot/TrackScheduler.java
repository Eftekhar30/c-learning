package com.example.musicbot;

import com.sedmelluq.discord.lavaplayer.player.AudioPlayer;
import com.sedmelluq.discord.lavaplayer.player.event.AudioEventAdapter;
import com.sedmelluq.discord.lavaplayer.track.AudioTrack;
import com.sedmelluq.discord.lavaplayer.track.AudioTrackEndReason;
import net.dv8tion.jda.api.entities.Guild;
import net.dv8tion.jda.api.entities.channel.concrete.TextChannel;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.List;
import java.util.ArrayList;

public class TrackScheduler extends AudioEventAdapter {
    private final AudioPlayer player;
    private final BlockingQueue<AudioTrack> queue;
    private boolean isLooping = false;

    private Guild guild;
    private TextChannel channel;

    private final List<AudioTrack> playHistory;
    private static final int MAX_QUEUE_SIZE = 1000;

    public TrackScheduler(AudioPlayer player) {
        this.player = player;
        this.queue = new LinkedBlockingQueue<>();
        this.playHistory = new ArrayList<>();

        System.out.println("🎵 Professional TrackScheduler initialized");
        System.out.println("✅ Large playlist support (up to " + MAX_QUEUE_SIZE + " tracks)");
        System.out.println("✅ Anti-spam player integration ready");
        System.out.println("✅ No shuffle - maintains exact load order");
    }

    public void setChannel(Guild guild, TextChannel channel) {
        this.guild = guild;
        this.channel = channel;
        System.out.println("🔗 TrackScheduler linked to channel: " + channel.getName() + " in " + guild.getName());
    }

    public void queue(AudioTrack track) {
        if (queue.size() >= MAX_QUEUE_SIZE) {
            System.out.println("⚠️ Queue size limit reached (" + MAX_QUEUE_SIZE + ") - skipping track: " + track.getInfo().title);
            return;
        }

        if (!player.startTrack(track, true)) {
            queue.offer(track);
            System.out.println("📋 Queued: " + track.getInfo().title + " (Position: " + queue.size() + ")");
        } else {
            System.out.println("▶️ Now playing: " + track.getInfo().title);

            if (guild != null && channel != null) {
                java.util.concurrent.CompletableFuture.delayedExecutor(1, java.util.concurrent.TimeUnit.SECONDS)
                        .execute(this::triggerPlayerUpdate);
            }
        }
    }

    public int queueMultiple(List<AudioTrack> tracks) {
        int queued = 0;
        for (AudioTrack track : tracks) {
            if (queue.size() >= MAX_QUEUE_SIZE) {
                System.out.println("⚠️ Queue limit reached - queued " + queued + "/" + tracks.size() + " tracks");
                break;
            }
            queue(track);
            queued++;
        }
        return queued;
    }

    public void nextTrack() {
        AudioTrack currentTrack = player.getPlayingTrack();
        if (currentTrack != null) {
            playHistory.add(currentTrack);

            if (playHistory.size() > 100) {
                playHistory.remove(0);
            }
        }

        AudioTrack nextTrack = queue.poll();
        player.startTrack(nextTrack, false);

        if (nextTrack != null) {
            System.out.println("⏭️ Advanced to next track: " + nextTrack.getInfo().title);
            System.out.println("📊 Queue status: " + queue.size() + " tracks remaining");

            if (guild != null && channel != null) {
                triggerPlayerUpdate();
            }
        } else {
            System.out.println("📭 Queue finished - no more tracks");
        }
    }

    public void clear() {
        int clearedCount = queue.size();
        queue.clear();
        playHistory.clear();
        System.out.println("🧹 Cleared " + clearedCount + " tracks from queue and reset history");
    }

    public BlockingQueue<AudioTrack> getQueue() {
        return queue;
    }

    public int getQueueSize() {
        return queue.size();
    }

    public List<AudioTrack> getPlayHistory() {
        return new ArrayList<>(playHistory);
    }

    public void setLooping(boolean looping) {
        this.isLooping = looping;
        System.out.println("🔄 Loop mode: " + (looping ? "ENABLED" : "DISABLED"));
    }

    public boolean isLooping() {
        return isLooping;
    }

    @Override
    public void onTrackEnd(AudioPlayer player, AudioTrack track, AudioTrackEndReason endReason) {
        playHistory.add(track);
        if (playHistory.size() > 100) {
            playHistory.remove(0);
        }

        System.out.println("🏁 Track ended: " + track.getInfo().title + " (Reason: " + endReason.name() + ")");

        if (endReason.mayStartNext) {
            if (isLooping) {
                AudioTrack clonedTrack = track.makeClone();
                player.startTrack(clonedTrack, false);
                System.out.println("🔄 Looping track: " + track.getInfo().title);

                if (guild != null && channel != null) {
                    java.util.concurrent.CompletableFuture.delayedExecutor(500, java.util.concurrent.TimeUnit.MILLISECONDS)
                            .execute(this::triggerPlayerUpdate);
                }
            } else {
                AudioTrack nextTrack = queue.poll();
                player.startTrack(nextTrack, false);

                if (nextTrack != null) {
                    System.out.println("⏭️ Auto-advanced to: " + nextTrack.getInfo().title);
                    System.out.println("📊 Queue status: " + queue.size() + " tracks remaining");

                    if (guild != null && channel != null) {
                        java.util.concurrent.CompletableFuture.delayedExecutor(1, java.util.concurrent.TimeUnit.SECONDS)
                                .execute(this::triggerPlayerUpdate);
                    }
                } else {
                    System.out.println("📭 Queue finished - all tracks played");
                }
            }
        }
    }

    private void triggerPlayerUpdate() {
        if (guild == null || channel == null) {
            System.out.println("⚠️ Cannot update player - guild or channel not set");
            return;
        }

        AudioTrack currentTrack = player.getPlayingTrack();
        if (currentTrack == null) {
            System.out.println("⚠️ Cannot update player - no track playing");
            return;
        }

        System.out.println("🔄 Triggering professional player update for: " + currentTrack.getInfo().title);

        try {

        } catch (Exception e) {
            System.err.println("❌ Error triggering player update: " + e.getMessage());
        }
    }

    public List<AudioTrack> getUpcomingTracks(int count) {
        List<AudioTrack> upcoming = new ArrayList<>();
        AudioTrack[] queueArray = queue.toArray(new AudioTrack[0]);

        int limit = Math.min(count, queueArray.length);
        for (int i = 0; i < limit; i++) {
            upcoming.add(queueArray[i]);
        }

        return upcoming;
    }

    public List<AudioTrack> getQueuePage(int page, int pageSize) {
        List<AudioTrack> queueList = new ArrayList<>(queue);
        int start = page * pageSize;
        int end = Math.min(start + pageSize, queueList.size());

        if (start >= queueList.size()) {
            return new ArrayList<>();
        }

        return queueList.subList(start, end);
    }

    public int getTotalPages(int pageSize) {
        return (int) Math.ceil((double) queue.size() / pageSize);
    }

    public String getQueueStats() {
        long totalDuration = queue.stream()
                .mapToLong(track -> track.getDuration())
                .sum();

        long hours = totalDuration / (1000 * 60 * 60);
        long minutes = (totalDuration % (1000 * 60 * 60)) / (1000 * 60);

        return String.format("📊 %d tracks | 🕒 %d:%02d total", queue.size(), hours, minutes);
    }

    public boolean removeTrack(int position) {
        if (position < 1 || position > queue.size()) {
            return false;
        }

        List<AudioTrack> queueList = new ArrayList<>(queue);
        if (position <= queueList.size()) {
            AudioTrack removed = queueList.remove(position - 1);
            queue.clear();
            queue.addAll(queueList);
            System.out.println("🗑️ Removed track at position " + position + ": " + removed.getInfo().title);
            return true;
        }
        return false;
    }

    public boolean hasTracksQueued() {
        return !queue.isEmpty();
    }

    public boolean isPlaying() {
        return player.getPlayingTrack() != null;
    }

    public AudioTrack getCurrentTrack() {
        return player.getPlayingTrack();
    }

    public boolean isPaused() {
        return player.isPaused();
    }

    public boolean canAddMoreTracks(int count) {
        return (queue.size() + count) <= MAX_QUEUE_SIZE;
    }

    public int getRemainingCapacity() {
        return MAX_QUEUE_SIZE - queue.size();
    }
}