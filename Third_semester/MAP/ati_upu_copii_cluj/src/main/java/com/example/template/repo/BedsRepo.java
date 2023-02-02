package com.example.template.repo;

import com.example.template.entities.Bed;
import com.example.template.entities.BedType;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class BedsRepo implements GenericRepo<Bed> {

    private List<Bed> beds;
    private String username;
    private String passwd;
    private String url;

    public BedsRepo(String username, String passwd, String url) {
        this.username = username;
        this.passwd = passwd;
        this.url = url;
        beds = new ArrayList<>();
        getData();
    }

    private Bed bedBuilder(Integer id, String type, Boolean o2){
        if(type.equals(BedType.TIC.toString())){
            return new Bed(id, BedType.TIC, o2);
        }
        if(type.equals(BedType.TIM.toString())){
            return new Bed(id, BedType.TIM, o2);
        }
        return new Bed(id, BedType.TIIP, o2);
    }

    @Override
    public void getData() {
        beds.clear();
        try (Connection connection = DriverManager.getConnection(url, username, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from beds");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Integer id = resultSet.getInt("id");
                String type = resultSet.getString("type");
                Boolean o2 = resultSet.getBoolean("o2");
                beds.add(bedBuilder(id, type, o2));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public List<Bed> getAll() {
        return beds;
    }
}
