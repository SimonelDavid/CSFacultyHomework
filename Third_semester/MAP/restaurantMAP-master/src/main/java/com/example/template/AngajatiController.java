package com.example.template;

import com.example.template.entities.MenuItem;
import com.example.template.entities.Order;
import com.example.template.services.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;

import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeFormatterBuilder;
import java.util.ArrayList;
import java.util.List;

public class AngajatiController {
    @FXML
    private Label welcomeText;

    @FXML

    private Service service;

    @FXML
    private ListView orders;

    private ObservableList<String> ordersList;

    public void setService(Service service) {
        this.service = service;
    }

    public void init(){
        ordersList = FXCollections.observableArrayList();
        orders.setItems(ordersList);
    }

    public void notif() {
        ordersList.clear();
        for(Order order: service.getOrders()){

            String items = "";

            for(MenuItem menuItem: order.getItems())
                items += menuItem.getItem() + ", " ;

            ordersList.add(
                    "masa " + order.getTable().toString() +
                    " || comanda: " + order.getId().toString() + " || "+
                    items + " || " +
                    order.getOrderStatus()
                            + " at "
                            + order.getDate().toString());
        }
    }
}