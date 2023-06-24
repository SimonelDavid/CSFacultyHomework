package rest;

import model.Configuration;
import model.DTOObject;
import model.DTOObject2;
import model.Game;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import repository.ConfigurationRepository;
import repository.GameRepository;

import java.util.Collection;
import java.util.Objects;

@CrossOrigin
@org.springframework.web.bind.annotation.RestController
@RequestMapping("/exam")
public class RestController {

    private ConfigurationRepository configurationRepository;
    private GameRepository gameRepository;

    @Autowired
    public RestController(ConfigurationRepository configurationRepository,GameRepository g) {
        this.configurationRepository = configurationRepository;
        this.gameRepository = g;
    }

    @RequestMapping(value = "/configurations", method = RequestMethod.POST)
    public ResponseEntity<?> createEntity(@RequestBody Configuration configuration){
        System.out.println("Rest - create configuration");
        configurationRepository.add(configuration);
        return new ResponseEntity<Configuration>(configuration, HttpStatus.OK);
    }

    @RequestMapping(value = "/games/{id}", method = RequestMethod.GET)
    public Collection<DTOObject2> getAllGames(@PathVariable Integer id){
        System.out.println("Rest - Get all games for one user");
        Collection<Game> games = gameRepository.getAll();
        Collection<DTOObject2> dtoObjectConfiguration = games.stream()
                .sorted((Game x, Game y) -> {
                    if (x.getScore() >= y.getScore())
                        return -1;
                    return 1;
                })
                .filter(x -> Objects.equals(x.getUser().getID(), id))
                .map(game -> {
                    return new DTOObject2(null, game.getUser().getUsername(),
                            game.getScore(), game.getCorrectGuesses());
                })
                .toList();
        Integer index = 0;
        for(DTOObject2 x : dtoObjectConfiguration){
            index ++;
            x.setRank(index);
        }
        return dtoObjectConfiguration;
    }
}
