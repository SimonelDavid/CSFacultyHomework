package com.example.template;

import com.example.template.entities.Client;
import com.example.template.entities.Hotel;
import com.example.template.entities.Location;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

import java.io.IOException;

public class MainController {
    public ComboBox<String> locations;
    public ListView hotels;
    public Label text;

    private Service service;
    private ObservableList<String> locationsList;
    private ObservableList<String> hotelsList;



    public void init(Service service){
        locationsList = FXCollections.observableArrayList();
        hotelsList = FXCollections.observableArrayList();
        this.service = service;



        locations.setItems(locationsList);
        hotels.setItems(hotelsList);
        for(Location location : service.getLocations()){
            locationsList.add(location.getName());
        }



    }

    public void selected(ActionEvent event) {
        if(locations.getSelectionModel().getSelectedItem() == null)
            return;
        String location = locations.getSelectionModel().getSelectedItem();
        Double lid = service.getLid(location);
        hotelsList.clear();
        for(Hotel hotel: service.getHotels()){
            if(hotel.getLid().intValue() == lid.intValue()){
                hotelsList.add(hotel.getName()+
                        ":"+hotel.getRooms()+
                        ":"+hotel.getType().toString()+
                        ":"+hotel.getPrice().toString());
            }
        }
    }

    public void selectedHotel(MouseEvent mouseEvent) throws IOException {
        if(hotels.getSelectionModel().getSelectedItem() == null)
            return;
        String hotelName = hotels.getSelectionModel().getSelectedItem().toString().split(":")[0];
        Double hotelId = service.getHid(hotelName);

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("offer-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 400, 600);
        Stage stage = new Stage();
        stage.setTitle("Oferte");
        stage.setScene(scene);
        ((OfferController)fxmlLoader.getController()).init(service, hotelId);
        stage.show();

    }

}