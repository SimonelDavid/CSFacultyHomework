package com.example.template;

import com.example.template.entities.Hotel;
import com.example.template.entities.Location;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.*;

import java.util.List;

public class LocationController {

    public ComboBox<String> locsList;
    public ListView<String> hotels;
    public TextField cotaValue;
    private Service service;

    private ObservableList<String> locs;
    private ObservableList<String> hotel;

    public void updateCombo(){
        locs.clear();
        for(Location loc : service.getLocations()) {
            locs.add(loc.getlocationName());
        }
    }
    public void updateList(){
        hotel.clear();
        for(Hotel hot : service.getHotels()){
            hotel.add(hot.gethotelName()+":"+hot.getNoRooms()+":"+hot.getpricePerNight()+":"+hot.getType());
        }
    }

    public void init(Service service){
        locs = FXCollections.observableArrayList();
        hotel = FXCollections.observableArrayList();
        this.service = service;
        updateList();
        updateCombo();
        locsList.setItems(locs);
        hotels.setItems(hotel);
    }

}