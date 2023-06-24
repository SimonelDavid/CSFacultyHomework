package org.example;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.example.rpc.ServicesRpcProxy;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

public class StartFX extends Application {
    private static int defaultChatPort = 55555;
    private static String defaultServer = "localhost";

    @Override
    public void start(Stage stage) throws IOException {
        Properties props = new Properties();

        try {
            props.load(StartFX.class.getResourceAsStream("/chatclient.properties"));
            System.out.println("Client properties set. ");
            props.list(System.out);
        } catch (IOException var13) {
            System.err.println("Cannot find chatclient.properties " + var13);
            return;
        }

        String serverIP = props.getProperty("chat.server.host", defaultServer);
        int serverPort = defaultChatPort;

        try {
            serverPort = Integer.parseInt(props.getProperty("chat.server.port"));
        } catch (NumberFormatException var12) {
            System.err.println("Wrong port number " + var12.getMessage());
            System.out.println("Using default port: " + defaultChatPort);
        }

        IServices server = new ServicesRpcProxy(serverIP, serverPort);

        FXMLLoader loader = new FXMLLoader(this.getClass().getClassLoader().getResource("login-view.fxml"));
        Parent root = (Parent)loader.load();
        LoginController ctrl = (LoginController)loader.getController();
        ctrl.setServer(server);

        FXMLLoader cloader = new FXMLLoader(this.getClass().getClassLoader().getResource("angajat-view.fxml"));
        Parent croot = (Parent)cloader.load();
        AngajatController angajatController = (AngajatController) cloader.getController();
        angajatController.setServer(server);
        ctrl.setAngajatController(angajatController);
        ctrl.setParent(croot);
        stage.setTitle("MPP");
        stage.setScene(new Scene(root));
        stage.show();

        /*
        FXMLLoader fxmlLoader = new FXMLLoader(StartFX.class.getResource("login-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Login");
        stage.setScene(scene);
        AngajatDBRepository angajatDBRepository = new AngajatDBRepository(props);
        AngajatService angajatService = new AngajatService(angajatDBRepository);
        ZborDBRepository zborDBRepository = new ZborDBRepository(props);
        ZborService zborService = new ZborService(zborDBRepository);
        BiletDBRepository biletDBRepository = new BiletDBRepository(props);
        BiletService biletService = new BiletService(biletDBRepository);
        */

        //LoginController loginController = fxmlLoader.getController();
        //loginController.setServer(angajatService, zborService, biletService);
        //stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}