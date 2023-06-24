package org.example.repo;

import org.example.domain.User;

public interface IUserRepository extends IRepository<Integer, User> {
    User getByMailPassword(String mail, String password);
    void updatee(User user, Integer id) throws Exception;
    Iterable<User> getAllWinners() throws Exception;
}
