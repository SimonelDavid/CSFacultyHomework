package com.example.zboruri.Repository;

import com.example.zboruri.Entities.Flight;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class FlightRepository implements GenericRepository<Flight>{
    private String url;
    private String username;
    private String password;
    private List<Flight> zboruri;


    public FlightRepository(String url, String username, String password)
    {
        this.url=url;
        this.username=username;
        this.password=password;
        zboruri=new ArrayList<>();
        getData();
    }

    @Override
    public void getData()
    {
        zboruri.clear();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from flights");
             ResultSet resultSet = statement.executeQuery())
        {
            while (resultSet.next())
            {
                Long flightId=resultSet.getLong("flightid");
                String from=resultSet.getString("froml");
                String to=resultSet.getString("tol");
                String depTime=resultSet.getString("departuretime");
                String landTime=resultSet.getString("landingtime");
                int seats=resultSet.getInt("seats");

                zboruri.add(new Flight(flightId,from,to, LocalDateTime.parse(depTime),LocalDateTime.parse(landTime),seats));
            }
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    public List<String> getFromLocations()
    {
        List<String> zboruriFrom=new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT distinct froml from flights");
             ResultSet resultSet = statement.executeQuery())
        {
            while (resultSet.next())
            {
                String from=resultSet.getString("froml");
                zboruriFrom.add(from);
            }
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
        return zboruriFrom;
    }


    public List<String> getToLocations()
    {
        List<String> zboruriFrom=new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT distinct tol from flights");
             ResultSet resultSet = statement.executeQuery())
        {
            while (resultSet.next())
            {
                String from=resultSet.getString("tol");
                zboruriFrom.add(from);
            }
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
        return zboruriFrom;
    }


    public void updateSeats(Long flightId,int seatsRemained)
    {
        String sql="update \"flights\" set seats=? where flightid=?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setInt(1,seatsRemained);
            ps.setLong(2,flightId);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public List<Flight> findAll()
    {
        getData();
        return zboruri;
    }
}
