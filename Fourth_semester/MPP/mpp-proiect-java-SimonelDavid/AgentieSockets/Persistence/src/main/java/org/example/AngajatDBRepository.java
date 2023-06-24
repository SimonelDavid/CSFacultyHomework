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

public class AngajatDBRepository implements Repository<Integer, Angajat>{
    private JdbcUtils dbUtils;
    private static final Logger logger= LogManager.getLogger();

    public AngajatDBRepository(Properties props) {
        logger.info("Initializing CarsDBRepository with properties: {} ",props);
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public Angajat findByID(Integer integer) throws IllegalArgumentException {
        logger.traceEntry("find by id task {}");
        Connection con = dbUtils.getConnection();
        Angajat rez = null;
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Angajati where id = ?")){
            preparedStatement.setInt(1, integer);
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    String nume = resultSet.getString("nume");
                    String parola = resultSet.getString("parola");
                    rez = new Angajat(integer, nume, parola);
                }
            }
        }catch(SQLException e){
            logger.error(e);
            System.err.println("ERROR DB"+ e);
        }
        logger.traceExit(rez);
        return rez;
    }

    public Angajat findByNumeParola(String nume, String parola) throws IllegalArgumentException {
        logger.traceEntry("find by nume parola task {}");
        Connection con = dbUtils.getConnection();
        Angajat rez = null;
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Angajati where nume = ? and parola = ?")){
            preparedStatement.setString(1, nume);
            preparedStatement.setString(2, parola);
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    Integer id = resultSet.getInt("id");
                    rez = new Angajat(id, nume, parola);
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
    public Angajat findByPredicate(Predicate<Angajat> predicate) throws IllegalArgumentException {
        logger.traceEntry("find by predicate task {}");
        Connection con = dbUtils.getConnection();
        Angajat rez = null;
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Angajati")){
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    Integer integer = resultSet.getInt("id");
                    String nume = resultSet.getString("nume");
                    String parola = resultSet.getString("parola");
                    Angajat one = new Angajat(integer, nume, parola);
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
    public Collection<Angajat> findAll() {
        logger.traceEntry("findall task {}");
        Connection con = dbUtils.getConnection();
        List<Angajat> rez = new ArrayList<>();
        try(PreparedStatement preparedStatement=con.prepareStatement("select * from Angajati")){
            try(ResultSet resultSet=preparedStatement.executeQuery()){
                while(resultSet.next()) {
                    Integer id = resultSet.getInt("id");
                    String nume = resultSet.getString("nume");
                    String parola = resultSet.getString("parola");
                    Angajat one = new Angajat(id, nume, parola);
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
    public Angajat save(Angajat entity) throws IllegalArgumentException {
        logger.traceEntry("saving task {}", entity);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preparedStatement=con.prepareStatement("insert into Angajati(nume, parola) values (?,?)")){
            preparedStatement.setString(1, entity.getNume());
            preparedStatement.setString(2, entity.getParola());
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
    public Angajat update(Integer integer, Angajat entity) throws IllegalArgumentException {
        logger.traceEntry("update task {}", entity);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preparedStatement=con.prepareStatement("update Angajati set nume = ?, parola = ? where id = ?")){
            preparedStatement.setString(1, entity.getNume());
            preparedStatement.setString(2, entity.getParola());
            preparedStatement.setInt(3, integer);
            int result = preparedStatement.executeUpdate();
        }catch(SQLException ex){
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return entity;
    }
}
