# Computer Networks
Send a command to a receiver side and they run it and send the output back to you.
Sender/Server Code:
The sender/server code establishes a connection with a client and allows the client to send commands to execute on the server. It creates a socket, prompts the user to enter the IP address they want to connect to, and establishes a TCP connection with the specified server IP address and port number. The code then enters a loop where it prompts the user to enter a command, sends the command to the client, and receives the output from the server. The received output is printed on the console. The loop continues until the user enters the command "exit" to close the connection. Finally, the server socket is closed.

Client/Receiver Code:
The client/receiver code listens for incoming connections from the sender. It creates a socket, binds it to a port, and listens for incoming connections. Once a connection is established, it accepts the connection and enters a loop to receive commands from the sender. It receives the command, executes it using a pipe, and redirects the output to a temporary file. Then, it sends the contents of the temporary file back to the sender. The loop continues until the sender closes the connection. Finally, the client and server sockets are closed.
