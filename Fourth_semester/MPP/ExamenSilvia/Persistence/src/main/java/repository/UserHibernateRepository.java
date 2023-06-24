package repository;


import model.User;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import java.util.ArrayList;
import java.util.Collection;

public class UserHibernateRepository implements UserRepository {

    private SessionFactory sessionFactory;

    public UserHibernateRepository(SessionFactory sessionFactory){
        this.sessionFactory = sessionFactory;
    }

//    private void setIdCrud(Session session, User elem){
//        String findAllStmt = "from User";
//        Collection<User> users = session.createQuery(findAllStmt, User.class).list();
//        Integer maxi = null;
//        for(User conf: users){
//            if(maxi == null)
//                maxi = conf.getID();
//            else
//                maxi = max(maxi, conf.getID());
//        }
//        if(maxi != null)
//            elem.setID(maxi);
//    }

    @Override
    public User filterByUsernameAndPassword(User user) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                String findStmt = "from User where username = :username and password = :password";
                User searchedUser = session.createQuery(findStmt, User.class)
                        .setParameter("username", user.getUsername())
                        .setParameter("password", user.getPassword())
                        .setMaxResults(1)
                        .uniqueResult();
                System.out.println(searchedUser);
                tx.commit();
                return searchedUser;
            }catch (RuntimeException ex){
                System.err.println("Error occurred to filterByUsernameAndPassword method: " + ex.getMessage());
                if(tx != null)
                    tx.rollback();
                return null;
            }
        }
    }

    @Override
    public void add(User elem) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                session.save(elem);
//                setIdCrud(session, elem);
                tx.commit();
            }catch (RuntimeException ex){
                System.err.println("Error occurred to add method User: " + ex.getMessage());
                if(tx != null)
                    tx.rollback();
            }
        }
    }

    @Override
    public void delete(User elem) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx = null;
            tx = session.beginTransaction();
            try {
                String selectStmt = "from User where ID = :idUser";
                User deleteFlight = session.createQuery(selectStmt, User.class).setParameter("idUser", elem.getID())
                        .setMaxResults(1)
                        .uniqueResult();
                session.delete(deleteFlight);
                tx.commit();
            }
            catch (RuntimeException ex){
                System.err.println("Error occurred to delete method User: "+ ex.getMessage());
                if(tx != null)
                    tx.rollback();
            }
        }
    }

    @Override
    public void update(User elem, Integer id) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                User updatedUser = session.load(User.class, id);
                updatedUser.setUsername(elem.getUsername());
                updatedUser.setPassword(elem.getPassword());
                elem = updatedUser;  ///!!!IMPORTANT
                tx.commit();
            }catch (RuntimeException ex){
                System.err.println("Error occurred to update method User : " + ex.getMessage());
                if(tx != null)
                    tx.rollback();
            }
        }
    }

    @Override
    public User findByID(Integer id) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx = session.beginTransaction();
            try{
                String findStmt = "from User where ID = :idUser";
                User findFlight = session.createQuery(findStmt, User.class).setParameter("idUser", id)
                        .setMaxResults(1)
                        .uniqueResult();
                tx.commit();
                return findFlight;
            }
            catch (RuntimeException ex){
                System.err.println("Error occurred to findById method User : " + ex.getMessage());
                if(tx != null)
                    tx.rollback();
                return null;
            }
        }
    }

    @Override
    public Iterable<User> findAll() {
        return null;
    }

    @Override
    public Collection<User> getAll() {
        Collection<User> users = new ArrayList<>();
        try(Session session = sessionFactory.openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                users = session.createQuery("from User", User.class).list();
                tx.commit();
                return users;
            }catch (RuntimeException ex){
                System.err.println("Error occurred to getAll method User" + ex.getMessage());
                if(tx != null)
                    tx.rollback();
                return new ArrayList<>();
            }
        }
    }
}
