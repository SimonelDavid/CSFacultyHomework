package com.example.template.service;

import com.example.template.BedsController;
import com.example.template.entities.Bed;
import com.example.template.entities.BedType;
import com.example.template.entities.Patient;
import com.example.template.repo.BedsRepo;
import com.example.template.repo.PatientsRepo;

import java.util.ArrayList;
import java.util.List;

public class Service {
    private BedsRepo bedsRepo;
    private PatientsRepo patientsRepo;

    private BedsController bedsController;

    public void setBedsController(BedsController bedsController) {
        this.bedsController = bedsController;
    }

    public Service(BedsRepo bedsRepo, PatientsRepo patientsRepo) {
        this.bedsRepo = bedsRepo;
        this.patientsRepo = patientsRepo;
    }

    public List<Bed> getBeds() {
        return bedsRepo.getAll();
    }

    public List<Patient> getWaitingPatients(){
        List<Patient> patients = new ArrayList<>();

        for(Patient patient: patientsRepo.getAll()){
            if(patient.getPending())
                patients.add(patient);
        }
        return patients;
    }

    private void updatePatient(String cnp){
        for(Patient patient: patientsRepo.getAll()){
            if(patient.getCnp().equals(cnp)) {
                patient.setPending(false);
                return;
            }
        }
    }

    public boolean setPatientToABed(BedType bedType, boolean o2, String cnp){
        for(Bed bed: bedsRepo.getAll()){
            if(bed.getPatient() == null && bed.getType().equals(bedType) && o2 == bed.getO2()){
                bed.setPatient(cnp);
                updatePatient(cnp);
                notif();
                return true;
            }
        }
        return false;
    }

    public Integer getFreeBeds(BedType type){
        Integer nr = 0;
        for(Bed bed: bedsRepo.getAll()){
            if(bed.getType().equals(type) && bed.getPatient() == null)
                nr++;
        }
        return nr;
    }

    public Integer getUsedBeds(){
        Integer nr = 0;
        for(Bed bed: bedsRepo.getAll()){
            if(bed.getPatient() != null)
                nr++;
        }
        return nr;
    }

    private void notif(){
        bedsController.notif();
    }

}
