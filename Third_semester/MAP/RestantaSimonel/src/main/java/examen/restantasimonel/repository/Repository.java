package examen.restantasimonel.repository;

import examen.restantasimonel.domain.Entity;

public interface Repository<ID, E extends Entity<ID>> {

    E find(ID id) throws IllegalArgumentException;
    Iterable<E> getAll();
}