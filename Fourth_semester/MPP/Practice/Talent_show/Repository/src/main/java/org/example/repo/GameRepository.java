package org.example.repo;

import org.example.domain.Rezultate;
import org.example.domain.Jurry;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class GameRepository implements IGameRepository{

    @Override
    public Rezultate add(Rezultate entity) {
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
    public Iterable<Rezultate> getAll() {
        try (Session session = HibernateUtils.getSessionFactory().openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                List<Rezultate> o = session.createQuery("from Rezultate", Rezultate.class).list();
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
                Rezultate game = session.get(Rezultate.class, id);
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
    public void update(Rezultate entity) throws Exception {
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
    public Rezultate getById(int id) {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Transaction tx = null;
            try {
                tx = session.beginTransaction();
                Rezultate game = session.get(Rezultate.class, id);
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
    public Iterable<Rezultate> getAllGamesOfPlayer(Integer id) throws Exception {
        try (Session session = HibernateUtils.getSessionFactory().openSession()) {
            Transaction tx = null;
            try {
                tx = session.beginTransaction();
                List<Rezultate> games = session.createQuery("from Rezultate where jurry_id = :id", Rezultate.class)
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
