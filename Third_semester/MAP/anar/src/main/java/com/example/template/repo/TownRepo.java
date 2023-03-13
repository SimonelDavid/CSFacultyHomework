package com.example.template.repo;

import com.example.template.entities.River;
import com.example.template.entities.Town;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class TownRepo implements Repo<Town> {

    private String url;

    public TownRepo(String url, String username, String passwd) {
        this.url = url;
        this.username = username;
        this.passwd = passwd;
        towns = new ArrayList<>();
        getData();
    }

    private String username;
    private String passwd;

    private List<Town> towns;

    @Override
    public List<Town> getAll() {
        return towns;
    }

    @Override
    public void getData() {
        towns.clear();
        try (Connection connection = DriverManager.getConnection(url, username, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from town");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                String name = resultSet.getString("name");
                String river = resultSet.getString("river");
                Integer cmdr = resultSet.getInt("cmdr");
                Integer cma = resultSet.getInt("cma");
                towns.add(new Town(name, river, cmdr, cma));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
