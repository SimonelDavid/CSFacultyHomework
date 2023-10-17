package org.example.repo;

import org.example.domain.Config;
import org.example.domain.Jurry;

public interface IConfigRepository extends IRepository<Integer, Config> {
    void updatee(Config entity, Integer id) throws Exception;
}
