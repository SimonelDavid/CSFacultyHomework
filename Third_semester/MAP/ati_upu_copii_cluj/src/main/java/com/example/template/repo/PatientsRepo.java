package com.example.template.repo;

import com.example.template.entities.Patient;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class PatientsRepo implements GenericRepo<Patient> {
    private List<Patient> patients;
    private String url;
    private String username;
    private String passwd;

    public PatientsRepo(String url, String username, String passwd) {
        this.url = url;
        this.username = username;
        this.passwd = passwd;

        patients = new ArrayList<>();
        getData();
    }


    @Override
    public void getData() {
        patients.clear();
        try (Connection connection = DriverManager.getConnection(url, username, passwd);
             PreparedStatement statement = connection.prepareStatement("SELECT * from patient order by severity desc");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                String cnp = resultSet.getString("cnp");
                Integer age = resultSet.getInt("age");
                Boolean premature = resultSet.getBoolean("premature");
                String diagnostic = resultSet.getString("diagnostic");
                Integer severity = resultSet.getInt("severity");
                patients.add(new Patient(cnp, age, premature, diagnostic, severity));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public List<Patient> getAll() {
        return patients;
    }
}
