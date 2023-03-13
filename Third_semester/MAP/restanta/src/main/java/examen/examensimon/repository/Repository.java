package examen.examensimon.repository;

import examen.examensimon.domain.Entity;

public interface Repository<ID, E extends Entity<ID>> {

    E find(ID id) throws IllegalArgumentException;
    Iterable<E> getAll();
}