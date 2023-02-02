package com.example.template;

import com.example.template.repo.BedsRepo;
import com.example.template.repo.PatientsRepo;
import com.example.template.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Service service = new Service(new BedsRepo("postgres", "adenozintrifosfat", "jdbc:postgresql://localhost:5432/upu"),
                new PatientsRepo("jdbc:postgresql://localhost:5432/upu", "postgres", "adenozintrifosfat"));

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 500, 400);
        stage.setTitle("Paturi");
        stage.setScene(scene);
        ((BedsController) fxmlLoader.getController()).init(service);
        stage.show();

        service.setBedsController(((BedsController) fxmlLoader.getController()));

        FXMLLoader fxmlLoaderP = new FXMLLoader(HelloApplication.class.getResource("patients-view.fxml"));
        Scene sceneP = new Scene(fxmlLoaderP.load(), 500, 700);
        Stage stagep = new Stage();
        stagep.setTitle("Pacienți");
        stagep.setScene(sceneP);
        ((PatientsController) fxmlLoaderP.getController()).init(service);
        stagep.show();


    }

    public static void main(String[] args) {
        launch();
    }
}