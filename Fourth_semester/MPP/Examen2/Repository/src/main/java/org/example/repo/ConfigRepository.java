package org.example.repo;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.domain.Config;
import org.example.domain.User;
import org.springframework.stereotype.Component;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

@Component
public class ConfigRepository implements IConfigRepository {
    private final JdbcUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public ConfigRepository(){
        Properties props=new Properties();
        try {
            props.load(new FileReader("server.properties"));
            System.out.println(props);
        } catch (IOException e) {
            System.out.println("Cannot find server.properties "+e);
            System.out.println(new File(".").getAbsolutePath());
        }
        dbUtils = new JdbcUtils(props);
    }
    public ConfigRepository(Properties props) {
        logger.info("Initializing org.example.repo.PointRepository with properties: {} ", props);
        dbUtils = new JdbcUtils(props);
    }
    @Override
    public Config add(Config entity) {
        String sql = "INSERT INTO \"Configs\"(idwords) VALUES(?)";
        logger.traceEntry("saving config {} ", entity);
        Connection con = dbUtils.getConnection();
        String generatedColumns[] = { "id" };
        try(PreparedStatement ps = con.prepareStatement(sql, generatedColumns)) {
            ps.setString(1, entity.getIdwords());
            int noRows = ps.executeUpdate();
            try(ResultSet result = ps.getGeneratedKeys()){
                if(result.next()){
                    int id = result.getInt(1);
                    entity.setId((int)id);
                    logger.trace("Saved {} configs", noRows);
                    return entity;
                } else {
                    return null;
                }
            }
        }catch (SQLException ex) {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return null;
    }

    @Override
    public void remove(Integer id) {
        String sql = "DELETE FROM \"Config\" WHERE id = ?";
        logger.traceEntry("deleting config");
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement(sql)){
            preStmt.setInt(1, id);
            int result= preStmt.executeUpdate();
            logger.trace("Deleted config");
        }catch (SQLException ex){
            logger.error(ex);
            System.err.println("Error DB " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void update(Config entity) throws Exception {
    }

    @Override
    public Config getById(int id) {
        String sql = "SELECT * FROM \"Configs\" WHERE id = ?";
        logger.traceEntry("finding config with the id {} ", id);
        Connection con = dbUtils.getConnection();
        try (PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setInt(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if(rs.next()) {
                    int idd = rs.getInt("id");
                    String idwords = rs.getString("idwords");
                    Config entity = new Config(idwords);
                    entity.setId(idd);
                    logger.trace("Found {} config", rs);
                    return entity;
                }
            }
        } catch (SQLException ex) {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return null;
    }


    @Override
    public Iterable<Config> getAll() {
        String sql = "SELECT * FROM \"Configs\"";
        logger.traceEntry("finding all configs");
        Connection con= dbUtils.getConnection();
        List<Config> entities = new ArrayList<>();
        try(PreparedStatement ps = con.prepareStatement(sql)) {
            try(ResultSet rs = ps.executeQuery()) {
                while(rs.next()) {
                    int idd = rs.getInt("id");
                    String idwords = rs.getString("idwords");
                    Config entity = new Config(idwords);
                    entity.setId(idd);
                    entities.add(entity);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
            System.err.println("Error DB " + e);
        }
        logger.traceExit(entities);
        return entities;
    }

    @Override
    public int sizee() {
        List<Config> all= (List<Config>)getAll();
        return all.size();
    }

    @Override
    public void updatee(Config entity, Integer id) throws Exception {
        String sql = "UPDATE \"Configs\" SET idwords = ? WHERE id = ?";
        logger.traceEntry("updating config {} ", entity);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement(sql)){
            preStmt.setString(1, entity.getIdwords());
            preStmt.setInt(2, id);
            int result= preStmt.executeUpdate();
            logger.trace("Updated {} instances", entity);
        }catch (SQLException ex){
            logger.error(ex);
            System.err.println("Error DB " + ex);
        }
        logger.traceExit();
    }
}