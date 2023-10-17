package app.rest.persistance.repository;

import domain.Entity;
import domain.Rezultat;

import java.io.Serializable;

public interface IScoreRepository<ID extends Serializable, E extends Entity<ID>> extends IRepository<ID, E> {
    Rezultat getLatestScoreForPlayer(Integer idPlayer);
    ID getMaxId();
}
