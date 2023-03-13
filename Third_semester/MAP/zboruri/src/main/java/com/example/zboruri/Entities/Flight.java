package com.example.zboruri.Entities;

import java.time.LocalDate;
import java.time.LocalDateTime;

public class Flight {
    private Long flightId;
    private String from,to;
    private LocalDateTime departureTime;
    private LocalDateTime landingTime;
    private int seats;

    public Flight(Long flightId, String from, String to, LocalDateTime departureTime, LocalDateTime landingTime, int seats)
    {
        this.flightId = flightId;
        this.from = from;
        this.to = to;
        this.departureTime = departureTime;
        this.landingTime = landingTime;
        this.seats = seats;
    }

    public Long getFlightId()
    {
        return flightId;
    }

    public void setFlightId(Long flightId)
    {
        this.flightId = flightId;
    }

    public String getFrom()
    {
        return from;
    }

    public void setFrom(String from)
    {
        this.from = from;
    }

    public String getTo()
    {
        return to;
    }

    public void setTo(String to)
    {
        this.to = to;
    }

    public LocalDateTime getDepartureTime()
    {
        return departureTime;
    }

    public void setDepartureTime(LocalDateTime departureTime)
    {
        this.departureTime = departureTime;
    }

    public LocalDateTime getLandingTime()
    {
        return landingTime;
    }

    public void setLandingTime(LocalDateTime landingTime)
    {
        this.landingTime = landingTime;
    }

    public int getSeats()
    {
        return seats;
    }

    public void setSeats(int seats)
    {
        this.seats = seats;
    }
}
