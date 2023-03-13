package com.example.template.service;

import com.example.template.HotelsController;
import com.example.template.entities.Location;
import com.example.template.entities.Hotel;
import com.example.template.repo.LocationRepo;
import com.example.template.repo.HotelRepo;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;

public class Service {
    private LocationRepo locationRepo;
    private HotelRepo hotelRepo;

    private HotelsController hotelsController;

    public Service(LocationRepo locationRepo, HotelRepo hotelRepo) {
        this.locationRepo = locationRepo;
        this.hotelRepo = hotelRepo;
    }

    public List<Location> getLocations(){
        return locationRepo.getAll();
    }
    public List<Hotel> getHotels(){
        return hotelRepo.getAll();
    }
    
}
