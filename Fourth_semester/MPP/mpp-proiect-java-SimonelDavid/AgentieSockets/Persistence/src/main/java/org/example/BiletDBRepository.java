package org.example;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Properties;
import java.util.function.Predicate;

public class BiletDBRepository implements Repository<Integer, Bilet>{
    private JdbcUtils dbUtils;
    private static final Logger logger= LogManager.getLogger();

    public BiletDBRepository(Properties props) {
        logger.info("Initializing CarsDBRepository with properties: {} ",props);
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public Bilet findByID(Integer integer) throws IllegalArgumentException {
        logger.traceEntry("find by id task {}");
        Connection con = dbUtils.getConnection();
        Bilet rez = null;
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Bilete where id = ?")){
            preparedStatement.setInt(1, integer);
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    String client = resultSet.getString("client");
                    String turisti = resultSet.getString("turisti");
                    String adresa = resultSet.getString("parola");
                    Integer locuri = resultSet.getInt("parola");
                    rez = new Bilet(integer, client, turisti, adresa, locuri);
                }
            }
        }catch(SQLException e){
            logger.error(e);
            System.err.println("ERROR DB"+ e);
        }
        logger.traceExit(rez);
        return rez;
    }

    @Override
    public Bilet findByPredicate(Predicate<Bilet> predicate) throws IllegalArgumentException {
        logger.traceEntry("find by predicate task {}");
        Connection con = dbUtils.getConnection();
        Bilet rez = null;
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Bilete")){
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    Integer integer = resultSet.getInt("id");
                    String client = resultSet.getString("client");
                    String turisti = resultSet.getString("turisti");
                    String adresa = resultSet.getString("parola");
                    Integer locuri = resultSet.getInt("parola");
                    Bilet one = new Bilet(integer, client, turisti, adresa, locuri);
                    if(predicate.test(one))
                        rez = one;
                }
            }
        }catch(SQLException e){
            logger.error(e);
            System.err.println("ERROR DB"+ e);
        }
        logger.traceExit(rez);
        return rez;
    }

    @Override
    public Collection<Bilet> findAll() {
        logger.traceEntry("findall task {}");
        Connection con = dbUtils.getConnection();
        List<Bilet> rez = new ArrayList<>();
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Bilete")){
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    Integer integer = resultSet.getInt("id");
                    String client = resultSet.getString("client");
                    String turisti = resultSet.getString("turisti");
                    String adresa = resultSet.getString("adresa");
                    Integer locuri = resultSet.getInt("locuri");
                    Bilet one = new Bilet(integer, client, turisti, adresa, locuri);
                    rez.add(one);
                }
            }
        }catch(SQLException e){
            logger.error(e);
            System.err.println("ERROR DB"+ e);
        }
        logger.traceExit(rez);
        return rez;
    }

    @Override
    public Bilet save(Bilet entity) throws IllegalArgumentException {
        logger.traceEntry("saving task {}", entity);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preparedStatement=con.prepareStatement("insert into Bilete(client, turisti, adresa, locuri) values (?,?,?,?)")){
            preparedStatement.setString(1, entity.getClient());
            preparedStatement.setString(2, entity.getTuristi());
            preparedStatement.setString(3, entity.getAdresa());
            preparedStatement.setInt(4, entity.getLocuri());
            int result=preparedStatement.executeUpdate();
            logger.trace("Saved {} instances",result);
        }
        catch(SQLException ex){
            logger.error(ex);
            System.err.println("ERROR DB "+ex);
        }
        logger.traceExit();
        return entity;
    }

    @Override
    public Bilet update(Integer integer, Bilet entity) throws IllegalArgumentException {
        logger.traceEntry("update task {}", entity);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preparedStatement=con.prepareStatement("update Angajati set client = ?, turisti = ?, adresa = ?, locuri = ? where id = ?")){
            preparedStatement.setString(1, entity.getClient());
            preparedStatement.setString(2, entity.getTuristi());
            preparedStatement.setString(3, entity.getAdresa());
            preparedStatement.setInt(4, entity.getLocuri());
            preparedStatement.setInt(5, integer);
            int result = preparedStatement.executeUpdate();
        }catch(SQLException ex){
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return entity;
    }
}
