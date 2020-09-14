/*************
/*
/* Nawaf Alharbi
/* FTP Client
/* Oct 2019
/*
/* 
*************/


#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "ftp_client_ui.hpp"
#include "ftp_client_control.hpp"

using namespace std;

void usage(const char* prog);
char* baseName(const char* pathname);

int main(int argc, char** argv) {
    if(argc<2) {
        char* base_name = baseName(argv[0]);
        usage(base_name);
        return 1;
    }
    
    char* serverIP = argv[1];
    int serverPort = FTP_CLIENT_DEFAULT_SERVER_PORT;
    if(argc>2) {
        serverPort = atoi(argv[2]);
    }
    cout<<"Server IP: "<<serverIP<<endl;
    cout<<"Server Port: "<<serverPort<<endl;

    connectToServerControl(serverIP, serverPort);
    if(isControlConnectionAvailable()) {
        usleep(5000);
        int ftpResponseMaxLength = 1024;
        char* response = new char[ftpResponseMaxLength];
        memset(response, '\0', ftpResponseMaxLength);
        if(receiveOnControl(response, ftpResponseMaxLength) != -1) {
            showFtpResponse(response);
        }
        delete [] response;
        while(1) {
            getUserCommand();
        }
    }
    else {
        cout<<"Can't connect to the FTP server"<<endl;
    }
    return 0;
}

void usage(const char* prog) {
    cout<<setw(6)<<" "<<"Usage:  "<<prog<<"  <server_ip>  "<<"<server_port>"<<endl;
    cout<<setw(6)<<" "<<setfill('*')<<setw(18)<<"*"<<" <server_port> is optional."<<endl;
}

char* baseName(const char* pathname) {
    char* path_name = const_cast<char*>(pathname);
    char* base_name = path_name;
    if((base_name=strrchr(path_name, '/')) != NULL) {
        ++base_name;
    }
    return base_name;
}
