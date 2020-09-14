/*************
/*
/* Nawaf Alharbi
/* FTP Client
/* Oct 2019
/*
/* 
*************/



#include "ftp_client_ui.hpp"
#include "ftp_client_command.hpp"
#include <bits/stdc++.h>
#include <string>


void getUserCommand()
{
  std::string user_command;
  printf ("%s", FTP_CLIENT_PROMT);
  std::cin.clear(); //clear buffer before recieving input 
  getline(std::cin, user_command);
  interpreteUserCommand(user_command); //send command to function to decide what to do 
}

void interpreteUserCommand(std::string command)
// Interprets user command and call appropriate function from 'ftp_client_command.hpp'.
{
  if (command.empty())
  {
    printf(" you have entered an empty command \n calling help function \n") ;         
    handleCommandHelp();
  }       
  std::string command_first;
  std::string command_second;
  bool inSpaces = true;
  int numWords = 0;
  
  for (unsigned int i =0; i<command.size(); i++)
  {
    if (command[i] == ' ')
    {
      inSpaces = true;
      if(i<5)
	command_first = command.substr(0,i);
      // else       
	//	command_second = name.substr(command_first.size(),i);   
    }
    else if (inSpaces)
    {      
      numWords++;
      inSpaces = false;    
    }	
  }

  command_second = command.substr(command_first.size(), command.size());     

  if (numWords > 2)
  {
    printf("you have entered an invlid number of arguments \n detching operation \n displaying help menu... \n");
    handleCommandHelp();
    command_first = "" ;
    command_second = "";
  }

 // command_first = command.substr(0,command.size());
  
  transform(command_first.begin(), command_first.end(), command_first.begin(), ::toupper); //change all letters in command to upper case for more percise comparision   

  // call appropriate function as per user's entry
  if(command_first == "HELP")
  {
    handleCommandHelp();
  }

  else if(command_first == "USER")
  {
    handleCommandUser(command_second);
  }
 
  else if(command_first == "PASS")
  {
    handleCommandPassword(command_second);
  }

  else if(command_first == "PWD")
  {
    handleCommandPrintDirectory();
  }

  else if(command_first == "DIR")
  {
    handleCommandDirectory();
  }

  else if(command_first == "CWD")
  {
    handleCommandChangeDirectory(command_second);
  }

  else if(command_first == "CDUP")
  {
    handleCommandChangeDirectoryUp();
  }

  else if(command_first == "GET")
  {
    handleCommandGetFile(command_second);
  }
  else if(command_first == "QUIT")
  {
    handleCommandQuit();
  }

  else 
  {
    printf("invalid command.. \n calling help function .. \n");
    handleCommandHelp();
  }

}
  
void showFtpResponse(std::string response) 
// Displays server response to the user on the prompt.
{
  std::cout << response << std::endl;
}

void showFtpDirResponse(std::string response)
// Displays server response to the user against user command
{  
 std::cout << response << std::endl;
}

