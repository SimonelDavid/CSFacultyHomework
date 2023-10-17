package org.example.domain;


import java.io.Serializable;
import java.util.Objects;

/**
 * Class that represents an entity, in our case it will be a User or a Friendship
 */
public class Entity<ID> implements Serializable {
    /**
     * id of entity
     */
    protected ID id;

    /**
     * Id getter
     * @return ID
     */
    public ID getId() {
        return id;
    }

    /**
     * Comparison function that verifies if two objects of type Entity have the same id
     * @param o Object
     * @return true if they have the same id, false if classes do not correspond, or they do but have different ids
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Entity<?> entity)) return false;
        return Objects.equals(id, entity.id);
    }

    /**
     * Hashcode function
     * @return String
     */
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    /**
     * Forms a string out of an entity
     * @return String
     */
    @Override
    public String toString() {
        return "Entity{" + "id='" + id + '\'' + '}';
    }

    /**
     * Id setter
     * @param id ID
     */
    public void setId(ID id) {
        this.id = id;
    }
}
