package com.example.zboruri;

import com.example.zboruri.Controller.LoginController;
import com.example.zboruri.Repository.ClientRepository;
import com.example.zboruri.Repository.FlightRepository;
import com.example.zboruri.Repository.TicketRepository;
import com.example.zboruri.Service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import java.io.IOException;

public class HelloApplication extends Application {
    ClientRepository repo_clienti=new ClientRepository("jdbc:postgresql://localhost:5432/zboruri","postgres","aezakmi");
    FlightRepository repo_zboruri=new FlightRepository("jdbc:postgresql://localhost:5432/zboruri","postgres","aezakmi");
    TicketRepository repo_bilete=new TicketRepository("jdbc:postgresql://localhost:5432/zboruri","postgres","aezakmi");

    Service service=new Service(repo_clienti,repo_zboruri,repo_bilete);
    
    @Override
    public void start(Stage stage) throws IOException
    {
        initView(stage);
        stage.setWidth(800);
        stage.setHeight(500);
        stage.show();
    }

    private void initView(Stage primaryStage) throws IOException
    {
        FXMLLoader fxmllLoader=new FXMLLoader(HelloApplication.class.getResource("views/LoginView.fxml"));
        Pane userLayout=(Pane) fxmllLoader.load();
        primaryStage.setScene(new Scene(userLayout,800,500));

        LoginController loginController= fxmllLoader.getController();
        loginController.setLoginService(service);
    }
}