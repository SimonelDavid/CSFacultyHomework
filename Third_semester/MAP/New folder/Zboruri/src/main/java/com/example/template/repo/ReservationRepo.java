package com.example.template.repo;

import com.example.template.entities.Reservation;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ReservationRepo implements Repo<Reservation>{

    private List<Reservation> reservations;

    private String url;
    private String username;
    private String passwd;

    public ReservationRepo(String url, String username, String passwd) {
        reservations = new ArrayList<>();
        this.url = url;
        this.username = username;
        this.passwd = passwd;
    }

    public void add(Reservation reservation){
        reservations.add(reservation);
        saveData(reservation);
    }

    private void saveData(Reservation reservation) {
        String sql = "insert into reservations (id, client, hotel, start, nights) values (?, ?, ?, ?, ?)";

        try (Connection connection = DriverManager.getConnection(url, username, passwd);
             PreparedStatement ps = connection.prepareStatement(sql)) {

            ps.setDouble(1, reservation.getId());
            ps.setInt(2, reservation.getClient().intValue());
            ps.setDouble(3, reservation.getHotel());
            ps.setDate(4, Date.valueOf(reservation.getStart()));
            ps.setInt(5, reservation.getNights());
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public List<Reservation> getAll() {
        return reservations;
    }

    @Override
    public void getData() {

    }
}
