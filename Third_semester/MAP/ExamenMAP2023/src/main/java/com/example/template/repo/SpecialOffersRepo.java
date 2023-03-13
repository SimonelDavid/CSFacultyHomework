package com.example.template.repo;

import com.example.template.entities.SpecialOffer;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class SpecialOffersRepo implements Repo<SpecialOffer> {

    private List<SpecialOffer> specialOffers;
    private String url;
    private String user;
    private String passwd;

    public SpecialOffersRepo(String url, String user, String passwd) {
        this.url = url;
        this.user = user;
        this.passwd = passwd;
        specialOffers = new ArrayList<>();
        getData();
    }

    @Override
    public List<SpecialOffer> getAll() {
        return specialOffers;
    }

    @Override
    public void getData() {
        specialOffers.clear();
        try (Connection connection = DriverManager.getConnection(url, user, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from special");
             ResultSet resultSet = statement.executeQuery()
        ) {

            while (resultSet.next()) {
                Double id = resultSet.getDouble("id");
                Double hotelId = resultSet.getDouble("hotel");
                LocalDate start = resultSet.getDate("start_d").toLocalDate();
                LocalDate end = resultSet.getDate("end_d").toLocalDate();
                Integer percent = resultSet.getInt("percents");

                specialOffers.add(new SpecialOffer(id, hotelId, start, end, percent));

            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
