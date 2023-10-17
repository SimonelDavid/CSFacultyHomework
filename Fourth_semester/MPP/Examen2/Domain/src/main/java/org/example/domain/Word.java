package org.example.domain;

public class Word extends Entity<Integer>{
    private String word;

    public Word(){}

    public Word(String word) {
        super();
        this.word = word;
    }

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }


    @Override
    public String toString() {
        return "Word{" +
                "id=" + id +
                ", word='" + word + '\'' +
                '}';
    }
}
