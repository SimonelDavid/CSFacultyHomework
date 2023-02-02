package com.example.template;

import com.example.template.entities.Table;
import com.example.template.repo.MenuItemRepo;
import com.example.template.repo.OrderRepo;
import com.example.template.repo.TableRepo;
import com.example.template.services.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        Service service = new Service(
          new TableRepo("jdbc:postgresql://localhost:5432/postgres", "postgres", "adenozintrifosfat"),
          new MenuItemRepo("jdbc:postgresql://localhost:5432/postgres", "postgres", "adenozintrifosfat"),
                new OrderRepo()
        );

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("angajati-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400);
        stage.setTitle("Staff");
        stage.setScene(scene);
        ((AngajatiController) fxmlLoader.getController()).setService(service);
        ((AngajatiController) fxmlLoader.getController()).init();
        stage.show();

        List<Table> tables = service.getTables();

        service.setObserver(((AngajatiController) fxmlLoader.getController()));

        for(Table table: tables){
            FXMLLoader fxmlLoaderT = new FXMLLoader();
            fxmlLoaderT.setLocation(HelloApplication.class.getResource("table-view.fxml"));

            Scene sceneT = new Scene(fxmlLoaderT.load(), 600, 400);
            Stage stageT = new Stage();
            stageT.setTitle("Masa " + table.getId().toString());
            stageT.setScene(sceneT);
            ((TableController) fxmlLoaderT.getController()).setTable(table);
            ((TableController) fxmlLoaderT.getController()).setService(service);
            ((TableController) fxmlLoaderT.getController()).init();

            stageT.show();
        }

    }

    public static void main(String[] args) {
        launch();
    }
}