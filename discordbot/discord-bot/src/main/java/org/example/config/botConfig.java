package org.example.config;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class botConfig {
    private static final Logger logger = LoggerFactory.getLogger(botConfig.class);
    private static final String CONFIG_FILE = "config.properties";
    private static final Properties properties = new Properties();

    static{
        try(InputStream input = botConfig.class.getClassLoader().getResourceAsStream(CONFIG_FILE)) {
            if(input == null){
                logger.error("Config file not found!", CONFIG_FILE);
            } else{
                properties.load(input);
                logger.info("config loaded from {}", CONFIG_FILE);
            }
        } catch (IOException e) {
            logger.error("Error loading config file: ", e);
        } ;
    }

    public static String getBotToken(){
        return properties.getProperty("botToken");
    }
}
