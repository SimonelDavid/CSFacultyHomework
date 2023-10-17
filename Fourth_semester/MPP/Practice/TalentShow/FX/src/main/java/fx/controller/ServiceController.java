package fx.controller;

import domain.DTO;
import domain.Pair;
import domain.Jurry;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableView;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import examen.service.IObserver;
import examen.service.IService;
import examen.service.MyException;

import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;

public class ServiceController implements Initializable, IObserver {
    private Jurry jurry;
    private IService service;
    private Stage loginStage;

    @FXML
    TableView<DTO> rankingTableView;
    ObservableList<DTO> observableList;
    @FXML
    Label control;
    @FXML
    GridPane gridPane;

    public ServiceController() {
        System.out.println("ServiceController created");
    }

    @FXML
    public void setEmployee(Jurry game) {
        this.jurry = game;
    }

    @FXML
    public void setService(IService service) {
        this.service = service;
    }

    @FXML
    public void setStage(Stage stage) {
        this.loginStage = stage;
    }


    @Override
    public void initialize(URL location, ResourceBundle resources) {

    }
    public void initialization(){

    }

//    public void init() throws MyException {
//        showRanking();
//        for (int nume = 0; nume < 4; nume++) {
//            for (int prenume = 0; prenume < 4; prenume++) {
//                Button button = new Button();
//                // make button fill entire cell
//                button.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
//                button.setStyle("-fx-text-fill: #07087e");
//                GridPane.setRowIndex(button, nume);
//                GridPane.setColumnIndex(button, prenume);
//                button.setOnAction(event -> {
//                    try {
//                        int buttonRow = GridPane.getRowIndex(button);
//                        int buttonCol = GridPane.getColumnIndex(button);
//                        Pair pair = new Pair(jurry, buttonRow, buttonCol);
//                        String result = service.participant(pair);
//                        button.setText(result);
//                    } catch (MyException e) {
//                        control.setText(e.getMessage());
//                    }
//                });
//                gridPane.getChildren().add(button);
//            }
//        }
//    }

//    @Override
//    public void updateRanking() {
//        Platform.runLater(() -> {
//            try {
//                showRanking();
//            } catch (MyException e) {
//                throw new RuntimeException(e);
//            }
//        });
//    }

//    @Override
//    public void updateControl(Jurry jurry) throws MyException {
//        Platform.runLater(() -> {
//            try {
//                control.setText(service.setControlGameOver(jurry));
//                // for each button from gridPane, make disable
//                for (Node node : gridPane.getChildren()) {
//                    node.setDisable(true);
//                }
//            } catch (MyException e) {
//                throw new RuntimeException(e);
//            }
//        });
//    }

//    private void showRanking() throws MyException {
//        List<DTO> scores = (List<DTO>) this.service.getRanking();
//        if (scores == null) {
//            return;
//        }
//        observableList = FXCollections.observableArrayList(scores);
//        rankingTableView.setItems(observableList);
//        rankingTableView.refresh();
//    }

    public void logout() {
        try {
            service.logout(jurry, this);
            loginStage.show();
        } catch (MyException e) {
            System.out.println("Logout error " + e);
        }
    }

}
