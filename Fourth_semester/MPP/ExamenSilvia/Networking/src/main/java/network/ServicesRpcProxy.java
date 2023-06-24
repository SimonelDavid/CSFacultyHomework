package network;


import model.Configuration;
import model.Game;
import model.User;
import services.IObserver;
import services.IServices;
import services.ServicesException;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Collection;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class ServicesRpcProxy implements IServices {

    private String host;
    private int port;

    private IObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private BlockingQueue<Response> qResponses;
    private volatile boolean finished;

    public ServicesRpcProxy(String host, int port){
        this.port = port;
        this.host = host;
        qResponses = new LinkedBlockingDeque<Response>();
    }

    private void closeConnection(){
        finished = true;
        try{
            input.close();
            output.close();
            connection.close();
            client = null;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendRequest(Request request) throws ServicesException {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new ServicesException("Error sending object " + e);
        }
    }

    private Response readResponse() throws ServicesException{
        Response response = null;
        try {
            response = qResponses.take();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }

    private void initializeConnection() throws ServicesException{
        try{
            connection = new Socket(host, port);
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            finished = false;
            startReader();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void startReader(){
        Thread tw = new Thread(new ReaderThread());
        tw.start();
    }

    private void handleUpdate(Response response) {
        if(response.type().equals(ResponseType.ENDGAME)){
            Collection<Game> games = (Collection<Game>) response.data();
            try {
                client.endGame(games);
            } catch (ServicesException e) {
                e.printStackTrace();
            }
        }
    }

    private boolean isUpdate(Response response) {
        return response.type().equals(ResponseType.ENDGAME);
    }

    private class ReaderThread implements Runnable{

        @Override
        public void run() {
            while (!finished){
                try{
                    Object response = input.readObject();
                    System.out.println("response recieved "  + response);
                    if(isUpdate((Response) response)){
                        handleUpdate((Response) response);
                    }else{
                        try{
                            qResponses.put((Response) response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException e) {
                    System.out.println("Reading error "+e);
                } catch (ClassNotFoundException e) {
                    System.out.println("Reading error "+e);
                }
            }
        }
    }

    @Override
    public User login(User user, IObserver client) throws ServicesException {
        initializeConnection();
        Request req = new Request.Builder().type(RequestType.LOGIN).data(user).build();
        sendRequest(req);
        Response response = readResponse();
        if( response.type() == ResponseType.OK ){
            this.client = client;
            return (User) response.data();
        }
        if(response.type() == ResponseType.ERROR){
            String err = response.data().toString();
            closeConnection();
            throw new ServicesException(err);
        }
        return null;
    }

    @Override
    public void logout(User user, IObserver client) throws ServicesException {
        Request req = new Request.Builder().type(RequestType.LOGOUT).data(user).build();
        sendRequest(req);
        Response response = readResponse();
        closeConnection();
        if(response.type().equals(ResponseType.ERROR)){
            String err = response.data().toString();
            throw new ServicesException(err);
        }
    }

    @Override
    public Game play(Game game) throws ServicesException {
        Request request = new Request.Builder().type(RequestType.PLAY).data(game).build();
        sendRequest(request);
        Response response = readResponse();
        if(response.type().equals(ResponseType.OK)){
            Game playedGame = (Game) response.data();
            return playedGame;
        }

        if(response.type().equals(ResponseType.ERROR)){
            String err = response.data().toString();
            throw new ServicesException(err);
        }

        return null;
    }

    @Override
    public Collection<Configuration> getAllConf() throws ServicesException {
        Request request = new Request.Builder().type(RequestType.GETCONF).build();
        sendRequest(request);
        Response response = readResponse();

        if(response.type().equals(ResponseType.OK)){
            Collection<Configuration> configurations = (Collection<Configuration>) response.data();
            return configurations;
        }

        if(response.type().equals(ResponseType.ERROR)){
            String err = response.data().toString();
            throw new ServicesException(err);
        }

        return null;
    }

}
