package model;

import java.io.Serializable;
import java.time.LocalDateTime;

public class DTOObject implements Serializable {

    private Integer rank;
    private String username;
    private LocalDateTime localDateTime;
    private Integer score;
    private Integer correctGuesses;

    public DTOObject(){

    }

    public DTOObject(Integer rank, String username, LocalDateTime localDateTime,  Integer score, Integer correctGuesses) {
        this.rank = rank;
        this.username = username;
        this.score = score;
        this.localDateTime = localDateTime;
        this.correctGuesses = correctGuesses;
    }

    public DTOObject(Integer rank, String username, Integer score, Integer correctGuesses) {
        this.rank = rank;
        this.username = username;
        this.score = score;
        this.correctGuesses = correctGuesses;
        this.localDateTime = LocalDateTime.now();
    }

    public Integer getRank() {
        return rank;
    }

    public void setRank(Integer rank) {
        this.rank = rank;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public LocalDateTime getLocalDateTime() {
        return localDateTime;
    }

    public void setLocalDateTime(LocalDateTime localDateTime) {
        this.localDateTime = localDateTime;
    }

    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    public Integer getCorrectGuesses() {
        return correctGuesses;
    }

    public void setCorrectGuesses(Integer correctGuesses) {
        this.correctGuesses = correctGuesses;
    }

    @Override
    public String toString() {
        return "DTOObject{" +
                "rank=" + rank +
                ", username='" + username + '\'' +
                ", score=" + score +
                ", localDateTime=" + localDateTime +
                ", correctGuesses='" + correctGuesses + '\'' +
                '}';
    }
}
