package org.example.repo;

import org.example.domain.Game;

public interface IGameRepository extends IRepository<Integer, Game> {
    Iterable<Game> getAllGamesOfPlayer(Integer id) throws Exception;
}
