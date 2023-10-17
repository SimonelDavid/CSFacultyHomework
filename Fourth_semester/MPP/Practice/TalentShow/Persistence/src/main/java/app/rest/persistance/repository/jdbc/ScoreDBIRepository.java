package app.rest.persistance.repository.jdbc;

import app.rest.persistance.repository.IGameRepository;
import app.rest.persistance.repository.IPositionRepository;
import app.rest.persistance.repository.IScoreRepository;
import app.rest.persistance.repository.IPlayerRepository;
import domain.Game;
import domain.Participant;
import domain.Rezultat;
import domain.Jurry;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.stereotype.Component;

import java.sql.*;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

@Component()
public class ScoreDBIRepository implements IScoreRepository<Integer, Rezultat> {

    private final JdbcUtils dbUtils;
    private static final Logger logger = LogManager.getLogger();
    private final IPlayerRepository<Integer, Jurry> playerDBIRepository;
    private final IGameRepository<Integer, Game> gameORMDBIRepository;
    private final IPositionRepository<Integer, Participant> positionORMDBIRepository;

    public ScoreDBIRepository(Properties props, IPlayerRepository<Integer, Jurry> playerDBIRepository,
                              IGameRepository<Integer, Game> gameORMDBIRepository,
                              IPositionRepository<Integer, Participant> positionORMDBIRepository) {
        logger.info("Initializing ScoreDBIRepository with properties: {} ", props);
        dbUtils = new JdbcUtils(props);
        this.playerDBIRepository = playerDBIRepository;
        this.gameORMDBIRepository = gameORMDBIRepository;
        this.positionORMDBIRepository = positionORMDBIRepository;
    }

    private Rezultat getScoreFromResultSet(ResultSet resultSet) throws SQLException {
        Integer rezultat_id = resultSet.getInt("rezultat_id");
        int game_id = resultSet.getInt("game_id");
        Game game = gameORMDBIRepository.findById(game_id);
        int jurry_id = resultSet.getInt("jurry_id");
        Jurry jurry = playerDBIRepository.findById(jurry_id);
        int participant_id = resultSet.getInt("participant_id");
        Participant participant = positionORMDBIRepository.findById(participant_id);
        String raspuns = resultSet.getString("raspuns");
        Time timeValue = resultSet.getTime("time");
        if (timeValue != null) {
            // Convert the time to LocalTime
            LocalTime time = timeValue.toLocalTime();
            return new Rezultat(rezultat_id, jurry, participant, raspuns);
        } else return new Rezultat(rezultat_id, jurry, participant, raspuns);
    }

    @Override
    public Rezultat findById(Integer id) {
        logger.traceEntry("find a rezultat by id");
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps = connection.prepareStatement("select * from rezultat where rezultat_id = ?")) {
            ps.setInt(1, id);
            try (ResultSet resultSet = ps.executeQuery()) {
                if (resultSet.next()) {
                    Rezultat rezultat = getScoreFromResultSet(resultSet);
                    logger.traceExit(rezultat);
                    return rezultat;
                }
            }
        } catch (SQLException exception) {
            logger.error("ERROR for findById in ScoreDBIRepository: " + exception);
        }
        return null;
    }

    @Override
    public Iterable<Rezultat> getAll() {
        logger.traceEntry("finding all scores");
        Connection connection = dbUtils.getConnection();
        List<Rezultat> scores = new ArrayList<>();
        try (PreparedStatement ps = connection.prepareStatement("select * from rezultat")) {
            try (ResultSet resultSet = ps.executeQuery()) {
                while (resultSet.next()) {
                    scores.add(getScoreFromResultSet(resultSet));
                }
            }
        } catch (SQLException exception) {
            logger.error("ERROR for getAll in ScoreDBIRepository: " + exception);
        }
        logger.traceExit(scores);
        return scores;
    }

    @Override
    public boolean add(Rezultat rezultat) {
        logger.traceEntry("Add rezultat {}", rezultat);
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps = connection.prepareStatement("insert into rezultat " +
                "(game_id, jurry_id, participant_id, raspuns, totalPoints, round, gameOver, time) " +
                "values (?, ?, ?, ?, ?, ?,?, ?)")) {
            setParameters(rezultat, ps);
//            ps.setInt(7, rezultat.getGameOver());
//            ps.setTime(8, Time.valueOf(rezultat.getTime()));
            int result = ps.executeUpdate();
            logger.trace("saved {} instance", result);
        } catch (SQLException exception) {
            logger.error("ERROR for insert in ScoreDBIRepository: " + exception);
            return false;
        }
        logger.traceExit("inserted successfully");
        return true;
    }

    private void setParameters(Rezultat rezultat, PreparedStatement ps) throws SQLException {
//        ps.setInt(1, rezultat.getGame().getId());
        ps.setInt(2, rezultat.getJurry().getId());
        ps.setInt(3, rezultat.getGuess().getId());
//        ps.setString(4, rezultat.getRaspuns());
//        ps.setInt(5, rezultat.getTotalPoints());
//        ps.setInt(6, rezultat.getRound());
    }

    @Override
    public boolean update(Rezultat rezultat) {
        logger.traceEntry("updating rezultat");
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps = connection.prepareStatement("update rezultat set " +
                "game_id = ?, jurry_id = ?, participant_id =?, " +
                "raspuns = ?, totalPoints=?, round=?, gameOver = ?, time=? where rezultat_id = ?")) {
            setParameters(rezultat, ps);
//            ps.setTime(7, Time.valueOf(rezultat.getTime()));
//            ps.setInt(8, rezultat.getGameOver());
            ps.setInt(9, rezultat.getId());
            int result = ps.executeUpdate();
            logger.trace("updated {} instance", result);
            if (result == 0) {
                return false;
            }
        } catch (SQLException exception) {
            logger.error("ERROR for update in ScoreDBIRepository: " + exception);
            return false;
        }
        logger.traceExit("updated successfully");
        return true;
    }

    @Override
    public Rezultat getLatestScoreForPlayer(Integer idPlayer) {
        logger.traceEntry("find a rezultat by id");
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps =
                     connection.prepareStatement("select * from rezultat where jurry_id = ? " +
                             "order by rezultat_id desc limit 1")) {
            ps.setInt(1, idPlayer);
            try (ResultSet resultSet = ps.executeQuery()) {
                if (resultSet.next()) {
                    Rezultat rezultat = getScoreFromResultSet(resultSet);
                    logger.traceExit(rezultat);
                    return rezultat;
                }
            }
        } catch (SQLException exception) {
            logger.error("ERROR for findById in ScoreDBIRepository: " + exception);
        }
        return null;
    }

    @Override
    public Integer getMaxId() {
        logger.traceEntry("find a rezultat by id");
        Connection connection = dbUtils.getConnection();
        try (PreparedStatement ps = connection.prepareStatement("select max(rezultat_id) from rezultat")) {
            try (ResultSet resultSet = ps.executeQuery()) {
                if (resultSet.next()) {
                    Integer id = resultSet.getInt(1);
                    logger.traceExit(id);
                    return id;
                }
            }
        } catch (SQLException exception) {
            logger.error("ERROR for findById in ScoreDBIRepository: " + exception);
        }
        return null;
    }
}
