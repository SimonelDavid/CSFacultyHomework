package repository;

import model.User;

public interface UserRepository extends Repository<User, Integer>{
    User filterByUsernameAndPassword(User user);
}
