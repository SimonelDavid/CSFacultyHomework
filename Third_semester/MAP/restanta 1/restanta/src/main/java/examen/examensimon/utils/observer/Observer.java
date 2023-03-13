package examen.examensimon.utils.observer;

import examen.examensimon.utils.utils.Event;

public interface Observer<E extends Event> {
    void update(E event);
}
