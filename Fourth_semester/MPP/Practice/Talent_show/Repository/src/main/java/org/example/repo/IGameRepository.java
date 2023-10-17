package org.example.repo;

import org.example.domain.Rezultate;

public interface IGameRepository extends IRepository<Integer, Rezultate> {
    Iterable<Rezultate> getAllGamesOfPlayer(Integer id) throws Exception;
}
