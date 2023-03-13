package com.example.template.repo;

import com.example.template.entities.Client;
import com.example.template.entities.Hobby;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ClientRepo implements Repo<Client> {
    private List<Client>clients;
    private String url;
    private String username;
    private String passwd;

    public ClientRepo(String url, String username, String passwd) {
        clients = new ArrayList<>();
        this.url = url;
        this.username = username;
        this.passwd = passwd;
        getData();
    }

    @Override
    public List<Client> getAll() {
        return clients;
    }

    @Override
    public void getData() {
        clients.clear();
        try (Connection connection = DriverManager.getConnection(url, username, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from client");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String name = resultSet.getString("name");
                Integer fidelity = resultSet.getInt("fidelity");
                Integer age = resultSet.getInt("age");
                Hobby hobby = Client.getHobbyFromString(resultSet.getString("hobbies"));

                clients.add(new Client(id, name, fidelity, age, hobby));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
