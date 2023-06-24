package org.example.client;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.example.domain.Config;
import org.example.domain.Game;
import org.example.domain.User;
import org.example.service.IObserver;
import org.example.service.IService;

import static org.example.client.Utils.showError;
import static org.example.client.Utils.showInfo;

public class MainController implements IObserver {
    @FXML
    Button tryButton;
    @FXML
    Label scoreLabel;
    @FXML
    TextField poz1Label;
    @FXML
    TextField poz2Label;
    @FXML
    Button logoutButton;
    @FXML
    Label configLabel;
    @FXML
    TableView<Game> clasamentTable;
    @FXML
    TableColumn<Game, String> idplayerColumn;
    @FXML
    TableColumn<Game, String> scoreColumn;
    IService server;
    User user;
    Game currentGame;
    Integer currentScore;
    String currentConfig;
    ObservableList<Game> clasament = FXCollections.observableArrayList();

    public void setServer(IService server) {
        this.server = server;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public void initialization() {
        Platform.runLater(() -> {
            try {
                scoreLabel.setText("0");
                Config addedConfig = server.addConfig();
                String wordsss = addedConfig.getIdwords();
                StringBuilder sb = new StringBuilder(wordsss);
                for (int i=1; i<sb.length(); i+=2)
                    sb.insert(i, ' ');
                configLabel.setText(String.valueOf(sb));
                currentConfig = addedConfig.getIdwords();
                currentScore = 0;
                idplayerColumn.setCellValueFactory(new PropertyValueFactory<Game, String>("idPlayer"));
                scoreColumn.setCellValueFactory(new PropertyValueFactory<Game, String>("score"));
                clasamentTable.setItems(clasament);
                setClasament();
                //currentGame = server.startGame(new Game(user.getId(), addedConfig.getId(), "", 0));
                //showInfo(currentGame.toString());
            } catch (Exception e) {
                showError(e.getMessage());
            }
        });
    }

    public void setClasament(){
        try {
            for(Game u : server.getAllGames()){
                clasament.add(u);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public void logoutButtonClicked() {
        try {
            server.logout(user, this);
            Stage stage = (Stage) logoutButton.getScene().getWindow();
            stage.close();
            showInfo(user.toString() + " logged out");
        } catch (Exception e) {
            showError("Logout failed!");
        }
    }

    public void startButtonClicked() {
        try {

        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public void tryButtonClicked() {
        String poz1s = poz1Label.getText();
        String poz2s = poz2Label.getText();
        int poz1 = Integer.parseInt(poz1s) - 1;
        int poz2 = Integer.parseInt(poz2s) - 1;
        if(currentConfig.charAt(poz1) == currentConfig.charAt(poz2)){
            currentScore = currentScore - 2;
        }
        else{
            currentScore = currentScore + 3;
        }
        scoreLabel.setText(currentScore.toString());
    }
}
