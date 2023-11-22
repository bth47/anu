import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;

public class EchoTCPClient {
    private Socket socket;
    private DataInputStream dis;
    private DataOutputStream dos;
    private TextArea memo;
    private TextField field;
    private Label label;
    private Button connectButton;

    private final String serverAddress;
    private final int serverPort;

    private boolean isConnected;

    public EchoTCPClient(String serverAddress, int serverPort) {
        this.serverAddress = serverAddress;
        this.serverPort = serverPort;
        isConnected = false;
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide a server address and port number.");
            System.exit(0);
        }

        String serverAddress = args[0];
        int serverPort = Integer.parseInt(args[1]);

        EchoTCPClient client = new EchoTCPClient(serverAddress, serverPort);
        client.run();
    }

    public void run() {
        Frame mainFrame = new Frame("Echo Client");
        mainFrame.addWindowListener(new ExitListener());
        mainFrame.setLayout(new BorderLayout());
        mainFrame.setFont(new Font("Arial", Font.PLAIN, 20));
        mainFrame.setSize(800, 600);

        label = new Label("Server: Connection completed!");
        label.setAlignment(Label.CENTER);

        memo = new TextArea();
        memo.setEditable(false);
        memo.append("Please enter a sentence from remove space button. \n");

        field = new TextField();
        field.setColumns(50);
        field.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Do nothing when Enter key is pressed
            }
        });

        Button removeSpaceButton = new Button("Remove Space");
        removeSpaceButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                removeSpace();
            }
        });

        Button disconnectButton = new Button("Disconnect");
        disconnectButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                disconnect();
            }
        });

        connectButton = new Button("Connect");
        connectButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                connect();
            }
        });

        Panel buttonPanel = new Panel();
        buttonPanel.setLayout(new GridLayout(3, 1));
        buttonPanel.add(removeSpaceButton);
        buttonPanel.add(disconnectButton);
        buttonPanel.add(connectButton);

        Panel mainPanel = new Panel();
        mainPanel.setLayout(new BorderLayout());
        mainPanel.add(label, BorderLayout.NORTH);
        mainPanel.add(memo, BorderLayout.CENTER);
        mainPanel.add(field, BorderLayout.SOUTH);
        mainPanel.add(buttonPanel, BorderLayout.EAST);

        mainFrame.add(mainPanel);
        mainFrame.setVisible(true);

        connect();
    }

    private void connect() {
        if (isConnected) {
            return;
        }

        try {
            socket = new Socket(serverAddress, serverPort);
            dis = new DataInputStream(socket.getInputStream());
            dos = new DataOutputStream(socket.getOutputStream());
            isConnected = true;
            label.setText("Server: Connection completed!");
            label.setForeground(Color.BLUE);
        } catch (IOException e) {
            memo.append("Can't open socket.\n");
        }
    }

    private void disconnect() {
        if (!isConnected) {
            return;
        }

        try {
            if (socket != null) {
                socket.close();
            }
            isConnected = false;
            label.setText("Server: Disconnection completed!");
            label.setForeground(Color.RED);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void sendMessage() {
        if (!isConnected) {
            return;
        }

        String sendMsg = field.getText();
        try {
            dos.writeUTF(sendMsg);
            dos.flush();
        } catch (IOException e) {
            memo.append("Sending error\n");
        }

        memo.append("Client Message: " + sendMsg + "\n");
        field.setText("");

        try {
            String recvMsg = dis.readUTF();
            memo.append("Server Message: " + recvMsg + "\n");
        } catch (IOException e) {
            memo.append("Read error\n");
        }
    }

    private void removeSpace() {
        if (!isConnected) {
            return;
        }

        String sendMsg = field.getText();
        String processedMsg = sendMsg.replace(" ", "");

        memo.append("Client Message: " + sendMsg + "\n");

        field.setText("");

        try {
            dos.writeUTF(processedMsg);
            dos.flush();
            String recvMsg = dis.readUTF();
            memo.append("Server Message: " + recvMsg + "\n");
        } catch (IOException e) {
            memo.append("Sending/Receiving error\n");
        }
    }

    private class ExitListener extends WindowAdapter {
        public void windowClosing(WindowEvent e) {
            disconnect();
            System.exit(0);
        }
    }
}