package org.example;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import org.example.utils.UtilsGUI;

import java.io.IOException;
import java.net.URL;
import java.util.Collection;
import java.util.List;
import java.util.ResourceBundle;

public class AngajatController implements IObserver {
    private IServices server;
    private Angajat user;

    private final ObservableList<Zbor> friendsModel = FXCollections.observableArrayList();

    @FXML
    TableView<Zbor> tableZbor;
    @FXML
    TableView<Zbor> _tableZbor;
    @FXML
    TextField _destinatie;
    @FXML
    TextField _client;
    @FXML
    TextField _turisti;
    @FXML
    TextField _adresa;
    @FXML
    TextField _locuri;
    @FXML
    DatePicker _data;
    @FXML
    Button cautaB;
    @FXML
    Button cumparaB;
    @FXML
    Label buyError;

    public void setServer(IServices s) {
        this.server = s;
    }

    public void setUser(Angajat user) {
        this.user = user;
        show();
    }

    public void show() {
        try{
            UtilsGUI.showTable(Zbor.class, tableZbor, server.findAll(), 1);
        } catch (AgentieException e) {
            System.out.println(" ");
        }
    }

    @FXML
    void cauta() {
        try{
            UtilsGUI.showTable(Zbor.class, _tableZbor, server.findByData(_destinatie.getText(), _data.getValue().toString()), 2);
        } catch (AgentieException e) {
            System.out.println(" ");
        }
        }

    @FXML
    void cumpara() {
        Zbor selected = _tableZbor.getSelectionModel().getSelectedItem();
        if (selected != null) {
            try {
                Bilet bilet = new Bilet(0, _client.getText(), _turisti.getText(), _adresa.getText(), Integer.parseInt(_locuri.getText()));
                int locuri = Integer.parseInt(_locuri.getText());
                server.cumparaBilet(selected, bilet, locuri, _destinatie.getText(), _data.getValue().toString());
                buyError.setText("Bilet cumparat");
                buyError.setTextFill(Color.GREEN);
                buyError.setVisible(true);


            } catch (AgentieException e) {
                buyError.setText("Nu sunt suficiente locuri");
                buyError.setTextFill(Color.RED);
                buyError.setVisible(true);
            }
        }
        else {
            buyError.setText("Selectati un zbor");
            buyError.setTextFill(Color.RED);
            buyError.setVisible(true);
        }
    }

    @FXML
    public void logOut(ActionEvent actionEvent) {
        logout();
        ((Node)actionEvent.getSource()).getScene().getWindow().hide();
    }

    void logout() {
        try {
            this.server.logout(this.user, this);
        } catch (AgentieException var2) {
            System.out.println("Logout error " + var2);
        }

    }

    @Override
    public void updateLista(List<Zbor> l1, List<Zbor> l2){
        System.out.println("OBSERVER NOTIFIED!");
        Platform.runLater(() -> {
            UtilsGUI.showTable(Zbor.class, tableZbor, l1, 1);
            UtilsGUI.showTable(Zbor.class, _tableZbor, l2, 2);
            try {
                UtilsGUI.showTable(Zbor.class, _tableZbor, server.findByData(_destinatie.getText(), _data.getValue().toString()), 2);
            } catch (AgentieException e) {
                throw new RuntimeException(e);
            }
        });
        }
}
