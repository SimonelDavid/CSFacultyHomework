package org.example.networking.utils;
import org.example.networking.rpcprotocol.ClientWorker;
import org.example.service.IService;

import java.net.Socket;

public class RpcConcurrentServer extends AbstractConcurrentServer {
    private IService server;
    public RpcConcurrentServer(int port, IService server) {
        super(port);
        this.server = server;
        System.out.println("RpcConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        ClientWorker worker = new ClientWorker(server, client);

        Thread tw = new Thread(worker);
        return tw;
    }

    @Override
    public void stop(){
        System.out.println("Stopping services ...");
    }
}
