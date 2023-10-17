package domain;

import java.io.Serializable;

public class Pair extends Entity<Integer>implements Serializable {
    private Jurry jurry;
    private String nume, prenume;

    public Pair(Jurry jurry, String nume, String prenume) {
        this.jurry = jurry;
        this.nume = nume;
        this.prenume = prenume;
    }

    public Pair() {

    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    public Jurry getJurry() {
        return jurry;
    }

    public void setJurry(Jurry jurry) {
        this.jurry = jurry;
    }
}
