package com.example.template.services;

import com.example.template.AngajatiController;
import com.example.template.entities.MenuItem;
import com.example.template.entities.Order;
import com.example.template.entities.Table;
import com.example.template.repo.MenuItemRepo;
import com.example.template.repo.OrderRepo;
import com.example.template.repo.TableRepo;

import java.util.List;

public class Service {
    AngajatiController angajatiController;
    TableRepo tableRepo;
    MenuItemRepo menuItemRepo;

    OrderRepo orderRepo;

    public void setObserver(AngajatiController observer){
        angajatiController = observer;
    }

    public TableRepo getTableRepo() {
        return tableRepo;
    }

    public void setTableRepo(TableRepo tableRepo) {
        this.tableRepo = tableRepo;
    }

    public MenuItemRepo getMenuItemRepo() {
        return menuItemRepo;
    }

    public void setMenuItemRepo(MenuItemRepo menuItemRepo) {
        this.menuItemRepo = menuItemRepo;
    }

    public Service(TableRepo tableRepo, MenuItemRepo menuItemRepo, OrderRepo orderRepo) {
        this.tableRepo = tableRepo;
        this.menuItemRepo = menuItemRepo;
        this.orderRepo = orderRepo;
    }

    public List<Table> getTables(){
        return tableRepo.getTables();
    }

    public List<MenuItem> getItems(){return  menuItemRepo.getItems();}

    public MenuItem findByName(String name){
        for(MenuItem item: getMenuItemRepo().getItems()){
            if(item.getItem().equals(name))
                return item;
        }
        return null;
    }

    public List<Order> getOrders(){
        return orderRepo.getOrders();
    }

    public void addOrder(Order order){
        orderRepo.addOrder(order);
        angajatiController.notif();
    }
}
