#ifndef FTP_CLIENT_COMMAND_H
#define FTP_CLIENT_COMMAND_H

#define FTP_COMMAND_MAX_LENGTH 512

#define FTP_CLIENT_USER_COMMAND_HELP "help"
#define FTP_CLIENT_USER_COMMAND_USER "user"
#define FTP_CLIENT_USER_COMMAND_PASSWORD "pass"
#define FTP_CLIENT_USER_COMMAND_DIRECTORY "dir"
#define FTP_CLIENT_USER_COMMAND_PRINT_DIRECTORY "pwd"
#define FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY "cwd"
#define FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_UP "cdup"
#define FTP_CLIENT_USER_COMMAND_GET "get"
#define FTP_CLIENT_USER_COMMAND_QUIT "quit"


#define FILE_OPEN_MODE "a"
#define DATA_SOCKET_RECEIVE_BUFFER_SIZE 65536 //64K

//Enumeration pasvNextCmd is used to pass parameter to function handlePassive()
//to keep track what will be the next command after the passive command
enum pasvNextCmd {PASV_NLST, PASV_RETR}; 

void handleCommandHelp();
// Displays following help information to the user terminal
// Usage: csci460Ftp>> [ help | user | pass | pwd | dir | cwd | cdup | get | quit ]
//          help                    Gives the list of FTP commands available and how to use them.
//          user    <username>      Sumbits the <username> to FTP server for authentication.
//          pass    <password>      Sumbits the <password> to FTP server for authentication.
//          pwd                     Requests FTP server to print current directory.
//          dir                     Requests FTP server to list the entries in the current directory.
//          cwd     <dirname>       Requests FTP server to change current working directory.
//          cdup                    Requests FTP server to change current directory to parent directory.
//          get     <filename>      Requests FTP server to send the file with <filename>.
//          quit                    Requests to end FTP session and quit.

void handleCommandUser(std::string username);
// Sends a 'USER <username>' request meesage to the FTP Server.
// Receives response from FTP Server.
// Reacts and informs the user about the response. 
// Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter true 
// to perform the activities mentioned above.

void handleCommandPassword(std::string password);
// Sends a 'PASS <password>' request message to the FTP Server.
// Receives response from FTP Server.
// Reacts and informs the user about the response. 
// Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter true 
// to perform the activities mentioned above.

void handleCommandDirectory();
// First sends a 'PASV' request message to the FTP server.
// Receives the response against PASV request message from the server.
// If the response is a successful one, retrives data-connection listener port number form the response.
// Requests a data connection to the server on the listener port at the server.
// Calls function handlePassive() to perform the activities mentioned above. 
// If the data connection is successful, sends a 'NLST' request message to the server on the control connection.
// Receives the response against NLST request from the server on the control connection.
// If the response is successful, retrieves the list of entries in server's current directory on the data connection.
// Displays the list of entries to the user.
// Calls function handleNLIST() to perform the activities mentioned above. 

void handleCommandPrintDirectory();
// Sends a 'PWD' request message to FTP Server.
// Receives the response from the server.
// If the response is successful, displays the name of the current working directory of the server.
// Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter false 
// to perform the activities mentioned above.

void handleCommandChangeDirectory(std::string path);
// Sends a 'CWD <path>' request message to the FTP Server.
// Receives the response from the server and displays the response to the user.
// Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter false 
// to perform the activities mentioned above.

void handleCommandChangeDirectoryUp();
// Sends a 'CDUP' request message to FTP Server.
// Receives the response from the server and displays the response to the user.
// Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter false 
// to perform the activities mentioned above.

void handleCommandGetFile(std::string filename);
// First sends a 'PASV' request message to the FTP server.
// Receives the response against PASV request message from the server.
// If the response is a successful one, retrives data-connection listener port number form the response.
// Requests a data connection to the server on the listener port at the server.
// Calls function handlePassive() to perform the activities mentioned above. 
// If the data connection is successful, sends a 'RETR <filename>' request message 
// to the server on the control connection.
// Receives the response against RETR request from the server on the control connection.
// If the response is successful, retrieves the content of the file on the data connection.
// Saves the file in the local directory at the client computer.
// Calls function handleRETR() to perform the activities mentioned above. 

void handleCommandQuit();
// Sends a 'QUIT' request message to FTP Server.
// Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter false 
// to send 'QUIT' request message.
// Quits from the application.

void handlePassive(pasvNextCmd pasvNext);
// Sends a 'PASV' request message to the FTP server.
// Receives the response against PASV request message from the server.
// If the response is a successful one, retrives data-connection listener port number form the response.
// Retrives data-connection listener port number form the response 
// using function getHostIPAndPortFromPassiveSuccessResponse().
// Requests a data connection to the server on the listener port at the server.

void handleNLIST();
// Sends a 'NLST' request message to the server on the control connection.
// Receives the response against NLST request from the server on the control connection.
// If the response is successful, retrieves the list of entries in server's current directory 
// on the data connection.
// Displays the list of entries to the user.

void handleRETR(std::string filename);
// Sends a 'RETR <filename>' request message to the server on the control connection.
// Receives the response against RETR request from the server on the control connection.
// If the response is successful, retrieves the content of the file on the data connection.
// Saves the file in the local directory at the client computer.

void handleSimpleCommandResponse(std::string ftpCommand, bool checkAuthentication);
// Sends 'ftpCommand' request message to FTP server on the control connection.
// Receives the response from the server against the request.
// Displays the response to the user.
// If the response is unsuccessful and checkAuthentication parameter value is true, quits the application.

void getHostIPAndPortFromPassiveSuccessResponse(char* response, char* hostIP, int& hostPort);
// Retrieves IP address of FTP Server from the response string into reference 'hostIP'.
// Retrives data-connection listening port number of FTP server from the response string into reference 'hostPort'. 
// The example of a successful response message is "227 Entering Passive Mode (192,168,1,65,202,143)."
// From the above response message 'hostIP' will be 192.168.1.65 and 'hostPort' will be
// (202x256 + 143) or 51855.


#endif