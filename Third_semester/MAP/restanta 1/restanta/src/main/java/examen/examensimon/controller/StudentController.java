package examen.examensimon.controller;

import examen.examensimon.domain.Intrebare;
import examen.examensimon.service.Service;
import examen.examensimon.utils.observer.Observer;
import examen.examensimon.utils.utils.ActualEvent;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.util.List;
import java.util.Objects;

public class StudentController implements Observer<ActualEvent> {
    Service service;
    String student;
    Integer idtest;
    @FXML
    TableView<Intrebare> intrebariTableView;
    ObservableList<Intrebare> intrebariObservableList;
    @FXML
    TableColumn select;
    public void setStudent(String student){
        this.student = student;
    }

    public void setTest(Integer idtest){
        this.idtest = idtest;
    }
    @FXML
    public void setService(Service service){
        this.service=service;
        this.service.addObservers(this);
        showIntrebari();
    }


    @FXML
    public void showIntrebari(){
        List<Intrebare> intrebares = (List<Intrebare>) this.service.getAllIntrebari();
        List<Intrebare> intrebari = intrebares.stream().filter(intrebare -> Objects.equals(intrebare.getTest(), idtest)).toList();
        intrebariObservableList = FXCollections.observableArrayList(intrebari);
        intrebariTableView.setItems(intrebariObservableList);
        intrebariTableView.refresh();
    }

    @Override
    public void update(ActualEvent event) {
        showIntrebari();
    }
}
