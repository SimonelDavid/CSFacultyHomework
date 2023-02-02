package com.example.template.entities;

import java.time.LocalDateTime;
import java.util.List;

public class Order {
    private int id;
    private int table;
    private List<MenuItem> items;
    private LocalDateTime date;
    private OrderStatus orderStatus;

    public Order(int id, int table, List<MenuItem> items) {
        this.id = id;
        this.table = table;
        this.items = items;
        date = LocalDateTime.now();
        orderStatus = OrderStatus.PLACED;
    }

    public Integer getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Integer getTable() {
        return table;
    }

    public void setTable(int table) {
        this.table = table;
    }

    public List<MenuItem> getItems() {
        return items;
    }

    public void setItems(List<MenuItem> items) {
        this.items = items;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public OrderStatus getOrderStatus() {
        return orderStatus;
    }

    public void setOrderStatus(OrderStatus orderStatus) {
        this.orderStatus = orderStatus;
    }
}
