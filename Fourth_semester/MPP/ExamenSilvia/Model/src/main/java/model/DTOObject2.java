package model;

import java.io.Serializable;
import java.time.LocalDateTime;

public class DTOObject2 implements Serializable {
    private Integer rank;
    private String username;
    private Integer score;
    private String correctGuesses;

    public DTOObject2(){

    }

    public DTOObject2(Integer rank, String username, Integer score,String correctGuesses) {
        this.rank = rank;
        this.username = username;
        this.score = score;
        this.correctGuesses = correctGuesses;
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


    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    public String getCorrectGuesses() {
        return correctGuesses;
    }

    public void setCorrectGuesses(String correctGuesses) {
        this.correctGuesses = correctGuesses;
    }

    @Override
    public String toString() {
        return "DTOObject2{" +
                "rank=" + rank +
                ", username='" + username + '\'' +
                ", score=" + score +
                ", correctGuesses='" + correctGuesses + '\'' +
                '}';
    }
}
