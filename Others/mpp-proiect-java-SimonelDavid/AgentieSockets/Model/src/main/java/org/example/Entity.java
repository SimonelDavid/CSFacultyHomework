package org.example;

import java.io.Serializable;
import java.util.Objects;

public class Entity<ID> implements Serializable {
    private static final long serialVersionUID = 37846873547835478L;

    private ID id;

    public Entity(ID id) {
        this.id = id;
    }

    public ID getId() {
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Entity that = (Entity) o;
        return id.equals(that.id);
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException("Two users can't have the same id!");
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}
