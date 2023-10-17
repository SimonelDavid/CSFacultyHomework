package org.example.repo;

import org.example.domain.Entity;
import org.example.domain.Rezultate;

/**
 * Interface for repository
 * @param <EntityType>
 */
public interface IRepository<ID, EntityType extends Entity<ID>> {
    EntityType add(EntityType entity);
    void remove(ID id);
    void update(EntityType entity) throws Exception;
    EntityType getById(int id);
    Iterable<EntityType> getAll();
    int sizee();
}

