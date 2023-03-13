package com.example.template.entities;

public class Hotel {
    private Integer hotelId;
    private Integer locationId;
    private String hotelName;
    private Integer noRooms;
    private Integer pricePerNight;
    private String type;

    public Hotel(Integer hotelId, Integer locationId, String hotelName, Integer noRooms, Integer pricePerNight, String type) {
        this.hotelId = hotelId;
        this.locationId = locationId;
        this.hotelName = hotelName;
        this.noRooms = noRooms;
        this.pricePerNight = pricePerNight;
        this.type = type;
    }

    public Integer getHotelId() {
        return hotelId;
    }
    public Integer getLocationId() {
        return locationId;
    }
    public String gethotelName() {
        return hotelName;
    }

    public void sethotelName(String hotelName) {
        this.hotelName = hotelName;
    }

    public Integer getNoRooms() {
        return noRooms;
    }

    public void setLocation(Integer noRooms) {
        this.noRooms = noRooms;
    }

    public Integer getpricePerNight() {
        return pricePerNight;
    }

    public void setpricePerNight(Integer pricePerNight) {
        this.pricePerNight = pricePerNight;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
