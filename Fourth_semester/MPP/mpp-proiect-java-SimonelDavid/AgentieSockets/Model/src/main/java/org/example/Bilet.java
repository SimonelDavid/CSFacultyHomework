package org.example;

public class Bilet extends Entity<Integer>{
    private String client;
    private String turisti;
    private String adresa;
    private Integer locuri;

    public Bilet(Integer integer, String client, String turisti, String adresa, Integer locuri) {
        super(integer);
        this.client = client;
        this.turisti = turisti;
        this.adresa = adresa;
        this.locuri = locuri;
    }

    public String getClient() {
        return client;
    }

    public void setClient(String client) {
        this.client = client;
    }

    public String getTuristi() {
        return turisti;
    }

    public void setTuristi(String turisti) {
        this.turisti = turisti;
    }

    public String getAdresa() {
        return adresa;
    }

    public void setAdresa(String adresa) {
        this.adresa = adresa;
    }

    public Integer getLocuri() {
        return locuri;
    }

    public void setLocuri(Integer locuri) {
        this.locuri = locuri;
    }

    @Override
    public String toString() {
        return "Bilet{" +
                "client='" + client + '\'' +
                ", turisti='" + turisti + '\'' +
                ", adresa='" + adresa + '\'' +
                ", locuri=" + locuri +
                '}';
    }
}
