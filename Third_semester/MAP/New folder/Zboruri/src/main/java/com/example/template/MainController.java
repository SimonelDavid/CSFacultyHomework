package com.example.template;

import com.example.template.entities.Client;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.stage.Window;

import java.io.IOException;
import java.sql.SQLException;

public class MainController {

    private Service service;
    private ObservableList<String> clientsList;

    @FXML
    private TextField clients;

    @FXML
    private Button submitButton;

    public void init(Service service){
        clientsList = FXCollections.observableArrayList();
        this.service = service;

        for(Client client : service.getClients()){
            clientsList.add(client.getName());
        }



    }

    public void login(ActionEvent event) throws SQLException, IOException {

        Window owner = submitButton.getScene().getWindow();

        System.out.println(clients.getText());

        if (clients.getText().isEmpty()) {
            showAlert(Alert.AlertType.ERROR, owner, "Form Error!",
                    "Please enter your username");
            return;
        }

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("offer-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 400, 600);
        Stage stage = new Stage();
        stage.setTitle("Nume utilizator");
        stage.setScene(scene);
        ((OfferController)fxmlLoader.getController()).init(service, clients.getText());
        stage.show();
    }

    private static void showAlert(Alert.AlertType alertType, Window owner, String title, String message) {
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.initOwner(owner);
        alert.show();
    }

//    public void selected(ActionEvent event) {
//
//    }

//    public void selectedHotel(MouseEvent mouseEvent) throws IOException {
//        if(hotels.getSelectionModel().getSelectedItem() == null)
//            return;
//        String hotelName = hotels.getSelectionModel().getSelectedItem().toString().split(":")[0];
//        Double hotelId = service.getHid(hotelName);
//
//        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("offer-view.fxml"));
//        Scene scene = new Scene(fxmlLoader.load(), 400, 600);
//        Stage stage = new Stage();
//        stage.setTitle("Oferte");
//        stage.setScene(scene);
//        ((OfferController)fxmlLoader.getController()).init(service, hotelId);
//        stage.show();
//
//    }

}