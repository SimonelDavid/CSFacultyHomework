package org.example.domain;

import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;

@javax.persistence.Entity
@Table(name = "Rezultate")
public class Rezultate extends Entity<Integer>{
    private Integer jurry_id;
    private Integer participant_id;
    private String raspuns;

    public Rezultate(){}

    public Rezultate(Integer jurry_id, Integer participant_id, String raspuns) {
        super();
        this.jurry_id = jurry_id;
        this.participant_id = participant_id;
        this.raspuns = raspuns;
    }

    @Column(name = "jurry_id")
    public Integer getIdPlayer() {
        return jurry_id;
    }

    public void setIdPlayer(Integer jurry_id) {
        this.jurry_id = jurry_id;
    }

    @Column(name = "participant_id")
    public Integer getIdConfig() {
        return participant_id;
    }

    public void setIdConfig(Integer participant_id) {
        this.participant_id = participant_id;
    }

    @Column(name = "raspuns")
    public String getPlayerInput() {
        return raspuns;
    }

    public void setPlayerInput(String raspuns) {
        this.raspuns = raspuns;
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
        return "Rezultate{" +
                "jurry_id=" + jurry_id +
                ", participant_id='" + participant_id + '\'' +
                ", raspuns='" + raspuns + '\'' +
                ", id=" + id +
                '}';
    }
}
