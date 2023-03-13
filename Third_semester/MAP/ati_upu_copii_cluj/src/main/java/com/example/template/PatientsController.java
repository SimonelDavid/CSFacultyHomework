package com.example.template;

import com.example.template.entities.BedType;
import com.example.template.entities.Patient;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.*;

import java.util.Objects;

public class PatientsController {
    public Label pending;
    public ListView<String> list;
    public ChoiceBox<String> choice;
    public CheckBox o2;
    public Button addBtn;

    private ObservableList<String> patients;
    private Service service;

    public void init(Service service) {
        choice.getItems().add("TIC");
        choice.getItems().add("TIM");
        choice.getItems().add("TIIP");


        this.service = service;


        patients = FXCollections.observableArrayList();
        addAll();
        list.setItems(patients);
    }

    private BedType stringToBedType(String type){
        if(Objects.equals(type, "TIC"))return BedType.TIC;
        if(Objects.equals(type, "TIM"))return BedType.TIC;
        return BedType.TIIP;
    }

    public void addPatient(ActionEvent mouseEvent) {
        if (choice.getSelectionModel().getSelectedItem() == null)
            return;
        if (list.getSelectionModel().getSelectedItem() == null)
            return;
        String cnp = list.getSelectionModel().getSelectedItem().split(":")[0];
        if (service.setPatientToABed(stringToBedType(choice.getSelectionModel().getSelectedItem()), o2.isSelected(), cnp)) {
            Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
            alert.setTitle("Confirmare");
            alert.setContentText("S-a adăugat");
            alert.show();
            addAll();
        } else {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Atenție");
            alert.setContentText("Nu mai sunt paturi disponibile");
            alert.show();
        }
    }

    private void addAll() {
        choice.getSelectionModel().select(0);
        o2.setSelected(false);
        patients.clear();
        pending.setText(((Integer) service.getWaitingPatients().size()).toString());
        for (Patient patient : service.getWaitingPatients()) {
            patients.add(patient.getCnp() + ":" + patient.getDiagnostic());
        }
    }
}
