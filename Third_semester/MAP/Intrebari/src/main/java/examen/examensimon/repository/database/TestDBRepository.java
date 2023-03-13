package examen.examensimon.repository.database;

import examen.examensimon.domain.Testul;
import examen.examensimon.repository.Repository;
import examen.examensimon.utils.observer.ConcreteObservable;
import examen.examensimon.utils.utils.ActualEvent;
import examen.examensimon.utils.utils.ChangeEventType;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

public class TestDBRepository extends ConcreteObservable<ActualEvent> implements Repository<Integer, Testul> {
    private String url;
    private String username;
    private String password;

    public TestDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Testul find(Integer id) throws IllegalArgumentException {
        String sql = "SELECT * FROM teste WHERE idtest = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setInt(1, id);
            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next()) {
                throw new IllegalArgumentException(id + " does not exist!");
            } else {
                return getTestFromResultSet(resultSet);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return null;
    }

    private Testul getTestFromResultSet(ResultSet resultSet) throws SQLException {
        Integer idTest  = resultSet.getInt("idtest");
        Integer idIntrebare  = resultSet.getInt("idintrebare");
        return new Testul(0,idTest,idIntrebare);
    }

    @Override
    public Iterable<Testul> getAll() {
        List<Testul> teste = new ArrayList<>();
        String sql = "SELECT * FROM teste";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql);
            ResultSet resultSet = statement.executeQuery()) {

            while(resultSet.next()) {
                Testul test = getTestFromResultSet(resultSet);
                teste.add(test);

            }
        }catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return teste;
    }


    public void addIntrebareToTest(Integer idIntrebare, Integer idTest) {
        AtomicReference<String> sql =
                new AtomicReference<>("INSERT INTO teste (idtest,idintrebare) " +
                        "VALUES (?,?)");
        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql.get())) {
            statement.setInt(1, idTest);
            statement.setInt(2, idIntrebare);
            statement.executeUpdate();
        }catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        this.notifyObservers(new ActualEvent(ChangeEventType.ADD));
    }

    public Integer idTestNou() {
        String sql = "SELECT MAX(idtest) as maxim FROM teste";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {
            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next()) {
                return -1;
            } else {
                return resultSet.getInt("maxim")+1;
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return -1;
    }
}
