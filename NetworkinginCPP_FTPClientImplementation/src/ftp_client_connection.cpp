/*************
/*
/* Nawaf Alharbi
/* FTP Client
/* Oct 2019
/*
/* 
*************/



#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include "ftp_client_connection.hpp"

//void connectToServer(int socketDescriptor, bool isConnected, const char* serverIP, int serverPort);
// Sends a connection request on severPort of a sever whose IP address is equal to serverIP.
// If a connection has been established as a result of the request sets the connection descriptor value 
// to reference 'socketDescriptor' and sets reference 'isConnected' to true.

struct sockaddr_in server_address;

void connectToServer(int &socketDescriptor, bool &isConnected, const char* serverIP, int serverPort)
{
// Sends a connection request on severPort of a sever whose IP address is equal to serverIP.
  
  // we need to specify where to connect to. i.e server. 
  // so we create ......  
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0); //create a socket, socket () function returns descriptor, 0 is default protocole/TCP
  server_address.sin_family = AF_INET; 
  server_address.sin_port = htons(serverPort); //htons does conversion for IP address to appropriate data type,, //PASS ADDRESS 
  server_address.sin_addr.s_addr = inet_addr(serverIP); // INADDR_ANY indicate local host 0.0.0.0
  // end of defining address to connect to 

  int connection_status =  connect (socketDescriptor, (struct sockaddr *) &server_address, sizeof(server_address)); //pass struct, a pointer, and the size  
  if (connection_status == 0)
  {
    printf (" CONNECTION SUCCESFUL! Connection staus is  %i \n",  connection_status);       	
    isConnected = true;  
  } else 
  {
  printf (" CONNECTION FAILED! Connection staus is  %i",  connection_status);  
  }
}


void disconnectFromServer(int& socketDescriptor, bool& isConnected)
{
// Closes network connection represented by reference 'socketDescriptor' and
// sets reference 'isConnected' to false.
  int disconnection_status = close(socketDescriptor);
  if (disconnection_status != 0)
  {
    perror ("connection coud not be succefully closed"); 
  }
  printf("connection has been succesfully closed \n"); 
  isConnected = false; 
  exit(1);
}
    
int sendToRemote(int sockDescriptor, const char* message, int messageLength)
// Sends 'message' of length 'messageLength' bytes to the server 
// on the network connection represented by 'sockDescriptor'.
{
  int status = send(sockDescriptor, message, messageLength,0); //recive will ask the server to send a response
  if (status == -1)
    {
      perror("could not recive from server");
      return 0;
    }
//  printf(" The server responded with: %s", message);
  return status;
}

int receiveFromRemote(int sockDescriptor, char* message, int messageLength)
// Receives 'message' of length 'messageLength' bytes from the server 
// on the network connection represented by 'sockDescriptor'
{
  int status = recv(sockDescriptor, message, messageLength,0); //recive will ask the server to send a response
  if (status == -1)
    {
      perror("could not recive from server");
      return 0;
    }  
//  printf(" The server responded with: %s", message);
    return status;
}
