// WindowsMultiplayer2DTanks_Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <list>
#include <thread>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Puck.h"
#include "Player.h"
#include "Map.h"

sf::TcpSocket socket;
sf::TcpSocket socket2;
sf::UdpSocket udpSocket;
class Client {
public:
    sf::IpAddress Ip;
    unsigned short port;

    Client(sf::IpAddress Ip, unsigned short port) {
        this->Ip = Ip;
        this->port = port;
    }
};

std::list<Client> clients;

void socketCommunication(int socketNumber)
{
    //std::this_thread::sleep_for(std::chrono::seconds(time));

    if (socketNumber == 1)
    {
        while (true)
        {
            // Receive a message back from the client
            char in[128];
            std::size_t received;
            sf::Socket::Status status = sf::Socket::Status::Disconnected;

            status = socket.receive(in, sizeof(in), received);

            if (status == sf::Socket::Disconnected)
                return;
            std::cout << "Answer received from the client 1: \"" << in << "\"" << std::endl;

            status = socket2.send(in, sizeof(in));
            // Send a message to the connected client 2
            if (status == sf::Socket::Disconnected)
                return;
            std::cout << "Message sent to the client 2: \"" << in << "\"" << std::endl;
        }
    }
    else {
        while (true)
        {
            // Receive a message back from the client
            char in[128];
            std::size_t received;
            sf::Socket::Status status = sf::Socket::Status::Disconnected;

            status = socket2.receive(in, sizeof(in), received);

            if (status == sf::Socket::Disconnected)
                return;
            std::cout << "Answer received from the client 2: \"" << in << "\"" << std::endl;

            status = socket.send(in, sizeof(in));
            // Send a message to the connected client 2
            if (status == sf::Socket::Disconnected)
                return;
            std::cout << "Message sent to the client 1: \"" << in << "\"" << std::endl;
        }
    }

}

void udpSocketCommunication(int socketNumber)
{
    //std::this_thread::sleep_for(std::chrono::seconds(time));

    if (socketNumber == 1)
    {
        while (true)
        {
            // Receive a message back from the client
            char in[128];
            std::size_t received;

            Client first = clients.front();

            udpSocket.receive(in, sizeof(in), received, first.Ip, first.port);
            std::cout << "Answer received from the client 1: \"" << in << "\"" << std::endl;

            Client second = clients.back();

            // Send a message to the connected client 2
            // Send an answer
            udpSocket.send(in, sizeof(in), second.Ip, second.port);
            std::cout << "Message sent to the client 2: \"" << in << "\"" << std::endl;
        }
    }
    else {
        while (true)
        {
            // Receive a message back from the client
            char in[128];
            std::size_t received;

            Client second = clients.back();

            udpSocket.receive(in, sizeof(in), received, second.Ip, second.port);
            std::cout << "Answer received from the client 2: \"" << in << "\"" << std::endl;

            Client first = clients.front();

            // Send a message to the connected client 1
            // Send an answer
            udpSocket.send(in, sizeof(in), first.Ip, first.port);
            std::cout << "Message sent to the client 1: \"" << in << "\"" << std::endl;
        }
    }

}


