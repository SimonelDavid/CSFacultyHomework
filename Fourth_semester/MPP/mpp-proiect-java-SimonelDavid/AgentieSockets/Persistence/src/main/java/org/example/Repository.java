package org.example;

import java.util.Collection;
import java.util.function.Predicate;

public interface Repository<ID, E extends Entity<ID>> {
    E findByID(ID id) throws IllegalArgumentException;

    E findByPredicate(Predicate<E> predicate) throws IllegalArgumentException;

    Collection<E> findAll();

    E save(E entity) throws IllegalArgumentException;

    //E remove(ID id) throws IllegalArgumentException;

    E update(ID id, E entity) throws IllegalArgumentException;
}
