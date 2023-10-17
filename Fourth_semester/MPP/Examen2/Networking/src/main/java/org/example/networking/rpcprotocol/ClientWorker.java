package org.example.networking.rpcprotocol;

import org.example.domain.Config;
import org.example.domain.Game;
import org.example.domain.User;
import org.example.networking.dto.ConfigDTO;
import org.example.networking.dto.GameDTO;
import org.example.networking.dto.UserDTO;
import org.example.service.IObserver;
import org.example.service.IService;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.stream.StreamSupport;

public class ClientWorker implements Runnable, IObserver {
    private IService server;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;
    public ClientWorker(IService server, Socket connection) {
        this.server = server;
        this.connection = connection;
        try{
            output=new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input=new ObjectInputStream(connection.getInputStream());
            connected=true;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private Response handleRequest(Request request) {
        if (request.type() == RequestType.GET_BY_MAIL_PASSWORD) {
            var user = ((UserDTO) request.data()).fromDTO();
            try {
                var respOff = server.getByMailPassword(user.getEmail(), user.getPassword(), this);
                return new Response(ResponseType.USER, UserDTO.toDTO(respOff));
            } catch (Exception e) {
                return new Response(ResponseType.ERROR, e.getMessage());
            }
        }
        else if (request.type() == RequestType.LOGOUT) {
            var user = ((UserDTO) request.data()).fromDTO();
            try {
                server.logout(user, this);
                connected=false;
                return new Response(ResponseType.OK, 12);
            } catch (Exception e) {
                return new Response(ResponseType.ERROR, e.getMessage());
            }
        }
        else if (request.type() == RequestType.ADD_CONFIG) {
            try {
                Config added = server.addConfig();
                return new Response(ResponseType.CONFIG, ConfigDTO.toDTO(added));
            } catch (Exception e) {
                return new Response(ResponseType.ERROR, e.getMessage());
            }
        }
        else if (request.type() == RequestType.GET_GAMES) {
            try {
                GameDTO[] games = StreamSupport.stream(server.getAllGames().spliterator(), false)
                        .map(GameDTO::toDTO)
                        .toArray(GameDTO[]::new);
                System.out.println(games.length);
                for (GameDTO g : games) {
                    System.out.println(g);
                }
                return new Response(ResponseType.GAMES, games);
            } catch (Exception e) {
                return new Response(ResponseType.ERROR, e.getMessage());
            }
        }
        return null;
    }
    private void sendResponse(Response response) throws IOException{
        System.out.println("sending response "+response);
        output.writeObject(response);
        output.flush();
    }

    public void run() {
        while(connected){
            try {
                Object request=input.readObject();
                Response response=handleRequest((Request)request);
                if (response!=null){
                    sendResponse(response);
                }
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
                break;
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            System.out.println("Error "+e);
        }
    }
}