////////////////////////////////////////////////////////////
/// Launch a server, wait for an incoming connection,
/// send a message and wait for the answer.
///
////////////////////////////////////////////////////////////
void runTcpServer()
{
    //bool running = true;

    //// Create a socket to listen to new connections
    //sf::TcpListener listener;
    //listener.listen(55001);
    //std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

    //// Create a list to store the future clients
    //std::list<sf::TcpSocket*> clients;
    //// Create a selector
    //sf::SocketSelector selector;
    //// Add the listener to the selector
    //selector.add(listener);
    //// Endless loop that waits for new connections
    //while (running)
    //{
    //    // Make the selector wait for data on any socket
    //    if (selector.wait())
    //    {
    //        // Test the listener
    //        if (selector.isReady(listener))
    //        {
    //            // The listener is ready: there is a pending connection
    //            sf::TcpSocket* client = new sf::TcpSocket;
    //            if (listener.accept(*client) == sf::Socket::Done)
    //            {
    //                // Add the new client to the clients list
    //                clients.push_back(client);
    //                // Add the new client to the selector so that we will
    //                // be notified when he sends something
    //                selector.add(*client);
    //                std::cout << "New Connection added to a list. " << client->getRemoteAddress() << std::endl;
    //            }
    //            else
    //            {
    //                std::cout << "Cannot handle new connection. " << std::endl;
    //                // Error, we won't get a new connection, delete the socket
    //                delete client;
    //            }
    //        }
    //        else
    //        {
    //            // The listener socket is not ready, test all other sockets (the clients)
    //            for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
    //            {
    //                sf::TcpSocket& client = **it;
    //                if (selector.isReady(client))
    //                {
    //                    // The client has sent some data, we can receive it
    //                    char in[1024];
    //                    std::size_t received;
    //                    if (client.receive(in, sizeof(in), received) != sf::Socket::Done)
    //                    {
    //                        for (std::list<sf::TcpSocket*>::iterator it_second = clients.begin(); it != clients.end(); ++it)
    //                        {
    //                            if (it_second != it) 
    //                            {
    //                                sf::TcpSocket& client_second = **it_second;
    //                                if (client_second.send(in, sizeof(int)) != sf::Socket::Done)
    //                                {
    //                                    std::cout << "Cannot send position: " << in << " To Client :( " << std::endl;
    //                                }
    //                                else
    //                                {
    //                                    std::cout << "Message sent to the client: \"" << in << "\"" << std::endl;
    //                                }
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}





    // ----- The server -----
    // Create a socket and bind it to the port 55002

    udpSocket.bind(50001);

    // Receive a message from anyone
    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;

    while (true)
    {
        std::cout << " waiting for clients on port 50001 " << std::endl;
        udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
        std::cout << sender.toString() << " said: " << buffer << std::endl;

        if (clients.size() == 0)
        {
            Client c(sender, port);
            clients.push_back(c);
        }
        else
        {
            std::cout << "List of Clients: " << std::endl;
            for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); ++it)
            {
                std::cout << "client: " << it->Ip.toString() << " " << it->port << std::endl;
                if (it->Ip == sender && it->port == port)
                    continue;
                else
                {
                    Client c(sender, port);
                    clients.push_back(c);
                }
            }

            if (clients.size() > 1)
                break;
        }
    }

    sf::IpAddress _sender;
    unsigned short _port;

    while (true)
    {
        // Receive a message back from the client
        char in[128];
        std::size_t received;

        udpSocket.receive(in, sizeof(in), received, _sender, _port);
        std::cout << "Answer received from the client: \"" << in << "\"" << std::endl;

        Client first = clients.front();
        Client second = clients.back();

        if (first.Ip == _sender && first.port == _port)
        {
            // Send a message to the connected client 1
            // Send an answer
            udpSocket.send(in, received, second.Ip, second.port);
            std::cout << "Message sent to the client " << second.Ip.toString() << ": \"" << in << "\"" << std::endl;
        }
        else
        {
            // Send a message to the connected client 1
            // Send an answer
            udpSocket.send(in, received, first.Ip, first.port);
            std::cout << "Message sent to the client " << first.Ip.toString() << ": \"" << in << "\"" << std::endl;
        }
    }

    /*std::thread bt(udpSocketCommunication, 1);
    std::cout << "async task launched for listening Client #1 \n";

    std::thread bt2(udpSocketCommunication, 2);
    std::cout << "async task launched for listening Client #2 \n";

    bt.join();
    bt2.join();*/






    /*sf::TcpListener listener;
    if (listener.listen(port) != sf::Socket::Done)
        return;
    std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;


    if (listener.accept(socket) != sf::Socket::Done)
        return;
    std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;

    sf::TcpSocket socket2;
    if (listener.accept(socket2) != sf::Socket::Done)
        return;
    std::cout << "Client 2 connected: " << socket2.getRemoteAddress() << std::endl;


    std::thread bt(socketCommunication, 1);
    std::cout << "async task launched for listening Client #1 \n";

    std::thread bt2(socketCommunication, 2);
    std::cout << "async task launched for listening Client #2 \n";

    bt.join();
    bt2.join();*/




    //// Create a server socket to accept new connections
    //sf::TcpListener listener;

    //// Listen to the given port for incoming connections
    //if (listener.listen(port) != sf::Socket::Done)
    //    return;
    //std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

    //// Wait for a connection
    //sf::TcpSocket socket;
    //if (listener.accept(socket) != sf::Socket::Done)
    //    return;
    //std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;

    //// Send a message to the connected client
    //const char out[] = "Hi, I'm the server";
    //if (socket.send(out, sizeof(out)) != sf::Socket::Done)
    //    return;
    //std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;

    //// Receive a message back from the client
    //char in[128];
    //std::size_t received;
    //if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
    //    return;
    //std::cout << "Answer received from the client: \"" << in << "\"" << std::endl;
}


