/*************
/*
/* Nawaf Alharbi
/* FTP Client
/* Oct 2019
/*
/* 
*************/



//#include "../include/ftp_client_control.hpp"
#include "ftp_client_control.hpp"
#include "ftp_client_ui.hpp"
#include "ftp_server_response.hpp"
#include "ftp_client_command.hpp"

//#include "../include/ftp_client_ui.hpp"
//#include "../include/ftp_server_response.hpp"
//#include "../include/ftp_client_command.hpp"
//#include " "

#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#define ftpResponseMaxLength 1024


//Enumeration pasvNextCmd is used to pass parameter to function handlePassive()
//to keep track what will be the next command after the passive command
//enum pasvNextCmd {PASV_NLST, PASV_RETR}; 

void handleCommandHelp()
{
  printf( " help                    Gives the list of FTP commands available and how to use them. \n" 
          " user    <username>      Sumbits the <username> to FTP server for authentication. \n" 
          " pass    <password>      Sumbits the <password> to FTP server for authentication. \n"
          " pwd                     Requests FTP server to print current directory. \n" 
          " dir                     Requests FTP server to list the entries in the current directory. \n" 
          " cwd     <dirname>       Requests FTP server to change current working directory. \n" 
          " cdup                    Requests FTP server to change current directory to parent directory. \n" 
          " get     <filename>      Requests FTP server to send the file with <filename>. \n" 
          " quit                    Requests to end FTP session and quit. \n");
}
  
void handleCommandUser(std::string username)
// Sends a 'USER <username>' request meesage to the FTP Server.
{
  std::string concate_command = "USER " + username; // add and store USER command and concatenates the username passed to the function to the string after space  
  handleSimpleCommandResponse(concate_command, true);
}

void handleCommandPassword(std::string password)
// Sends a 'PASS <password>' request message to the FTP Server.
{
  std::string concate_command =  "PASS " + password; // adds PASS command and concatenates the password passed to the function to the string after space
  handleSimpleCommandResponse(concate_command, true);
}

void handleCommandDirectory()
{
	// send pasive command to function handelPassive 
    handlePassive(PASV_NLST);
    if(isDataConnectionAvailable())
    {
        handleNLIST();
    }
}

void handleCommandPrintDirectory()
// Sends a 'PWD' request message to FTP Server.
// Receives the response from the server.
// If the response is successful, displays the name of the current working directory of the server.
// Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter false 
// to perform the activities mentioned above.
{
  std::string concate_command = "PWD"; // store command PWD that prints directory  
  handleSimpleCommandResponse(concate_command, false);
}

void handleCommandChangeDirectory(std::string path)
// Sends a 'CWD <path>' request message to the FTP Server.
{
  std::string concate_command = "CWD " + path; // add and store CWD command and concatenates the path of the new directory we want to change to the string after space
  handleSimpleCommandResponse(concate_command, false);
}

void handleCommandChangeDirectoryUp()
// Sends a 'CDUP' request message to FTP Server.
{
  std::string concate_command = "CDUP"; // store CDUP command that returns to parent dir   
  handleSimpleCommandResponse(concate_command, false);
}

void handleCommandGetFile(std::string filename)
{
    handlePassive(PASV_RETR);
    if(isDataConnectionAvailable())
    {
        handleRETR(filename);
    }
}
// First sends a 'PASV' request message to the FTP server.
void handleCommandQuit()
// Sends a 'QUIT' request message to FTP Server.
{
  std::string concate_command = "QUIT"; // adds USER command and concatenates the username passed to the function to the string after space
  handleSimpleCommandResponse(concate_command, false);
   // should i disconnect here??????
  disconnectControlConnection();
}

void handlePassive(pasvNextCmd pasvNext)
// Sends a 'PASV' request message to the FTP server.
// Receives the response against PASV request message from the server.
// If the response is a successful one, retrives data-connection listener port number form the response.
// Retrives data-connection listener port number form the response 
// using function getHostIPAndPortFromPassiveSuccessResponse().
// Requests a data connection to the server on the listener port at the server.
{
    std::string concate_command = "PASV"; 
    sendOnControl(concate_command.c_str(), FTP_COMMAND_MAX_LENGTH); 
    char* response = new char[ftpResponseMaxLength];
    memset(response, '\0', ftpResponseMaxLength);  
    char* hostIP = new char[ftpResponseMaxLength]; 
    memset(hostIP, '\0', ftpResponseMaxLength); 
    int hostPort;
    if(receiveOnControl(response, ftpResponseMaxLength) != -1) // test if recieving the response went fine
     {
            if(strcmp(response,INVALID_USERNAME_RESPONSE) == 0 || strcmp(response,NOT_LOGGED_IN_RESPONSE) == 0)
            {
              printf("could NOT recieve response.. \n could not authnticate \n\n  Quitting the applicattion...");
              handleCommandQuit();
            }else{
                showFtpResponse(response);
                getHostIPAndPortFromPassiveSuccessResponse(response,hostIP,hostPort);     
                connectToServerData(hostIP,hostPort);
                  //  std::cout << "hostIP: "<< hostIP << std::endl;
                  //  std::cout << "Port: "<< hostPort << std::endl;
            }
     }
    delete [] response;
    delete [] hostIP;
}

