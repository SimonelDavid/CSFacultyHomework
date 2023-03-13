package examen.examensimon.utils.observer;

import examen.examensimon.utils.utils.Event;

public interface Observable<E extends Event> {
    void addObserver(Observer<E> observer);
    void removeObserver(Observer<E> observer);
    void notifyObservers(E event);
}

