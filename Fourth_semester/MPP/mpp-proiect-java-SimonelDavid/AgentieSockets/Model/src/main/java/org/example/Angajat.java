package org.example;

public class Angajat extends Entity<Integer>{
    private String nume;
    private String parola;

    public Angajat(Integer integer, String nume, String parola) {
        super(integer);
        this.nume = nume;
        this.parola = parola;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getParola() {
        return parola;
    }

    public void setParola(String parola) {
        this.parola = parola;
    }

    @Override
    public String toString() {
        return "Angajat{" +
                "nume='" + nume + '\'' +
                ", parola='" + parola + '\'' +
                '}';
    }
}
