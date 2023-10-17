package domain;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalTime;

@javax.persistence.Entity
@Table(name = "rezultat")
@AttributeOverride(name = "id", column = @Column(name = "rezultat_id"))
public class Rezultat extends Entity<Integer>implements Serializable {
    @ManyToOne
    @JoinColumn(name = "player_id")
    private Jurry jurry;
    @ManyToOne
    @JoinColumn(name = "position_id")
    private Participant participant;
    private String raspuns;

    public Rezultat() {
    }

    public Rezultat(Integer id, Jurry jurry, Participant participant, String raspuns) {
        super(id);
        this.jurry = jurry;
        this.participant = participant;
        this.raspuns = raspuns;
    }


    public Rezultat(Jurry jurry, Participant participant, String raspuns) {
        this.jurry = jurry;
        this.participant = participant;
        this.raspuns = raspuns;
    }

    public Jurry getJurry() {
        return jurry;
    }

    public void setJurry(Jurry jurry) {
        this.jurry = jurry;
    }

    public Participant getGuess() {
        return participant;
    }

    public void setGuess(Participant participant) {
        this.participant = participant;
    }

    public String getParticipant() {
        return raspuns;
    }

    public void setParticipant(String raspuns) {
        this.raspuns = raspuns;
    }
}
