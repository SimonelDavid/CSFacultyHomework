package com.example.zboruri.Entities;

import java.time.LocalDateTime;

public class Ticket {
    int id;
    String username;
    Long flightId;
    LocalDateTime purchaseTime;

    public Ticket(int id,String username, Long flightId, LocalDateTime purchaseTime)
    {
        this.id=id;
        this.username = username;
        this.flightId = flightId;
        this.purchaseTime = purchaseTime;
    }

    public String getUsername()
    {
        return username;
    }

    public void setUsername(String username)
    {
        this.username = username;
    }

    public Long getFlightId()
    {
        return flightId;
    }

    public void setFlightId(Long flightId)
    {
        this.flightId = flightId;
    }

    public LocalDateTime getPurchaseTime()
    {
        return purchaseTime;
    }

    public void setPurchaseTime(LocalDateTime purchaseTime)
    {
        this.purchaseTime = purchaseTime;
    }

    public int getId()
    {
        return id;
    }

    public void setId(int id)
    {
        this.id = id;
    }
}
