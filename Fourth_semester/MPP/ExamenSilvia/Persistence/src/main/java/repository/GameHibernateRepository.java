package repository;

import model.Game;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.Collection;

@Component
public class GameHibernateRepository implements GameRepository {
    private SessionFactory sessionFactory;

    @Autowired
    public GameHibernateRepository(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }


//    private void setIdCrud(Session session, Game elem) {
//        String findStmt = "from Game";
//        Collection<Game> games = session.createQuery(findStmt, Game.class).list();
//        Integer maxi = null;
//        for (Game conf : games) {
//            if (maxi == null)
//                maxi = conf.getID();
//            else
//                maxi = max(maxi, conf.getID());
//        }
//        if (maxi != null)
//            elem.setID(maxi);
//    }


        @Override
    public void add(Game elem) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                session.save(elem);
//                setIdCrud(session, elem);
                tx.commit();
            }catch (RuntimeException ex){
                System.err.println("Error occurred to add method: " + ex.getMessage());
                if(tx != null)
                    tx.rollback();
            }
        }
    }

    @Override
    public void delete(Game elem) {

    }

    @Override
    public void update(Game elem, Integer id) {
    }

    @Override
    public Game findByID(Integer id) {
        return null;
    }

    @Override
    public Iterable<Game> findAll() {
        return null;
    }

    @Override
    public Collection<Game> getAll() {
        Collection<Game> games = new ArrayList<>();
        try(Session session = sessionFactory.openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                games = session.createQuery("from Game", Game.class).list();
                tx.commit();
                return games;
            }catch (RuntimeException ex){
                System.err.println("Error occurred to getAll " + ex.getMessage());
                if(tx != null)
                    tx.rollback();
                return new ArrayList<>();
            }
        }
    }
}
