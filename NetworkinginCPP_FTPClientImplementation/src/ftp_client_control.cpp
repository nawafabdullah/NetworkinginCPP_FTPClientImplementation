/*************
/*
/* Nawaf Alharbi
/* FTP Client
/* Oct 2019
/*
/* 
*************/


#include "ftp_client_connection.hpp"
#include "ftp_client_ui.hpp"
#include "ftp_client_control.hpp"

int controlSocket = -1;
int dataSocket = -1;
bool isControlConnected = false; 
bool isDataConnected = false;

void connectToServerControl(const char* serverIP, int serverPort)
// Sends a control connection request on severPort of a sever whose IP address is equal to serverIP.
{
  connectToServer(controlSocket,isControlConnected,serverIP,serverPort); //call function to establish connection from ftp_client_connextion
  //note: pass control socket here-
}

void connectToServerData(const char* serverIP, int serverPort)
// Sends a data connection request on severPort of a sever whose IP address is equal to serverIP.
{
 connectToServer(dataSocket,isDataConnected,serverIP,serverPort); //call function to establish connection from ftp_client_connextion
 //note: pass data socket here-
}

int sendOnControl(const char* buffer, int length)
// Sends the info in the buffer of length equal to 'length' on control connection.
//returns num of bytes sent
{
  int count = sendToRemote(controlSocket,buffer,length); //function send to remote return num of bytes sent and we will store that value in count
  // note :send control socket here-   
  return count; 
}

int sendOnData(const char* buffer, int length)
// Sends the info in the buffer of length equal to 'length' on data connection.
// Returns the actual number of bytes sent.
{
  int count = sendToRemote(dataSocket,buffer,length); //function send to remote return num of bytes sent and we will store that value in count
  //note : pass data socket here-
  return count;
}

int receiveOnControl(char* buffer, int length)
// Receives the info in the buffer of length equal to 'length' on control connection.
// Returns the actual number of bytes received.
{
  int count = receiveFromRemote(controlSocket,buffer,length); //function recive from remote return num of bytes sent and we will store that value in count -note: pass control socket here-
  return count;
}

int receiveOnData(char* buffer, int length)
// Receives the info in the buffer of length equal to 'length' on data connection.
// Returns the actual number of bytes received.

{
  int count = receiveFromRemote(dataSocket,buffer,length); //function recive from remote return num of bytes sent and we will store that value in count -note: pass data socket here-
  return count;
}

void disconnectDataConnection() //disconnect data before control
// Closes the opened data connection and sets isDataConnected to false;
{
  //disconnectFromServer(int& socketDescriptor, bool& isConnected)
  disconnectFromServer(dataSocket,isDataConnected = false); //call function to dissconnect from ftp_client_connection
}

void disconnectControlConnection()
// Closes the opened control connection and sets isControlConnected to false;
{
  //disconnectFromServer(int& socketDescriptor, bool& isConnected)
  disconnectFromServer(controlSocket,isControlConnected = false); //call function to dissconnect from ftp_client_connection 
}

bool isControlConnectionAvailable()
// Returns the value of isControlConnected.
{
  return isControlConnected;
}
bool isDataConnectionAvailable()
// Returns the value of isDataConnected.
{
  return isDataConnected;
}

