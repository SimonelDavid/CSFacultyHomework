package org.example.repo;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.domain.Game;
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
public class UserRepository implements IUserRepository {
    private final JdbcUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();

    public UserRepository(){
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
    public UserRepository(Properties props) {
        logger.info("Initializing org.example.repo.UserRepository with properties: {} ", props);
        dbUtils = new JdbcUtils(props);
    }
    @Override
    public User add(User entity) {
        String sql = "INSERT INTO \"Users\"(email, password) VALUES(?, ?)";
        logger.traceEntry("saving user {} ", entity);
        Connection con = dbUtils.getConnection();
        String generatedColumns[] = { "id" };
        try(PreparedStatement ps = con.prepareStatement(sql, generatedColumns)) {
            ps.setString(1, entity.getEmail());
            ps.setString(2, entity.getPassword());
            int noRows = ps.executeUpdate();
            try(ResultSet result = ps.getGeneratedKeys()){
                if(result.next()){
                    int id = result.getInt(1);
                    entity.setId((int)id);
                    logger.trace("Saved {} users", noRows);
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
        String sql = "DELETE FROM \"Users\" WHERE id = ?";
        logger.traceEntry("deleting user");
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement(sql)){
            preStmt.setInt(1, id);
            int result= preStmt.executeUpdate();
            logger.trace("Deleted user");
        }catch (SQLException ex){
            logger.error(ex);
            System.err.println("Error DB " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void update(User entity) throws Exception {
        String sql = "UPDATE \"Users\" SET password = ? WHERE id = ?";
        logger.traceEntry("updating race {} ", entity);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement(sql)){
            preStmt.setString(1, entity.getPassword());
            preStmt.setInt(2, entity.getId());
            int result= preStmt.executeUpdate();
            logger.trace("Updated {} instances", entity);
        }catch (SQLException ex){
            logger.error(ex);
            System.err.println("Error DB " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void updatee(User newUser, Integer id) throws Exception {
        String sql = "UPDATE \"Users\" SET password = ? WHERE id = ?";
        logger.traceEntry("updating user {} ", newUser);
        Connection con= dbUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement(sql)){
            preStmt.setString(1, newUser.getPassword());
            preStmt.setInt(2, id);
            int result= preStmt.executeUpdate();
            logger.trace("Updated {} instances", newUser);
        }catch (SQLException ex){
            logger.error(ex);
            System.err.println("Error DB " + ex);
        }
        logger.traceExit();
    }

    @Override
    public Iterable<User> getAllWinners() throws Exception {
        String sql = "SELECT u.id, u.email, u.password FROM \"Users\" u INNER JOIN \"Games\" g ON u.id == g.idwinner";
        logger.traceEntry("finding all users that won at any game");
        Connection con= dbUtils.getConnection();
        List<User> entities = new ArrayList<>();
        try(PreparedStatement ps = con.prepareStatement(sql)) {
            try(ResultSet rs = ps.executeQuery()) {
                while(rs.next()) {
                    int idd = rs.getInt("id");
                    String email = rs.getString("email");
                    String password = rs.getString("password");
                    User entity = new User(email, password);
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
    public User getById(int id) {
        String sql = "SELECT * FROM \"Users\" WHERE id = ?";
        logger.traceEntry("finding user with the id {} ", id);
        Connection con = dbUtils.getConnection();
        try (PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setInt(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if(rs.next()) {
                    int idd = rs.getInt("id");
                    String email = rs.getString("email");
                    String password = rs.getString("password");
                    User entity = new User(email, password);
                    entity.setId(idd);
                    logger.trace("Found {} user", rs);
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
    public User getByMailPassword(String email, String password){
        String sql = "SELECT * FROM \"Users\" WHERE email = ? AND password = ?";
        logger.traceEntry("finding user with the email {} and password {}", email, password);
        Connection con = dbUtils.getConnection();
        try (PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, email);
            ps.setString(2, password);
            try (ResultSet rs = ps.executeQuery()) {
                if(rs.next()) {
                    int id = rs.getInt("id");
                    String emaill = rs.getString("email");
                    String passwordd = rs.getString("password");
                    User entity = new User(emaill, passwordd);
                    entity.setId(id);
                    logger.trace("Found {} user", rs);
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
    public Iterable<User> getAll() {
        String sql = "SELECT * FROM \"Users\"";
        logger.traceEntry("finding all users");
        Connection con= dbUtils.getConnection();
        List<User> entities = new ArrayList<>();
        try(PreparedStatement ps = con.prepareStatement(sql)) {
            try(ResultSet rs = ps.executeQuery()) {
                while(rs.next()) {
                    int idd = rs.getInt("id");
                    String email = rs.getString("email");
                    String password = rs.getString("password");
                    User entity = new User(email, password);
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
        List<User> all= (List<User>)getAll();
        return all.size();
    }
}