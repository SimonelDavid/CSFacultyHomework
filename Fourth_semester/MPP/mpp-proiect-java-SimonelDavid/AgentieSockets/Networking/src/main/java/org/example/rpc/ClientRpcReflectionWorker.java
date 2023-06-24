package org.example.rpc;

import org.example.*;
import org.example.dto.BiletBuyDTO;
import org.example.dto.ListDTO;
import org.example.dto.UserDTO;
import org.example.utils.DTOUtils;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.util.Collection;
import java.util.List;


public class ClientRpcReflectionWorker implements Runnable, IObserver {
    private IServices server;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;
    public ClientRpcReflectionWorker(IServices server, Socket connection) {
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

    public void run() {
        while(connected){
            try {
                Object request=input.readObject();
                Response response=handleRequest((Request)request);
                if (response!=null){
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

    public void updateLista(List<Zbor> l1, List<Zbor> l2) throws AgentieException {
        Response resp=new Response.Builder().type(ResponseType.UPDATE).data(new ListDTO((List<Zbor>) l1, (List<Zbor>) l2)).build();
        System.out.println("Updated list ");
        try {
            sendResponse(resp);
        } catch (IOException e) {
            throw new AgentieException("Sending error: "+e);
        }
    }

    private static Response okResponse=new Response.Builder().type(ResponseType.OK).build();
    //  private static Response errorResponse=new Response.Builder().type(ResponseType.ERROR).build();
    private Response handleRequest(Request request){
        Response response=null;
        String handlerName="handle"+(request).type();
        System.out.println("HandlerName "+handlerName);
        try {
            Method method=this.getClass().getDeclaredMethod(handlerName, Request.class);
            response=(Response)method.invoke(this,request);
            System.out.println("Method "+handlerName+ " invoked");
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }

        return response;
    }

    private Response handleLOGIN(Request request){
        System.out.println("Login request ..."+request.type());
        UserDTO udto=(UserDTO)request.data();
        Angajat user=DTOUtils.getFromDTO(udto);
        try {
            server.login(user, this);
            return okResponse;
        } catch (AgentieException e) {
            connected=false;
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleLOGOUT(Request request){
        System.out.println("Logout request...");
        UserDTO udto=(UserDTO)request.data();
        Angajat user=DTOUtils.getFromDTO(udto);
        try {
            server.logout(user, this);
            connected=false;
            return okResponse;

        } catch (AgentieException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleFINDALL(Request request){
        try{
            System.out.println("findall handler");
            List<Zbor> zboruri = server.findAll();
            System.out.println(zboruri);
            return new Response.Builder().type(ResponseType.OK).data(zboruri).build();
        } catch (AgentieException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleFINDDATA(Request request){
        UserDTO dto = (UserDTO) request.data();
        Zbor info = DTOUtils.getZborFromDTO(dto);
        try{
            List<Zbor> filtered = server.findByData(info.getDestinatie(), info.getData());
            return new Response.Builder().type(ResponseType.OK).data(filtered).build();
        } catch (AgentieException e){
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleCUMPARA(Request request){
        System.out.println("Cumpara request ...");
        BiletBuyDTO dto = (BiletBuyDTO) request.data();
        Zbor zbor = DTOUtils.getZborFromD(dto);
        Bilet bilet = DTOUtils.getBiletFromD(dto);
        int locuri = DTOUtils.getLocuriFromD(dto);
        try {
            server.cumparaBilet(zbor, bilet, locuri, dto.getDest_(), dto.getData_());
            return okResponse;
        } catch (AgentieException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private void sendResponse(Response response) throws IOException{
        System.out.println("sending response "+response);
        output.writeObject(response);
        output.flush();
    }
}