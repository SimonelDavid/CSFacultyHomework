package com.example.template.repo;

import com.example.template.entities.River;

import java.util.ArrayList;
import java.util.List;

import java.sql.*;

public class RiverRepo implements Repo<River>{

    private List<River> rivers;
    private String url;
    private String username;
    private String passwd;

    public RiverRepo(String url, String username, String passwd) {
        this.url = url;
        this.username = username;
        this.passwd = passwd;
        rivers = new ArrayList<>();
        getData();
    }

    @Override
    public List<River> getAll() {
        return rivers;
    }

    @Override
    public void getData() {
        rivers.clear();
        try (Connection connection = DriverManager.getConnection(url, username, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from river");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                String name = resultSet.getString("name");
                Integer cota = resultSet.getInt("cota");
                rivers.add(new River(name, cota));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void updateCota(String name, Integer cota){
        for(River river: rivers){
            if(river.getName().equals(name)){
                river.setCota(cota);
            }
        }
    }
}
