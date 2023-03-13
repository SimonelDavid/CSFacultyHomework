package com.example.template.repo;

import com.example.template.entities.Hotel;
import com.example.template.entities.HotelType;
import com.example.template.entities.Client;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class HotelRepo implements Repo<Hotel> {

    private List<Hotel> hotels;
    private String url;
    private String username;
    private String passwd;

    public HotelRepo(String url, String username, String passwd) {
        this.url = url;
        this.username = username;
        this.passwd = passwd;
        hotels = new ArrayList<>();
        getData();
    }

    @Override
    public List<Hotel> getAll() {
        return hotels;
    }

    @Override
    public void getData() {
        hotels.clear();
        try (Connection connection = DriverManager.getConnection(url, username, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from hotel");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Double id = resultSet.getDouble("id");
                Double lid = resultSet.getDouble("lid");
                String name = resultSet.getString("name");
                Integer rooms = resultSet.getInt("rooms");
                Double price = resultSet.getDouble("price");
                HotelType type = Hotel.stringToType(resultSet.getString("type"));
                hotels.add(new Hotel(id, lid, name, rooms, price, type));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
