package com.example.template;

import com.example.template.entities.River;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.*;

public class RiverController {

    public ListView<String> riversList;
    public Button cotaChangeBtn;
    public TextField cotaValue;
    private Service service;

    private ObservableList<String> rivers;

    public void updateList(){
        rivers.clear();
        for(River rive : service.getRivers()){
            rivers.add(rive.getName()+":"+rive.getCota());
        }
    }

    public void init(Service service){
        rivers = FXCollections.observableArrayList();
        this.service = service;
        updateList();
        riversList.setItems(rivers);
    }

    public void changeCota(ActionEvent event) {
        if(riversList.getSelectionModel().getSelectedItem() == null)
            return;
        if(cotaValue.getText() == "")return;
        try {
            service.updateCota(riversList.getSelectionModel().getSelectedItem()
                            .split(":")[0],
                    Integer.parseInt(cotaValue.getText()));
            updateList();
        }catch (NumberFormatException ignored){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Eroare");
            alert.setContentText("Trebuie introdus un număr!!!!!!!!");
        }
        cotaValue.setText("");
    }
}