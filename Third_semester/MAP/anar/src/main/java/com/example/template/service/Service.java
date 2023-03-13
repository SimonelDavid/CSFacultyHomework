package com.example.template.service;

import com.example.template.TownsController;
import com.example.template.entities.River;
import com.example.template.entities.Town;
import com.example.template.repo.RiverRepo;
import com.example.template.repo.TownRepo;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;

public class Service {
    private RiverRepo riverRepo;
    private TownRepo townRepo;

    private TownsController townsController;

    public Service(RiverRepo riverRepo, TownRepo townRepo) {
        this.riverRepo = riverRepo;
        this.townRepo = townRepo;
    }

    public List<River> getRivers(){
        return riverRepo.getAll();
    }

    public boolean highRisk(Town town){
        for(River river: riverRepo.getAll()){
            if(town.getRiver().equals(river.getName())){
                if(town.getCma() < river.getCota())
                    return true;
            }
        }
        return false;
    }

    public boolean risk(Town town){
        for(River river: riverRepo.getAll()){
            if(town.getRiver().equals(river.getName())){
                if(town.getCma() >= river.getCota() && town.getCmdr() < river.getCota())
                    return true;
            }
        }
        return false;
    }

    public boolean noRisk(Town town){
        for(River river: riverRepo.getAll()){
            if(town.getRiver().equals(river.getName())){
                if(town.getCmdr() >= river.getCota())
                    return true;
            }
        }
        return false;
    }

    public List<Town> getRiskGroup(String riskG){
        List<Town> group = new ArrayList<>();
        for(Town town: townRepo.getAll()){
            if(riskG.equals("h") && highRisk(town)){
                group.add(town);
            }if(riskG.equals("r") && risk(town)){
                group.add(town);
            }if(riskG.equals("n") && noRisk(town)){
                group.add(town);
            }
        }
        return group;
    }

    public void updateCota(String riverName, Integer cota){
        riverRepo.updateCota(riverName, cota);
        townsController.notif();
    }

    public void setController(TownsController controller) {
        this.townsController = controller;
    }

    public Integer getCota(String riverName){
        for(River river: riverRepo.getAll())
            if(river.getName().equals(riverName))
                return river.getCota();
        return null;
    }
}
