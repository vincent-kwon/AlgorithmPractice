/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* template.c  Convenience source including all other headers
 *
 *  Copyright 2012 VINCETECH Inc.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 * 
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */


#include <stdio.h>
#include <stdlib.h>  //exit
#include <string.h> //
#include <stdbool.h> //true, false
#include <unistd.h> //sleep

//#include <dbus/dbus.h>

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h> 

#include <stdlib.h>
#include "dbus_interface/vc_dbus_interface_client.h"
//#include <arpa/inet.h> //inet_atona
//#include "darkstar2_private_common.h"
/*********************** Summary of Socket ***********************************
 *   hostent: get host infrom
 *           - h_addr (ip address)
 *           - h_length (???)
 *   sockaddr_in:
 *   struct sockaddr_in{
 *		  short  sin_family; //AF_INET, AF_INET6, AF_LOCAL
 *		  unsigned short sin_port; //htons(atoi("1234"));
 *	 	  struct  in_addr  sin_addr; //sin_addr.s_addr = htonl(INADDR_ANY) or inet_addr(serv_ip)
 *		  char sin_zero[8];
 *    };
 ************************ Summary of Socket ***********************************/
#if 0
void error_handling(const char *message)
{
    fputs(message, stderr);4
    fputc('\n', stderr);
    exit(1);
}

void send_socket_request(char *server_port, char *server_ip)
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	//struct hostent *server;

	char buffer[256];

	//define socket fd
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 
	    log4c_category_log(logcat, LOG_ERROR, "[System Server Client] ERROR opening socket");
	//get hostent
	//server = gethostbyname("localhost");
	
	//initialize serv_addr
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//Internet
	serv_addr.sin_family = AF_INET;
	//@20120122-vincent: Below is working fine but disabled since want to set a specific IP
	//serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr(server_ip);
	//if (!inet_aton(server_ip, &serv_addr.sin_addr))
	//	error_handling("Conversion Error");
	serv_addr.sin_addr.s_addr = inet_addr(server_ip);
	serv_addr.sin_port = htons(atoi(server_port));

	log4c_category_log(logcat, LOG_NOTICE, "[System Server Client] ip: %s, port %d,%d\n", server_ip, serv_addr.sin_port, atoi(server_port));

	//copy hostent info into sockaddr for address, length
#if 0
	bcopy(/*(char *)server->h_addr*/"192.168.10.4", 
	  (char *)&serv_addr.sin_addr.s_addr,
	  /*server->h_length*/strlen("192.168.10.4"));

#else

//bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length));

#endif
	//set port
	//serv_addr.sin_port = htons(portno);
	log4c_category_log(logcat, LOG_NOTICE, "[System Server Client] Now wait for connection made...\n");

	//try to connect, thus wait on here
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
	    log4c_category_log(logcat, LOG_ERROR, "ERROR connecting cant'");
		return;
	}
	else 
		log4c_category_log(logcat, LOG_WARN, "[System Server Client]  CONNECTED>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	//wait here
	bzero(buffer,256);
	//fprintf(stderr, "[System Server Client]  rEnter message to send\n");
	//fgets(buffer,255,stdin);
	sprintf(buffer, "%s","new app request");

	log4c_category_log(logcat, LOG_WARN, "[System Server Client] About to write message %s\n", buffer);

		
	n = write(sockfd,buffer,strlen(buffer));

	if (n < 0) {
	     log4c_category_log(logcat, LOG_ERROR, "[System Server Client] ERROR writing to socket");
		 return;
	}
	log4c_category_log(logcat, LOG_NOTICE, "[System Server Client] [System Server Client]  sent message %s\n", buffer);
	
	bzero(buffer,256);
	n = read(sockfd,buffer,255);

	if (n < 0) {
	     log4c_category_log(logcat, LOG_ERROR, "[System Server Client] ERROR reading from socket");
		 return;
	}
	
	log4c_category_log(logcat, LOG_NOTICE, "[System Server Client] [System Server Client]  read %d byte from socket %s\n",n, buffer);

	const char* application_path = "/home/vince15/development/DarkStar/out/X86/bin/SLP3.0";

	n = write(sockfd,application_path, strlen(application_path));
	
	close(sockfd);
	log4c_category_log(logcat, LOG_NOTICE, "[System Server Client] [System Server Client]  socket is closing\n");
	exit(1);
	return;
}

