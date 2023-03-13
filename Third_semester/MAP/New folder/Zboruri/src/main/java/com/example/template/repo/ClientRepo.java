package com.example.template.repo;

import com.example.template.entities.Client;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ClientRepo implements Repo<Client>{
    private List<Client> clients;
    private String url;
    private String userName;
    private String passwd;

    public ClientRepo(String url, String userName, String passwd) {
        this.url = url;
        this.userName = userName;
        this.passwd = passwd;
        clients = new ArrayList<>();
        getData();
    }

    @Override
    public List<Client> getAll() {
        return clients;
    }

    @Override
    public void getData() {
        clients.clear();
        try (Connection connection = DriverManager.getConnection(url, userName, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from client");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String name = resultSet.getString("name");
                clients.add(new Client(username, name));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
