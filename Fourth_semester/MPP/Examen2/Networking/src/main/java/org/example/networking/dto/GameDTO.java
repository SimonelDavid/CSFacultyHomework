package org.example.networking.dto;

import org.example.domain.Game;

import java.io.Serializable;

public class GameDTO implements Serializable {
    Integer id;
    Integer idPlayer;
    Integer idConfig;
    String playerInput;
    Integer score;

    public GameDTO(Integer id, Integer idConfig, Integer idPlayer, String playerInput, Integer score) {
        this.id = id;
        this.idPlayer = idPlayer;
        this.idConfig = idConfig;
        this.playerInput = playerInput;
        this.score = score;
    }

    public Integer getIdPlayer() {
        return idPlayer;
    }

    public void setIdPlayer(Integer idPlayer) {
        this.idPlayer = idPlayer;
    }

    public Integer getIdConfig() {
        return idConfig;
    }

    public void setIdConfig(Integer idConfig) {
        this.idConfig = idConfig;
    }

    public String getPlayerInput() {
        return playerInput;
    }

    public void setPlayerInput(String playerInput) {
        this.playerInput = playerInput;
    }

    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    public Integer getId(){ return id;}

    public void setId(Integer id){ this.id = id;}

    public Game fromDTO(){
        var o = new Game(getIdPlayer(), getIdConfig(), getPlayerInput(), getScore());
        o.setId(getId());
        return o;
    }

    public static GameDTO toDTO(Game o){
        return new GameDTO(o.getId(), o.getIdPlayer(), o.getIdConfig(), o.getPlayerInput(), o.getScore());
    }
}
