// Example program
#include <iostream>
#include <string>


#include <string.h>
using namespace std;

void getHostIPAndPortFromPassiveSuccessResponse(char* response, char* hostIP, int& hostPort)
{


  string converted_response = response; // convert response from a char* to a string for easier manipulation
  std::string extracted_IP; // to store IP after extracting it from string
  std::string extracted_Port; // to store IP after extracting it from string
  std::string extracted_Port_add;
  char comma = ',';
  char dot = '.';

  int scanner = converted_response.rfind("192"); // scans the string looking for 192

  //  std::string extracted_IP;


  extracted_IP.assign(converted_response, scanner,13); //assign value to extracted_ip based on in range starting from scanner to 13 chars after

  extracted_Port.assign(converted_response, scanner+13, 3);  //assign value to extracted_port based on in range starting from (scanner + 13) to 3 chars after

  extracted_Port_add.assign(converted_response, scanner+16, 3);  //assign value to extracted_port_add based on in range starting from (scanner + 16) to 3 chars after


  int converted_port = stoi(extracted_Port); //convert string to an int using stoi

  int converted_port_add = stoi(extracted_Port_add);

  int final_port = (converted_port*256 + converted_port_add); //finalaized port number

  hostPort = final_port;

  for (unsigned int i = 0; i < extracted_IP.length(); ++i)
  {
    if (extracted_IP[i] == comma)
      extracted_IP[i] = dot;
  }

  //hostIP = extracted_IP.c_str();        // now IP is in the right format so we cant store it in hostIP

  strcpy(hostIP, extracted_IP.c_str());

    cout << "HOST PORT IS NOW : " << hostPort <<endl;
    
    cout << "HOST IP IS NOW : " << hostIP <<endl;
    


}



int main()
{
//  char* mychar; 
//  mychar = "hello i am a full line of stuff";
 // std::string name;
 // std::cout << "What is your name? ";
  //getline (std::cin, name);
 
// name = mychar;
 
// std::cout << "I AM A STRING, " << name << "!\n";

//std::cout << "I AM A CHAR, " << mychar << "!\n";

int hostPort;
char* hostIP = NULL; 
char* message;
message = '227 Entering Passive Mode (192,168,1,65,202,143).';

getHostIPAndPortFromPassiveSuccessResponse(message, hostIP,  hostPort);

}
