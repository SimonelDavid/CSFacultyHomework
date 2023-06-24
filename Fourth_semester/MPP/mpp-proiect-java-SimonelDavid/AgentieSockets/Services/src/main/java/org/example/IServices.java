package org.example;

import java.util.List;

public interface IServices {
    void login(Angajat user, IObserver client) throws AgentieException;
    void cumparaBilet(Zbor selected, Bilet bilet, int locuri, String dest, String data) throws AgentieException;
    void logout(Angajat user, IObserver client) throws AgentieException;
    List<Zbor> findAll() throws AgentieException;
    List<Zbor> findByData(String dest, String data) throws AgentieException;
}
