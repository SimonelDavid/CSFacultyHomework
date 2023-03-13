package com.example.zboruri.Controller;

import com.example.zboruri.Entities.Client;
import com.example.zboruri.HelloApplication;
import com.example.zboruri.Service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.Objects;

public class LoginController {
    @FXML
    private TextField usernameField;
    @FXML
    private Button loginButton;

    private Service service;


    public void setLoginService(Service service)
    {
        this.service=service;
    }


    @FXML
    public void initialize()
    {

    }

    public void handleLoginButton(ActionEvent actionEvent) throws IOException
    {
        List<Client> clients=service.getClients();
        boolean exists=false;
        String username=usernameField.getText();
        for(Client c:clients)
            if(c.getUsername().equals(username))
            {
                exists=true;
                FXMLLoader fxmlLoader=new FXMLLoader(HelloApplication.class.getResource("views/FlightsView.fxml"));
                Scene scene=new Scene(fxmlLoader.load(),800,600);
                Stage stage=new Stage();
                stage.setTitle(c.getName());
                stage.setScene(scene);
                stage.show();
                FlightsController flightController=fxmlLoader.getController();
                flightController.setFlightsService(service,c.getUsername());
                //((Node)(actionEvent.getSource())).getScene().getWindow().hide();
            }
        if(!exists)
        {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Eroare");
            alert.setContentText("Username-ul introdus nu exista!");
            alert.show();
        }
    }
}
