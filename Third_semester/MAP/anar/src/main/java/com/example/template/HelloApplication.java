package com.example.template;

import com.example.template.repo.RiverRepo;
import com.example.template.repo.TownRepo;
import com.example.template.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class xHelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Service service = new Service(new RiverRepo("jdbc:postgresql://localhost:5432/anar",
                "postgres",
                "postgres"),
                new TownRepo("jdbc:postgresql://localhost:5432/anar",
                        "postgres",
                        "postgres"));

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 500, 240);
        stage.setTitle("Râuri");
        stage.setScene(scene);
        ((RiverController)fxmlLoader.getController()).init(service);
        stage.show();



        FXMLLoader fxmlLoaderT = new FXMLLoader(HelloApplication.class.getResource("towns-view.fxml"));
        Scene sceneT = new Scene(fxmlLoaderT.load(), 800, 240);
        Stage stageT = new Stage();
        stageT.setTitle("Orașe");
        stageT.setScene(sceneT);
        ((TownsController)fxmlLoaderT.getController()).init(service);
        stageT.show();
        service.setController(fxmlLoaderT.getController());
    }

    public static void main(String[] args) {
        launch();
    }
}