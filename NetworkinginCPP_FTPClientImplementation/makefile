CC = g++
WFLAG = -Wall  		#Warning Flag
DFLAG = -ggdb		#Debugging Flag
CFLAG = -c			#Compiling Flag
SOURCES = src
INCLUDES = include
BUILDS = build
BINARY = bin

all:ftp_client

ftp_client: ftp_client.o ftp_client_ui.o ftp_client_control.o ftp_client_connection.o \
ftp_client_command.o
	${CC} ${WFLAG} ${DFLAG} -o ${BINARY}/myftp ${BUILDS}/ftp_client.o ${BUILDS}/ftp_client_ui.o ${BUILDS}/ftp_client_control.o \
	${BUILDS}/ftp_client_connection.o ${BUILDS}/ftp_client_command.o

ftp_client.o: ${SOURCES}/ftp_client.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_client.o ${SOURCES}/ftp_client.cpp

ftp_client_ui.o: ${SOURCES}/ftp_client_ui.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_client_ui.o ${SOURCES}/ftp_client_ui.cpp

ftp_client_control.o: ${SOURCES}/ftp_client_control.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_client_control.o ${SOURCES}/ftp_client_control.cpp

ftp_client_connection.o: ${SOURCES}/ftp_client_connection.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_client_connection.o ${SOURCES}/ftp_client_connection.cpp

ftp_client_command.o: ${SOURCES}/ftp_client_command.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_client_command.o ${SOURCES}/ftp_client_command.cpp


.PHONY: clean

clean:
	rm -rf ${BINARY}/*
	rm -rf ${BUILDS}/*