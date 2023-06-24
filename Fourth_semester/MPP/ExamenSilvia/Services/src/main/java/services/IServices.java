package services;

import model.Configuration;
import model.Game;
import model.User;

import java.util.Collection;

public interface IServices {
    User login(User user, IObserver client) throws ServicesException;
    void logout(User user, IObserver client) throws ServicesException;
    Game play(Game game) throws  ServicesException;
    Collection<Configuration> getAllConf() throws ServicesException;
}
