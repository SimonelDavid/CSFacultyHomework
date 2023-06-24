package org.example.server;

import org.example.networking.utils.AbstractServer;
import org.example.networking.utils.RpcConcurrentServer;
import org.example.repo.*;
import org.example.service.IService;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalDate;
import java.util.Properties;

public class StartServer {
    private static int defaultPort=55555;
    public static void main(String[] args) {
        Properties serverProps=loadProperties();
        serverProps.list(System.out);
        IUserRepository userRepo = new UserRepository(serverProps);
        IGameRepository gameRepo = new GameRepository();
        IConfigRepository configRepo = new ConfigRepository(serverProps);
        IWordRepository wordRepo = new WordRepository(serverProps);
        IService srv = new Service(userRepo, gameRepo, configRepo, wordRepo);

        int serverPort=defaultPort;
        try {
            serverPort = Integer.parseInt(serverProps.getProperty("server.port"));
        }catch (NumberFormatException nef){
            System.err.println("Wrong  Port Number"+nef.getMessage());
            System.err.println("Using default port "+defaultPort);
        }
        System.out.println("Starting server on port: " + serverPort);
        AbstractServer server = new RpcConcurrentServer(serverPort, srv);
        try {
            server.start();
        } catch (Exception e) {
            System.err.println("Error starting the server" + e.getMessage());
        }finally {
            try {
                server.stop();
            }catch(Exception e){
                System.err.println("Error stopping server "+e.getMessage());
            }
        }
        HibernateUtils.close();
    }

    public static Properties loadProperties() {
        Properties props=new Properties();
        try {
            props.load(new FileReader("server.properties"));
        } catch (IOException e) {
            System.out.println("Cannot find server.properties "+e);
        }
        return props;
    }
}
