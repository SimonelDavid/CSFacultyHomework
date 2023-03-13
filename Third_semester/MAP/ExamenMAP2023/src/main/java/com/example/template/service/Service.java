package com.example.template.service;

import com.example.template.ClientController;
import com.example.template.entities.*;
import com.example.template.repo.*;

import java.util.ArrayList;
import java.util.List;

public class Service {

    private LocationRepo locationRepo;
    private HotelRepo hotelRepo;

    private SpecialOffersRepo specialOffersRepo;

    private ClientRepo clientRepo;

    private ReservationRepo reservationRepo;

    List<ClientController> controllers;

    public void addController(ClientController clientController){
        controllers.add(clientController);
    }

    public Service(LocationRepo locationRepo, HotelRepo hotelRepo, SpecialOffersRepo specialOffersRepo, ClientRepo clientRepo, ReservationRepo reservationRepo) {
        this.locationRepo = locationRepo;
        this.hotelRepo = hotelRepo;
        this.specialOffersRepo = specialOffersRepo;
        this.clientRepo = clientRepo;
        this.reservationRepo = reservationRepo;
        controllers = new ArrayList<>();
    }

    public List<Location> getLocations(){
        return locationRepo.getAll();
    }

    public List<Hotel> getHotels(){
        return hotelRepo.getAll();
    }

    public Double getLid(String location) {
        for(Location loc: locationRepo.getAll()){
            if(loc.getName().equals(location))
                return loc.getId();
        }
        return 0.0;
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

    public List<Client> getClients() {
        return clientRepo.getAll();
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

    public Location getLocation(Hotel hotel){
        for(Location location: locationRepo.getAll()){
            if(location.getId().equals(hotel.getLid()))
                return location;
        }
        return null;
    }

    public Client getClient(String name){
        for(Client location: clientRepo.getAll()){
            if(location.getName().equals(name))
                return location;
        }
        return null;
    }

    public void addReservation(Reservation reservation) {
        reservationRepo.add(reservation);
        notif(reservation.getClient());
    }

    private void notif(Long client) {
        for(ClientController clientController: controllers){
            clientController.notif(client);
        }
    }

    public String findHotel(Double hotel) {
        for(Hotel hotel1: hotelRepo.getAll()){
            if(hotel1.getId().equals(hotel))
                return hotel1.getName();
        }
        return "";
    }
}

