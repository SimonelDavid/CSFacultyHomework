package org.example.service;

import org.example.domain.Config;
import org.example.domain.Game;
import org.example.domain.User;

public interface IService {
    User getByMailPassword(String email, String password, IObserver client) throws Exception;
    void logout(User user, IObserver client) throws Exception;
    Config addConfig() throws Exception;
    Iterable<Game> getAllGames() throws Exception;
}
