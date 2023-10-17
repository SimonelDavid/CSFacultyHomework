package network;


import model.Game;
import model.User;
import services.IObserver;
import services.IServices;
import services.ServicesException;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Collection;

public class ClientRpcWorker implements Runnable, IObserver {

    private IServices server;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;

    public ClientRpcWorker(IServices server, Socket connection) {
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

    @Override
    public void run() {
        while(connected){
            try {
                Object request = input.readObject();
                System.out.println("Worker - Run of ClientRpcWorker" + request);
                Response response = handleRequest((Request)request);
                System.out.println("Worker - Responese " + response);
                if (response != null){
                    sendResponse(response);
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
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



    private void sendResponse(Response response) throws IOException{
        System.out.println("Worker - Sending response " + response);
        output.writeObject(response);
        output.flush();
    }

    private static Response okResponse = new Response.Builder().type(ResponseType.OK).build();

    private Response handleRequest(Request request){
        Response response = null;
        if (request.type()== RequestType.LOGIN){
            System.out.println("Login request ..." + request.type());
            User user = (User) request.data();
            try{
                User loggedUser = server.login(user, this);
                return new Response.Builder().type(ResponseType.OK).data(loggedUser).build();
            } catch (ServicesException e) {
                connected = false;
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }
        if (request.type()== RequestType.LOGOUT){
            System.out.println("Logout request ...." + request.type());
            User user = (User) request.data();
            try{
                server.logout(user, this);
                connected = false;
                return okResponse;
            } catch (ServicesException e) {
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }
        if (request.type()== RequestType.PLAY){
            System.out.println("Play request ...." + request.type());
            Game game = (Game) request.data();
            try{
                Game playedGame = server.play(game);
                return new Response.Builder().type(ResponseType.OK).data(playedGame).build();
            } catch (ServicesException e) {
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }

        if (request.type()== RequestType.GETCONF){
            System.out.println("Get all conf ..." + request.type());
            try{
                return new Response.Builder().type(ResponseType.OK).data(server.getAllConf()).build();
            } catch (ServicesException e) {
                return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
            }
        }
        return response;
    }


    @Override
    public void endGame(Collection<Game> games) throws ServicesException {
        Response resp = new Response.Builder().type(ResponseType.ENDGAME).data(games).build();
        System.out.println("Refresh ranking " + games);
        try{
            sendResponse(resp);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
