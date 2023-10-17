package org.example;

public class Zbor extends Entity<Integer>{
    private String destinatie;
    private String data;
    private String ora;
    private String aeroport;
    private Integer locuri;

    public Zbor(Integer integer, String destinatie, String data, String ora, String aeroport, Integer locuri) {
        super(integer);
        this.destinatie = destinatie;
        this.data = data;
        this.ora = ora;
        this.aeroport = aeroport;
        this.locuri = locuri;
    }

    public String getDestinatie() {
        return destinatie;
    }

    public void setDestinatie(String destinatie) {
        this.destinatie = destinatie;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public String getOra() {
        return ora;
    }

    public void setOra(String time) {
        this.ora = time;
    }

    public String getAeroport() {
        return aeroport;
    }

    public void setAeroport(String aeroport) {
        this.aeroport = aeroport;
    }

    public Integer getLocuri() {
        return locuri;
    }

    public void setLocuri(Integer locuri) {
        this.locuri = locuri;
    }

    @Override
    public String toString() {
        return "Zbor{" +
                "destinatie='" + destinatie + '\'' +
                ", data='" + data + '\'' +
                ", ora='" + ora + '\'' +
                ", aeroport='" + aeroport + '\'' +
                ", locuri=" + locuri +
                '}';
    }
}
