package com.example.template.service;

import com.example.template.entities.*;
import com.example.template.repo.*;

import java.util.ArrayList;
import java.util.List;

public class Service {

    private ClientRepo clientRepo;
    private HotelRepo hotelRepo;

    private SpecialOffersRepo specialOffersRepo;

    private ReservationRepo reservationRepo;



    public Service(ClientRepo clientRepo, HotelRepo hotelRepo, SpecialOffersRepo specialOffersRepo, ReservationRepo reservationRepo) {
        this.clientRepo = clientRepo;
        this.hotelRepo = hotelRepo;
        this.specialOffersRepo = specialOffersRepo;
        this.reservationRepo = reservationRepo;
    }

    public List<Client> getClients(){
        return clientRepo.getAll();
    }

    public List<Hotel> getHotels(){
        return hotelRepo.getAll();
    }

    public String getLid(String client) {
        for(Client loc: clientRepo.getAll()){
            if(loc.getName().equals(client))
                return loc.getId();
        }
        return null;
    }

    public Double getHid(String hotel) {
        for(Hotel loc: hotelRepo.getAll()){
            if(loc.getName().equals(hotel))
                return loc.getId();
        }
        return 0.0;
    }

    public List<SpecialOffer> getOffers(){
        return specialOffersRepo.getAll();
    }


    public List<Reservation> getReservations() {
        return reservationRepo.getAll();
    }

    public Hotel getHotel(SpecialOffer offer){
        for(Hotel hotel: hotelRepo.getAll()){
            if(hotel.getId().equals(offer.getHotel()))
                return hotel;
        }
        return null;
    }

    public Client getClient(Hotel hotel){
        for(Client client: clientRepo.getAll()){
            if(client.getId().equals(hotel.getLid()))
                return client;
        }
        return null;
    }



    public String findHotel(Double hotel) {
        for(Hotel hotel1: hotelRepo.getAll()){
            if(hotel1.getId().equals(hotel))
                return hotel1.getName();
        }
        return "";
    }
}

