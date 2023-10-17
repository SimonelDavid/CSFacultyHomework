package app.rest.persistance.repository.jdbc;

import app.rest.persistance.repository.IPlayerRepository;
import domain.Jurry;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.stereotype.Component;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

@Component()
public class PlayerDBIRepository implements IPlayerRepository<Integer, Jurry> {

    private final JdbcUtils dbUtils;
    private static final Logger logger= LogManager.getLogger();

    public PlayerDBIRepository(Properties props) {
        logger.info("Initializing playerDBRepository with properties: {} ",props);
        dbUtils=new JdbcUtils(props);
    }


    private Jurry getPlayerFromResultSet(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("jurry_id");
        String alias = resultSet.getString("alias");
        return new Jurry(id, alias);
    }

    @Override
    public Jurry findById(Integer id) {
        logger.traceEntry("find a jurry by id");
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps = connection.prepareStatement("select * from jurry where jurry_id = ?")) {
            ps.setInt(1, id);
            try (ResultSet resultSet = ps.executeQuery()) {
                if (resultSet.next()) {
                    Jurry jurry = getPlayerFromResultSet(resultSet);
                    logger.traceExit(jurry);
                    return jurry;
                }
            }
        } catch (SQLException exception) {
            logger.error("ERROR for findById in PlayerDBRepository: " + exception);
        }
        return null;
    }


    @Override
    public Iterable<Jurry> getAll() {
        logger.traceEntry("finding all players");
        Connection connection = dbUtils.getConnection();
        List<Jurry> players = new ArrayList<>();
        try (PreparedStatement ps = connection.prepareStatement("select * from jurry")) {
            try (ResultSet resultSet = ps.executeQuery()) {
                while (resultSet.next()) {
                    players.add(getPlayerFromResultSet(resultSet));
                }
            }
        } catch (SQLException exception) {
            logger.error("ERROR for getAll in PlayerDBRepository: " + exception);
        }
        logger.traceExit(players);
        return players;
    }

    @Override
    public boolean add(Jurry jurry) {
        logger.traceEntry("adding jurry {}", jurry);
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps = connection.prepareStatement("insert into jurry (alias) values (?)")) {
            ps.setString(1, jurry.getAlias());
            int result = ps.executeUpdate();
            logger.trace("saved {} instance", result);
        } catch (SQLException exception) {
            logger.error("ERROR for insert in playerDBRepository: " + exception);
            return false;
        }
        logger.traceExit("inserted successfully");
        return true;
    }

    @Override
    public boolean update(Jurry jurry) {
        logger.traceEntry("updating jurry");
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps = connection.prepareStatement("update jurry set alias = ?" +
                " where jurry_id = ?")) {
            ps.setString(1, jurry.getAlias());
            ps.setInt(2, jurry.getId());
            int result = ps.executeUpdate();
            logger.trace("updated {} instance", result);
        } catch (SQLException exception) {
            logger.error("ERROR for update in PlayerDBRepository: " + exception);
            return false;
        }
        logger.traceExit("updated successfully");
        return true;
    }

    public Jurry login(String username) {
        logger.traceEntry("find a jurry by username and password");
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps = connection.prepareStatement("select * from jurry where alias = ?")) {
            ps.setString(1,username);
            try (ResultSet resultSet = ps.executeQuery()) {
                if (resultSet.next()) {
                    Jurry jurry = getPlayerFromResultSet(resultSet);
                    logger.traceExit(jurry);
                    return jurry;
                }
            }
        } catch (SQLException exception) {
            logger.error("ERROR for authenticate jurry in PlayerDBRepository: " + exception);
        }
        logger.traceExit("authentication failed");
        return null;
    }
}
