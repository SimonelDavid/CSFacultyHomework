package com.example.template.entities;

public class Client {
    private String username;
    private String name;

    public Client(String username, String name) {
        this.username = username;
        this.name = name;
    }

    public String getId() {
        return username;
    }

    public void setId(String username) {
        this.username = username;
    }

    public String getName() {
        return name;
    }


}
