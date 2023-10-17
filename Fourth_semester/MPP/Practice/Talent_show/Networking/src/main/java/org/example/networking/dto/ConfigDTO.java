package org.example.networking.dto;

import org.example.domain.Config;
import org.example.domain.Jurry;

import java.io.Serializable;

public class ConfigDTO implements Serializable {
    Integer id;
    private String idwords;

    public ConfigDTO(Integer id, String idwords) {
        this.id = id;
        this.idwords = idwords;
    }

    public String getIdwords() {
        return idwords;
    }

    public void setIdwords(String idwords) {
        this.idwords = idwords;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Config fromDTO(){
        var o = new Config(getIdwords());
        o.setId(getId());
        return o;
    }

    public static ConfigDTO toDTO(Config o){
        return new ConfigDTO(o.getId(), o.getIdwords());
    }
}
