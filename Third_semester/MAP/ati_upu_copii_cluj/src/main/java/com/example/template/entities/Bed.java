package com.example.template.entities;

import java.util.Objects;

public class Bed {
    private Integer id;
    private BedType type;
    private Boolean o2;
    private String patient;

    public Bed(Integer id, BedType type, Boolean o2) {
        this.id = id;
        this.type = type;
        this.o2 = o2;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public BedType getType() {
        return type;
    }

    public void setType(BedType type) {
        this.type = type;
    }

    public Boolean getO2() {
        return o2;
    }

    public void setO2(Boolean o2) {
        this.o2 = o2;
    }

    public String getPatient() {
        return patient;
    }

    public void setPatient(String patient) {
        this.patient = patient;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Bed bed)) return false;
        return id.equals(bed.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}
