package com.example.template;

import com.example.template.entities.Hotel;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;
import javafx.scene.text.*;

public class HotelsController {
    public ListView<Text> h;
    public ListView<Text> r;
    public ListView<Text> n;
    public Button unknownBtn;
    public TextField noRooms;
    public TextField type;
    public TextField pricePerNight;
    private Service service;

    private ObservableList<Text> noR;
    private ObservableList<Text> mR;
    private ObservableList<Text> hR;

    private void addHotels() {
        noR.clear();
        mR.clear();
        hR.clear();

    }
}
