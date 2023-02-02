package com.example.template.repo;

import com.example.template.entities.Order;

import java.util.ArrayList;
import java.util.List;

public class OrderRepo {
    List<Order> orders;

    public OrderRepo() {
        orders = new ArrayList<>();
    }

    public List<Order> getOrders() {
        return orders;
    }

    public void setOrders(List<Order> orders) {
        this.orders = orders;
    }

    public void addOrder(Order order){
        orders.add(order);
    }
}
