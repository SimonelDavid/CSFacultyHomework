package com.example.template;

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
        Service service = new Service(new ClientRepo("jdbc:postgresql://localhost:5432/zboruri",
                "postgres",
                "postgres"),
                                    new HotelRepo("jdbc:postgresql://localhost:5432/zboruri",
                                            "postgres",
                                            "postgres"),
                new SpecialOffersRepo("jdbc:postgresql://localhost:5432/zboruri",
                        "postgres",
                        "postgres"),
                new ReservationRepo("jdbc:postgresql://localhost:5432/zboruri",
                        "postgres",
                        "postgres")
        );


        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("main-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 400, 100);
        stage.setTitle("Login Page");
        stage.setScene(scene);
        ((MainController)fxmlLoader.getController()).init(service);
        stage.show();


    }

    public static void main(String[] args) {
        launch();
    }
}