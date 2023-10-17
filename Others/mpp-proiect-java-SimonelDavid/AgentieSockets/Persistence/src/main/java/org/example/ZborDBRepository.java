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

public class ZborDBRepository implements Repository<Integer, Zbor>{
    private JdbcUtils dbUtils;
    private static final Logger logger= LogManager.getLogger();

    public ZborDBRepository(Properties props) {
        logger.info("Initializing CarsDBRepository with properties: {} ",props);
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public Zbor findByID(Integer integer) throws IllegalArgumentException {
        logger.traceEntry("find by id task {}");
        Connection con = dbUtils.getConnection();
        Zbor rez = null;
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Zboruri where id = ?")){
            preparedStatement.setInt(1, integer);
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    String destinatie = resultSet.getString("destinatie");
                    String data = resultSet.getString("data");
                    String ora = resultSet.getString("ora");
                    String aeroport = resultSet.getString("aeroport");
                    Integer locuri = resultSet.getInt("locuri");
                    rez = new Zbor(integer, destinatie, data, ora, aeroport, locuri);
                }
            }
        }catch(SQLException e){
            logger.error(e);
            System.err.println("ERROR DB"+ e);
        }
        logger.traceExit(rez);
        return rez;
    }

    public Collection<Zbor> findByDestinatieData(String destinatie, String data) {
        logger.traceEntry("dinf by destinatie si data task {}");
        Connection con = dbUtils.getConnection();
        List<Zbor> rez = new ArrayList<>();
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Zboruri where destinatie = ? and data = ?")){
            preparedStatement.setString(1, destinatie);
            preparedStatement.setString(2, data);
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    Integer integer = resultSet.getInt("id");
                    String ora = resultSet.getString("ora");
                    String aeroport = resultSet.getString("aeroport");
                    Integer locuri = resultSet.getInt("locuri");
                    Zbor one = new Zbor(integer, destinatie, data, ora, aeroport, locuri);
                    if(locuri > 0)
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
    public Zbor findByPredicate(Predicate<Zbor> predicate) throws IllegalArgumentException {
        logger.traceEntry("find by predicate task {}");
        Connection con = dbUtils.getConnection();
        Zbor rez = null;
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Zboruri")){
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    Integer integer = resultSet.getInt("id");
                    String destinatie = resultSet.getString("destinatie");
                    String data = resultSet.getString("data");
                    String ora = resultSet.getString("ora");
                    String aeroport = resultSet.getString("aeroport");
                    Integer locuri = resultSet.getInt("locuri");
                    Zbor one = new Zbor(integer, destinatie, data, ora, aeroport, locuri);
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
    public Collection<Zbor> findAll() {
        logger.traceEntry("findall task {}");
        Connection con = dbUtils.getConnection();
        List<Zbor> rez = new ArrayList<>();
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Zboruri")){
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    Integer integer = resultSet.getInt("id");
                    String destinatie = resultSet.getString("destinatie");
                    String data = resultSet.getString("data");
                    String ora = resultSet.getString("ora");
                    String aeroport = resultSet.getString("aeroport");
                    Integer locuri = resultSet.getInt("locuri");
                    Zbor one = new Zbor(integer, destinatie, data, ora, aeroport, locuri);
                    if(locuri > 0)
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
    public Zbor save(Zbor entity) throws IllegalArgumentException {
        logger.traceEntry("saving task {}", entity);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preparedStatement=con.prepareStatement("insert into Zboruri(destinatie, data, ora, aeroport, locuri) values (?,?,?,?,?)")){
            preparedStatement.setString(1, entity.getDestinatie());
            preparedStatement.setString(2, entity.getData());
            preparedStatement.setString(3, entity.getOra());
            preparedStatement.setString(4, entity.getAeroport());
            preparedStatement.setInt(5, entity.getLocuri());
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
    public Zbor update(Integer integer, Zbor entity) throws IllegalArgumentException {
        logger.traceEntry("update task {}", entity);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preparedStatement=con.prepareStatement("update Zboruri set destinatie = ?, data = ?, ora = ?, aeroport = ?, locuri = ? where id = ?")){
            preparedStatement.setString(1, entity.getDestinatie());
            preparedStatement.setString(2, entity.getData());
            preparedStatement.setString(3, entity.getOra());
            preparedStatement.setString(4, entity.getAeroport());
            preparedStatement.setInt(5, entity.getLocuri());
            preparedStatement.setInt(6, integer);
            int result = preparedStatement.executeUpdate();
        }catch(SQLException ex){
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return entity;
    }
}
