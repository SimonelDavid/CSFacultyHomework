package com.example.template.entities;

public class River {
    private String name;
    private Integer cota;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getCota() {
        return cota;
    }

    public void setCota(Integer cota) {
        this.cota = cota;
    }

    public River(String name, Integer cota) {
        this.name = name;
        this.cota = cota;
    }
}
