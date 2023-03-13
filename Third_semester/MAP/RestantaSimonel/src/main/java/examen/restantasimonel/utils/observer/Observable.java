package examen.restantasimonel.utils.observer;

import examen.restantasimonel.utils.utils.Event;

public interface Observable<E extends Event> {
    void addObserver(Observer<E> observer);
    void removeObserver(Observer<E> observer);
    void notifyObservers(E event);
}

