package examen.server;

import app.rest.persistance.repository.IGameRepository;
import app.rest.persistance.repository.IPlayerRepository;
import app.rest.persistance.repository.IPositionRepository;
import app.rest.persistance.repository.IScoreRepository;
import domain.*;
import examen.service.IObserver;
import examen.service.IService;
import examen.service.MyException;

import java.time.Duration;
import java.time.LocalTime;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;


public class ServicesImpl implements IService {
    private final IPlayerRepository<Integer, Jurry> playerRepository;
    private final IGameRepository<Integer, Game> gameRepository;
    private final IScoreRepository<Integer, Rezultat> scoreRepository;
    private final IPositionRepository<Integer, Participant> positionRepository;
    private final Map<Integer, IObserver> loggedOnes;
    private final Map<Jurry, Game> gamePlayerMap = new HashMap<>();

    public ServicesImpl(IPlayerRepository<Integer, Jurry> playerRepository,
                        IGameRepository<Integer, Game> gameRepository,
                        IScoreRepository<Integer, Rezultat> scoreRepository,
                        IPositionRepository<Integer, Participant> positionRepository) {
        this.playerRepository = playerRepository;
        this.gameRepository = gameRepository;
        this.scoreRepository = scoreRepository;
        this.positionRepository = positionRepository;
        loggedOnes = new ConcurrentHashMap<>();
    }

    @Override
    public Iterable<DTO> getRanking() {
        List<DTO> list = new ArrayList<>();
        List<Rezultat> scores = (List<Rezultat>) scoreRepository.getAll();
        scores = scores.stream()
                .collect(java.util.stream.Collectors.toList());
        List<Rezultat> allScores = (List<Rezultat>) scoreRepository.getAll();
//        for (Rezultat rezultat : scores) {
//            int seconds = 0;
//            for (Rezultat score1 : allScores) {
//                if (score1.getJurry().getId().equals(rezultat.getJurry().getId()) && score1.getRound()==0
//                        && score1.getGame().getId().equals(rezultat.getGame().getId())) {
//                    Duration duration = Duration.between(score1.getTime(), rezultat.getTime());
//                    long milliseconds = duration.toMillis();
//                    seconds += milliseconds;
//                }
//            }
//            DTO dto = new DTO(rezultat.getJurry(), seconds, rezultat.getTotalPoints());
//            list.add(dto);
//        }
        // sort descending by raspuns and ascending by seconds
        list.sort((o1, o2) -> {
            if (o1.getRaspuns().equals(o2.getRaspuns()))
                return o1.getSeconds().compareTo(o2.getSeconds());
            return o2.getRaspuns().compareTo(o1.getRaspuns());
        });
        return list;
    }

//    private void update(Jurry jurry) throws MyException {
//        for (IObserver observer : loggedOnes.values()) {
//            observer.updateRanking();
//        }
//        for (Integer id : loggedOnes.keySet()) {
//            if (id.equals(jurry.getId())) {
//                loggedOnes.get(id).updateControl(jurry);
//            }
//        }
//    }

//    @Override
//    public String participant(Pair player_coordinates) throws MyException {
//        Jurry jurry = player_coordinates.getJurry();
//        Game game = gamePlayerMap.get(jurry);
//        if (game == null)
//            throw new MyException("Jurry not in game.");
//        Rezultat oldScore = scoreRepository.getLatestScoreForPlayer(jurry.getId());
//        String nume = player_coordinates.getNume();
//        String prenume = player_coordinates.getPrenume();
////        if (nume > oldScore.getRound())
////            throw new MyException("You can't participant in the future.");
////        if (nume < oldScore.getRound())
////            throw new MyException("You already guessed for this round.");
//        // verify if the coordinates are in the game
//        if ((game.getPosition1().getNume() == nume && game.getPosition1().getPrenume() == prenume) ||
//                (game.getPosition2().getNume() == nume && game.getPosition2().getPrenume() == prenume) ||
//                (game.getPosition3().getNume() == nume && game.getPosition3().getPrenume() == prenume) ||
//                (game.getPosition4().getNume() == nume && game.getPosition4().getPrenume() == prenume) ||
//                (game.getPosition5().getNume() == nume && game.getPosition5().getPrenume() == prenume)) {
////            Participant participant = positionRepository.findByRowCol(nume, prenume);
////            Rezultat newScore = new Rezultat(0, game, jurry, participant, 0, oldScore.getTotalPoints(), oldScore.getRound()+1, 1, LocalTime.now());
////            scoreRepository.add(newScore);
//            update(jurry);
//            return "You lost!";
//        }
////        Participant newPosition = new Participant(0, nume, prenume);
////        Participant participant = positionRepository.findByRowCol(nume, prenume);
////        if (participant == null) {
////            positionRepository.add(newPosition);
////            participant = positionRepository.findByRowCol(nume, prenume);
////        }
////        int raspuns = nume + 1;
////        int oldPoints = oldScore.getTotalPoints();
////        int newPoints = oldPoints + raspuns;
////        int oldRound = oldScore.getRound();
////        int newRound = oldRound + 1;
////        if (newRound == 4) {
////            Rezultat newScore = new Rezultat(0, game, jurry, participant, raspuns, newPoints, newRound, 1, LocalTime.now());
////            scoreRepository.add(newScore);
////            update(jurry);
////            return "You win!";
////        }
////        Rezultat newScore = new Rezultat(0, game, jurry, participant, raspuns, newPoints, newRound, 0, LocalTime.now());
////        scoreRepository.add(newScore);
//        return "Ok!";
//    }

//    @Override
//    public String setControlGameOver(Jurry jurry) {
//        Game game = gamePlayerMap.get(jurry);
//        gamePlayerMap.remove(jurry);
//        Rezultat oldScore = scoreRepository.getLatestScoreForPlayer(jurry.getId());
//        String control = "Points: " + oldScore.getTotalPoints() + "\n" ;
//        control += "Positions: " + game;
//        List<DTO> list = (List<DTO>) getRanking();
//        int index = 0;
//        for (int i = 0; i < list.size(); i++) {
//            if (list.get(i).getJurry().getId().equals(jurry.getId()) &&
//                    Objects.equals(list.get(i).getRaspuns(), oldScore.getTotalPoints())){
//                index = i + 1;
//                break;
//            }
//        }
//        control += "\nRanking: " + index + " out of " + list.size() + " games finished.";
//        return control;
//    }


