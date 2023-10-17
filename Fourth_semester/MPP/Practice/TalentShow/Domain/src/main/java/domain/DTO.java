package domain;

import java.io.Serializable;

public class DTO extends Entity<Integer>implements Serializable {
    private Jurry jurry;
    private Integer seconds;
    private String raspuns;

    public DTO(Integer id, Jurry jurry, Integer seconds, String raspuns) {
        super(id);
        this.jurry = jurry;
        this.seconds = seconds;
        this.raspuns = raspuns;
    }

    public DTO(Jurry jurry, Integer seconds, String raspuns) {
        this.jurry = jurry;
        this.seconds = seconds;
        this.raspuns = raspuns;
    }

    public DTO() {
        this.jurry = null;
        this.seconds = null;
        this.raspuns = null;
    }

    public Jurry getJurry() {
        return jurry;
    }

    public void setJurry(Jurry jurry) {
        this.jurry = jurry;
    }

    public Integer getSeconds() {
        return seconds;
    }

    public void setSeconds(Integer seconds) {
        this.seconds = seconds;
    }

    public String getRaspuns() {
        return raspuns;
    }

    public void setRaspuns(String raspuns) {
        this.raspuns = raspuns;
    }
}
