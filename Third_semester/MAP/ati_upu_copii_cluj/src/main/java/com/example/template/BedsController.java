package com.example.template;

import com.example.template.entities.Bed;
import com.example.template.entities.BedType;
import com.example.template.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.paint.Color;

public class BedsController {

    public Label usedBeds;
    public TextField cnp;
    public Button outBtn;

    Service service;

    public void init(Service service) {
        this.service = service;

        Integer ticn = service.getFreeBeds(BedType.TIC);
        Integer timn = service.getFreeBeds(BedType.TIM);
        Integer tiipn = service.getFreeBeds(BedType.TIIP);

        tic.setText(ticn.toString());
        tim.setText(timn.toString());
        tiip.setText(tiipn.toString());
        color(ticn, timn, tiipn);
        usedBeds.setText(service.getUsedBeds().toString());

        cnp.setText("");
    }

    private void color(Integer ticn, Integer timn, Integer tiipn) {
        if(ticn == 0){
            tic.setTextFill(Color.color(1, 0, 0));
        }else{
            tic.setTextFill(Color.color(0, 1, 0));
        }
        if(timn == 0){
            tim.setTextFill(Color.color(1, 0, 0));
        }else{
            tim.setTextFill(Color.color(0, 1, 0));
        }
        if(tiipn == 0){
            tiip.setTextFill(Color.color(1, 0, 0));
        }else{
            tiip.setTextFill(Color.color(0, 1, 0));
        }
    }

    public Label tic;
    public Label tim;
    public Label tiip;

    public void notif() {
        init(service);
    }

    public void out(ActionEvent event) {
        if (cnp.getText().strip().equals("")) return;
        for(Bed bed: service.getBeds()){
            if(bed.getPatient() != null && bed.getPatient().equals(cnp.getText())){
                bed.setPatient(null);
                Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
                alert.setTitle("Confirmare");
                alert.setContentText("Patul a fost eliberat!");
                alert.show();
                notif();
                return;
            }
        }
        Alert alert = new Alert(Alert.AlertType.WARNING);
        alert.setTitle("Atenție!");
        alert.setContentText("Nu s-a găsit pacientul cu CNP " + cnp.getText());
        alert.show();
        notif();
    }
}