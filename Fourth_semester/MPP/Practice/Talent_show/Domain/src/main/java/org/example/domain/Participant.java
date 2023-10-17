package org.example.domain;

public class Participant extends Entity<Integer>{
    private String participant;

    public Participant(){}

    public Participant(String participant) {
        super();
        this.participant = participant;
    }

    public String getWord() {
        return participant;
    }

    public void setWord(String participant) {
        this.participant = participant;
    }


    @Override
    public String toString() {
        return "Participant{" +
                "id=" + id +
                ", participant='" + participant + '\'' +
                '}';
    }
}
