package org.example.rest;
import org.example.domain.Game;
import org.example.domain.Config;
import org.example.repo.IGameRepository;
import org.example.repo.IConfigRepository;
import org.example.repo.IUserRepository;
import org.example.repo.IWordRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@CrossOrigin
@RestController
@RequestMapping("/database")
public class ControllerRest {
    private static final String template = "Hello, %s!";
    @Autowired
    private IUserRepository userRepository;

    @Autowired
    private IGameRepository gameRepository;

    @Autowired
    private IConfigRepository configRepository;

    @Autowired
    private IWordRepository wordRepository;

    @RequestMapping(value="/games", method = RequestMethod.GET)
    public String[] getAllGames(){
        System.out.println("Getting all games ...");
        try {
            Game[] games = ((List<Game>) gameRepository.getAll()).toArray(new Game[0]);
            List<String> gamesStrings = new ArrayList<>();
            for(Game g : games){
                String aliasplayer = userRepository.getById(g.getIdPlayer()).getEmail();
                String playerinput = g.getPlayerInput();
                String config = configRepository.getById(g.getIdConfig()).getIdwords();
                String score = g.getScore().toString();
                String gameString = "{ alias: " + aliasplayer + ";   " +
                        "playerinput: " + playerinput + ";   " +
                        "config: " + config + ";   " +
                        "score: " + score + " }";
                gamesStrings.add(gameString);
            }
            return ((List<String>) gamesStrings).toArray(new String[0]);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @RequestMapping(value = "/configs/{id}", method = RequestMethod.PUT)
    public Config update(@PathVariable Integer id, @RequestBody Config entity) {
        System.out.println("Updating ..." + entity);
        try {
            configRepository.updatee(entity, id);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return entity;
    }

    @ExceptionHandler(Exception.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public String userError(Exception e) {
        return e.getMessage();
    }
}
