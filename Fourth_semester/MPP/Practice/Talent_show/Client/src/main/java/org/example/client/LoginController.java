package org.example.client;

import org.example.domain.Jurry;
import org.example.service.IObserver;
import org.example.service.IService;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController {
    IService server;
    @FXML
    PasswordField passwordField;
    @FXML
    Label loginLabel;
    @FXML
    Label emailLabel;
    @FXML
    Label passwordLabel;
    @FXML
    Button loginButton;
    @FXML
    TextField emailTextField;

    public void setServer(IService server){
        this.server = server;
    }

    @FXML
    protected void loginButtonClicked() {
        String nume = emailTextField.getText();
        String password = passwordField.getText();
        Jurry user = null;
        Stage stage = null;
        try {
            var sc = openMain(null);
            stage = sc.stage;
            MainController controller = sc.controller;
            user = server.getByMailPassword(nume, password, controller);
            controller.setUser(user);
            stage.setTitle(user.getNume());
            if(user != null){
                stage.show();
                emailTextField.clear();
                passwordField.clear();
            }
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Login failed!");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    class StageController {
        public Stage stage;
        public MainController controller;

        public StageController(Stage stage, MainController controller) {
            this.stage = stage;
            this.controller = controller;
        }
    }

    protected StageController openMain(Jurry user){
        Stage stage = new Stage();
        Scene scene;
        FXMLLoader loader = new FXMLLoader(StartClient.class.getResource("main-view.fxml"));
        try {
            scene = new Scene(loader.load(), 860, 500);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        MainController ctrl = loader.getController();
        ctrl.setServer(server);
        ctrl.setUser(user);
        ctrl.initialization();

        stage.setScene(scene);
        return new StageController(stage, ctrl);
    }
}