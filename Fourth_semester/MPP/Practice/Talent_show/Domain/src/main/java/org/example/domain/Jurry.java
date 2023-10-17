package org.example.domain;

public class Jurry extends Entity<Integer>{
    private String nume;
    private String password;

    public Jurry(){}

    public Jurry(String nume, String password) {
        super();
        this.nume = nume;
        this.password = password;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "Jurry{" +
                "id=" + id +
                ", nume='" + nume + '\'' +
                ", password='" + password + '\'' +
                '}';
    }
}

