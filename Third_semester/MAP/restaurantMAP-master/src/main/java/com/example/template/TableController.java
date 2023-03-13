package com.example.template;

import com.example.template.entities.MenuItem;
import com.example.template.entities.Order;
import com.example.template.entities.Table;
import com.example.template.services.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableArray;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class TableController {

    private ObservableList<String> menuItems;

    private Table table;
    private Service service;
    @FXML
    private Label tableIdText;

    @FXML
    private ListView mItems;

    public void init(){


        menuItems = FXCollections.observableArrayList();

        tableIdText.setText(table.getId().toString());

        List<MenuItem> menuItemsUngrouped = service.getItems();

        String category = "";
        for(MenuItem menuItem: menuItemsUngrouped){
            if(!Objects.equals(category, menuItem.getCategory())){
                menuItems.add(menuItem.getCategory() + ":");
                category = menuItem.getCategory();
            }
            menuItems.add(menuItem.getItem() + "," + menuItem.getPrice() + " " + menuItem.getCurrency());
        }
        mItems.setItems(menuItems);
        mItems.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);

    }

    public void setTable(Table table) {
        this.table = table;
    }

    public void setService(Service service) {
        this.service = service;
    }

    @FXML
    private Button placeButton;

    public void onClick(ActionEvent event) {


        ObservableList<String> items = mItems.getSelectionModel().getSelectedItems();

        List<MenuItem> menuItemsOrder = new ArrayList<>();
        if(items.isEmpty())return;
        for(String item: items){
            if(item.contains(":"))
                continue;
            menuItemsOrder.add(service.findByName(item.split(",")[0].strip()));
            tableIdText.setText(item.split(",")[0].strip());
        }
        mItems.getSelectionModel().select(-1);
        if(menuItemsOrder.isEmpty())
            return;
        mItems.getSelectionModel().select(-1);
        Order order = new Order(service.getOrders().size()+1, table.getId(), menuItemsOrder);
        service.addOrder(order);
        tableIdText.setText("Placed Order");
    }
}
