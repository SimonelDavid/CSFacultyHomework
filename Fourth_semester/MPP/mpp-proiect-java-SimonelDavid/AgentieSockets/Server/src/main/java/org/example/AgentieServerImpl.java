package org.example;

import java.time.LocalTime;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class AgentieServerImpl implements IServices{
    private AngajatDBRepository angajatDBRepository;
    private ZborDBRepository zborDBRepository;
    private BiletDBRepository biletDBRepository;
    private Map<String, IObserver> loggedClients;

    public AgentieServerImpl(AngajatDBRepository angajatDBRepository, ZborDBRepository zborDBRepository, BiletDBRepository biletDBRepository) {
        this.angajatDBRepository = angajatDBRepository;
        this.zborDBRepository = zborDBRepository;
        this.biletDBRepository = biletDBRepository;
        loggedClients=new ConcurrentHashMap<>();;
    }

    public synchronized void login(Angajat user, IObserver client) throws AgentieException {
        Angajat userR=angajatDBRepository.findByNumeParola(user.getNume(),user.getParola());
        if (userR!=null){
            if(loggedClients.get(user.getNume())!=null)
                throw new AgentieException("User already logged in.");
            loggedClients.put(user.getNume(), client);
        }else
            throw new AgentieException("Authentication failed.");
    }

    public synchronized List<Zbor> findAll() {
        Iterable<Zbor> listIterable = zborDBRepository.findAll();
        return StreamSupport.stream(listIterable.spliterator(), false).collect(Collectors.toList());
    }

    @Override
    public List<Zbor> findByData(String dest, String data) {
        Iterable<Zbor> listIterable = zborDBRepository.findByDestinatieData(dest, data);
        return StreamSupport.stream(listIterable.spliterator(), false).collect(Collectors.toList());
    }

    public void cumparaBilet(Zbor selected, Bilet bilet, int locuri, String dest, String data) throws AgentieException{
        if(selected.getLocuri() < locuri)
            throw new AgentieException();
        selected.setLocuri(selected.getLocuri() - locuri);
        zborDBRepository.update(selected.getId(), selected);

        biletDBRepository.save(bilet);

        Iterable<Angajat> angajati = angajatDBRepository.findAll();

        ExecutorService executor= Executors.newFixedThreadPool(5);
        for(Angajat a :angajati){
            IObserver client=loggedClients.get(a.getNume());
            if (client!=null)
                executor.execute(() -> {
                    try {
                        client.updateLista((List<Zbor>) zborDBRepository.findAll(), (List<Zbor>) zborDBRepository.findByDestinatieData(dest, data));
                    } catch (AgentieException e) {
                        System.err.println("Error notifying angajat " + e);
                    }
                });
        }

        executor.shutdown();
    }

    public synchronized void logout(Angajat user, IObserver client) throws AgentieException {
        IObserver localClient=loggedClients.remove(user.getNume());
        if (localClient==null)
            throw new AgentieException("User "+user.getId()+" is not logged in.");
    }
}
