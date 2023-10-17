package domain;

import javax.persistence.AttributeOverride;
import javax.persistence.Column;
import javax.persistence.Table;
import java.io.Serializable;

@javax.persistence.Entity
@Table(name = "participant")
@AttributeOverride(name = "id", column = @Column(name = "participant_id"))
public class Participant extends Entity<Integer>implements Serializable {

    @Column(name = "nume")
    private String nume;
    @Column(name = "prenume")
    private String prenume;

    public Participant(Integer integer, String nume, String prenume) {
        super(integer);
        this.nume = nume;
        this.prenume = prenume;
    }

    public Participant(String nume, String prenume) {
        this.nume = nume;
        this.prenume = prenume;
    }

    public Participant() {
        this.nume = null;
        this.prenume = null;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    @Override
    public String toString() {
        return "(" + nume + ", " + prenume + ")";
    }
}
