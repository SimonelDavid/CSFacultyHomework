package com.example.zboruri.Service;

import com.example.zboruri.Entities.Client;
import com.example.zboruri.Entities.Flight;
import com.example.zboruri.Entities.Ticket;
import com.example.zboruri.Events.ChangeEventType;
import com.example.zboruri.Events.FlightChangeEvent;
import com.example.zboruri.Observer.Observable;
import com.example.zboruri.Observer.Observer;
import com.example.zboruri.Repository.ClientRepository;
import com.example.zboruri.Repository.FlightRepository;
import com.example.zboruri.Repository.TicketRepository;

import java.util.ArrayList;
import java.util.List;

public class Service implements Observable<FlightChangeEvent> {
    private static ClientRepository repo_clienti;
    private static FlightRepository repo_zboruri;
    private static TicketRepository repo_bilete;

    private List<Observer<FlightChangeEvent>> obs=new ArrayList<>();


    public Service(ClientRepository repo_clienti,FlightRepository repo_zboruri,
                   TicketRepository repo_bilete)
    {
        this.repo_clienti=repo_clienti;
        this.repo_zboruri=repo_zboruri;
        this.repo_bilete=repo_bilete;
    }



    public List<Client> getClients()
    {
        return repo_clienti.findAll();
    }

    public List<Flight> getFlights()
    {
        return repo_zboruri.findAll();
    }

    public List<Ticket> getTickets()
    {
        return repo_bilete.findAll();
    }
    
    

    public List<String> getFromLocations()
    {
        return repo_zboruri.getFromLocations();
    }
    
    public List<String> getToLocations()
    {
        return repo_zboruri.getToLocations();
    }

    public void cumparaBilet(String username,Long flightId,String datetime)
    {
        int max=0;
        List<Ticket> tickets=getTickets();
        for(Ticket t:tickets)
            if(t.getId()>max)
                max=t.getId();
        repo_bilete.cumparaBilet(max+1,username,flightId,datetime);
        List<Flight> flights=getFlights();
        int nrLocuri=1;
        Flight f1=null;
        for(Flight f:flights)
            if(f.getFlightId()==flightId)
            {
                nrLocuri=f.getSeats();
                f1=f;
                f1.setSeats(nrLocuri-1);
                break;
            }
        repo_zboruri.updateSeats(flightId,nrLocuri-1);
        notifyObservers(new FlightChangeEvent(ChangeEventType.UPDATE,f1));
    }

    @Override
    public void addObserver(Observer<FlightChangeEvent> e)
    {
        obs.add(e);
    }

    @Override
    public void removeObserver(Observer<FlightChangeEvent> e)
    {
        obs.remove(e);
    }

    @Override
    public void notifyObservers(FlightChangeEvent entity)
    {
        obs.stream().forEach(x->x.update(entity));
    }
}