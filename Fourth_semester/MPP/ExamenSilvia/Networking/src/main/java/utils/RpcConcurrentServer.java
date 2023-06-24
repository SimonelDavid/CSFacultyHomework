package utils;

import network.ClientRpcWorker;
import services.IServices;

import java.net.Socket;

public class RpcConcurrentServer extends AbsConcurrentServer{
    private IServices services;

    public RpcConcurrentServer(int port, IServices services){
        super(port);
        this.services = services;
        System.out.println("Game - GameRpcConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        ClientRpcWorker worker = new ClientRpcWorker(services, client);
        Thread tw = new Thread(worker);
        return tw;
    }

    @Override
    public void stop(){
        System.out.println("Stopping services ...");
    }
}
