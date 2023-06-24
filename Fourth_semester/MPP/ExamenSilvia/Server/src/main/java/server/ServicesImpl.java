package server;

import model.Configuration;
import model.Game;
import model.User;
import repository.ConfigurationRepository;
import repository.GameRepository;
import repository.UserRepository;
import services.IObserver;
import services.IServices;
import services.ServicesException;

import java.util.Collection;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ServicesImpl implements IServices {
    UserRepository userRepository;
    GameRepository gameRepository;
    ConfigurationRepository configurationRepository;
    private Map<Integer, IObserver> logged;


    public ServicesImpl(UserRepository userRepository, GameRepository gameRepository, ConfigurationRepository configurationRepository) {
        this.userRepository = userRepository;
        this.gameRepository = gameRepository;
        this.configurationRepository = configurationRepository;
        logged = new ConcurrentHashMap<Integer, IObserver>();
    }

    @Override
    public User login(User user, IObserver client) throws ServicesException {
        User loginUser = userRepository.filterByUsernameAndPassword(user);

        if(loginUser != null){
            if(logged.get(loginUser.getID()) != null)
                throw new ServicesException("User already logged in");
            logged.put(loginUser.getID(), client);
            return loginUser;
        }else
            throw new ServicesException("Authentication failed!");
    }

    @Override
    public void logout(User user, IObserver client) throws ServicesException {
        User logoutUser = userRepository.filterByUsernameAndPassword(user);
        IObserver localClient = logged.remove(logoutUser.getID());
        if(localClient == null)
            throw new ServicesException("User " + logoutUser.getUsername() + " is not logged in");
    }

    @Override
    public Game play(Game game) throws ServicesException {
        Game playedGame = playGame(game);
        if(playedGame.getVisited().size() == 4 || playedGame.getOver()){
            game.setOver(true);
            gameRepository.add(playedGame);
            notifyUsers(playedGame);
        }
        return playedGame;
    }

    private Integer getScoreForALetter(String word, String letter) {
        Integer score = 0;
        for(int i = 0; i < word.length(); i++) {
            if(Objects.equals(word.charAt(i), letter.charAt(0))) {
                score++;
            }
        }
        return score;
    }

    private String decodeWord(String word, String codedWord, String letter) {
        StringBuilder result = new StringBuilder();
        for(int i = 0; i < word.length(); i++) {
            if(Objects.equals(word.charAt(i), letter.charAt(0))) {
                result.append(letter);
            }
            else {
                result.append(codedWord.charAt(i));
            }
        }
        return result.toString();
    }

    public Game playGame(Game game) throws ServicesException {
        if(game.getOver()){
            throw new ServicesException("Game is over! You won !");
        }

        if(game.getVisited().size() == 4){
            throw new ServicesException("The maximum number of moves has been reached !");
        }

        String letterUser = game.getChoosedLetter();
        String actualWord = game.getConfiguration().getActualWord();
        String actualCodedWord = game.getCodedWordProgress();
        String lettersGuessed = game.getCorrectGuesses();
        Integer actualScore = game.getScore();
        Integer scoreRound = 0;

        if(Objects.equals(actualWord, actualCodedWord)) {
            game.setOver(true);
            return game;
        }

        if(!actualWord.contains(letterUser)) {
            scoreRound = scoreRound - 2;
        }
        else if (actualWord.contains(letterUser) && !actualCodedWord.contains(letterUser)) {
            //scorul egal cu nr de aparitie al literei
            scoreRound = getScoreForALetter(actualWord, letterUser);
            //decode word
            String decodedWord = decodeWord(actualWord, actualCodedWord, letterUser);
            game.setCodedWordProgress(decodedWord);
            //adaugam litera la restul literelor gasite corect
            String finalGuesses = lettersGuessed + letterUser;
            game.setCorrectGuesses(finalGuesses);
        }
        else {
            scoreRound = 0;
        }

        Integer newScore = actualScore + scoreRound;
        game.setScore(newScore);

        //set la visited in care se retin incercarile utilizatorului
        Collection<String> newVisited = game.getVisited();
        newVisited.add(letterUser);
        game.setVisited(newVisited);

        return game;
    }



    @Override
    public Collection<Configuration> getAllConf() throws ServicesException {
        return configurationRepository.getAll();
    }

    private final int defaultThreadsNo=5;
    private void notifyUsers(Game game){
        ExecutorService executor = Executors.newFixedThreadPool(defaultThreadsNo);
        for(Map.Entry<Integer, IObserver> elem : logged.entrySet()){
            Integer id = elem.getKey();
            IObserver client = elem.getValue();
            executor.execute(() -> {
                try {
                    System.out.println("Notifying user with id: [" + id + "] that a game was ended");
                    client.endGame(gameRepository.getAll());
                } catch (ServicesException e) {
                    System.err.println("Error notifying friend " + e);
                }
            });
        }
        executor.shutdown();
    }

}
