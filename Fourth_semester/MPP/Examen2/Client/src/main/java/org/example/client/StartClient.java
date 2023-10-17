package org.example.client;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.example.networking.rpcprotocol.ServiceProxy;
import org.example.service.IService;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class StartClient extends Application {
    private Stage primaryStage;
    private static int defaultChatPort = 55555;
    private static String defaultServer = "localhost";

    public void start(Stage primaryStage) throws Exception {
        System.out.println("In start");
        Properties clientProps = loadProperties();
        clientProps.list(System.out);

        String serverIP = clientProps.getProperty("server.host", defaultServer);
        int serverPort = defaultChatPort;

        System.out.println(clientProps.getProperty("server.port"));

        try {
            serverPort = Integer.parseInt(clientProps.getProperty("server.port"));
        } catch (NumberFormatException ex) {
            System.err.println("Wrong port number " + ex.getMessage());
            System.out.println("Using default port: " + defaultChatPort);
        }
        System.out.println("Using server IP " + serverIP);
        System.out.println("Using server port " + serverPort);

        IService server = new ServiceProxy(serverIP, serverPort);

        Scene scene;
        FXMLLoader loader = new FXMLLoader(StartClient.class.getResource("login-view.fxml"));
        try {
            scene = new Scene(loader.load(), 300, 300);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        LoginController ctrl = loader.getController();
        ctrl.setServer(server);

        primaryStage.setTitle("Login");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static Properties loadProperties() {
        Properties props=new Properties();
        try {
            props.load(new FileReader("client.properties"));
        } catch (IOException e) {
            System.out.println("Cannot find client.properties "+e);
        }
        return props;
    }
}