void send_signal()
{
	DBusMessage* msg;
	DBusMessageIter args;
	DBusConnection* conn;
	DBusError err;
	//const char* application_path = "/home/vince15/development/DarkStar/out/X86/bin/gtk_sample_app/gtk_sample_app";
	const char* application_path = "/home/vince15/development/DarkStar/out/X86/bin/SLP3.0";
	int ret = 0;
	dbus_uint32_t serial = 0;
	static int count = 0;

	log4c_category_log(logcat, LOG_NOTICE, "[System Server Client]  start test.....\n");

	//The bus name must be unique to use DBus in any case
	const char* new_bus_name = "my.system_server.sender.bus.name";

	const char* object_name_of_the_signal = "/any/file/location";

	const char* object_name_of_the_method = "/any/file/location2";

	//Must have identical signal interface name to the server
	const char* interface_name_of_the_signal = "request.to.launcherdaemon";

	//Must have identical signal name to the server
	const char* name_of_the_signal = "launch_new_application";

	//Client will add the interface name for add_match
	//e.g., "type='signal',interface='test.signal.Type'
	const char* interface_name_of_the_method = "my.methodinterface.name";

	//Once interface name is filtered, then name of signal is used
	//This value will be used by client with dbus_message_is_signal
    const char* name_of_the_method = "my_method_name";

    const char* target_bus_name = "my.system_server.bus.name";

	//initialize the error
	dbus_error_init(&err);

	//connect to the bus and check for errors
	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

	//Check for dbus error
	if (dbus_error_is_set(&err)) {
		log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Connection Error (%s)\n", err.message);
		dbus_error_free(&err);
	}

	if (NULL == conn) {
		log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Connection Null\n");
		exit(1);
	}

	//request our name on the bus and check for errors
	ret = dbus_bus_request_name(conn, new_bus_name, DBUS_NAME_FLAG_REPLACE_EXISTING , &err);

	//For request name, check error
	if (dbus_error_is_set(&err)) {
		log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Name Error (%s)\n", err.message);
		dbus_error_free(&err);
	}

	//Check for primary for the requested name
	if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
		log4c_category_log(logcat, LOG_ERROR, "Not Primary Owner (%d)\n", ret);
		exit(1);
	}

	//Wait for new message
	while (true) {
	    //send new signal here
  	    //create a signal & check for errors
		if (count%2) {
			log4c_category_log(logcat, LOG_NOTICE, "[SystemServer] start send signal now\n");
			msg = dbus_message_new_signal(object_name_of_the_signal,
										  interface_name_of_the_signal,
										  name_of_the_signal);

			if (NULL == msg) {
				log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Message Null\n");
				exit(1);
			}

			//append arguments onto signal
			dbus_message_iter_init_append(msg, &args);

			if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &count)) {
				log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Out Of Memory!\n");
				exit(1);
			}

			if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &application_path)) {
				log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Out Of Memory!\n");
				exit(1);
			}

			//send the message and flush the connection
			if (!dbus_connection_send(conn, msg, &serial)) {
				log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Out Of Memory!\n");
				exit(1);
			}

			//Flush
			dbus_connection_flush(conn);

			//Free the message and close the connection
			dbus_message_unref(msg);
		    log4c_category_log(logcat, LOG_NOTICE, "[System Server Client]  End of Signal Sending call\n");
		}
		else {
#if 1
			//@20111210-vincent: DBus will not work if below value is empty;
			 const char* param = "This must not be null";
			 DBusPendingCall* pending;
			 int level;
			 bool stat;
		     log4c_category_log(logcat, LOG_NOTICE, "[System Server Client]  start remote method call\n");
			 msg = dbus_message_new_method_call(target_bus_name, // target for the method call
					 	 	 	 	 	 	 	object_name_of_the_method, // object to call on
			                                    interface_name_of_the_method, // interface to call on
			                                    name_of_the_method); // method name
		    if (NULL == msg) {
			  log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Message Null\n");
			  exit(1);
			}

		    // append arguments
		    dbus_message_iter_init_append(msg, &args);

			if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &param)) {
			  log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Out Of Memory!\n");
			  exit(1);
			}

			// send message and get a handle for a reply
			if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) { // -1 is default timeout
			  log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Out Of Memory!\n");
			  exit(1);
			}

			if (NULL == pending) {
			  log4c_category_log(logcat, LOG_ERROR, "[System Server Client] Pending Call Null\n");
			  exit(1);
			}
			dbus_connection_flush(conn);

  		    // free message
			dbus_message_unref(msg);
		    log4c_category_log(logcat, LOG_NOTICE, "[System Server Client]  End of remote method call\n");

#endif

#if 1
			// block until we recieve a reply
			dbus_pending_call_block(pending);

			// get the reply message
			msg = dbus_pending_call_steal_reply(pending);
			if (NULL == msg) {
			  log4c_category_log(logcat, LOG_ERROR, "[System Server Client]  Error!!! Reply Null\n");
			  exit(1);
			}
			// free the pending message handle
			dbus_pending_call_unref(pending);

			// read the parameters
			if (!dbus_message_iter_init(msg, &args)) {
			  log4c_category_log(logcat, LOG_ERROR, "[System Server Client]  Error!!! Message has no arguments!\n");
			  exit(1);
			}
			else if (DBUS_TYPE_UINT32 != dbus_message_iter_get_arg_type(&args)) {
			  log4c_category_log(logcat, LOG_ERROR, "[System Server Client]  Error!!! Argument is not int!\n");
			  exit(1);
			}
			else {
			  dbus_message_iter_get_basic(&args, &level);
			  log4c_category_log(logcat, LOG_NOTICE, "[System Server Client]  Got Reply:%d\n", level);
			}
			// free reply and close connection
			dbus_message_unref(msg);
#endif
		}

		if (count++ == 10)
			break;

		sleep(1);
	}
	dbus_connection_close(conn);
}
#endif

#define NEW_BUS_NAME "my.system_client.sender.bus.name"

#define TARGET_BUS_NAME "my.system_server.bus.name"

#define INTERFACE_NAME_OF_SIGNAL "request.to.launcherdaemon"

#define NAME_OF_SIGNAL "launch_new_application"

#define OBJECT_NAME_OF_SIGNAL "/any/file/location"

#define INTERFACE_NAME_OF_METHOD "my.methodinterface.name"

#define NAME_OF_METHOD "my_method_name"

#define OBJECT_NAME_OF_METHOD "/any/file/location2"



/**
 * Main function for the System Server Daemon
 */
int main(int argc, char** argv){
	LOGVC_INIT("c3po.log");
	send_signal_to_dbus_server(NEW_BUS_NAME, TARGET_BUS_NAME, INTERFACE_NAME_OF_SIGNAL, NAME_OF_SIGNAL,	OBJECT_NAME_OF_SIGNAL, INTERFACE_NAME_OF_METHOD, NAME_OF_METHOD, OBJECT_NAME_OF_METHOD);
    return 0;
}
