package org.example.networking.dto;

import org.example.domain.Rezultate;

import java.io.Serializable;

public class GameDTO implements Serializable {
    Integer id;
    Integer jurry_id;
    Integer participant_id;
    String raspuns;

    public GameDTO(Integer id, Integer participant_id, Integer jurry_id, String raspuns) {
        this.id = id;
        this.jurry_id = jurry_id;
        this.participant_id = participant_id;
        this.raspuns = raspuns;
    }

    public Integer getIdPlayer() {
        return jurry_id;
    }

    public void setIdPlayer(Integer jurry_id) {
        this.jurry_id = jurry_id;
    }

    public Integer getIdConfig() {
        return participant_id;
    }

    public void setIdConfig(Integer participant_id) {
        this.participant_id = participant_id;
    }

    public String getPlayerInput() {
        return raspuns;
    }

    public void setPlayerInput(String raspuns) {
        this.raspuns = raspuns;
    }


    public Integer getId(){ return id;}

    public void setId(Integer id){ this.id = id;}

    public Rezultate fromDTO(){
        var o = new Rezultate(getIdPlayer(), getIdConfig(), getPlayerInput());
        o.setId(getId());
        return o;
    }

    public static GameDTO toDTO(Rezultate o){
        return new GameDTO(o.getId(), o.getIdPlayer(), o.getIdConfig(), o.getPlayerInput());
    }
}
