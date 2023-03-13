package com.example.template.repo;

import com.example.template.entities.Hotel;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class HotelRepo implements Repo<Hotel> {

    private String url;

    public HotelRepo(String url, String username, String passwd) {
        this.url = url;
        this.username = username;
        this.passwd = passwd;
        hotels = new ArrayList<>();
        getData();
    }

    private String username;
    private String passwd;

    private List<Hotel> hotels;

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
                Integer locationId = resultSet.getInt("locationId");
                Integer hotelId = resultSet.getInt("hotelId");
                String hotelName = resultSet.getString("hotelName");
                String type = resultSet.getString("type");
                Integer noRooms = resultSet.getInt("noRooms");
                Integer pricePerNight = resultSet.getInt("pricePerNight");
                hotels.add(new Hotel(hotelId, locationId,hotelName, noRooms, pricePerNight, type));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
