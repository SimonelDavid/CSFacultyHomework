package org.example.service;

import org.example.domain.Config;
import org.example.domain.Rezultate;
import org.example.domain.Jurry;

public interface IService {
    Jurry getByMailPassword(String nume, String password, IObserver client) throws Exception;
    void logout(Jurry user, IObserver client) throws Exception;
    Config addConfig() throws Exception;
    Iterable<Rezultate> getAllGames() throws Exception;
}
