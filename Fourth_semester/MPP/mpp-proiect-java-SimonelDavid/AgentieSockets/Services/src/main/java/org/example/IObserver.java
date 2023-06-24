package org.example;

import java.util.Collection;
import java.util.List;

public interface IObserver {
    void updateLista(List<Zbor> l1, List<Zbor> l2) throws AgentieException;
}
