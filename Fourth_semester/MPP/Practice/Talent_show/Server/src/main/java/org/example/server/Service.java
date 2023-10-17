package org.example.server;

import org.example.domain.*;
import org.example.repo.IConfigRepository;
import org.example.repo.IGameRepository;
import org.example.repo.IUserRepository;
import org.example.repo.IWordRepository;
import org.example.service.IObserver;
import org.example.service.IService;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class Service implements IService {
    private IUserRepository userRepo;
    private IGameRepository gameRepo;
    private IConfigRepository configRepo;
    private IWordRepository wordRepo;
    private Map<Jurry, IObserver> observers;

    public Service(IUserRepository userRepo, IGameRepository gameRepo, IConfigRepository configRepo, IWordRepository wordRepo)
    {
        this.userRepo = userRepo;
        this.gameRepo = gameRepo;
        this.configRepo = configRepo;
        this.wordRepo = wordRepo;
        this.observers = new ConcurrentHashMap<>();
    }

    @Override
    public Jurry getByMailPassword(String nume, String password, IObserver client) throws Exception {
        var user = userRepo.getByMailPassword(nume, password);
        if(user==null)
            throw new Exception("Invalid user credentials");
        else {
            if (client != null) {
                if (observers.containsKey(user)) {
                    throw new Exception("Cannot open same client twice!!!");
                } else {
                    observers.put(user, client);
                }
            }
        }
        return user;
    }

    @Override
    public void logout(Jurry user, IObserver client) throws Exception {
        for(var o: observers.keySet()){
            System.out.println(o);
        }
        var localClient = observers.remove(user);
        if(localClient==null){
            throw new Exception("Cannot close a client that is not opened!!!");
        }
    }

    public static String shuffleString(String input) {
        char[] chars = input.toCharArray();
        Random rand = new Random();

        for (int i = 0; i < chars.length; i++) {
            int randomIndex = rand.nextInt(chars.length);
            char temp = chars[i];
            chars[i] = chars[randomIndex];
            chars[randomIndex] = temp;
        }
        return new String(chars);
    }

    @Override
    public Config addConfig() throws Exception {
        Iterable<Participant> words = wordRepo.getAll();
        String ws = "";
        for(Participant w : words){
            ws = ws + w.getWord();
        }
        String shuffled= shuffleString(ws);
        String sub = shuffled.substring(0,5);
        String subb = sub + sub;
        String shsub = shuffleString(subb);
        Config added = configRepo.add(new Config(shsub));
        return added;
    }

    @Override
    public Iterable<Rezultate> getAllGames() throws Exception {
        return gameRepo.getAll();
    }
}
