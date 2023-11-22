import java.io.*;
import java.net.*;

public class EchoTCPServer {
    private final int PORT;

    public EchoTCPServer(int port) {
        this.PORT = port;
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a port number.");
            System.exit(0);
        }

        try {
            int port = Integer.parseInt(args[0]);
            EchoTCPServer server = new EchoTCPServer(port);
            server.start();
        } catch (NumberFormatException e) {
            System.out.println("Invalid port number.");
        }
    }

    public void start() {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server started. Listening on port " + PORT);

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client connected: " + clientSocket.getInetAddress());

                Thread clientThread = new Thread(new ClientHandler(clientSocket));
                clientThread.start();
            }
        } catch (IOException e) {
            System.out.println("Server error: " + e.getMessage());
        }
    }

    private class ClientHandler implements Runnable {
        private final Socket clientSocket;

        public ClientHandler(Socket clientSocket) {
            this.clientSocket = clientSocket;
        }

        @Override
        public void run() {
            try (DataInputStream dis = new DataInputStream(clientSocket.getInputStream());
                 DataOutputStream dos = new DataOutputStream(clientSocket.getOutputStream())) {

                while (true) {
                    String clientMsg = dis.readUTF();
                    System.out.println("Client Message: " + clientMsg);

                    String processedMsg = clientMsg.replace(" ", ""); // Remove spaces from the message

                    dos.writeUTF(processedMsg);
                    System.out.println("Processed Message: " + processedMsg);
                }
            } catch (IOException e) {
                System.out.println("Client disconnected: " + clientSocket.getInetAddress());
            }
        }
    }
}