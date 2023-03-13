package examen.examensimon.repository.database;

import examen.examensimon.domain.Intrebare;
import examen.examensimon.repository.Repository;
import examen.examensimon.utils.observer.ConcreteObservable;
import examen.examensimon.utils.utils.ActualEvent;
import examen.examensimon.utils.utils.ChangeEventType;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

public class IntrebareDBRepository extends ConcreteObservable<ActualEvent> implements Repository<Integer, Intrebare> {
    private String url;
    private String username;
    private String password;

    public IntrebareDBRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Intrebare find(Integer id) throws IllegalArgumentException {
        String sql = "SELECT * FROM intrebari WHERE nrintrebare = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setInt(1, id);
            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next()) {
                throw new IllegalArgumentException(id + " does not exist!");
            } else {
                return getIntrebareFromResultSet(resultSet);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return null;
    }

    private Intrebare getIntrebareFromResultSet(ResultSet resultSet) throws SQLException {
        Integer nrIntrebare = resultSet.getInt("nrintrebare");
        String descriere = resultSet.getString("descriere");
        String v1 = resultSet.getString("v1");
        String v2 = resultSet.getString("v2");
        String v3 = resultSet.getString("v3");
        String corect = resultSet.getString("corect");
        Float punctaj = resultSet.getFloat("punctaj");
        Integer test = resultSet.getInt("test");

        return new Intrebare(nrIntrebare,descriere,v1,v2,v3,corect,punctaj,test);
    }

    @Override
    public Iterable<Intrebare> getAll() {
        List<Intrebare> intrebari = new ArrayList<>();
        String sql = "SELECT * FROM intrebari";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql);
            ResultSet resultSet = statement.executeQuery()) {

            while(resultSet.next()) {
                Intrebare intrebare = getIntrebareFromResultSet(resultSet);
                intrebari.add(intrebare);
            }
        }catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return intrebari;
    }
    public void addIntrebareToTest(Integer idIntrebare, Integer idTest) {
        AtomicReference<String> sql =
                new AtomicReference<>("UPDATE intrebari SET test = ? WHERE nrintrebare = ?");
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
}
