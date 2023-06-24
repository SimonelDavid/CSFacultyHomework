package model;

import org.hibernate.annotations.GenericGenerator;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Table(name = "configurations")
public class Configuration implements Serializable, Identifiable<Integer> {
    private Integer ID;
    private String actualWord;
    private String codedWord;


    public Configuration(){}

    public Configuration(Integer ID, String actualWord, String codedWord) {
        this.ID = ID;
        this.actualWord = actualWord;
        this.codedWord = codedWord;
    }

    public Configuration(String actualWord, String codedWord) {
        this.actualWord = actualWord;
        this.codedWord = codedWord;
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

    public String getActualWord() {
        return actualWord;
    }

    public void setActualWord(String actualWord) {
        this.actualWord = actualWord;
    }

    public String getCodedWord() {
        return codedWord;
    }

    public void setCodedWord(String codedWord) {
        this.codedWord = codedWord;
    }
}
