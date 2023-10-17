package domain;

import javax.persistence.Table;

import javax.persistence.AttributeOverride;
import javax.persistence.Column;
import java.io.Serializable;

@javax.persistence.Entity
@Table(name = "jurry")
@AttributeOverride(name = "id", column = @Column(name = "jurry_id"))
public class Jurry extends Entity<Integer> implements Serializable {
    private String alias;

    public Jurry(Integer id, String alias) {
        super(id);
        this.alias = alias;
    }

    public Jurry(String alias) {
        this.alias = alias;
    }

    public Jurry() {
        this.alias = null;
    }

    public String getAlias() {
        return alias;
    }

    public void setAlias(String alias) {
        this.alias = alias;
    }

    @Override
    public String toString() {
        return  alias;
    }

}
