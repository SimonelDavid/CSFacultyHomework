package com.example.zboruri.Repository;

import com.example.zboruri.Entities.Client;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ClientRepository implements GenericRepository<Client>{
    private String url;
    private String username;
    private String password;
    private List<Client> clienti;


    public ClientRepository(String url, String username, String password)
    {
        this.url=url;
        this.username=username;
        this.password=password;
        clienti=new ArrayList<>();
        getData();
    }

    @Override
    public void getData()
    {
        clienti.clear();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from clienti");
             ResultSet resultSet = statement.executeQuery())
        {
            while (resultSet.next())
            {
                String username=resultSet.getString("username");
                String name=resultSet.getString("name");

                clienti.add(new Client(username,name));
            }
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public List<Client> findAll()
    {
        getData();
        return clienti;
    }
}