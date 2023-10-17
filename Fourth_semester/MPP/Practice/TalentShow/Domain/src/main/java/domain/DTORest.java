package domain;

import java.io.Serializable;
import java.util.List;

public class DTORest extends Entity<Integer>implements Serializable {
    private Game game;
    private List<Participant> positions;
    private String raspuns;
    private Integer seconds;

    public DTORest(Integer id, Game game, List<Participant> positions, String raspuns, Integer seconds) {
        super(id);
        this.game = game;
        this.positions = positions;
        this.raspuns = raspuns;
        this.seconds = seconds;
    }

    public DTORest(Game game, List<Participant> positions, String raspuns, Integer seconds) {
        this.game = game;
        this.positions = positions;
        this.raspuns = raspuns;
        this.seconds = seconds;
    }

    public Game getGame() {
        return game;
    }

    public void setGame(Game game) {
        this.game = game;
    }

    public List<Participant> getPositions() {
        return positions;
    }

    public void setPositions(List<Participant> positions) {
        this.positions = positions;
    }

    public String getRaspuns() {
        return raspuns;
    }

    public void setRaspuns(String raspuns) {
        this.raspuns = raspuns;
    }

    public Integer getSeconds() {
        return seconds;
    }

    public void setSeconds(Integer seconds) {
        this.seconds = seconds;
    }
}
