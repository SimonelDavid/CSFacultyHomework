package org.example.repo;

import org.example.domain.Jurry;

public interface IUserRepository extends IRepository<Integer, Jurry> {
    Jurry getByMailPassword(String mail, String password);
    void updatee(Jurry user, Integer id) throws Exception;
    Iterable<Jurry> getAllWinners() throws Exception;
}
