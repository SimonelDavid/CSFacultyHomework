package org.example.networking.rpcprotocol;

import org.example.domain.Config;
import org.example.domain.Game;
import org.example.domain.User;
import org.example.networking.dto.ConfigDTO;
import org.example.networking.dto.GameDTO;
import org.example.networking.dto.UserDTO;
import org.example.service.IObserver;
import org.example.service.IService;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Arrays;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ServiceProxy implements IService {
    private String host;
    private int port;

    private IObserver client;
    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private BlockingQueue<Response> qresponses =new LinkedBlockingQueue<Response>();;

    private volatile boolean finished;
    public ServiceProxy(String host, int port) {
        System.out.println(host);
        System.out.println(port);
        this.host = host;
        this.port = port;
    }

    @Override
    public User getByMailPassword(String email, String password, IObserver client) throws Exception {
        try {
            this.client = client;
            initializeConnection();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        sendRequest(new Request(RequestType.GET_BY_MAIL_PASSWORD, new UserDTO(0, email, password)));
        this.client=client;
        var response = readResponse();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new Exception(err);
        }
        System.out.println(response.data());
        var user = ((UserDTO)response.data()).fromDTO();
        System.out.println(response);
        System.out.println(user);
        return user;
    }

    @Override
    public void logout(User user, IObserver client) throws Exception {
        sendRequest(new Request(RequestType.LOGOUT, new UserDTO(user.getId(), user.getEmail(), user.getPassword())));
        Response response=readResponse();
        closeConnection();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new Exception(err);
        }
    }

    @Override
    public Config addConfig() throws Exception {
        sendRequest(new Request(RequestType.ADD_CONFIG, null));
        var response = readResponse();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new Exception(err);
        }
        System.out.println(response.data());
        var config = ((ConfigDTO)response.data()).fromDTO();
        System.out.println(response);
        System.out.println(config);
        return config;
    }

    @Override
    public Iterable<Game> getAllGames() throws Exception {
        sendRequest(new Request(RequestType.GET_GAMES, null));
        var response = readResponse();
        var games = Arrays.stream(((GameDTO[])response.data())).map(GameDTO::fromDTO).toList();
        games.forEach(System.out::println);
        System.out.println(response);
        return games;
    }

    private void sendRequest(Request request)throws Exception {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new Exception("Error sending object "+e);
        }

    }

    private Response readResponse() throws Exception {
        Response response=null;
        try{

            response=qresponses.take();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }
    private void initializeConnection() throws Exception {
        try {
            connection=new Socket(host,port);
            output=new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input=new ObjectInputStream(connection.getInputStream());
            finished=false;
            startReader();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void closeConnection() {
        finished=true;
        try {
            input.close();
            output.close();
            connection.close();
            client=null;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void startReader(){
        Thread tw=new Thread(new ReaderThread());
        tw.start();
    }


    private void handleUpdate(Response response){
    }

    private class ReaderThread implements Runnable{
        public void run() {
            while(!finished){
                try {
                    Object response = input.readObject();
                    System.out.println("response received " + response);
                    /*if (((Response) response).type()==ResponseType.UPDATE_CONNECTED ||
                            ((Response) response).type()==ResponseType.UPDATE_START_GAME ||
                            ((Response) response).type()==ResponseType.UPDATE_END_GAME) {
                        handleUpdate((Response) response);
                    } else {*/
                        try {
                            qresponses.put((Response) response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    //}
                }catch (EOFException e) {
                    continue;
                }catch (IOException | ClassNotFoundException e) {
                    //throw new RuntimeException(e);
                }
            }
        }
    }
}
