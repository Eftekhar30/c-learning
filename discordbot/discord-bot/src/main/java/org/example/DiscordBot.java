package org.example;

import net.dv8tion.jda.api.JDA;
import net.dv8tion.jda.api.JDABuilder;
import org.example.config.botConfig;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class DiscordBot {
    private static final Logger logger = LoggerFactory.getLogger(DiscordBot.class);
    private static JDA jda;
    public static void main(String[] args){
        String botToken = botConfig.getBotToken();
        if(botToken == null){
            logger.error("bot token not found in config.properties. please provide a valid");
            return;
        }
        try{
            jda = JDABuilder.createDefault(botToken);
        } catch (Exception e){
            logger.error("Error starting the bot.");
        }



    }
}
