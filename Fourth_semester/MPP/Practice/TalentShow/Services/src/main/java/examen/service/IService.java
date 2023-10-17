package examen.service;


import domain.*;

public interface IService {
     Jurry login(Jurry game, IObserver iObserver) throws MyException;
     void logout(Jurry game, IObserver iObserver) throws MyException;
     Iterable<DTO> getRanking() throws MyException;
//     String participant(Pair player_coordinates) throws MyException;
//     String setControlGameOver(Jurry jurry) throws MyException;
}
