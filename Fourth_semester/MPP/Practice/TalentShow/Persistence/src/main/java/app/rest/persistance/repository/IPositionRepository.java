package app.rest.persistance.repository;

import domain.Entity;
import domain.Participant;

import java.io.Serializable;

public interface IPositionRepository<ID extends Serializable, E extends Entity<ID>> extends IRepository<ID, E> {
    ID getMaxId();
    Participant findByRowCol(int nume, int prenume);
}
