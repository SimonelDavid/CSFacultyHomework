package org.example.domain;

import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;

@javax.persistence.Entity
@Table(name = "Games")
public class Game extends Entity<Integer>{
    private Integer idPlayer;
    private Integer idConfig;
    private String playerInput;
    private Integer score;

    public Game(){}

    public Game(Integer idPlayer, Integer idConfig, String playerInput, Integer score) {
        super();
        this.idPlayer = idPlayer;
        this.idConfig = idConfig;
        this.playerInput = playerInput;
        this.score = score;
    }

    @Column(name = "idplayer")
    public Integer getIdPlayer() {
        return idPlayer;
    }

    public void setIdPlayer(Integer idPlayer) {
        this.idPlayer = idPlayer;
    }

    @Column(name = "idconfig")
    public Integer getIdConfig() {
        return idConfig;
    }

    public void setIdConfig(Integer idConfig) {
        this.idConfig = idConfig;
    }

    @Column(name = "playerinput")
    public String getPlayerInput() {
        return playerInput;
    }

    public void setPlayerInput(String playerInput) {
        this.playerInput = playerInput;
    }

    @Column(name = "score")
    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    @Override
    @Id
    @GeneratedValue(generator = "increment")
    @GenericGenerator(name="increment", strategy="increment")
    @Column(name = "id", updatable = false, nullable = false)
    public Integer getId(){ return super.getId();}

    @Override
    public void setId(Integer id){ super.setId(id);}

    @Override
    public String toString() {
        return "Game{" +
                "idPlayer=" + idPlayer +
                ", idConfig='" + idConfig + '\'' +
                ", playerInput='" + playerInput + '\'' +
                ", score=" + score +
                ", id=" + id +
                '}';
    }
}
