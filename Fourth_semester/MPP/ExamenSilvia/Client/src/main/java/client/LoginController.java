package client;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import model.User;
import services.IServices;
import services.ServicesException;

public class LoginController {
    private IServices server;
    private MainController mainController;
    private Parent mainParent;

    @FXML
    TextField textFieldUsername;
    @FXML
    PasswordField textFieldPassword;

    public LoginController(){
        //thos constructor is used by form
    }

    public void setServer(IServices server){
        this.server = server;
    }

    public void setMainController(MainController mainController) {
        this.mainController = mainController;
    }

    public void setMainParent(Parent mainParent) {
        this.mainParent = mainParent;
    }

    @FXML
    public void initialize(){
    }

    @FXML
    public void handleLogin(ActionEvent actionEvent){
        String username = textFieldUsername.getText();
        String password = textFieldPassword.getText();
        User user = new User(username, password);
        try{
            User loggedUser = server.login(user, mainController);
            mainController.setServer(server, loggedUser);
            Stage stage = new Stage();
            stage.setScene(new Scene(mainParent));

            stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
                @Override
                public void handle(WindowEvent event) {
                    try {
                        server.logout(user, mainController);
                    } catch (ServicesException e) {
                        e.printStackTrace();
                    }
                    System.exit(0);
                }
            });

            stage.show();


            ((Node)(actionEvent.getSource())).getScene().getWindow().hide();

        } catch (ServicesException e) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Exam");
            alert.setHeaderText("Authentication failure");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }
}
