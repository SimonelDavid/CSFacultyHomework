package fx.controller;

import domain.Jurry;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import examen.service.IService;
import examen.service.MyException;

public class LoginController {
    @FXML
    TextField usernameField;
    @FXML
    Button loginButton;
    @FXML
    Label controlLabel;
    private IService service;
    private ServiceController serviceController;
    private Parent mainParent;
    private final Stage employeeStage = new Stage();

    @FXML
    public void setService(IService service) {
        this.service = service;
    }
    public void setServiceController(ServiceController serviceController) {
        this.serviceController = serviceController;
    }

    public void setParent(Parent parent) {
        this.mainParent = parent;
    }

    @FXML
    private void loginAction(ActionEvent actionEvent) {
        if (usernameField.getText().length() > 0) {
            try {
                Jurry trying = new Jurry(0,usernameField.getText());
                Jurry jurry = service.login(trying, serviceController);
                if (jurry != null) {
                    employeeStage.setOnCloseRequest(event -> {
                        serviceController.logout();
                    });
                    employeeStage.setTitle("Game: " + jurry);
                    if (employeeStage.getScene()==null)
                        employeeStage.setScene(new Scene(mainParent, 1200, 800));
                    employeeStage.show();
                    serviceController.setEmployee(jurry);
                    serviceController.setStage((Stage) usernameField.getScene().getWindow());
                    serviceController.initialization();
                    controlLabel.setText("");
                    Stage stage = (Stage) ((Node)(actionEvent.getSource())).getScene().getWindow();
                    stage.close();
                }
                else
                    controlLabel.setText("Error: no such jurry!");
            } catch (IllegalArgumentException | MyException e) {
                controlLabel.setText("Error: " + e.getMessage());
            }
            usernameField.clear();
        } else
            controlLabel.setText("The fields for alias is empty!");
    }
}
