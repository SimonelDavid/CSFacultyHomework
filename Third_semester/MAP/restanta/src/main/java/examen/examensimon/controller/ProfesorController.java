package examen.examensimon.controller;

import examen.examensimon.domain.*;
import examen.examensimon.service.Service;
import examen.examensimon.utils.observer.Observer;
import examen.examensimon.utils.utils.ActualEvent;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Callback;

import java.util.List;


public class ProfesorController implements Observer<ActualEvent> {
    Service service;
    Integer idTest;
    @FXML
    TableView<Intrebare> intrebariTableView;
    ObservableList<Intrebare> intrebariObservableList;
    @FXML
    TableView<Testul> testTableView;
    ObservableList<Testul> testObservableList;

    @FXML
    TableColumn select;
    @FXML
    public void setService(Service service){
        this.service=service;
        this.service.addObservers(this);
        showIntrebari();
        showTeste();
        init();
    }
    public void setTest(Integer idtest){
        this.idTest = idtest;
    }

    private void init(){
        Callback<TableColumn<Intrebare, String>, TableCell<Intrebare, String>> cellFactory =
                new Callback<TableColumn<Intrebare, String>, TableCell<Intrebare, String>>() {
                    @Override
                    public TableCell call(final TableColumn<Intrebare, String> param) {
                        final TableCell<Intrebare, String> cell = new TableCell<Intrebare, String>() {

                            Button btn = new Button("Select");

                            @Override
                            public void updateItem(String item, boolean empty) {
                                super.updateItem(item, empty);
                                if (empty) {
                                    setGraphic(null);
                                    setText(null);
                                } else {
                                    btn.setOnAction(event -> {
                                        Intrebare intrebare = getTableView().getItems().get(getIndex());
                                        Integer idIntrebare = intrebare.getNrIntrebare();
                                        service.addIntrebareToTest(idIntrebare,idTest);
                                    });
                                    setGraphic(btn);
                                    setText(null);
                                }
                            }
                        };
                        return cell;
                    }
                };
        select.setCellFactory(cellFactory);
    }

    @FXML
    public void showIntrebari(){
        List<Intrebare> intrebares = (List<Intrebare>) this.service.getAllIntrebari();
        List<Intrebare> intrebari = intrebares.stream().filter(intrebare -> intrebare.getTest()==0).toList();
        intrebariObservableList = FXCollections.observableArrayList(intrebari);
        intrebariTableView.setItems(intrebariObservableList);
        intrebariTableView.refresh();
    }
    @FXML
    public void showTeste(){
        List<Testul> tests = (List<Testul>) this.service.getAllTest();
        testObservableList = FXCollections.observableArrayList(tests);
        testTableView.setItems(testObservableList);
        testTableView.refresh();
    }

    @Override
    public void update(ActualEvent event) {
        showIntrebari();
        showTeste();
    }
}