////////////////////////////////////////////////////////////
/// Create a client, connect it to a server, display the
/// welcome message and send an answer.
///
////////////////////////////////////////////////////////////
void runTcpClient(unsigned short port)
{
    // Ask for the server address
    sf::IpAddress server("176.58.109.136");

    // Create a socket for communicating with the server
    sf::TcpSocket socket;

    // Connect to the server
    if (socket.connect(server, port) != sf::Socket::Done)
        return;
    std::cout << "Connected to server " << server << std::endl;

    // Receive a message from the server
    char in[128];
    std::size_t received;
    if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
        return;
    std::cout << "Message received from the server: \"" << in << "\"" << std::endl;

    // Send an answer to the server
    const char out[] = "Hi, I'm a client";
    if (socket.send(out, sizeof(out)) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
}


// a = 10 (meters) = 10 * FROM_METERE_TO_PIXEL (pixels)
const float FROM_METER_TO_PIXEL = 30.0f;
const float FROM_PIXEL_TO_METER = 1 / 30.0f;
// a = 30 (radians) = 30 * FROM_RADIAN_TO_DEGREE (degrees) 
const float FROM_RADIAN_TO_DEGREE = 180 / M_PI;
const float FROM_DEGREE_TO_RADIAN = M_PI / 180;

int main()
{
    //runTcpServer();

    sf::RenderWindow window(sf::VideoMode(1260, 720), "SFML works!");
    //sf::RenderWindow window(sf::VideoMode(1400, 1000), "SFML works!");


    sf::CircleShape puckShape(60.0f);
    sf::CircleShape playerShape(60.0f);
    sf::CircleShape playerRightShape(60.0f);
    std::vector<sf::RectangleShape> wallShapes;

    puckShape.setFillColor(sf::Color::Green);

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 0.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World* world = new b2World(gravity);

    Map map(world, 42, 24);

    Puck puck(world);
    puck.body->SetTransform(b2Vec2(10, 10), 0);
    puckShape.setRadius((puck.width / 2) * FROM_METER_TO_PIXEL);
    puckShape.setOrigin(puckShape.getGlobalBounds().width / 2, puckShape.getGlobalBounds().height / 2);


    Player player(world, b2Vec2(10, 4));
    playerShape.setRadius((player.width / 2) * FROM_METER_TO_PIXEL);
    playerShape.setOrigin(playerShape.getGlobalBounds().width / 2, playerShape.getGlobalBounds().height / 2);

    Player playerRight(world, b2Vec2(25, 4));
    playerRightShape.setRadius((playerRight.width / 2) * FROM_METER_TO_PIXEL);
    playerRightShape.setOrigin(playerRightShape.getGlobalBounds().width / 2, playerRightShape.getGlobalBounds().height / 2);

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int i = 0; i < map.walls.size(); i++)
    {
        sf::RectangleShape wallShape(sf::Vector2f(map.walls.at(i).width * 2 * FROM_METER_TO_PIXEL, map.walls.at(i).height * 2 * FROM_METER_TO_PIXEL));

        if (i == 0)
            wallShape.setFillColor(sf::Color::Blue);
        else if (i == 1)
            wallShape.setFillColor(sf::Color::Green);
        else if (i == 2)
            wallShape.setFillColor(sf::Color::Red);

        wallShape.setOrigin(wallShape.getGlobalBounds().width / 2, wallShape.getGlobalBounds().height / 2);
        wallShape.setPosition(map.walls.at(i).body->GetPosition().x * FROM_METER_TO_PIXEL, map.walls.at(i).body->GetPosition().y * FROM_METER_TO_PIXEL);

        wallShapes.push_back(wallShape);
    }

    // This is our little game loop.
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (puck.body->GetPosition().x + (puck.width / 2.0f) < 0
            || puck.body->GetPosition().x - (puck.width / 2.0f) > map.width)
        {
            puck.body->SetLinearVelocity(b2Vec2(0, 0));
            puck.body->SetTransform(b2Vec2(map.width / 2.0f, map.height / 2.0f), 0);
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            b2Vec2 MousePosition;
            if (sf::Mouse::getPosition(window).x * FROM_PIXEL_TO_METER > (map.width / 2.0f) - (player.width / 2.0f)
                && player.body->GetPosition().x + (player.width / 2.0f) + ((player.width / 2.0f) / 4.0f) >= map.width / 2.0f)
                MousePosition.Set(player.body->GetPosition().x, sf::Mouse::getPosition(window).y * FROM_PIXEL_TO_METER);
            else
                MousePosition.Set(sf::Mouse::getPosition(window).x * FROM_PIXEL_TO_METER, sf::Mouse::getPosition(window).y * FROM_PIXEL_TO_METER);

            player.MoveTo(world, MousePosition);
        }
        else
        {
            player.StopMoving(world);
        }

        float speed = 60.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerRight.body->ApplyForceToCenter(b2Vec2(speed, 0), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerRight.body->ApplyForceToCenter(b2Vec2(-1 * speed, 0), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            playerRight.body->ApplyForceToCenter(b2Vec2(0, -1 * speed), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            playerRight.body->ApplyForceToCenter(b2Vec2(0, speed), true);// ->SetLinearVelocity(b2Vec2(0, 2));

        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world->Step(timeStep, velocityIterations, positionIterations);

        puckShape.setPosition(puck.body->GetPosition().x * FROM_METER_TO_PIXEL, puck.body->GetPosition().y * FROM_METER_TO_PIXEL);
        puckShape.setRotation(puck.body->GetAngle() * FROM_RADIAN_TO_DEGREE);

        playerShape.setPosition(player.body->GetPosition().x * FROM_METER_TO_PIXEL, player.body->GetPosition().y * FROM_METER_TO_PIXEL);
        playerShape.setRotation(player.body->GetAngle() * FROM_RADIAN_TO_DEGREE);

        playerRightShape.setPosition(playerRight.body->GetPosition().x * FROM_METER_TO_PIXEL, playerRight.body->GetPosition().y * FROM_METER_TO_PIXEL);
        playerRightShape.setRotation(player.body->GetAngle() * FROM_RADIAN_TO_DEGREE);

        window.clear();
        for (int i = 0; i < wallShapes.size(); i++)
        {
            window.draw(wallShapes.at(i));
        }
        window.draw(puckShape);
        window.draw(playerShape);
        window.draw(playerRightShape);
        window.display();

    }

    // When the world destructor is called, all bodies and joints are freed. This can
    // create orphaned pointers, so be careful about your world management.




    // Wait until the user presses 'enter' key
    /*std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');*/

    return 0;
}

//int main()
//{
//    std::cout << "Hello World!\n";
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
