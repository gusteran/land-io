#include "driver.h"

void *startGameClock(void *arg) {
    auto start = std::chrono::steady_clock::now();
    Board board;
    short botId = 1;
    int ticks = 0;

    for (int i = 0; i < MAX_PLAYERS; i++) {

        std::string name = "Bot" + std::to_string(botId);
        Player *player = new Bot(botId++, name);

        bool res = board.addBot(player);
        std::cout << res << std::endl;
    }

    while (1) {
        std::cout << std::endl;

        auto end = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                .count();
        std::cout << "Running board update at " << time << " ms" << std::endl;

        if (time > GAME_DURATION) {
            std::cout << "Game Over!\n";
            return nullptr;
        }

        if (!board.update()) {
            std::cout << "Board update failed\n";
            return nullptr;
        }

        board.printBoard();

        ticks++;
        end = std::chrono::steady_clock::now();
        time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                .count();

        time -= ticks * SLEEP_TIME;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(SLEEP_TIME - time));
    }
    return nullptr;
}

// Using this article:
// https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
// Only allows as many sockets as max players
#define PORT 8888
#define MAX_CLIENTS MAX_PLAYERS
#define BUFFER_SIZE 1024
#define MAX_PENDING 3

void handleSocket() {
    int opt = true;
    int master_socket, addrlen, new_socket, client_socket[MAX_CLIENTS],
        activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[BUFFER_SIZE + 1];

    // set of socket descriptors
    fd_set readfds;

    std::string message = "HTTP/1.1 101 Switching Protocols \
        Upgrade: websocket \
        Connection: Upgrade \
        Sec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk= \
        Sec-WebSocket-Protocol: chat";

    // Initialize all client sockets
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_socket[i] = 0;
    }

    /// Creates a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    // sets the master socket to allow multiple clients
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) <
        0) {
        std::cerr << "setsockopt failed" << std::endl;
        return;
    }

    // type of socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // binds the socket to the port specified
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return;
    }

    std::cout << "Master listening on port " << PORT << std::endl;

    // sets the maximum pending connections
    if (listen(master_socket, MAX_PENDING) < 0) {
        std::cerr << "Listen failed from too many clients" << std::endl;
        return;
    }

    // accepts the new connection
    addrlen = sizeof(address);
    puts("Accepting connection");

    while (true) {
        // clears the sockket set
        FD_ZERO(&readfds);

        // add master socket to the set of sockets
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        // adds the child sockets to the set of sockets
        for (i = 0; i < MAX_CLIENTS; i++) {
            // socket descriptor
            sd = client_socket[i];

            // adds valid sockets to the read list
            if (sd > 0) {
                FD_SET(sd, &readfds);
            }

            // sets thee highest file descriptor number
            if (sd > max_sd) {
                max_sd = sd;
            }
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) {
            std::cerr << "select failed" << std::endl;
            return;
        }

        // handles incoming connections
        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address,
                                     (socklen_t *)&addrlen)) < 0) {
                std::cerr << "Accept failed" << std::endl;
                return;
            }

            std::cout << "Accepted connection on socket " << new_socket
                      << " from " << inet_ntoa(address.sin_addr) << ":"
                      << ntohs(address.sin_port) << std::endl;

            // sends the acknowledge message
            // if (send(new_socket, message.c_str(), message.length(), 0) !=
            //     message.length()) {
            //     std::cerr << "Send failed" << std::endl;
            //     return;
            // }

            puts("Connection accepted and acknowledged");

            for (i = 0; i < MAX_CLIENTS; i++) {
                // adds the client if the socket is empty
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        // handles IO from other clients
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];
            // if (sd > 0) {
            //     std::cout << "Client " << i << " connected" << std::endl;
            // }

            if (FD_ISSET(sd, &readfds)) {
                // reads the message and checks if it is closing connection
                if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0) {
                    // handles the disconnect
                    getpeername(sd, (struct sockaddr *)&address,
                                (socklen_t *)&addrlen);
                    std::cout << "Client disconnected from "
                              << inet_ntoa(address.sin_addr) << ":"
                              << ntohs(address.sin_port) << std::endl;

                    // closes the  socket
                    close(sd);
                    client_socket[i] = 0;
                } else {
                    // prints the incoming message
                    buffer[valread] = '\0';
                    std::cout << buffer << std::endl;
                    // for(int j = 0; j < 8; j++) {
                    //     unsigned char bits1 = 0, bits2 = 0;
                    //     for(int k = 0; k < valread; k++) {
                    //         bits2 = buffer[k] & 0x07;
                    //         buffer[k] >>= 3;
                    //         buffer[k] |= bits1 << 5;
                    //         bits1 = bits2;
                    //     }
                    //     buffer[valread] = '\0';
                    //     std::cout << (buffer + j) << std::endl;
                    // }

                    

                    std::string recv = std::string(buffer);
                    if (recv.find("Sec-WebSocket-Key:") != std::string::npos) {
                        std::string key = recv.substr(
                            recv.find("Sec-WebSocket-Key:") + 19, 24);
                        // key = "dGhlIHNhbXBsZSBub25jZQ==";
                        int resSize = key.size()-4; // magic?
                        key += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
                        std::cout << "Sec-WebSocket-Key: " << key << std::endl;

                        // base64_encode(SHA1(key.c_str()));
                        unsigned char balls[key.size()]; // might need larger balls
                        auto d = (const unsigned char *)key.c_str();
                        std::cout << "size of the encoded key: "
                                  << strlen(key.c_str())
                                  << " balls " << d
                                  << std::endl;
                        SHA1(d, key.size(), balls);
                        // std::string balls2 = std::string(balls); // now we
                        // have a pair. Hopefully the same size.
                        auto b64 = base64_encode(
                            balls, resSize); // double-checking balls size
                        std::cout << "base64_encode: " << b64.c_str() << std::endl;
                        std::string res =
                            "HTTP/1.1 101 Switching Protocols \r\n";
                        res += "Connection: Upgrade \r\n";
                        res += "Upgrade: websocket \r\n";
                        res += "Sec-WebSocket-Accept: " + b64 + "\r\n\r\n";

                        if (send(sd, res.c_str(), res.length(), 0) !=
                            res.length()) {
                            std::cerr << "Send failed" << std::endl;
                            return;
                        }
                        // C# implementation of this thing
                        // byte[] swkaSha1 =
                        // System.Security.Cryptography.SHA1.Create().ComputeHash(Encoding.UTF8.GetBytes(swka));
                        // string swkaSha1Base64 =
                        // Convert.ToBase64String(swkaSha1);
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}