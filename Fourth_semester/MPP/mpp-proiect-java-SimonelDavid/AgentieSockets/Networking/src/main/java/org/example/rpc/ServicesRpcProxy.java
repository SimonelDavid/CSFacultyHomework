package org.example.rpc;

import org.example.*;
import org.example.dto.BiletBuyDTO;
import org.example.dto.ListDTO;
import org.example.dto.UserDTO;
import org.example.utils.DTOUtils;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;


public class ServicesRpcProxy implements IServices {
    private String host;
    private int port;

    private IObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private BlockingQueue<Response> qresponses;
    private volatile boolean finished;
    public ServicesRpcProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses=new LinkedBlockingQueue<Response>();
    }

    public void login(Angajat user, IObserver client) throws AgentieException {
        initializeConnection();
        UserDTO udto= DTOUtils.getDTO(user);
        Request req=new Request.Builder().type(RequestType.LOGIN).data(udto).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()== ResponseType.OK){
            this.client=client;
            return;
        }
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            closeConnection();
            throw new AgentieException(err);
        }
    }

    public List<Zbor> findAll() throws AgentieException {
        Request request = new Request.Builder().type(RequestType.FINDALL).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR){
            String err = response.data().toString();
            throw new AgentieException(err);
        }
        return (List<Zbor>) response.data();
    }

    public List<Zbor> findByData(String dest, String data) throws AgentieException {
        Request request = new Request.Builder().type(RequestType.FINDDATA).data(DTOUtils.getDTO(new Zbor(0, dest, data, "", "", 0))).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR){
            String err = response.data().toString();
            throw new AgentieException(err);
        }
        return (List<Zbor>) response.data();
    }

    public void cumparaBilet(Zbor selected, Bilet bilet, int locuri, String dest, String data) throws AgentieException {
        BiletBuyDTO blt = new BiletBuyDTO(bilet.getTuristi(), bilet.getAdresa(), bilet.getLocuri(), bilet.getClient(),
                selected.getId(), selected.getDestinatie(), selected.getData(), selected.getOra(), selected.getAeroport(), selected.getLocuri(),
                locuri, dest, data);
        Request req=new Request.Builder().type(RequestType.CUMPARA).data(blt).build();
        sendRequest(req);
        Response response=readResponse();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new AgentieException(err);
        }
    }

    public void logout(Angajat user, IObserver client) throws AgentieException {
        UserDTO udto= DTOUtils.getDTO(user);
        Request req=new Request.Builder().type(RequestType.LOGOUT).data(udto).build();
        sendRequest(req);
        Response response=readResponse();
        closeConnection();
        if (response.type()== ResponseType.ERROR){
            String err=response.data().toString();
            throw new AgentieException(err);
        }
    }

    private void closeConnection() {
        finished=true;
        try {
            System.out.println("Inchidere conexiune");
            input.close();
            output.close();
            connection.close();
            client=null;
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void sendRequest(Request request)throws AgentieException {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new AgentieException("Error sending object "+e);
        }

    }

    private Response readResponse() throws AgentieException {
        Response response=null;
        try{

            response=qresponses.take();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }
    private void initializeConnection() throws AgentieException {
        try {
            System.out.println("Initializare conexiune");
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
    private void startReader(){
        Thread tw=new Thread(new ReaderThread());
        tw.start();
    }


    private void handleUpdate(Response response){
        if (response.type()== ResponseType.UPDATE){
            ListDTO dto = (ListDTO) response.data();
            System.out.println("Friend logged in ");
            try {
                client.updateLista(dto.getAll(), dto.getSome());
            } catch (AgentieException e) {
                e.printStackTrace();
            }
        }
    }

    private boolean isUpdate(Response response){
        return response.type()== ResponseType.UPDATE;
    }
    private class ReaderThread implements Runnable{
        public void run() {
            while(!finished){
                try {
                    Object response=input.readObject();
                    System.out.println("response received "+response);
                    if (isUpdate((Response)response)){
                        handleUpdate((Response)response);
                    }else{

                        try {
                            qresponses.put((Response)response);
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
}
