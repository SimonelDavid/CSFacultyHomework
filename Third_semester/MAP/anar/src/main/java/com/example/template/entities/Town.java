package com.example.template.entities;

public class Town {
    private String name;
    private String river;
    private Integer cmdr;
    private Integer cma;

    public Town(String name, String river, Integer cmdr, Integer cma) {
        this.name = name;
        this.river = river;
        this.cmdr = cmdr;
        this.cma = cma;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getRiver() {
        return river;
    }

    public void setRiver(String river) {
        this.river = river;
    }

    public Integer getCmdr() {
        return cmdr;
    }

    public void setCmdr(Integer cmdr) {
        this.cmdr = cmdr;
    }

    public Integer getCma() {
        return cma;
    }

    public void setCma(Integer cma) {
        this.cma = cma;
    }
}
