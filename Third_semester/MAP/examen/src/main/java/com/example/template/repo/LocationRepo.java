package com.example.template.repo;

import com.example.template.entities.Location;

import java.util.ArrayList;
import java.util.List;

import java.sql.*;

public class LocationRepo implements Repo<Location>{

    private List<Location> locs;
    private String url;
    private String username;
    private String passwd;

    public LocationRepo(String url, String username, String passwd) {
        this.url = url;
        this.username = username;
        this.passwd = passwd;
        locs = new ArrayList<>();
        getData();
    }

    @Override
    public List<Location> getAll() {
        return locs;
    }

    @Override
    public void getData() {
        locs.clear();
        try (Connection connection = DriverManager.getConnection(url, username, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from loc");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                String name = resultSet.getString("locationName");
                Integer cota = resultSet.getInt("locationId");
                locs.add(new Location(name, cota));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void updateCota(String name, Integer cota){
        for(Location loc: locs){
            if(loc.getlocationName().equals(name)){
                loc.setlocationId(cota);
            }
        }
    }
}
