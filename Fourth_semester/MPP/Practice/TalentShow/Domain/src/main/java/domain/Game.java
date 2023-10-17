package domain;

import javax.persistence.*;
import java.io.Serializable;

@javax.persistence.Entity
@Table(name = "game")
@AttributeOverride(name = "id", column = @Column(name = "game_id"))
public class Game extends Entity<Integer>implements Serializable {
    @ManyToOne
    @JoinColumn(name = "position_id1")
    private Participant position1;
    @ManyToOne
    @JoinColumn(name = "position_id2")
    private Participant position2;
    @ManyToOne
    @JoinColumn(name = "position_id3")
    private Participant position3;
    @ManyToOne
    @JoinColumn(name = "position_id4")
    private Participant position4;
    @ManyToOne
    @JoinColumn(name = "position_id5")
    private  Participant position5;

    public Game() {
    }

    public Game(Integer id, Participant position1, Participant position2, Participant position3, Participant position4, Participant position5) {
        super(id);
        this.position1 = position1;
        this.position2 = position2;
        this.position3 = position3;
        this.position4 = position4;
        this.position5 = position5;
    }

public Game(Participant position1, Participant position2, Participant position3, Participant position4, Participant position5) {
        this.position1 = position1;
        this.position2 = position2;
        this.position3 = position3;
        this.position4 = position4;
        this.position5 = position5;
    }

    public Participant getPosition1() {
        return position1;
    }

    public void setPosition1(Participant position1) {
        this.position1 = position1;
    }

    public Participant getPosition2() {
        return position2;
    }

    public void setPosition2(Participant position2) {
        this.position2 = position2;
    }

    public Participant getPosition3() {
        return position3;
    }

    public void setPosition3(Participant position3) {
        this.position3 = position3;
    }

    public Participant getPosition4() {
        return position4;
    }

    public void setPosition4(Participant position4) {
        this.position4 = position4;
    }

    public Participant getPosition5() {
        return position5;
    }

    public void setPosition5(Participant position5) {
        this.position5 = position5;
    }

    @Override
    public String toString() {
        return "Game{" +
                "position1=" + position1 +
                ", position2=" + position2 +
                ", position3=" + position3 +
                ", position4=" + position4 +
                ", position5=" + position5 +
                '}';
    }
}
