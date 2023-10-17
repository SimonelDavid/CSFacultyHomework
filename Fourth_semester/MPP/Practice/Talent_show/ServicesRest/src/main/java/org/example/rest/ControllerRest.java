package org.example.rest;
import org.example.domain.Participant;
import org.example.domain.Rezultate;
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
import java.util.Objects;

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

    @RequestMapping(value="/participants/{id}", method = RequestMethod.GET)
    public String[] getAllGames(@PathVariable Integer id){
        System.out.println("Getting all games ...");
        try {
            Rezultate[] rez = ((List<Rezultate>) gameRepository.getAll()).toArray(new Rezultate[0]);
            List<String> gamesStrings = new ArrayList<>();
            try {
                for(Rezultate rezultat:rez){
                    if(Objects.equals(rezultat.getId(), id)){
                        Participant participant = wordRepository.getById(rezultat.getIdConfig());
                        System.out.println("Participant:"+participant);
                        System.out.println(participant.getWord());
                        String aliasplayer = participant.getWord();
                        String gameString = "{ alias: " + aliasplayer + " }";
                        gamesStrings.add(gameString);
                    }
                }
            }
            catch (Exception e){
                throw new RuntimeException(e);
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
