package com.example.template.entities;

public class Hotel {
    private Double id;
    private Double lid;
    private String name;
    private Integer rooms;
    private Double price;
    private HotelType type;

    public Hotel(Double id, Double lid, String name, Integer rooms, Double price, HotelType type) {
        this.id = id;
        this.lid = lid;
        this.name = name;
        this.rooms = rooms;
        this.price = price;
        this.type = type;
    }

    public Double getId() {
        return id;
    }

    public void setId(Double id) {
        this.id = id;
    }

    public Double getLid() {
        return lid;
    }



    public String getName() {
        return name;
    }



    public Integer getRooms() {
        return rooms;
    }



    public Double getPrice() {
        return price;
    }

    public void setPrice(Double price) {
        this.price = price;
    }

    public HotelType getType() {
        return type;
    }



    public static HotelType stringToType(String type){
        if(type.equals("FAMILY"))return HotelType.FAMILY;
        if(type.equals("TEENAGERS"))return HotelType.TEENAGERS;
        if(type.equals("OLDPEOPLE"))return HotelType.OLDPEOPLE;
        return null;
    }
}
