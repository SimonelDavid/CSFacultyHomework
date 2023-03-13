package com.example.template;

import com.example.template.repo.LocationRepo;
import com.example.template.repo.HotelRepo;
import com.example.template.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Service service = new Service(new LocationRepo("jdbc:postgresql://localhost:5432/examen",
                "postgres",
                "postgres"),
                new HotelRepo("jdbc:postgresql://localhost:5432/examen",
                        "postgres",
                        "postgres"));

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 500, 240);
        stage.setTitle("Locatii");
        stage.setScene(scene);
        ((LocationController)fxmlLoader.getController()).init(service);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}