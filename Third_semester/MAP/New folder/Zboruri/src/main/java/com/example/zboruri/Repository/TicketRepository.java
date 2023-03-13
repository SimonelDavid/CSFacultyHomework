package com.example.zboruri.Repository;

import com.example.zboruri.Entities.Ticket;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class TicketRepository implements GenericRepository<Ticket>{
    private String url;
    private String username;
    private String password;
    private List<Ticket> bilete;


    public TicketRepository(String url, String username, String password)
    {
        this.url=url;
        this.username=username;
        this.password=password;
        bilete=new ArrayList<>();
        getData();
    }

    @Override
    public void getData()
    {
        bilete.clear();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from tickets");
             ResultSet resultSet = statement.executeQuery())
        {
            while (resultSet.next())
            {
                int id=resultSet.getInt("id");
                String username=resultSet.getString("username");
                Long flightId=resultSet.getLong("flightid");
                String purchaseTime=resultSet.getString("purchasetime");

                bilete.add(new Ticket(id,username,flightId,LocalDateTime.parse(purchaseTime)));
            }
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
    }


    public void cumparaBilet(int id,String user,Long flightId,String datetime)
    {
        String sql="insert into tickets (id,username,flightid,purchasetime) values (?,?,?,?)";
        try (Connection connection=DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql))
        {
            ps.setInt(1,id);
            ps.setString(2,user);
            ps.setLong(3,flightId);
            ps.setString(4,datetime);
            ps.executeUpdate();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
    }


    @Override
    public List<Ticket> findAll()
    {
        getData();
        return bilete;
    }
}