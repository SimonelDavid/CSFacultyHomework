package org.example.networking.dto;

import org.example.domain.User;

import java.io.Serializable;

public class UserDTO implements Serializable {
    Integer id;
    String email;
    String password;

    public UserDTO(Integer id, String email, String password) {
        this.id = id;
        this.email = email;
        this.password = password;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public User fromDTO(){
        var o = new User(getEmail(), getPassword());
        o.setId(getId());
        return o;
    }

    public static UserDTO toDTO(User o){
        return new UserDTO(o.getId(), o.getEmail(), o.getPassword());
    }
}
