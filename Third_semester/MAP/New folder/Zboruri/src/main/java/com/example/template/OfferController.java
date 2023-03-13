package com.example.template;

import com.example.template.entities.Reservation;
import com.example.template.entities.SpecialOffer;
import com.example.template.service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.*;

import java.time.LocalDate;

import static java.time.temporal.ChronoUnit.DAYS;

public class OfferController {

    public Label text;
    public DatePicker startDate;
    public DatePicker endDate;
    public ListView offers;
    private Service service;

    public ComboBox users;
    private String client;
    private ObservableList<String>clientsList;

    private ObservableList<String> offersList;

    public void init(Service service, String client) {
        offersList = FXCollections.observableArrayList();
        offers.setItems(offersList);
        this.service = service;
        this.client = client;
        text.setText("Hotelul "+
                service.findHotel(Double.valueOf(client)));


        clientsList = FXCollections.observableArrayList();
        users.setItems(clientsList);

    }


    public void search(ActionEvent event) {
        if (endDate.getValue() == null || startDate.getValue() == null)
            return;
        LocalDate sd = startDate.getValue();
        LocalDate ed = endDate.getValue();
        offersList.clear();
        for (SpecialOffer specialOffer : service.getOffers()) {
            if (specialOffer.getStart().isAfter(sd) && specialOffer.getEnd().isBefore(ed) && specialOffer.getHotel().equals(client)) {
                offersList.add(specialOffer.getId() + ":"
                        + specialOffer.getPercent() + "% începe la "
                        + specialOffer.getStart().toString()
                        + " până la " + specialOffer.getEnd().toString());
            }
        }
    }

    public void reservation(ActionEvent event) {
        if (endDate.getValue() == null || startDate.getValue() == null)
            return;

        if(users.getSelectionModel().getSelectedItem() == null)
            return;

        LocalDate sd = startDate.getValue();
        LocalDate ed = endDate.getValue();
        long nights = DAYS.between(sd, ed);

//        Reservation reservation = new Reservation(
//                ((Integer) (service.getReservations().size()+1)).doubleValue(),
//                service.getClient(users.getSelectionModel().getSelectedItem().toString()).getId(),
//                hotel,
//                sd,
//                ((Long)nights).intValue()
//        );
//
//        service.addReservation(reservation);
//        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
//        alert.setTitle("Ok");
//        alert.setContentText("S-a făcut rezervare <3");
//        alert.show();

    }
}
