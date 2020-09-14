#ifndef FTP_CLIENT_UI_H
#define FTP_CLIENT_UI_H

#include <string>

#define FTP_CLIENT_PROMT "csci460Ftp>>"


void getUserCommand();
// Displays a command line prompt as follows:
//      csci460Ftp>>
// Lets user to type command and reads the user command from the prompt.
// Interprets user command by calling function interpreteUserCommand().

void interpreteUserCommand(std::string command);
// Interprets user command and call appropriate function from 'ftp_client_command.hpp'.

void showFtpResponse(std::string response); 
// Displays server response to the user on the prompt.
// For example, success response of user command
//      csci460Ftp>>user csci460
// is displayes as 
//      csci460Ftp>>331 Username okay, need password.

void showFtpDirResponse(std::string response);
// Displays server response to the user against user command
//      csci460Ftp>>dir
// as 
//      csci460Ftp>>226 Directory listing (11) entries sent OK . Closing data connection..
//
//      D       .
//      D       ..
//      D       bin
//      F       makefile                2631
//      D       include
//      F       README                  0
//      D       build
//      D       resource
//      D       src

#endif