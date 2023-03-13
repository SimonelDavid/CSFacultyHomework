package com.example.zboruri.Controller;

import com.example.zboruri.Entities.Flight;
import com.example.zboruri.Events.FlightChangeEvent;
import com.example.zboruri.Observer.Observer;
import com.example.zboruri.Service.Service;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

import java.io.IOException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class FlightsController implements Observer<FlightChangeEvent> {
    @FXML
    private TableView<Flight> tableFlightView;
    @FXML
    private TableColumn<Flight,String> tableColumnFrom;
    @FXML
    private TableColumn<Flight,String> tableColumnTo;
    @FXML
    private TableColumn<Flight, LocalDateTime> tableColumnDepTime;
    @FXML
    private TableColumn<Flight, LocalDateTime> tableColumnLandTime;
    @FXML
    private TableColumn<Flight, Integer> tableColumnSeats;


    @FXML
    private ComboBox<String> fromComboBox;
    @FXML
    private ComboBox<String> toComboBox;
    @FXML
    private DatePicker dayPicker;
    @FXML
    private Button butonFiltrare;
    @FXML
    private Button butonAchizitie;
    @FXML
    private Button previous;
    @FXML
    private Button next;
    @FXML
    private Label nrPaginaLabel;


    private Service service;
    private String username;
    //paginare1
     private int index=5;
    //paginare2
    private int filteredNumber;
    //paginare3
    private double totalFiltered;
    //paginare 3.1
    String from,to;
    //paginare 3.2
    LocalDate ziua;
    private ObservableList<Flight> modelFlight= FXCollections.observableArrayList();


    public void setFlightsService(Service service,String username)
    {
        this.service=service;
        this.username=username;
        service.addObserver(this);
        initModel();
    }


    @FXML
    public void initialize()
    {
        //paginare3
        previous.setDisable(true);
        tableColumnFrom.setCellValueFactory(new PropertyValueFactory<Flight,String>("from"));
        tableColumnTo.setCellValueFactory(new PropertyValueFactory<Flight,String>("to"));
        tableColumnDepTime.setCellValueFactory(new PropertyValueFactory<Flight,LocalDateTime>("departureTime"));
        tableColumnLandTime.setCellValueFactory(new PropertyValueFactory<Flight,LocalDateTime>("landingTime"));
        tableColumnSeats.setCellValueFactory(new PropertyValueFactory<Flight,Integer>("seats"));
        tableFlightView.setItems(modelFlight);
    }


    @FXML
    public void initModel()
    {
        //paginare4
        previous.setDisable(true);
        //paginare5
        next.setDisable(true);
        butonAchizitie.setDisable(true);
        List<String> locatii1=service.getFromLocations();
        ObservableList<String> valori1=FXCollections.observableArrayList();
        for(String l:locatii1)
            valori1.add(l);
        fromComboBox.setItems(valori1);

        List<String> locatii2=service.getToLocations();
        ObservableList<String> valori2=FXCollections.observableArrayList();
        for(String l:locatii2)
            valori2.add(l);
        toComboBox.setItems(valori2);

        //List<Flight> flights=service.getFlights();
        //modelFlight.setAll(flights);
    }



    public void handleFiltrareZboruri(ActionEvent actionEvent)
    {
        //paginare6
        previous.setDisable(true);
        //paginare7
        next.setDisable(true);
        //paginare8
        index=5;
        from=fromComboBox.getValue();
        to=toComboBox.getValue();
        ziua=dayPicker.getValue();
        if(from==null || to==null || ziua==null)
        {
            Alert alert=new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Eroare");
            alert.setContentText("Informatii incomplete!");
            alert.show();
            return;
        }
        //paginare9
        toBeFiltered();
        handleUpdateTable();
    }

    //paginare10
    public void toBeFiltered()
    {
        totalFiltered=0;
        List<Flight> flights=service.getFlights();
        for(Flight f:flights)
            if(f.getFrom().equals(from) && f.getTo().equals(to) && f.getDepartureTime().toLocalDate().equals(ziua))
                totalFiltered++;
    }


    public void handleUpdateTable()
    {
        //paginare11
        List<Flight> flights=service.getFlights();
        //paginare11.1
        nrPaginaLabel.setText(index/5+"/"+Math.max(1,(int)(Math.ceil(totalFiltered/5))));
        List<Flight> flightsFiltered=new ArrayList<>();
        //paginare12
        int localIndex=0;
        for(Flight f:flights)
            if(f.getFrom().equals(from) && f.getTo().equals(to) && f.getDepartureTime().toLocalDate().equals(ziua))
            {
                //paginare12.1
                localIndex++;
                //paginare13
                if(localIndex<=index && localIndex>index-5)
                    flightsFiltered.add(f);
            }
        //paginare14
        filteredNumber=flightsFiltered.size();
        //paginare15
        if(totalFiltered>5)
            next.setDisable(false);
        modelFlight.setAll(flightsFiltered);
    }


    public void handleSelectareZbor(MouseEvent actionEvent)
    {
        if(tableFlightView.getSelectionModel().getSelectedItem()!=null)
            butonAchizitie.setDisable(false);
    }


    public void handleCumparaBilet(ActionEvent actionEvent)
    {
        Long flightId=tableFlightView.getSelectionModel().getSelectedItem().getFlightId();
        String dateTime=LocalDateTime.now().toString();
        service.cumparaBilet(username,flightId,dateTime);
        //handleFiltrareZboruri(actionEvent);
        butonAchizitie.setDisable(true);
    }


    @Override
    public void update(FlightChangeEvent flightChangeEvent)
    {
        handleFiltrareZboruri(new ActionEvent());
    }

    //paginare16
    public void handlePrevious(ActionEvent event){
        index=index-5;
        nrPaginaLabel.setText(String.valueOf(index/5));
        handleUpdateTable();
        if(index==5 && totalFiltered>5)
            previous.setDisable(true);
        else
            next.setDisable(false);
    }


    //paginare17
    public void handleNext(ActionEvent event){
        index=index+5;
        nrPaginaLabel.setText(String.valueOf(index/5));
        handleUpdateTable();
        if(filteredNumber<5 && totalFiltered>5)
            next.setDisable(true);
        else
            previous.setDisable(false);
    }
}