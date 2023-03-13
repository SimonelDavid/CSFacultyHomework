package com.example.template.entities;

import java.time.LocalDate;

public class Reservation{
    private Double id;
    private Long client;
    private Double hotel;
    private LocalDate start;
    private Integer nights;

    public Reservation(Double id, Long client, Double hotel, LocalDate start, Integer nights) {
        this.id = id;
        this.client = client;
        this.hotel = hotel;
        this.start = start;
        this.nights = nights;
    }

    public Double getId() {
        return id;
    }

    public void setId(Double id) {
        this.id = id;
    }

    public Long getClient() {
        return client;
    }



    public Double getHotel() {
        return hotel;
    }


    public LocalDate getStart() {
        return start;
    }



    public Integer getNights() {
        return nights;
    }


}
