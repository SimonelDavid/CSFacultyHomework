package com.example.template;

import com.example.template.entities.Client;
import com.example.template.entities.Hotel;
import com.example.template.entities.Location;
import com.example.template.entities.SpecialOffer;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;

import java.time.LocalDate;
import java.util.Objects;

public class ClientController {
    public ListView<String> offers;
    public Label text;
    private Client client;
    private Service service;

    private ObservableList<String> offersList;

    public void init(Service service, Client client){
        text.setText(client.getName());
        offersList = FXCollections.observableArrayList();
        this.client = client;
        this.service = service;
        offers.setItems(offersList);
        offersList.clear();

        for(SpecialOffer specialOffer: service.getOffers()){
            ///s-ar prefera ca operațiile de genu să se facă în Service :/ (nu aici). Da' e _ok_
            if(specialOffer.getEnd().isAfter(LocalDate.now())
            && specialOffer.getPercent() < client.getFidelity()){
                Hotel hotel = service.getHotel(specialOffer);
                Location location = service.getLocation(hotel);
                offersList.add(hotel.getName()+":"+location.getName()+":("+
                        specialOffer.getStart()+"-"+
                        specialOffer.getEnd()+")");
            }
        }
    }

    public void notif(Long clt) {
        for(Client client1: service.getClients()){
            if(client1.getId().equals(clt)
                    && client1.getHobby().equals(client.getHobby())
                    && !Objects.equals(client.getId(), clt)){
                Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
                alert.setTitle("Hopa!");
                alert.setHeaderText("Dragă, " +  client.getName());
                alert.setContentText("Încă un client cu hobby-ul tău a făcut o rezervare");
                alert.show();
            }
        }
    }
}
