package repository;


import model.Configuration;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.Collection;

@Component
public class ConfigurationHibernateRepository implements ConfigurationRepository {

    private SessionFactory sessionFactory;

    @Autowired
    public ConfigurationHibernateRepository(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

//
//    private void setIdCrud(Session session, Configuration elem){
//        String findStmt = "from Configuration ";
//        Collection<Configuration> games = session.createQuery(findStmt, Configuration.class).list();
//        Integer maxi = null;
//        for(Configuration conf: games){
//            if(maxi == null)
//                maxi = conf.getID();
//            else
//                maxi = max(maxi, conf.getID());
//        }
//        if(maxi != null)
//            elem.setID(maxi);
//    }

    @Override
    public void add(Configuration elem) {
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
    public void delete(Configuration elem) {
    }

    @Override
    public void update(Configuration elem, Integer id) {

    }

    @Override
    public Configuration findByID(Integer id) {
        return null;
    }

    @Override
    public Iterable<Configuration> findAll() {
        return null;
    }

    @Override
    public Collection<Configuration> getAll() {
        Collection<Configuration> configurations = new ArrayList<>();
        try(Session session = sessionFactory.openSession()){
            Transaction tx = null;
            try{
                tx = session.beginTransaction();
                configurations = session.createQuery("from Configuration ", Configuration.class).list();
                tx.commit();
                return configurations;
            }catch (RuntimeException ex){
                System.err.println("Error occurred to getAll " + ex.getMessage());
                if(tx != null)
                    tx.rollback();
                return new ArrayList<>();
            }
        }
    }
}
