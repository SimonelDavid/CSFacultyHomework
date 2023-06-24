package client;


import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import model.Configuration;
import model.DTOObject;
import model.Game;
import model.User;
import services.IObserver;
import services.IServices;
import services.ServicesException;

import java.time.LocalDateTime;
import java.util.Collection;
import java.util.Objects;
import java.util.Random;


public class MainController implements IObserver {


    private IServices server;
    private User rootUser;
    private Game game;

    ObservableList<DTOObject> modelAllObjects = FXCollections.observableArrayList();

    @FXML
    TableView<DTOObject> tableView;
    @FXML
    TableColumn<DTOObject, Integer> tableColumn1;
    @FXML
    TableColumn<DTOObject, String> tableColumn2;
    @FXML
    TableColumn<DTOObject, LocalDateTime> tableColumn3;
    @FXML
    TableColumn<DTOObject, Integer> tableColumn4;
    @FXML
    TableColumn<DTOObject, Integer> tableColumn5;

    @FXML
    private TextField letterTextField;
    @FXML
    private Label infoLabel;
    @FXML
    private Label infoLabelScore;




    public MainController(){
        //this constructor is used by form
    }

    public MainController(IServices server) {
        this.server = server;
        System.out.println("Constructor with server param...");
    }


    public void setServer(IServices server, User rootUser) {
        this.server = server;
        this.rootUser = rootUser;
        System.out.println(rootUser);
        try {
            Collection<Configuration> configurations = server.getAllConf();
            Random random = new Random();
            int num = random.nextInt(configurations.size());
            Configuration conf = configurations.stream().toList().get(num);
            System.out.println(conf);
            //setButton(conf.getPozX(), conf.getPozY(), conf.getVal());
            String codedeWord = conf.getCodedWord();
            infoLabel.setText("YOUR CODED WORD: " + codedeWord);
            game = new Game(rootUser, conf, LocalDateTime.now());
        } catch (ServicesException e) {
            e.printStackTrace();
        }
    }

    @FXML
    public void initialize(){
        tableColumn1.setCellValueFactory(new PropertyValueFactory<DTOObject, Integer>("rank"));
        tableColumn2.setCellValueFactory(new PropertyValueFactory<DTOObject, String>("username"));
        tableColumn3.setCellValueFactory(new PropertyValueFactory<DTOObject, LocalDateTime>("localDateTime"));
        tableColumn4.setCellValueFactory(new PropertyValueFactory<DTOObject, Integer>("score"));
        tableColumn5.setCellValueFactory(new PropertyValueFactory<DTOObject, Integer>("correctGuesses"));
        tableView.setItems(modelAllObjects);
    }

    @Override
    public void endGame(Collection<Game> games) throws ServicesException {
        Platform.runLater(() -> {
            Collection<DTOObject> dtoObjectConfiguration = games.stream()
                    .sorted((Game x, Game y) -> {
                        if (x.getScore() <= y.getScore())
                            return 1;
                        return -1;
                    })
                    .map(game -> {
                        Integer nr = Integer.parseInt(String.valueOf(game.getCorrectGuesses().length()));
                        return new DTOObject(null, game.getUser().getUsername(),
                                game.getLocalDateTime(), game.getScore(),  nr);
                    })
                    .toList();
            Integer index = 0;
            for(DTOObject x : dtoObjectConfiguration){
                index ++;
                x.setRank(index);
                System.out.println(x);
            }

            modelAllObjects.setAll(dtoObjectConfiguration);
        });
    }


    @FXML
    public void handlePlay(ActionEvent actionEvent) {
        //aici faci set la tribute din game
        if(game.getVisited().size() == 0) {
            game.setCodedWordProgress(game.getConfiguration().getCodedWord());
        }
        String letterUser = letterTextField.getText();
        game.setChoosedLetter(letterUser);
        try {
//            if(game.getVisited().contains(userLetter))
//                throw new ServicesException("You already choosed this letter!");
            game = server.play(game);

            if(game.getOver() || game.getVisited().size() == 4) {
                //to do
                infoLabel.setText("Game over! You guessed the word " + game.getCodedWordProgress());
                infoLabelScore.setText("Finale score : " + game.getScore());
            }
            else {
                //to do
                infoLabelScore.setText("Score : " + game.getScore());
                infoLabel.setText("YOUR CODED WORD: " + game.getCodedWordProgress());
            }
            letterTextField.clear();

        } catch (ServicesException e) {
            //da clear la text boxes daca ai
            letterTextField.clear();
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Exam");
            alert.setHeaderText(e.getMessage());
            alert.setContentText("Score: " + game.getScore());
            alert.showAndWait();
        }
    }


    @FXML
    public void handleLogout(ActionEvent actionEvent) {
        try {
            server.logout(rootUser, this);
        } catch (ServicesException e) {
            e.printStackTrace();
        }
        System.exit(0);
    }

}
