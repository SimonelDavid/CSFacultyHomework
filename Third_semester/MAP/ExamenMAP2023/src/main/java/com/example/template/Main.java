package com.example.template;

import com.example.template.entities.Client;
import com.example.template.repo.*;
import com.example.template.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Service service = new Service(new LocationRepo("jdbc:postgresql://localhost:5432/exam",
                "postgres",
                "postgres"),
                                    new HotelRepo("jdbc:postgresql://localhost:5432/exam",
                                            "postgres",
                                            "postgres"),
                new SpecialOffersRepo("jdbc:postgresql://localhost:5432/exam",
                        "postgres",
                        "postgres"),
                new ClientRepo("jdbc:postgresql://localhost:5432/exam",
                        "postgres",
                        "postgres"),
                new ReservationRepo("jdbc:postgresql://localhost:5432/exam",
                        "postgres",
                        "postgres")
        );


        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 500);
        stage.setTitle("Locatii");
        stage.setScene(scene);
        ((MainController)fxmlLoader.getController()).init(service);
        stage.show();

        for(Client client: service.getClients()){
            FXMLLoader fxmlLoaderC = new FXMLLoader(Main.class.getResource("client-view.fxml"));
            Scene sceneC = new Scene(fxmlLoaderC.load(), 320, 240);
            Stage stageC = new Stage();
            stageC.setTitle("Client");
            stageC.setScene(sceneC);
            ((ClientController)fxmlLoaderC.getController()).init(service, client);
            service.addController(fxmlLoaderC.getController());
            stageC.show();

        }


    }

    public static void main(String[] args) {
        launch();
    }
}