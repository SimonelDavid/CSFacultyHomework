package org.example.repository;

import org.example.Entity;

import java.io.Serializable;

public interface CrudRepository<ID extends Serializable, E extends Entity<ID>> {
    E findOne(ID id);
    Iterable<E> findAll();
    E save(E entity);
}
