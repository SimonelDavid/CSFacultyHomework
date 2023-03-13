package com.example.rezerva.controller;

import com.example.rezerva.domain.Intrebare;
import com.example.rezerva.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class ProfController {
    private Service service;
    ObservableList<String> intrebariList= FXCollections.observableArrayList();
    public void setService(Service service) {
        this.service = service;
        initModel();
    }

    private void initModel() {
        for(Intrebare intrebare : this.service.getIntrebari()){
            intrebariList.add(String.valueOf(intrebare.getNrIntrebare()));
        }
    }
    @FXML
    private Label welcomeText;

    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
    }
}
