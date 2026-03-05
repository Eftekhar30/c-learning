package com.example.musicbot;

import net.dv8tion.jda.api.JDABuilder;
import net.dv8tion.jda.api.entities.Activity;
import net.dv8tion.jda.api.requests.GatewayIntent;
import net.dv8tion.jda.api.utils.cache.CacheFlag;
import net.dv8tion.jda.api.interactions.commands.OptionType;
import net.dv8tion.jda.api.interactions.commands.build.Commands;
import net.dv8tion.jda.api.hooks.ListenerAdapter;

public class Main {
    public static void main(String[] args) {
        String token = "MTQwMTIwOTcwOTM2MDQ1MTU4NA.Gh0hHH.PJwBR6G0Zb_vQWaDFYzdhy7sG1AwdDn9uvs-j4";

        try {
            JDABuilder builder = JDABuilder.createDefault(token)
                    .setActivity(Activity.listening("/g3play • Professional Audio"))
                    .enableIntents(GatewayIntent.MESSAGE_CONTENT,
                            GatewayIntent.GUILD_VOICE_STATES,
                            GatewayIntent.GUILD_MEMBERS
                    )
                    .disableCache(CacheFlag.MEMBER_OVERRIDES)
                    .addEventListeners(new CommandListener());

            var jda = builder.build();

            jda.awaitReady();

            System.out.println("🔧 Registering professional slash commands...");

            jda.updateCommands().addCommands(
                    Commands.slash("g3play", "Play music with professional audio processing")
                            .addOption(OptionType.STRING, "query", "Song name, URL, or Spotify link", true),

                    Commands.slash("g3volume", "Set volume with professional audio scaling")
                            .addOption(OptionType.INTEGER, "level", "Volume level (0-100)", true),

                    Commands.slash("g3bass", "Professional bass boost control")
                            .addOption(OptionType.STRING, "level", "Bass level (off/low/medium/high/extreme)", true),

                    Commands.slash("g3preset", "Professional audio presets")
                            .addOption(OptionType.STRING, "preset", "Audio preset (rock/electronic/vocal/clear)", true),

                    Commands.slash("g3queue", "View queue with anti-spam scrolling")
                            .addOption(OptionType.INTEGER, "page", "Page number (optional)", false),

                    Commands.slash("g3skip", "Skip current track"),

                    Commands.slash("g3stop", "Stop music and disconnect from voice"),

                    Commands.slash("g3help", "Show all professional bot commands")

            ).queue(
                    success -> {
                        System.out.println("✅ Professional slash commands registered successfully!");
                        System.out.println("🎵 /g3play - Main music command");
                        System.out.println("🔊 /g3volume - Professional volume control");
                        System.out.println("🎛️ /g3bass - Studio-grade bass boost");
                        System.out.println("🎵 /g3preset - Audio presets");
                        System.out.println("📋 /g3queue - Anti-spam queue browsing");
                        System.out.println("⏭️ /g3skip - Skip track");
                        System.out.println("⏹️ /g3stop - Complete stop & disconnect");
                        System.out.println("❓ /g3help - Command help");
                    },
                    error -> {
                        System.err.println("❌ Failed to register slash commands: " + error.getMessage());
                    }
            );

            System.out.println("🎵 Professional Discord Music Bot V2 starting...");
            System.out.println("✅ High-quality audio processing enabled");
            System.out.println("✅ Anti-spam system active");
            System.out.println("✅ Bass boost and professional filters ready");
            System.out.println("✅ Large playlist support (300+ tracks)");
            System.out.println("✅ Slash commands enabled");
            System.out.println("✅ Auto-delete queue messages (1 min)");
            System.out.println("✅ Medium volume default for comfort");

        } catch (Exception e) {
            System.err.println("Failed to start professional bot: " + e.getMessage());
            e.printStackTrace();
        }
    }
}