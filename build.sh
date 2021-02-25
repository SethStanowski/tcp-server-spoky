#!/bin/bash

#####################################
# temporary build scripts           #
#                                   #
#	will be repleaced with make #
#####################################

if [ $1 = "make" ]
then
	gcc server.c -o server
	gcc socket.c -o socket
	gcc client.c -o client
fi

if [ $1 = "-c" ] 
then
	rm server socket client
fi
