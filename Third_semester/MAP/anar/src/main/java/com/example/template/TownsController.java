package com.example.template;

import com.example.template.entities.Town;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.text.*;

public class TownsController {
    public ListView<Text> h;
    public ListView<Text> r;
    public ListView<Text> n;
    public Button unknownBtn;
    public TextField river;
    public TextField cma;
    public TextField cmdr;
    private Service service;

    private ObservableList<Text> noR;
    private ObservableList<Text> mR;
    private ObservableList<Text> hR;

    private void addTowns(){
        noR.clear();
        mR.clear();
        hR.clear();
        for(Town town: service.getRiskGroup("n")) {
            Text text = new Text();
            text.setFill(Color.GREEN);
            text.setText(town.getName()+":"+town.getRiver()
                    +"-" + service.getCota (town.getRiver()).toString()
                    +"  (" +town.getCmdr().toString()+" - "+town.getCma().toString()+")");
            noR.add(text);
        }
        for(Town town: service.getRiskGroup("r")) {
            Text text = new Text();
            text.setFill(Color.ORANGE);
            text.setText(town.getName()+":"+town.getRiver()
                    +"-" + service.getCota (town.getRiver()).toString()
                    +"  (" +town.getCmdr().toString()+" - "+town.getCma().toString()+")");
            mR.add(text);
        }
        for(Town town: service.getRiskGroup("h")) {
            Text text = new Text();
            text.setFill(Color.RED);
            text.setText(town.getName()+":"+town.getRiver()
                    +"-" + service.getCota (town.getRiver()).toString()
                    +"  (" +town.getCmdr().toString()+" - "+town.getCma().toString()+")");
            hR.add(text);
        }



    }

    public void init(Service service) {
        this.service = service;
        noR = FXCollections.observableArrayList();
        mR = FXCollections.observableArrayList();
        hR = FXCollections.observableArrayList();
        n.setItems(noR);
        r.setItems(mR);
        h.setItems(hR);
        addTowns();
    }

    public void notif(){
        addTowns();
    }

    public void compute(ActionEvent event) {

        Integer cmdrV;
        Integer cmaV;
        String riverV;
        try{
            cmdrV = Integer.parseInt(cmdr.getText());
            cmaV = Integer.parseInt(cma.getText());
            cmdr.setText("");
            cma.setText("");
            if(service.getCota(river.getText().strip()) == null) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Eroare");
                alert.setContentText("Râul nu există");
                alert.show();
                river.setText("");
                return;
            }
            riverV = river.getText().strip();
            river.setText("");
            Town town = new Town("idk", riverV, cmdrV, cmaV);
            if(service.highRisk(town)){
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Atenție!");
                alert.setContentText("Orașul prezintă un risc major de inundații!");
                alert.show();
                return;
            }
            if(service.risk(town)){
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Atenție!");
                alert.setContentText("Orașul prezintă un risc mediu de inundații!");
                alert.show();
                return;
            }
            Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
            alert.setTitle("E ok!");
            alert.setContentText("Localitatea nu prezintă nicun risc.");
            alert.show();
        }catch (NumberFormatException ignored){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Eroare");
            alert.setContentText("Trebuie introdus un număr!!!!!!!!");
            alert.show();
        }
    }
}
