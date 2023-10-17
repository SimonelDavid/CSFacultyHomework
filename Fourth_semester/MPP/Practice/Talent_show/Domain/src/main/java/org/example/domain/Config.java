package org.example.domain;

public class Config extends Entity<Integer>{
    private String idwords;

    public Config(){}

    public Config(String idwords) {
        super();
        this.idwords = idwords;
    }

    public String getIdwords() {
        return idwords;
    }

    public void setIdwords(String idwords) {
        this.idwords = idwords;
    }

    @Override
    public String toString() {
        return "Config{" +
                ", idwords='" + idwords + '\'' +
                ", id=" + id +
                '}';
    }
}