    @Override
    public synchronized Jurry login(Jurry jurry, IObserver iObserver) throws MyException {
        Jurry toLogin = playerRepository.login(jurry.getAlias());
        if (toLogin != null) {
            if (loggedOnes.get(toLogin.getId()) != null)
                throw new MyException("User already logged in.");
            loggedOnes.put(toLogin.getId(), iObserver);
            // choose random 5 positions from positionRepository
            // at least 1 have nume = 0, 1 have nume = 1, 1 have nume = 2, 1 have nume = 3
            List<Participant> positions = (List<Participant>) positionRepository.getAll();
            List<Participant> randomPositions = new ArrayList<>();
            int row0 = 0, row1 = 0, row2 = 0, row3 = 0;
            while (randomPositions.size() < 5) {
                int randomPosition = (int) (Math.random() * positions.size());
                Participant participant = positions.get(randomPosition);
//                if (participant.getNume() == 0 && row0 == 0) {
//                    randomPositions.add(participant);
//                    row0++;
//                } else {
//                    if (participant.getNume() == 1 && row1 == 0 && !randomPositions.contains(participant)) {
//                        randomPositions.add(participant);
//                        row1++;
//                    } else {
//                        if (participant.getNume() == 2 && row2 == 0 && !randomPositions.contains(participant)) {
//                            randomPositions.add(participant);
//                            row2++;
//                        } else {
//                            if (participant.getNume() == 3 && row3 == 0 && !randomPositions.contains(participant)) {
//                                randomPositions.add(participant);
//                                row3++;
//                            } else {
//                                if (!randomPositions.contains(participant))
//                                    randomPositions.add(participant);
//                            }
//                        }
//                    }
//                }
            }
            Game game = new Game(0, randomPositions.get(0), randomPositions.get(1), randomPositions.get(2), randomPositions.get(3), randomPositions.get(4));
            gameRepository.add(game);
            gamePlayerMap.put(toLogin, game);
            Rezultat rezultat = new Rezultat(0, toLogin, new Participant(0,"-1","-1"), "PENDING");
            scoreRepository.add(rezultat);
        } else
            throw new MyException("Authentication failed.");
        return toLogin;
    }

    @Override
    public synchronized void logout(Jurry game, IObserver iObserver) throws MyException {
        IObserver localClient = loggedOnes.remove(game.getId());
        if (localClient == null)
            throw new MyException("User " + game.getId() + " is not logged in.");
    }

}
