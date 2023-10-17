package org.example.networking.dto;

import org.example.domain.Jurry;

import java.io.Serializable;

public class UserDTO implements Serializable {
    Integer id;
    String nume;
    String password;

    public UserDTO(Integer id, String nume, String password) {
        this.id = id;
        this.nume = nume;
        this.password = password;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
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

    public Jurry fromDTO(){
        var o = new Jurry(getNume(), getPassword());
        o.setId(getId());
        return o;
    }

    public static UserDTO toDTO(Jurry o){
        return new UserDTO(o.getId(), o.getNume(), o.getPassword());
    }
}