void handleNLIST()
// Sends a 'NLST' request message to the server on the control connection.
// Receives the response against NLST request from the server on the control connection.
// If the response is successful, retrieves the list of entries in server's current directory 
// on the data connection.
// Displays the list of entries to the user.
{
  std::string concate_command = "NLST"; 
  sendOnControl(concate_command.c_str(), FTP_COMMAND_MAX_LENGTH); // call the function sendOnControl from ftp_client_control.cpp and pass it the command and previously declared length to preform communication with server
  char* store_list = new char[DATA_SOCKET_RECEIVE_BUFFER_SIZE]; //64K 
  char* response = new char[ftpResponseMaxLength]; // define char* array to hold the servr response as per main
  memset(response, '\0', ftpResponseMaxLength); // free memory buffer

  if(receiveOnControl(response, ftpResponseMaxLength) != -1) // test if recieving the response went fine
 {
    showFtpResponse(response);

    if(receiveOnControl(response, ftpResponseMaxLength) != -1)
    {
        showFtpResponse(response);
        receiveOnData(store_list, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
        showFtpDirResponse(store_list);
    }
 }

}
  
void handleRETR(std::string filename)
// Sends a 'RETR <filename>' request message to the server on the control connection.
{
  std::string concate_command = "RETR " + filename; 
  sendOnControl(concate_command.c_str(), FTP_COMMAND_MAX_LENGTH); // call the function sendOnControl from ftp_client_control.cpp and pass it the command and previously declared length to preform communication with server

  // int ftpResponseMaxLength = 1024; //as per intialaization in main
  char* store_data = new char[DATA_SOCKET_RECEIVE_BUFFER_SIZE]; //64K
  char* response = new char[ftpResponseMaxLength]; // define char* array to hold the servr response as per main
  memset(response, '\0', ftpResponseMaxLength); // free memory buffer
  memset(store_data, '\0', ftpResponseMaxLength); // free memory buffer

  if(receiveOnControl(response, ftpResponseMaxLength) != -1) // test if recieving the response went fine
 {
       showFtpResponse(response);

       if(receiveOnControl(response, ftpResponseMaxLength) != -1)
       {
        
        showFtpResponse(response);
        receiveOnData(store_data, DATA_SOCKET_RECEIVE_BUFFER_SIZE);

            std::ofstream output;
            if (output.fail())
            {
                std::cout << "FAiled \n" <<std::endl;
            }
            output.open(filename);
            output << store_data;
            output.close();
       }
 }
  delete [] store_data;
  delete [] response; 
}


void handleSimpleCommandResponse(std::string ftpCommand, bool checkAuthentication)
// Sends 'ftpCommand' request message to FTP server on the control connection.
// Receives the response from the server against the request.
// Displays the response to the user.
// If the response is unsuccessful and checkAuthentication parameter value is true, quits the application.
{
  sendOnControl(ftpCommand.c_str(), FTP_COMMAND_MAX_LENGTH); // call the function sendOnControl from ftp_client_control.cpp and pass it the command and previously declared length to preform communication with server  

  //  int ftpResponseMaxLength = 1024;// as per intialaization in main 
  char* response = new char[ftpResponseMaxLength]; // define char* array to hold the servr response as per main 
  memset(response, '\0', ftpResponseMaxLength); // free memory buffer  
  if(receiveOnControl(response, ftpResponseMaxLength) != -1) // test if recieving the response went fine 
 {
   showFtpResponse(response); //if the test was passed, then we know we have succefully recieved the response. now DISPLAY it 
 // if recieving response failed, then we check authrntication as per requirment 
    if(checkAuthentication == true && (strcmp(response,INVALID_USERNAME_RESPONSE) == 0 || strcmp(response,NOT_LOGGED_IN_RESPONSE) == 0))
    {
      printf("could NOT recieve response.. \n could not authnticate \n\n  Quitting the applicattion...");
      handleCommandQuit();
    }
  }
 delete [] response; //free memory 
}


void getHostIPAndPortFromPassiveSuccessResponse(char* response, char* hostIP, int& hostPort)
// Retrieves IP address of FTP Server from the response string into reference 'hostIP'.
// Retrives data-connection listening port number of FTP server from the response string into reference 'hostPort'. 
// The example of a successful response message is "227 Entering Passive Mode (192,168,1,65,202,143)."
// From the above response message 'hostIP' will be 192.168.1.65 and 'hostPort' will be
// (202x256 + 143) or 51855.
{
  std::string converted_response = response; // convert response from a char* to a string for easier manipulation 
  std::string extracted_IP; // to store IP after extracting it from string 
  std::string extracted_Port; // to store IP after extracting it from string
  std::string extracted_Port_add;
  char comma = ',';
  char dot = '.'; 

  int scanner = converted_response.rfind("192"); // scans the string looking for 192

  //  std::string extracted_IP;
  

  extracted_IP.assign(converted_response, scanner,13); //assign value to extracted_ip based on in range starting from scanner to 13 chars after 

  extracted_Port.assign(converted_response, scanner+14, 3);  //assign value to extracted_port based on in range starting from (scanner + 13) to 3 chars after

  extracted_Port_add.assign(converted_response, scanner	+18, 3);  //assign value to extracted_port_add based on in range starting from (scanner + 16) to 3 chars after

 std::cout <<"CONVERTED IP   IS: "<< extracted_IP <<std::endl;
      

  int converted_port = std::stoi(extracted_Port); //convert string to an int using stoi 
    std::cout <<"CONVERTED PORT 1  IS: "<< converted_port <<std::endl;
      
 int converted_port_add = std::stoi(extracted_Port_add);
  
  
  std::cout <<"CONVERTED PORT ADD IS: "<< converted_port_add <<std::endl;

  int final_port = (converted_port*256 + converted_port_add); //finalaized port number 

  hostPort = final_port; 
 
  for (unsigned int i = 0; i < extracted_IP.length(); ++i)
  {
    if (extracted_IP[i] == comma)
      extracted_IP[i] = dot;
  }

  //hostIP = extracted_IP.c_str();        // now IP is in the right format so we cant store it in hostIP

  strcpy(hostIP, extracted_IP.c_str());
  
}

