package org.example.repo;

import org.example.domain.Game;
import org.example.domain.User;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class GameRepository implements IGameRepository{

    @Override
    public Game add(Game entity) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                session.save(entity);
                tx.commit();
            } catch (RuntimeException ex) {
                if (tx != null)
                    tx.rollback();
            }
        }
        return entity;
    }

    @Override
    public Iterable<Game> getAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                List<Game> o = session.createQuery("from Game", Game.class).list();
                tx.commit();
                return o;
            } catch (RuntimeException ex) {
                if (tx != null)
                    tx.rollback();
                return null;
            }
        }
    }

    @Override
    public int sizee() {
        return 0;
    }

    @Override
    public void remove(Integer id) {
        try(Session session = HibernateUtils.getSessionFactory().openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                Game game = session.get(Game.class, id);
                session.delete(game);
                tx.commit();
            }
            catch(RuntimeException ex){
                if (tx!=null)
                    tx.rollback();
            }
        }
    }

    @Override
    public void update(Game entity) throws Exception {
        try(Session session = HibernateUtils.getSessionFactory().openSession()){
            try{
                session.beginTransaction();
                session.update(entity);
                session.getTransaction().commit();
            }catch (RuntimeException ex){
                session.getTransaction().rollback();
                System.err.println(ex.getMessage());
            }
        }
    }

    @Override
    public Game getById(int id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Transaction tx = null;
            try {
                tx = session.beginTransaction();
                Game game = session.get(Game.class, id);
                tx.commit();
                return game;
            } catch (RuntimeException ex) {
                if (tx != null)
                    tx.rollback();
                return null;
            }
        }
    }

    @Override
    public Iterable<Game> getAllGamesOfPlayer(Integer id) throws Exception {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Transaction tx = null;
            try {
                tx = session.beginTransaction();
                List<Game> games = session.createQuery("from Game where idplayer = :id", Game.class)
                        .setParameter("id", id)
                        .list();
                tx.commit();
                return games;
            } catch (RuntimeException ex) {
                if (tx != null)
                    tx.rollback();
                return null;
            }
        }
    }
}
