package app.services.rest;

import app.rest.persistance.repository.IGameRepository;
import app.rest.persistance.repository.IPositionRepository;
import app.rest.persistance.repository.IScoreRepository;
import domain.DTORest;
import domain.Game;
import domain.Participant;
import domain.Rezultat;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.Duration;
import java.util.ArrayList;
import java.util.List;

@CrossOrigin
@RestController
@RequestMapping("/app")
public class EntityController {

    @Autowired
    private IScoreRepository<Integer, Rezultat> scoreRepository;
    @Autowired
    private IPositionRepository<Integer, Participant> positionRepository;
    @Autowired
    private IGameRepository<Integer, Game> gameRepository;

//    @RequestMapping(value = "players/{id}", method = RequestMethod.GET)
//    public DTORest[] getAllGamesForPlayer(@PathVariable Integer id) {
//        System.out.println("Get games for jurry with id = " + id);
//        List<Rezultat> allScores = (List<Rezultat>) scoreRepository.getAll();
//        List<Rezultat> scores = (List<Rezultat>) scoreRepository.getAll();
//        // get all scores for jurry with id stream
//        scores = scores.stream()
//                .filter(rezultat -> rezultat.getJurry() != null)
//                .filter(rezultat -> rezultat.getJurry().getId().equals(id))
//                .filter(rezultat -> rezultat.getGameOver() == 1)
//                .collect(java.util.stream.Collectors.toList());
//        DTORest[] dtos = new DTORest[scores.size()];
//        int i = 0;
//        for (Rezultat rezultat : scores) {
//            int seconds = 0;
//            List<Participant> positions = new ArrayList<>();
//            for (Rezultat score1 : allScores) {
//                if (score1.getJurry().getId().equals(id) && score1.getRound() == 0
//                        && score1.getGame().getId().equals(rezultat.getGame().getId())) {
//                    Duration duration = Duration.between(score1.getTime(), rezultat.getTime());
//                    long milliseconds = duration.toMillis();
//                    seconds += milliseconds;
//                }
//                if (score1.getJurry().getId().equals(id) && score1.getRound() != 0
//                        && score1.getGame().getId().equals(rezultat.getGame().getId())) {
//                    positions.add(positionRepository.findById(score1.getGuess().getId()));
//                }
//            }
//            DTORest dto = new DTORest(rezultat.getGame(), positions, rezultat.getTotalPoints(), seconds);
//            dtos[i] = dto;
//            i++;
//        }
//        return dtos;
//    }

//    @CrossOrigin
//    @RequestMapping(value = "/games/{id}", method = RequestMethod.PUT)
//    public ResponseEntity<?> changeOnePositionAtGame(@PathVariable Integer id, @RequestBody Participant participant) {
//        if (participant.getNume() < 0 || participant.getNume() > 3)
//            return new ResponseEntity<>("Row must be between 0 and 3", HttpStatus.BAD_REQUEST);
//        if (participant.getPrenume() < 0 || participant.getPrenume() > 3)
//            return new ResponseEntity<>("Col must be between 0 and 3", HttpStatus.BAD_REQUEST);
//        Participant currentPosition = positionRepository.findByRowCol(participant.getNume(), participant.getPrenume());
//        if (currentPosition == null) {
//            positionRepository.add(participant);
//            participant.setId(positionRepository.getMaxId());
//            currentPosition = participant;
//        }
//        int random = (int) (Math.random() * 5);
//        Game game = gameRepository.findById(id);
//        if (game == null)
//            return new ResponseEntity<>("Game not found", HttpStatus.BAD_REQUEST);
//        if (random == 0)
//            game.setPosition1(currentPosition);
//        if (random == 1)
//            game.setPosition2(currentPosition);
//        if (random == 2)
//            game.setPosition3(currentPosition);
//        if (random == 3)
//            game.setPosition4(currentPosition);
//        if (random == 4)
//            game.setPosition5(currentPosition);
//        gameRepository.update(game);
//        return new ResponseEntity<>(game, HttpStatus.OK);
//    }
}
