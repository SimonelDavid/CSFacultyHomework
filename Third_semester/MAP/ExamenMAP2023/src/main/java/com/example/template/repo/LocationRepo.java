package com.example.template.repo;

import com.example.template.entities.Location;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class LocationRepo implements Repo<Location>{
    private List<Location> locations;
    private String url;
    private String userName;
    private String passwd;

    public LocationRepo(String url, String userName, String passwd) {
        this.url = url;
        this.userName = userName;
        this.passwd = passwd;
        locations = new ArrayList<>();
        getData();
    }

    @Override
    public List<Location> getAll() {
        return locations;
    }

    @Override
    public void getData() {
        locations.clear();
        try (Connection connection = DriverManager.getConnection(url, userName, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from location");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Double id = resultSet.getDouble("id");
                String name = resultSet.getString("name");
                locations.add(new Location(id, name));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
