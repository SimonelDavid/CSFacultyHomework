package org.example.repo;

import org.example.domain.Config;
import org.example.domain.User;

public interface IConfigRepository extends IRepository<Integer, Config> {
    void updatee(Config entity, Integer id) throws Exception;
}
