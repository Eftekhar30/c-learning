package com.example.musicbot;

import net.dv8tion.jda.api.EmbedBuilder;
import net.dv8tion.jda.api.entities.Guild;
import net.dv8tion.jda.api.entities.Member;
import net.dv8tion.jda.api.entities.Message;
import net.dv8tion.jda.api.entities.MessageEmbed;
import net.dv8tion.jda.api.entities.channel.concrete.TextChannel;
import net.dv8tion.jda.api.entities.channel.concrete.VoiceChannel;
import net.dv8tion.jda.api.events.message.MessageReceivedEvent;
import net.dv8tion.jda.api.events.interaction.component.ButtonInteractionEvent;
import net.dv8tion.jda.api.events.interaction.command.SlashCommandInteractionEvent;
import net.dv8tion.jda.api.hooks.ListenerAdapter;
import net.dv8tion.jda.api.interactions.components.buttons.Button;
import net.dv8tion.jda.api.interactions.components.ActionRow;
import net.dv8tion.jda.api.managers.AudioManager;
import com.sedmelluq.discord.lavaplayer.filter.equalizer.EqualizerFactory;
import com.sedmelluq.discord.lavaplayer.track.AudioTrack;

import java.awt.Color;
import java.time.Instant;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class CommandListener extends ListenerAdapter {
    private final Map<Long, GuildMusicManager> musicManagers;
    private final PlayerManager playerManager;
    private final SpotifyManager spotifyManager;

    private final Map<Long, String> guildBassLevel;
    private final Map<Long, String> guildAudioPreset;

    private final Map<Long, Message> currentPlayerMessages;
    private final Map<Long, Message> currentQueueMessages;
    private final Map<Long, Integer> queuePages;

    private final ScheduledExecutorService scheduler;

    public CommandListener() {
        this.musicManagers = new HashMap<>();
        this.playerManager = new PlayerManager();
        this.spotifyManager = new SpotifyManager();
        this.guildBassLevel = new HashMap<>();
        this.guildAudioPreset = new HashMap<>();
        this.currentPlayerMessages = new HashMap<>();
        this.currentQueueMessages = new HashMap<>();
        this.queuePages = new HashMap<>();
        this.scheduler = Executors.newScheduledThreadPool(2);

        System.out.println("🚫 Complete anti-spam system initialized");
        System.out.println("⏰ Auto-delete queue system ready (1 minute)");
        System.out.println("🎵 Slash commands handler ready");
    }

    @Override
    public void onSlashCommandInteraction(SlashCommandInteractionEvent event) {
        String command = event.getName();
        Guild guild = event.getGuild();
        TextChannel channel = event.getChannel().asTextChannel();
        Member member = event.getMember();

        if (guild == null || member == null) {
            event.reply("❌ Error processing slash command!").setEphemeral(true).queue();
            return;
        }

        if (member.getVoiceState() == null || member.getVoiceState().getChannel() == null) {
            if (command.equals("g3play")) {
                event.reply("❌ You need to be in a voice channel to use `/g3play`!").setEphemeral(true).queue();
                return;
            }
        }

        switch (command) {
            case "g3play":
                String query = event.getOption("query").getAsString();
                event.reply("🎵 Loading: **" + query + "** with professional audio...").setEphemeral(true).queue();
                handlePlayCommandSlash(guild, member, channel, query);
                break;

            case "g3volume":
                int volume = (int) event.getOption("level").getAsLong();
                if (volume < 0 || volume > 100) {
                    event.reply("❌ Volume must be between 0 and 100!").setEphemeral(true).queue();
                    return;
                }
                handleVolumeCommandSlash(guild, channel, volume);
                event.reply("🔊 Volume set to **" + volume + "%** with smart audio scaling!").setEphemeral(true).queue();
                break;

            case "g3bass":
                String bassLevel = event.getOption("level").getAsString().toLowerCase();
                if (!bassLevel.matches("off|low|medium|high|extreme")) {
                    event.reply("❌ Invalid bass level! Use: `off`, `low`, `medium`, `high`, or `extreme`").setEphemeral(true).queue();
                    return;
                }
                handleBassCommandSlash(guild, channel, bassLevel);
                event.reply("🔊 Professional bass boost set to: **" + bassLevel.toUpperCase() + "**").setEphemeral(true).queue();
                break;

            case "g3preset":
                String preset = event.getOption("preset").getAsString().toLowerCase();
                if (!preset.matches("rock|electronic|vocal|clear")) {
                    event.reply("❌ Invalid preset! Use: `rock`, `electronic`, `vocal`, or `clear`").setEphemeral(true).queue();
                    return;
                }
                handlePresetCommandSlash(guild, channel, preset);
                event.reply("🎛️ Professional audio preset: **" + preset.toUpperCase() + "**").setEphemeral(true).queue();
                break;

            case "g3queue":
                int page = 0;
                if (event.getOption("page") != null) {
                    page = Math.max(0, (int) event.getOption("page").getAsLong() - 1);
                }
                createOrUpdateQueueDisplayWithAutoDelete(guild, channel, page);
                event.reply("📋 Professional queue displayed with auto-delete!").setEphemeral(true).queue();
                break;

            case "g3skip":
                GuildMusicManager musicManager = getMusicManager(guild);
                if (musicManager.player.getPlayingTrack() == null) {
                    event.reply("❌ No song is currently playing!").setEphemeral(true).queue();
                    return;
                }
                String skippedTitle = musicManager.player.getPlayingTrack().getInfo().title;
                musicManager.scheduler.nextTrack();
                event.reply("⏭️ Skipped: **" + skippedTitle + "**").setEphemeral(true).queue();
                createOrUpdatePlayerDisplay(guild, channel);
                break;

            case "g3stop":
                handleStopCommandSlash(guild, channel);
                event.reply("⏹️ Professional audio system stopped and disconnected!").setEphemeral(true).queue();
                break;

            case "g3help":
                handleHelpCommandSlash(channel);
                event.reply("📖 Professional bot commands sent!").setEphemeral(true).queue();
                break;
        }
    }

    @Override
    public void onMessageReceived(MessageReceivedEvent event) {
        if (event.getAuthor().isBot()) return;

        String message = event.getMessage().getContentRaw();
        if (!message.startsWith("!")) return;

        String[] args = message.substring(1).split("\\s+");
        String command = args[0].toLowerCase();

        TextChannel channel = event.getChannel().asTextChannel();
        Member member = event.getMember();
        Guild guild = event.getGuild();

        if (member == null || member.getVoiceState() == null ||
                member.getVoiceState().getChannel() == null) {
            if (command.equals("play") || command.equals("join")) {
                channel.sendMessage("❌ You need to be in a voice channel! (Try `/g3play` instead)").queue();
                return;
            }
        }

        switch (command) {
            case "join":
                handleJoinCommand(guild, member, channel);
                break;
            case "leave":
                handleLeaveCommand(guild, channel);
                break;
            case "play":
                if (args.length < 2) {
                    channel.sendMessage("❌ Usage: `!play <song name or URL>` or try `/g3play`").queue();
                    return;
                }
                String query = String.join(" ", java.util.Arrays.copyOfRange(args, 1, args.length));
                handlePlayCommand(guild, member, channel, query);
                break;
            case "skip":
                handleSkipCommand(guild, channel);
                break;
            case "stop":
                handleStopCommand(guild, channel);
                break;
            case "queue":
            case "q":
                int page = 0;
                if (args.length > 1) {
                    try {
                        page = Integer.parseInt(args[1]) - 1;
                        if (page < 0) page = 0;
                    } catch (NumberFormatException e) {
                        page = 0;
                    }
                }
                createOrUpdateQueueDisplayWithAutoDelete(guild, channel, page);
                break;
            case "np":
            case "nowplaying":
            case "player":
                handleNowPlayingCommand(guild, channel);
                break;
            case "volume":
                if (args.length < 2) {
                    channel.sendMessage("❌ Usage: `!volume <0-100>` or try `/g3volume`").queue();
                    return;
                }
                try {
                    int volume = Integer.parseInt(args[1]);
                    handleVolumeCommand(guild, channel, volume);
                } catch (NumberFormatException e) {
                    channel.sendMessage("❌ Volume must be a number between 0 and 100!").queue();
                }
                break;
            case "bass":
                if (args.length < 2) {
                    channel.sendMessage("❌ Usage: `!bass <off/low/medium/high/extreme>` or try `/g3bass`").queue();
                    return;
                }
                handleBassCommand(guild, channel, args[1].toLowerCase());
                break;
            case "preset":
                if (args.length < 2) {
                    channel.sendMessage("❌ Usage: `!preset <rock/electronic/vocal/clear>` or try `/g3preset`").queue();
                    return;
                }
                handlePresetCommand(guild, channel, args[1].toLowerCase());
                break;
            case "help":
                handleHelpCommand(channel);
                break;
            case "sources":
                handleSourcesCommand(channel);
                break;
        }
    }

    @Override
    public void onButtonInteraction(ButtonInteractionEvent event) {
        String buttonId = event.getComponentId();
        Guild guild = event.getGuild();
        TextChannel channel = event.getChannel().asTextChannel();
        Member member = event.getMember();

        if (guild == null || member == null) {
            event.reply("❌ Error processing button interaction!").setEphemeral(true).queue();
            return;
        }

        GuildMusicManager musicManager = getMusicManager(guild);

        switch (buttonId) {
            case "music_skip":
                if (musicManager.player.getPlayingTrack() == null) {
                    event.reply("❌ No song is currently playing!").setEphemeral(true).queue();
                    return;
                }
                String skippedTitle = musicManager.player.getPlayingTrack().getInfo().title;
                musicManager.scheduler.nextTrack();
                event.reply("⏭️ Skipped: **" + skippedTitle + "**").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "music_pause":
                if (musicManager.player.getPlayingTrack() == null) {
                    event.reply("❌ No song is currently playing!").setEphemeral(true).queue();
                    return;
                }

                if (musicManager.player.isPaused()) {
                    musicManager.player.setPaused(false);
                    event.reply("▶️ Resumed playback!").setEphemeral(true).queue();
                } else {
                    musicManager.player.setPaused(true);
                    event.reply("⏸️ Paused playback!").setEphemeral(true).queue();
                }
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "music_stop":
                AudioManager audioManager = guild.getAudioManager();
                musicManager.scheduler.clear();
                musicManager.player.stopTrack();
                audioManager.closeAudioConnection();
                clearAllCurrentMessages(guild);
                event.reply("⏹️ Stopped music, cleared queue, and left voice channel!").setEphemeral(true).queue();
                break;

            case "music_volume_up":
                int currentVol = musicManager.player.getVolume();
                int newVolUp = Math.min(100, currentVol + 10);
                musicManager.player.setVolume(newVolUp);
                reapplyCurrentAudioFilters(guild);
                event.reply("🔊 Volume: " + newVolUp + "%").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "music_volume_down":
                int currentVolDown = musicManager.player.getVolume();
                int newVolDown = Math.max(0, currentVolDown - 10);
                musicManager.player.setVolume(newVolDown);
                reapplyCurrentAudioFilters(guild);
                event.reply("🔉 Volume: " + newVolDown + "%").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "music_queue":
                int currentPage = queuePages.getOrDefault(guild.getIdLong(), 0);
                createOrUpdateQueueDisplayWithAutoDelete(guild, channel, currentPage);
                event.reply("📋 Queue displayed with auto-delete!").setEphemeral(true).queue();
                break;

            case "queue_prev":
                int prevPage = Math.max(0, queuePages.getOrDefault(guild.getIdLong(), 0) - 1);
                queuePages.put(guild.getIdLong(), prevPage);
                updateExistingQueueDisplayWithAutoDelete(guild, channel, prevPage);
                event.deferEdit().queue();
                break;

            case "queue_next":
                GuildMusicManager queueManager = getMusicManager(guild);
                int totalPages = Math.max(1, (int) Math.ceil((double) queueManager.scheduler.getQueue().size() / 10));
                int nextPage = Math.min(totalPages - 1, queuePages.getOrDefault(guild.getIdLong(), 0) + 1);
                queuePages.put(guild.getIdLong(), nextPage);
                updateExistingQueueDisplayWithAutoDelete(guild, channel, nextPage);
                event.deferEdit().queue();
                break;

            case "music_refresh":
                updateExistingPlayerDisplay(guild, channel);
                event.reply("🔄 Player refreshed!").setEphemeral(true).queue();
                break;

            case "bass_off":
                setBassBoostProfessional(guild, "off");
                event.reply("🔊 Bass: **OFF**").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "bass_low":
                setBassBoostProfessional(guild, "low");
                event.reply("🔊 Bass: **LOW** 🎵").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "bass_medium":
                setBassBoostProfessional(guild, "medium");
                event.reply("🔊 Bass: **MEDIUM** 🎵🎵").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "bass_high":
                setBassBoostProfessional(guild, "high");
                event.reply("🔊 Bass: **HIGH** 🎵🎵🎵").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "bass_extreme":
                setBassBoostProfessional(guild, "extreme");
                event.reply("🔊 Bass: **EXTREME** 🎵🎵🎵🎵").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "preset_rock":
                setAudioPresetProfessional(guild, "rock");
                event.reply("🎸 Preset: **ROCK**").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "preset_electronic":
                setAudioPresetProfessional(guild, "electronic");
                event.reply("🎧 Preset: **ELECTRONIC**").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "preset_vocal":
                setAudioPresetProfessional(guild, "vocal");
                event.reply("🎤 Preset: **VOCAL**").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;

            case "preset_clear":
                clearAudioFiltersProfessional(guild);
                event.reply("🎵 Filters: **CLEARED**").setEphemeral(true).queue();
                updateExistingPlayerDisplay(guild, channel);
                break;
        }
    }

    private void handlePlayCommandSlash(Guild guild, Member member, TextChannel channel, String query) {
        VoiceChannel voiceChannel = member.getVoiceState().getChannel().asVoiceChannel();
        AudioManager audioManager = guild.getAudioManager();

        if (!audioManager.isConnected()) {
            audioManager.openAudioConnection(voiceChannel);
        }

        GuildMusicManager musicManager = getMusicManager(guild);
        musicManager.scheduler.setChannel(guild, channel);

        if (spotifyManager.isSpotifyUrl(query)) {
            handleSpotifyUrl(channel, query, musicManager);
            return;
        }

        String finalQuery;
        if (isUrl(query)) {
            finalQuery = query;
        } else if (hasSearchPrefix(query)) {
            finalQuery = query;
        } else {
            finalQuery = "scsearch:" + query;
        }

        playerManager.loadAndPlay(channel, finalQuery, musicManager);
    }

    private void handleVolumeCommandSlash(Guild guild, TextChannel channel, int volume) {
        GuildMusicManager musicManager = getMusicManager(guild);
        musicManager.player.setVolume(volume);
        reapplyCurrentAudioFilters(guild);
        updateExistingPlayerDisplay(guild, channel);
    }

    private void handleBassCommandSlash(Guild guild, TextChannel channel, String level) {
        setBassBoostProfessional(guild, level);
        updateExistingPlayerDisplay(guild, channel);
    }

    private void handlePresetCommandSlash(Guild guild, TextChannel channel, String preset) {
        if (preset.equals("clear")) {
            clearAudioFiltersProfessional(guild);
        } else {
            setAudioPresetProfessional(guild, preset);
        }
        updateExistingPlayerDisplay(guild, channel);
    }

    private void handleStopCommandSlash(Guild guild, TextChannel channel) {
        GuildMusicManager musicManager = getMusicManager(guild);
        AudioManager audioManager = guild.getAudioManager();

        musicManager.scheduler.clear();
        musicManager.player.stopTrack();
        audioManager.closeAudioConnection();
        clearAllCurrentMessages(guild);
    }

    private void handleHelpCommandSlash(TextChannel channel) {
        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.decode("#7289DA"))
                .setTitle("🎵 Professional Music Bot - Slash Commands")
                .setDescription("Studio-grade audio with modern slash commands!")
                .addField("🎶 Music Playback", "`/g3play <song>` - Play with professional audio\n`/g3skip` - Skip current track\n`/g3stop` - Complete stop & disconnect", false)
                .addField("🔊 Professional Audio", "`/g3volume <0-100>` - Smart volume (55% default)\n`/g3bass <off/low/medium/high/extreme>` - Volume-aware bass\n`/g3preset <rock/electronic/vocal/clear>` - Studio presets", false)
                .addField("📋 Queue Management", "`/g3queue [page]` - Anti-spam scrollable queue\nQueue auto-deletes after 1 minute", false)
                .addField("🎮 Interactive Controls", "**Auto-appearing player with buttons:**\n• Professional audio filters\n• Anti-spam system\n• Real-time updates\n• No message clutter", false)
                .addField("🚫 Anti-Spam Features", "• **Player updates in-place**\n• **Queue auto-deletes (1 min)**\n• **Clean chat experience**\n• **Professional UX**", false)
                .addField("ℹ️ Legacy Commands", "Old `!` commands still work alongside slash commands", false)
                .setFooter("✨ Professional slash commands + Complete anti-spam system")
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
    }

    private void handleJoinCommand(Guild guild, Member member, TextChannel channel) {
        VoiceChannel voiceChannel = member.getVoiceState().getChannel().asVoiceChannel();
        AudioManager audioManager = guild.getAudioManager();

        audioManager.openAudioConnection(voiceChannel);

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.GREEN)
                .setTitle("🔊 Connected to Voice")
                .setDescription("Joined **" + voiceChannel.getName() + "**")
                .setFooter("Professional audio ready • Try /g3play for modern commands")
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
    }

    private void handleLeaveCommand(Guild guild, TextChannel channel) {
        AudioManager audioManager = guild.getAudioManager();
        GuildMusicManager musicManager = getMusicManager(guild);

        musicManager.scheduler.clear();
        musicManager.player.stopTrack();
        audioManager.closeAudioConnection();
        clearAllCurrentMessages(guild);

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.RED)
                .setTitle("👋 Disconnected")
                .setDescription("Left voice channel and cleared the queue")
                .setFooter("Try /g3play to start music with professional audio")
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
    }

    private void handlePlayCommand(Guild guild, Member member, TextChannel channel, String query) {
        VoiceChannel voiceChannel = member.getVoiceState().getChannel().asVoiceChannel();
        AudioManager audioManager = guild.getAudioManager();

        if (!audioManager.isConnected()) {
            audioManager.openAudioConnection(voiceChannel);
        }

        GuildMusicManager musicManager = getMusicManager(guild);
        musicManager.scheduler.setChannel(guild, channel);

        if (spotifyManager.isSpotifyUrl(query)) {
            handleSpotifyUrl(channel, query, musicManager);
            return;
        }

        String finalQuery;
        if (isUrl(query)) {
            finalQuery = query;
        } else if (hasSearchPrefix(query)) {
            finalQuery = query;
        } else {
            finalQuery = "scsearch:" + query;
        }

        playerManager.loadAndPlay(channel, finalQuery, musicManager);
    }

    private void handleSpotifyUrl(TextChannel channel, String url, GuildMusicManager musicManager) {
        String spotifyId = spotifyManager.extractSpotifyId(url);
        String type = spotifyManager.getSpotifyType(url);

        if (spotifyId == null || type == null) {
            channel.sendMessage("❌ Invalid Spotify URL!").queue();
            return;
        }

        switch (type) {
            case "track":
                SpotifyManager.SpotifyTrackInfo trackInfo = spotifyManager.getTrackInfo(spotifyId);
                if (trackInfo != null) {
                    EmbedBuilder embed = new EmbedBuilder()
                            .setColor(Color.decode("#1DB954"))
                            .setTitle("🎵 Loading from Spotify")
                            .setDescription("**" + trackInfo.getTitle() + "**\nby " + trackInfo.getArtist())
                            .addField("Source", "Spotify → SoundCloud", true)
                            .addField("Duration", formatDuration(trackInfo.getDuration()), true)
                            .setFooter("Professional audio processing")
                            .setTimestamp(Instant.now());

                    channel.sendMessageEmbeds(embed.build()).queue(message -> {
                        String searchQuery = "scsearch:" + trackInfo.getSearchQuery();
                        playerManager.loadAndPlay(channel, searchQuery, musicManager);

                        java.util.concurrent.CompletableFuture.delayedExecutor(2, java.util.concurrent.TimeUnit.SECONDS)
                                .execute(() -> createOrUpdatePlayerDisplay(channel.getGuild(), channel));
                    });
                } else {
                    channel.sendMessage("❌ Failed to get Spotify track information!").queue();
                }
                break;

            case "playlist":
                EmbedBuilder loadingEmbed = new EmbedBuilder()
                        .setColor(Color.decode("#1DB954"))
                        .setTitle("🔍 Loading Spotify Playlist")
                        .setDescription("Fetching playlist tracks... Please wait.")
                        .setFooter("Professional processing • Large playlists supported • Try /g3queue to browse")
                        .setTimestamp(Instant.now());

                channel.sendMessageEmbeds(loadingEmbed.build()).queue(loadingMessage -> {
                    List<SpotifyManager.SpotifyTrackInfo> spotifyTracks = spotifyManager.getAllPlaylistTracks(spotifyId);

                    if (spotifyTracks.isEmpty()) {
                        EmbedBuilder errorEmbed = new EmbedBuilder()
                                .setColor(Color.RED)
                                .setTitle("❌ Playlist Load Failed")
                                .setDescription("Playlist is empty or failed to load!")
                                .setTimestamp(Instant.now());

                        loadingMessage.editMessageEmbeds(errorEmbed.build()).queue();
                        return;
                    }

                    EmbedBuilder successEmbed = new EmbedBuilder()
                            .setColor(Color.decode("#1DB954"))
                            .setTitle("✅ Playlist Processing Complete")
                            .setDescription("**" + spotifyTracks.size() + "** tracks ready for professional processing")
                            .addField("📋 Browse Tracks", "Use `/g3queue` or the **Queue** button to browse all tracks", false)
                            .addField("🎵 Audio Quality", "Studio-grade processing with bass boost ready", false)
                            .addField("🔊 Professional Features", "Medium volume default • Volume-aware bass boost • No distortion", false)
                            .setFooter("Professional playlist ready • Player will auto-appear")
                            .setTimestamp(Instant.now());

                    loadingMessage.editMessageEmbeds(successEmbed.build()).queue();

                    playerManager.loadSpotifyPlaylistBatch(spotifyTracks, musicManager, loadingMessage);

                    java.util.concurrent.CompletableFuture.delayedExecutor(3, java.util.concurrent.TimeUnit.SECONDS)
                            .execute(() -> createOrUpdatePlayerDisplay(channel.getGuild(), channel));
                });
                break;

            case "album":
                channel.sendMessage("❌ Spotify album support coming soon! Try individual tracks or playlists.").queue();
                break;
        }
    }

    private void handleSkipCommand(Guild guild, TextChannel channel) {
        GuildMusicManager musicManager = getMusicManager(guild);

        if (musicManager.player.getPlayingTrack() == null) {
            channel.sendMessage("❌ No song is currently playing! Try `/g3play` to start music.").queue();
            return;
        }

        String currentTitle = musicManager.player.getPlayingTrack().getInfo().title;
        musicManager.scheduler.nextTrack();

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.ORANGE)
                .setTitle("⏭️ Track Skipped")
                .setDescription("Skipped: **" + currentTitle + "**")
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
        createOrUpdatePlayerDisplay(guild, channel);
    }

    private void handleStopCommand(Guild guild, TextChannel channel) {
        GuildMusicManager musicManager = getMusicManager(guild);
        AudioManager audioManager = guild.getAudioManager();

        musicManager.scheduler.clear();
        musicManager.player.stopTrack();
        audioManager.closeAudioConnection();
        clearAllCurrentMessages(guild);

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.RED)
                .setTitle("⏹️ Music Stopped")
                .setDescription("Stopped playback, cleared queue, and left voice channel")
                .setFooter("Try /g3play to start music again")
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
    }

    private void handleNowPlayingCommand(Guild guild, TextChannel channel) {
        GuildMusicManager musicManager = getMusicManager(guild);

        if (musicManager.player.getPlayingTrack() == null) {
            EmbedBuilder embed = new EmbedBuilder()
                    .setColor(Color.GRAY)
                    .setTitle("❌ No Music Playing")
                    .setDescription("No song is currently playing! Use `/g3play` to start music.")
                    .setTimestamp(Instant.now());

            channel.sendMessageEmbeds(embed.build()).queue();
            return;
        }

        createOrUpdatePlayerDisplay(guild, channel);
    }

    private void createOrUpdateQueueDisplayWithAutoDelete(Guild guild, TextChannel channel, int page) {
        Message existingQueueMessage = currentQueueMessages.get(guild.getIdLong());

        if (existingQueueMessage != null) {
            updateExistingQueueDisplayWithAutoDelete(guild, channel, page);
        } else {
            createNewQueueDisplayWithAutoDelete(guild, channel, page);
        }
    }

    private void updateExistingQueueDisplayWithAutoDelete(Guild guild, TextChannel channel, int page) {
        Message existingQueueMessage = currentQueueMessages.get(guild.getIdLong());

        if (existingQueueMessage == null) {
            createNewQueueDisplayWithAutoDelete(guild, channel, page);
            return;
        }

        MessageEmbed updatedQueueEmbed = createQueueEmbed(guild, page);
        List<ActionRow> updatedQueueComponents = createQueueButtons(guild, page);

        existingQueueMessage.editMessageEmbeds(updatedQueueEmbed)
                .setComponents(updatedQueueComponents)
                .queue(
                        success -> {
                            System.out.println("🔄 Queue message updated (auto-delete timer refreshed)");
                            scheduleQueueAutoDelete(guild, existingQueueMessage);
                        },
                        error -> {
                            System.out.println("⚠️ Queue message deleted - creating new one");
                            createNewQueueDisplayWithAutoDelete(guild, channel, page);
                        }
                );
    }

    private void createNewQueueDisplayWithAutoDelete(Guild guild, TextChannel channel, int page) {
        MessageEmbed queueEmbed = createQueueEmbed(guild, page);
        List<ActionRow> queueComponents = createQueueButtons(guild, page);

        channel.sendMessageEmbeds(queueEmbed)
                .setComponents(queueComponents)
                .queue(message -> {
                    currentQueueMessages.put(guild.getIdLong(), message);
                    System.out.println("📋 New queue message created with auto-delete (1 minute)");

                    scheduleQueueAutoDelete(guild, message);
                });
    }

    private void scheduleQueueAutoDelete(Guild guild, Message queueMessage) {
        scheduler.schedule(() -> {
            queueMessage.delete().queue(
                    success -> {
                        currentQueueMessages.remove(guild.getIdLong());
                        System.out.println("⏰ Queue message auto-deleted after 1 minute (anti-spam)");
                    },
                    error -> {
                        currentQueueMessages.remove(guild.getIdLong());
                        System.out.println("⏰ Queue message already deleted (cleanup tracking)");
                    }
            );
        }, 1, TimeUnit.MINUTES);
    }

    private MessageEmbed createQueueEmbed(Guild guild, int page) {
        GuildMusicManager musicManager = getMusicManager(guild);

        if (musicManager.scheduler.getQueue().isEmpty() && musicManager.player.getPlayingTrack() == null) {
            return new EmbedBuilder()
                    .setColor(Color.GRAY)
                    .setTitle("📭 Queue is Empty")
                    .setDescription("No songs in queue. Use `/g3play` to add music!")
                    .setFooter("Professional audio system ready • Auto-deletes in 1 minute")
                    .setTimestamp(Instant.now())
                    .build();
        }

        List<AudioTrack> queueList = new ArrayList<>(musicManager.scheduler.getQueue());
        AudioTrack currentTrack = musicManager.player.getPlayingTrack();

        int pageSize = 10;
        int totalPages = Math.max(1, (int) Math.ceil((double) queueList.size() / pageSize));
        page = Math.max(0, Math.min(page, totalPages - 1));
        queuePages.put(guild.getIdLong(), page);

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.BLUE)
                .setTitle("📋 Professional Queue - Page " + (page + 1) + "/" + totalPages)
                .setTimestamp(Instant.now());

        StringBuilder queueText = new StringBuilder();

        if (currentTrack != null) {
            queueText.append("**🎵 NOW PLAYING:**\n")
                    .append("**").append(currentTrack.getInfo().title).append("**\n")
                    .append("*by ").append(currentTrack.getInfo().author).append("*\n")
                    .append("`").append(formatDuration(currentTrack.getDuration())).append("` 🔊\n\n");
        }

        if (!queueList.isEmpty()) {
            queueText.append("**📅 UPCOMING TRACKS:**\n");

            int start = page * pageSize;
            int end = Math.min(start + pageSize, queueList.size());

            for (int i = start; i < end; i++) {
                AudioTrack track = queueList.get(i);
                queueText.append("`").append(String.format("%2d", i + 1)).append(".` ")
                        .append("**").append(track.getInfo().title).append("**\n")
                        .append("     *").append(track.getInfo().author).append("*\n")
                        .append("     `").append(formatDuration(track.getDuration())).append("` 🎵\n\n");
            }
        } else {
            queueText.append("*No tracks in queue*");
        }

        embed.setDescription(queueText.toString());

        embed.addField("📊 Queue Stats",
                "Total: **" + queueList.size() + "** tracks\n" +
                        "Page: **" + (page + 1) + "**/**" + totalPages + "**", true);

        if (currentTrack != null) {
            boolean isPaused = musicManager.player.isPaused();
            embed.addField("🎵 Status",
                    (isPaused ? "⏸️ Paused: " : "▶️ Playing: ") + "**" + currentTrack.getInfo().title + "**", true);
        }

        String currentBass = guildBassLevel.getOrDefault(guild.getIdLong(), "off");
        String currentPreset = guildAudioPreset.getOrDefault(guild.getIdLong(), "none");
        embed.addField("🔊 Audio", "Bass: " + currentBass.toUpperCase() + " | Preset: " + currentPreset.toUpperCase(), false);

        embed.setFooter("⏰ Auto-deletes in 1 minute • Use /g3queue for fresh display");

        return embed.build();
    }

    private List<ActionRow> createQueueButtons(Guild guild, int page) {
        GuildMusicManager musicManager = getMusicManager(guild);
        List<AudioTrack> queueList = new ArrayList<>(musicManager.scheduler.getQueue());
        int totalPages = Math.max(1, (int) Math.ceil((double) queueList.size() / 10));

        Button prevButton = page > 0 ?
                Button.primary("queue_prev", "⬅️ Previous") :
                Button.secondary("queue_prev", "⬅️ Previous").asDisabled();
        Button nextButton = page < totalPages - 1 ?
                Button.primary("queue_next", "➡️ Next") :
                Button.secondary("queue_next", "➡️ Next").asDisabled();

        ActionRow queueNav = ActionRow.of(
                prevButton,
                nextButton,
                Button.secondary("music_refresh", "🔄 Refresh"),
                Button.success("preset_clear", "🎵 Clear Filters")
        );

        List<ActionRow> components = new ArrayList<>();
        components.add(queueNav);
        return components;
    }

    private void createOrUpdatePlayerDisplay(Guild guild, TextChannel channel) {
        Message existingMessage = currentPlayerMessages.get(guild.getIdLong());

        if (existingMessage != null) {
            updateExistingPlayerDisplay(guild, channel);
        } else {
            createNewPlayerDisplay(guild, channel);
        }
    }

    private void updateExistingPlayerDisplay(Guild guild, TextChannel channel) {
        Message existingMessage = currentPlayerMessages.get(guild.getIdLong());

        if (existingMessage == null) {
            createNewPlayerDisplay(guild, channel);
            return;
        }

        GuildMusicManager musicManager = getMusicManager(guild);
        var track = musicManager.player.getPlayingTrack();

        if (track == null) {
            clearCurrentPlayerMessage(guild);
            return;
        }

        MessageEmbed updatedEmbed = createPlayerEmbed(guild, track, musicManager);
        List<ActionRow> updatedComponents = createPlayerButtons(guild);

        existingMessage.editMessageEmbeds(updatedEmbed)
                .setComponents(updatedComponents)
                .queue(
                        success -> {},
                        error -> createNewPlayerDisplay(guild, channel)
                );
    }

    private void createNewPlayerDisplay(Guild guild, TextChannel channel) {
        GuildMusicManager musicManager = getMusicManager(guild);
        var track = musicManager.player.getPlayingTrack();

        if (track == null) return;

        MessageEmbed embed = createPlayerEmbed(guild, track, musicManager);
        List<ActionRow> components = createPlayerButtons(guild);

        channel.sendMessageEmbeds(embed)
                .setComponents(components)
                .queue(message -> currentPlayerMessages.put(guild.getIdLong(), message));
    }

    private MessageEmbed createPlayerEmbed(Guild guild, AudioTrack track, GuildMusicManager musicManager) {
        long position = track.getPosition();
        long duration = track.getDuration();
        boolean isPaused = musicManager.player.isPaused();
        int volume = musicManager.player.getVolume();

        String progressBar = createProgressBar(position, duration);
        String statusIcon = isPaused ? "⏸️" : "▶️";

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(isPaused ? Color.ORANGE : Color.decode("#FF6B6B"))
                .setTitle(statusIcon + " Now Playing")
                .setDescription("**" + track.getInfo().title + "**\nby " + track.getInfo().author)
                .addField("Progress", progressBar + "\n`" + formatDuration(position) + " / " + formatDuration(duration) + "`", false)
                .addField("Volume", createVolumeBar(volume) + " " + volume + "%", false)
                .addField("Queue", String.valueOf(musicManager.scheduler.getQueue().size()) + " tracks remaining", true)
                .addField("Status", isPaused ? "⏸️ Paused" : "▶️ Playing", true);

        String currentBass = guildBassLevel.getOrDefault(guild.getIdLong(), "off");
        String currentPreset = guildAudioPreset.getOrDefault(guild.getIdLong(), "none");
        float volumeScaling = calculateVolumeScaling(volume);
        String scalingInfo = volumeScaling < 1.0f ? " (Auto-scaled " + Math.round(volumeScaling * 100) + "%)" : "";
        String audioStatus = "🔊 Bass: " + currentBass.toUpperCase() + scalingInfo + " | 🎛️ Preset: " + currentPreset.toUpperCase();
        embed.addField("🎵 Professional Audio", audioStatus, false);

        embed.setTimestamp(Instant.now());

        if (track.getInfo().uri != null && !track.getInfo().uri.isEmpty()) {
            embed.setFooter("Source: " + getSourceName(track.getInfo().uri) + " | Try /g3queue for queue");
        }

        return embed.build();
    }

    private List<ActionRow> createPlayerButtons(Guild guild) {
        GuildMusicManager musicManager = getMusicManager(guild);
        boolean isPaused = musicManager.player.isPaused();
        String currentBass = guildBassLevel.getOrDefault(guild.getIdLong(), "off");
        String currentPreset = guildAudioPreset.getOrDefault(guild.getIdLong(), "none");

        Button skipButton = Button.primary("music_skip", "⏭️ Skip");
        Button pauseButton = isPaused ?
                Button.success("music_pause", "▶️ Resume") :
                Button.secondary("music_pause", "⏸️ Pause");
        Button stopButton = Button.danger("music_stop", "⏹️ Stop");
        Button volumeDownButton = Button.secondary("music_volume_down", "🔉 Vol-");
        Button volumeUpButton = Button.secondary("music_volume_up", "🔊 Vol+");

        Button bassOffButton = currentBass.equals("off") ?
                Button.primary("bass_off", "🔇 Off") :
                Button.secondary("bass_off", "🔇 Off");
        Button bassLowButton = currentBass.equals("low") ?
                Button.primary("bass_low", "🔊 Low") :
                Button.secondary("bass_low", "🔊 Low");
        Button bassMedButton = currentBass.equals("medium") ?
                Button.primary("bass_medium", "🔊 Med") :
                Button.secondary("bass_medium", "🔊 Med");
        Button bassHighButton = currentBass.equals("high") ?
                Button.primary("bass_high", "🔊 High") :
                Button.secondary("bass_high", "🔊 High");
        Button bassExtremeButton = currentBass.equals("extreme") ?
                Button.danger("bass_extreme", "🔊 MAX") :
                Button.secondary("bass_extreme", "🔊 MAX");

        Button rockButton = currentPreset.equals("rock") ?
                Button.primary("preset_rock", "🎸 Rock") :
                Button.secondary("preset_rock", "🎸 Rock");
        Button electronicButton = currentPreset.equals("electronic") ?
                Button.primary("preset_electronic", "🎧 Electronic") :
                Button.secondary("preset_electronic", "🎧 Electronic");
        Button vocalButton = currentPreset.equals("vocal") ?
                Button.primary("preset_vocal", "🎤 Vocal") :
                Button.secondary("preset_vocal", "🎤 Vocal");
        Button clearButton = currentPreset.equals("none") ?
                Button.success("preset_clear", "🎵 Clear") :
                Button.secondary("preset_clear", "🎵 Clear");

        ActionRow controlRow = ActionRow.of(pauseButton, skipButton, stopButton,
                Button.primary("music_queue", "📋 Queue"), Button.secondary("music_refresh", "🔄"));
        ActionRow volumeRow = ActionRow.of(volumeDownButton, volumeUpButton, bassOffButton, bassLowButton, bassMedButton);
        ActionRow bassRow = ActionRow.of(bassHighButton, bassExtremeButton, rockButton, electronicButton, vocalButton);
        ActionRow presetRow = ActionRow.of(clearButton);

        List<ActionRow> components = new ArrayList<>();
        components.add(controlRow);
        components.add(volumeRow);
        components.add(bassRow);
        components.add(presetRow);

        return components;
    }

    private void clearCurrentPlayerMessage(Guild guild) {
        currentPlayerMessages.remove(guild.getIdLong());
    }

    private void clearCurrentQueueMessage(Guild guild) {
        currentQueueMessages.remove(guild.getIdLong());
    }

    private void clearAllCurrentMessages(Guild guild) {
        clearCurrentPlayerMessage(guild);
        clearCurrentQueueMessage(guild);
        queuePages.remove(guild.getIdLong());
    }

    private float calculateVolumeScaling(int volume) {
        if (volume <= 50) {
            return 1.0f;
        } else if (volume <= 75) {
            return 0.7f;
        } else if (volume <= 90) {
            return 0.5f;
        } else {
            return 0.3f;
        }
    }

    private void setBassBoostProfessional(Guild guild, String level) {
        GuildMusicManager musicManager = getMusicManager(guild);
        guildBassLevel.put(guild.getIdLong(), level);

        int currentVolume = musicManager.player.getVolume();
        float volumeScaling = calculateVolumeScaling(currentVolume);

        EqualizerFactory equalizer = new EqualizerFactory();

        float[] baseGains = new float[4];

        switch (level.toLowerCase()) {
            case "off":
                for (int i = 0; i < 15; i++) {
                    equalizer.setGain(i, 0.0f);
                }
                break;
            case "low":
                baseGains = new float[]{0.08f, 0.12f, 0.08f, 0.04f};
                break;
            case "medium":
                baseGains = new float[]{0.15f, 0.20f, 0.12f, 0.08f};
                break;
            case "high":
                baseGains = new float[]{0.25f, 0.30f, 0.20f, 0.12f};
                break;
            case "extreme":
                baseGains = new float[]{0.35f, 0.40f, 0.28f, 0.16f};
                break;
        }

        if (!level.equals("off")) {
            setBassEqualizerProfessional(equalizer, baseGains, volumeScaling);
        }

        musicManager.player.setFilterFactory(equalizer);
    }

    private void setBassEqualizerProfessional(EqualizerFactory equalizer, float[] baseGains, float volumeScaling) {
        for (int i = 0; i < 15; i++) {
            equalizer.setGain(i, 0.0f);
        }

        equalizer.setGain(0, baseGains[0] * volumeScaling);
        equalizer.setGain(1, baseGains[1] * volumeScaling);
        equalizer.setGain(2, baseGains[2] * volumeScaling);
        equalizer.setGain(3, baseGains[3] * volumeScaling);
    }

    private void setAudioPresetProfessional(Guild guild, String preset) {
        GuildMusicManager musicManager = getMusicManager(guild);
        guildAudioPreset.put(guild.getIdLong(), preset);

        int currentVolume = musicManager.player.getVolume();
        float volumeScaling = calculateVolumeScaling(currentVolume);

        EqualizerFactory equalizer = new EqualizerFactory();

        for (int i = 0; i < 15; i++) {
            equalizer.setGain(i, 0.0f);
        }

        switch (preset.toLowerCase()) {
            case "rock":
                equalizer.setGain(0, 0.08f * volumeScaling);
                equalizer.setGain(1, 0.08f * volumeScaling);
                equalizer.setGain(6, 0.12f * volumeScaling);
                equalizer.setGain(7, 0.12f * volumeScaling);
                equalizer.setGain(12, 0.15f * volumeScaling);
                equalizer.setGain(13, 0.12f * volumeScaling);
                break;
            case "electronic":
                equalizer.setGain(0, 0.15f * volumeScaling);
                equalizer.setGain(1, 0.20f * volumeScaling);
                equalizer.setGain(2, 0.12f * volumeScaling);
                equalizer.setGain(11, 0.08f * volumeScaling);
                equalizer.setGain(12, 0.12f * volumeScaling);
                break;
            case "vocal":
                equalizer.setGain(5, 0.12f * volumeScaling);
                equalizer.setGain(6, 0.15f * volumeScaling);
                equalizer.setGain(7, 0.20f * volumeScaling);
                equalizer.setGain(8, 0.15f * volumeScaling);
                equalizer.setGain(9, 0.12f * volumeScaling);
                break;
        }

        musicManager.player.setFilterFactory(equalizer);
    }

    private void clearAudioFiltersProfessional(Guild guild) {
        GuildMusicManager musicManager = getMusicManager(guild);
        guildBassLevel.put(guild.getIdLong(), "off");
        guildAudioPreset.put(guild.getIdLong(), "none");

        EqualizerFactory equalizer = new EqualizerFactory();
        for (int i = 0; i < 15; i++) {
            equalizer.setGain(i, 0.0f);
        }

        musicManager.player.setFilterFactory(equalizer);
    }

    private void reapplyCurrentAudioFilters(Guild guild) {
        String currentBass = guildBassLevel.getOrDefault(guild.getIdLong(), "off");
        String currentPreset = guildAudioPreset.getOrDefault(guild.getIdLong(), "none");

        if (!currentBass.equals("off")) {
            setBassBoostProfessional(guild, currentBass);
        } else if (!currentPreset.equals("none")) {
            setAudioPresetProfessional(guild, currentPreset);
        }
    }

    private void handleBassCommand(Guild guild, TextChannel channel, String level) {
        if (!level.matches("off|low|medium|high|extreme")) {
            channel.sendMessage("❌ Invalid bass level! Use: `off`, `low`, `medium`, `high`, or `extreme`\n💡 Try `/g3bass` for modern slash command").queue();
            return;
        }

        setBassBoostProfessional(guild, level);

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.decode("#FF6B6B"))
                .setTitle("🔊 Professional Bass Boost")
                .setDescription("Bass boost set to: **" + level.toUpperCase() + "**")
                .addField("💡 Tip", "Try `/g3bass` for modern slash commands!", false)
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
        updateExistingPlayerDisplay(guild, channel);
    }

    private void handlePresetCommand(Guild guild, TextChannel channel, String preset) {
        if (!preset.matches("rock|electronic|vocal|clear")) {
            channel.sendMessage("❌ Invalid preset! Use: `rock`, `electronic`, `vocal`, or `clear`\n💡 Try `/g3preset` for modern slash command").queue();
            return;
        }

        if (preset.equals("clear")) {
            clearAudioFiltersProfessional(guild);
        } else {
            setAudioPresetProfessional(guild, preset);
        }

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.decode("#7289DA"))
                .setTitle("🎛️ Audio Preset Applied")
                .setDescription("Audio preset set to: **" + preset.toUpperCase() + "**")
                .addField("💡 Tip", "Try `/g3preset` for modern slash commands!", false)
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
        updateExistingPlayerDisplay(guild, channel);
    }

    private void handleVolumeCommand(Guild guild, TextChannel channel, int volume) {
        if (volume < 0 || volume > 100) {
            channel.sendMessage("❌ Volume must be between 0 and 100!").queue();
            return;
        }

        GuildMusicManager musicManager = getMusicManager(guild);
        musicManager.player.setVolume(volume);
        reapplyCurrentAudioFilters(guild);

        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.CYAN)
                .setTitle("🔊 Volume Changed")
                .setDescription("Volume set to **" + volume + "%**")
                .addField("🎛️ Smart Audio", "Bass auto-adjusted for optimal quality", false)
                .addField("💡 Tip", "Try `/g3volume` for modern slash commands!", false)
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
        updateExistingPlayerDisplay(guild, channel);
    }

    private void handleHelpCommand(TextChannel channel) {
        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.decode("#7289DA"))
                .setTitle("🎵 Professional Music Bot - Modern Commands")
                .setDescription("Studio-grade audio with modern slash commands and zero spam!")
                .addField("🎶 Modern Slash Commands", "`/g3play <song>` - Professional audio playback\n`/g3volume <0-100>` - Smart volume control\n`/g3bass <level>` - Professional bass boost\n`/g3preset <preset>` - Studio audio presets", false)
                .addField("📋 Queue Management", "`/g3queue [page]` - Auto-delete queue (1 min)\n`/g3skip` - Skip current track\n`/g3stop` - Complete stop & disconnect", false)
                .addField("🔧 Legacy Commands", "Old `!` commands still work:\n`!play`, `!volume`, `!bass`, `!preset`, `!queue`", false)
                .addField("🚫 Anti-Spam Features", "• **Player updates in-place**\n• **Queue auto-deletes (1 min)**\n• **Professional UX**\n• **Zero message clutter**", false)
                .addField("🔊 Professional Audio", "• **55% comfortable default volume**\n• **Volume-aware bass boost**\n• **Studio-grade processing**\n• **No distortion guarantee**", false)
                .setFooter("✨ Modern slash commands + Complete anti-spam system")
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
    }

    private void handleSourcesCommand(TextChannel channel) {
        EmbedBuilder embed = new EmbedBuilder()
                .setColor(Color.decode("#FF9500"))
                .setTitle("🔍 Professional Audio Sources")
                .addField("🎧 SoundCloud (Recommended)", "Use `/g3play song name` for automatic SoundCloud search\nStudio quality + professional processing", false)
                .addField("🎵 Spotify", "Use `/g3play https://open.spotify.com/...`\nSupports 300+ track playlists with compact loading", false)
                .addField("📺 YouTube", "Limited availability due to bot restrictions", false)
                .addField("📁 Direct Audio", "FLAC, MP3, OGG, M4A files\nLossless quality support", false)
                .addField("💡 Modern Commands", "Try `/g3play` instead of `!play` for the best experience!", false)
                .setFooter("Default: SoundCloud (studio-grade) + Anti-spam system")
                .setTimestamp(Instant.now());

        channel.sendMessageEmbeds(embed.build()).queue();
    }

    private GuildMusicManager getMusicManager(Guild guild) {
        return musicManagers.computeIfAbsent(guild.getIdLong(), (guildId) -> {
            GuildMusicManager musicManager = new GuildMusicManager(playerManager.getAudioPlayerManager());
            guild.getAudioManager().setSendingHandler(musicManager.getSendHandler());

            musicManager.player.setVolume(55);
            System.out.println("🔊 Guild setup with comfortable 55% default volume: " + guild.getName());

            return musicManager;
        });
    }

    private boolean isUrl(String input) {
        return input.startsWith("http://") || input.startsWith("https://") || input.startsWith("www.");
    }

    private boolean hasSearchPrefix(String query) {
        return query.startsWith("ytsearch:") || query.startsWith("ytmsearch:") ||
                query.startsWith("scsearch:") || query.startsWith("spsearch:") || query.startsWith("amsearch:");
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

    private String createProgressBar(long position, long duration) {
        if (duration == 0) return "▬▬▬▬▬▬▬▬▬▬▬▬";

        int totalBars = 12;
        double progress = (double) position / duration;
        int filledBars = (int) (progress * totalBars);

        StringBuilder bar = new StringBuilder();
        for (int i = 0; i < totalBars; i++) {
            if (i == filledBars) {
                bar.append("🔘");
            } else if (i < filledBars) {
                bar.append("▬");
            } else {
                bar.append("▬");
            }
        }
        return bar.toString();
    }

    private String createVolumeBar(int volume) {
        int bars = volume / 10;
        StringBuilder volumeBar = new StringBuilder();

        for (int i = 0; i < 10; i++) {
            if (i < bars) {
                volumeBar.append("🟩");
            } else {
                volumeBar.append("⬜");
            }
        }
        return volumeBar.toString();
    }

    private String getSourceName(String uri) {
        if (uri.contains("youtube.com") || uri.contains("youtu.be")) return "YouTube";
        if (uri.contains("soundcloud.com")) return "SoundCloud";
        if (uri.contains("spotify.com")) return "Spotify";
        if (uri.contains("bandcamp.com")) return "Bandcamp";
        return "Direct URL";
    }
}