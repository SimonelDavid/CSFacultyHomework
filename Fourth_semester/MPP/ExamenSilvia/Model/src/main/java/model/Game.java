package model;

import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.LazyCollection;
import org.hibernate.annotations.LazyCollectionOption;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Objects;

@Entity
@Table(name = "games")
public class Game implements Serializable, Identifiable<Integer> {

    private Integer ID;
    private User user;
    private Configuration configuration;
    private Integer score = 0;
    private Collection<String> visited = new ArrayList<>();
    private LocalDateTime localDateTime;
    private String choosedLetter;
    private String correctGuesses = "";
    private String codedWordProgress;
    private Boolean isOver = false;

    public Game(){

    }

    public Game(User user, Configuration configuration, LocalDateTime localDateTime) {
        this.user = user;
        this.configuration = configuration;
        this.localDateTime = localDateTime;
    }

    public Game(Integer ID, User user, Configuration configuration, LocalDateTime localDateTime) {
        this.ID = ID;
        this.user = user;
        this.configuration = configuration;
        this.localDateTime = localDateTime;
    }

    @Id
    @GeneratedValue(generator = "increment")
    @GenericGenerator(name = "increment", strategy = "increment")
    @Override
    public Integer getID() {
        return ID;
    }

    @Override
    public void setID(Integer id) {
        this.ID = id;
    }

    public Boolean getOver() {
        return isOver;
    }

    public void setOver(Boolean over) {
        isOver = over;
    }

    @LazyCollection(LazyCollectionOption.FALSE)
    @ManyToOne
    @JoinColumn(name = "idUser")
    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    @LazyCollection(LazyCollectionOption.FALSE)
    @ManyToOne
    @JoinColumn(name = "idConfiguration")
    public Configuration getConfiguration() {
        return configuration;
    }

    public void setConfiguration(Configuration configuration) {
        this.configuration = configuration;
    }

    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    @LazyCollection(LazyCollectionOption.FALSE)
    @ElementCollection
    public Collection<String> getVisited() {
        return visited;
    }

    public void setVisited(Collection<String> visited) {
        this.visited = visited;
    }

    public LocalDateTime getLocalDateTime() {
        return localDateTime;
    }

    public void setLocalDateTime(LocalDateTime localDateTime) {
        this.localDateTime = localDateTime;
    }

    public String getChoosedLetter() {
        return choosedLetter;
    }

    public void setChoosedLetter(String choosedLetter) {
        this.choosedLetter = choosedLetter;
    }

    public String getCorrectGuesses() {
        return correctGuesses;
    }

    public void setCorrectGuesses(String correctGuesses) {
        this.correctGuesses = correctGuesses;
    }

    public String getCodedWordProgress() {
        return codedWordProgress;
    }

    public void setCodedWordProgress(String codedWordProgress) {
        this.codedWordProgress = codedWordProgress;
    }

    @Override
    public String toString() {
        return "Game{" +
                "ID=" + ID +
                ", user=" + user +
                ", configuration=" + configuration +
                ", score=" + score +
                ", visited=" + visited +
                ", localDateTime=" + localDateTime +
                ", choosedLetter='" + choosedLetter + '\'' +
                ", correctGuesses='" + correctGuesses + '\'' +
                ", codedWordProgress='" + codedWordProgress + '\'' +
                ", isOver=" + isOver +
                '}';
    }
}
