package org.example;

import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.IOException;

public class LoginController {
    private IServices server;
    private AngajatController angajatController;
    private Angajat user;

    Parent mainChatParent;

    @FXML
    TextField loginNume;
    @FXML
    PasswordField loginParola;
    @FXML
    Label loginError;

    @FXML
    protected void onConnectButtonClick() {
        String name = loginNume.getText();
        String password = loginParola.getText();

        this.user = new Angajat(0, name, password);

        try {
            this.server.login(this.user, this.angajatController);
            Stage stage = new Stage();
            stage.setTitle("Window for " + this.user.getId());
            stage.setScene(new Scene(this.mainChatParent));
            stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
                public void handle(WindowEvent event) {
                    LoginController.this.angajatController.logout();
                    System.exit(0);
                }
            });
            stage.show();
            this.angajatController.setUser(this.user);
            //this.angajatController.setLoggedFriends();
            loginNume.getScene().getWindow().hide();
            //((Node)actionEvent.getSource()).getScene().getWindow().hide();
        } catch (AgentieException var6) {
            loginError.setText(var6.getMessage());
            loginError.setVisible(true);
        }

    }

    public void setServer(IServices server) {
        this.server = server;
    }

    public void setUser(Angajat user) {
        this.user = user;
    }

    public void setAngajatController(AngajatController angajatController) {
        this.angajatController = angajatController;
    }

    public void setParent(Parent p) {
        this.mainChatParent = p;
    }
}