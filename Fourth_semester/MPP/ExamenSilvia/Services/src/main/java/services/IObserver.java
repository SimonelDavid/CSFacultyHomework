package services;

import model.Game;

import java.util.Collection;

public interface IObserver {
    //    the input param refers to the data with which they will be notified
    void endGame(Collection<Game> games) throws ServicesException;
}
