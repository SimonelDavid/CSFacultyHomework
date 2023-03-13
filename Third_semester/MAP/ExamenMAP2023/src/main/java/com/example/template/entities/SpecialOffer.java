package com.example.template.entities;

import java.time.LocalDate;

public class SpecialOffer {
    private Double id;
    private Double hotel;
    private LocalDate start;
    private LocalDate end;
    private Integer percent;

    public SpecialOffer(Double id, Double hotel, LocalDate start, LocalDate end, Integer percent) {
        this.id = id;
        this.hotel = hotel;
        this.start = start;
        this.end = end;
        this.percent = percent;
    }

    public Double getId() {
        return id;
    }

    public void setId(Double id) {
        this.id = id;
    }

    public Double getHotel() {
        return hotel;
    }



    public LocalDate getStart() {
        return start;
    }



    public LocalDate getEnd() {
        return end;
    }



    public Integer getPercent() {
        return percent;
    }


}
