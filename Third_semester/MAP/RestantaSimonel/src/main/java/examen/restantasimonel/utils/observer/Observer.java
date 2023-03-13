package examen.restantasimonel.utils.observer;

import examen.restantasimonel.utils.utils.Event;

public interface Observer<E extends Event> {
    void update(E event);
}
