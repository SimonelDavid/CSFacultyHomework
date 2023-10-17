package app.rest.persistance.repository.jdbc;

import app.rest.persistance.repository.IPositionRepository;
import domain.Participant;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import org.springframework.stereotype.Component;

import java.util.List;

@Component()
public class PositionORMDBIRepository implements IPositionRepository<Integer, Participant> {

    private  static SessionFactory sessionFactory;
    public PositionORMDBIRepository(){
        initialize();
    }
    public void initialize() {
        // A SessionFactory is set up once for an application!
        final StandardServiceRegistry registry = new StandardServiceRegistryBuilder()
                .configure() // configures settings from hibernate.cfg.xml
                .build();
        try {
            sessionFactory = new MetadataSources(registry).buildMetadata().buildSessionFactory();
        } catch (Exception e) {
            System.out.println("Exceptie " + e);
            StandardServiceRegistryBuilder.destroy(registry);
        }
    }
    private static final Logger logger= LogManager.getLogger();

    @Override
    public Participant findById(Integer id) {
        logger.traceEntry("find an participant by id");
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try {
                transaction=session.beginTransaction();
                Participant game =session.createQuery("from Participant where id=:id", Participant.class)
                        .setParameter("id",id)
                        .setMaxResults(1)
                        .uniqueResult();
                transaction.commit();
                logger.traceExit(game);
                return game;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
                logger.error("ERROR for findById, with id = " + id+", in PositionORMDBIRepository: " + ex);
            }

        }
        return null;
    }

    @Override
    public Participant findByRowCol(int nume, int prenume){
        logger.traceEntry("find an participant by nume and prenume");
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try {
                transaction=session.beginTransaction();
                Participant game =session.createQuery("from Participant where nume=:nume and prenume=:prenume", Participant.class)
                        .setParameter("nume",nume)
                        .setParameter("prenume",prenume)
                        .setMaxResults(1)
                        .uniqueResult();
                transaction.commit();
                logger.traceExit(game);
                return game;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
                logger.error("ERROR for findByRowCol, with nume = " + nume + " and prenume = " + prenume + ", in PositionORMDBIRepository: " + ex);
            }

        }
        return null;
    }

    @Override
    public Iterable<Participant> getAll() {
        logger.traceEntry("find all employees");
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try{
                transaction=session.beginTransaction();
                List<Participant> games =session.createQuery("from Participant", Participant.class)
                        .list();
                transaction.commit();
                logger.traceExit(games);
                return games;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
                logger.error("ERROR for getAll in GameORMDBIRepository: " + ex);
            }
        }
        return null;
    }

    @Override
    public boolean add(Participant participant) {
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try{
                transaction=session.beginTransaction();
                session.save(participant);
                transaction.commit();
                logger.trace("saved {} instance", participant);
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
                logger.error("ERROR for insert in PositionORMDBIRepository: " + ex);
            }
        }
        logger.traceExit("inserted successfully");
        return true;
    }


    @Override
    public boolean update(Participant participant) {
        logger.traceEntry("updating participant");
        try(Session session = sessionFactory.openSession()){
            Transaction tx=null;
            try{
                tx = session.beginTransaction();
                session.update(participant);
                tx.commit();
                logger.traceExit("updated successfully");
                return true;
            } catch(RuntimeException ex){
                if (tx!=null)
                    tx.rollback();
                logger.error("ERROR for update in PositionORMDBIRepository: " + ex);
            }
        }
        return true;
    }

    @Override
    public Integer getMaxId() {
        logger.traceEntry("get max id for participant");
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try{
                transaction=session.beginTransaction();
                Integer maxId =session.createQuery("select max(id) from Participant", Integer.class)
                        .uniqueResult();
                transaction.commit();
                logger.traceExit(maxId);
                return maxId;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
                logger.error("ERROR for getMaxId in PositionORMDBIRepository: " + ex);
            }
        }
        return null;
    }
}
