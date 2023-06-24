package repository;

import model.Identifiable;

import java.util.Collection;

public interface Repository<T extends Identifiable<TID>, TID> {
    void add(T elem);
    void delete(T elem);
    void update(T elem,TID id);
    T findByID(TID id);
    Iterable<T> findAll();
    Collection<T> getAll();
}
