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
#include <string.h>  
#include <stdbool.h> //true, false
#include <unistd.h>  //sleep
#include <dbus/dbus.h>


#define NEW_BUS_NAME    "my.system_server.sender.bus.name"
#define TARGET_BUS_NAME "my.system_server.bus.name"
#define INTERFACE_NAME_OF_SIGNAL "request.to.launcherdaemon"
#define NAME_OF_SIGNAL "launch_new_application"
#define OBJECT_NAME_OF_SIGNAL "/any/file/location"
#define INTERFACE_NAME_OF_METHOD "my.methodinterface.name"
#define NAME_OF_METHOD "my_method_name"
#define OBJECT_NAME_OF_METHOD "/any/file/location2"

#define DBUS_SERVER_BUS_NAME "darkstar3.system.controller.server"
#define DBUS_TARGET_BUS_NAME "darkstar3.system.controller.client"
#define DBUS_NAME_SIGNAL     "darkstar3.system.controller.signal"
#define DBUS_INTERFACE_NAME_SIGNAL "darkstar3.system.controller.signal.interface"
#define DBUS_OBJECT_NAME_SIGNAL    "/darkstar3/system/controller/signal/object"
#define DBUS_METHOD_NAME           "darkstar3.system.controller.signal.method"
#define DBUS_OBJECT_NAME_METHOD    "/darkstar3/system/controller/signal/method/object"


#if 0
log4c_category_t* logcat = NULL;

static void init_logger()
{
    if (log4c_init()) 
    {
		printf("logger init failed....");
		exit(ILLEGAL_EXIT);
    }
	
	logcat = log4c_category_get(LOG4C_LABEL);

	if (!logcat)
	{
		printf("log4c_category_get failed....");
		exit(ILLEGAL_EXIT);
	}
	else 
	{
		printf("hmm..");
		log4c_category_log(logcat, LOG_DEBUG, "Debugging app");			
	}
}

static void finalize_logger()
{
	if (log4c_fini())
	{
		printf("log4c_fini() failed");
	}
}

void invoke_app_process(const char *app_path) 
{
    //fork and execv
    int pid = fork();
	static int uid_count = 10000;
	static int gid_count = 15000;
	static int puid_count = 25000;
	
	//child
	if (pid == 0) 
	{
		log4c_category_log(logcat, LOG_NOTICE,"[SystemServerD:Child]: (%d)\n", pid);
		setuid(uid_count);
		setgid(gid_count);
		log4c_category_log(logcat, LOG_NOTICE,
				"[SystemServerD:Child]:Real	   %d  Real 	 %d  \n"
				"[SystemServerD:Child]:Effective %d  Effective %d  \n",
					 getuid (), 	getgid (),
					 geteuid(), 	getegid()
			);
		execv(app_path, NULL);
	}
	else if (pid < 0) 
	{
		log4c_category_log(logcat, LOG_ERROR,"[SystemServerD] failed for a new process %s\n", app_path);
		return;
	}
	else 
	{
		puid_count++;
		uid_count++;
		gid_count++;
		log4c_category_log(logcat, LOG_NOTICE,"[SystemServerD:Parent]just fork finished (%d), puid is (%d), and you are (%d)\n", pid, puid_count,getpid());
		return;
	}		
}

void reply_to_method_call(DBusMessage* msg, DBusConnection* conn)
{
   DBusMessage* reply;
   DBusMessageIter args;
   bool stat = true;
   dbus_uint32_t level = 21614;
   dbus_uint32_t serial = 0;
   char* param;
   dbus_uint32_t retVal = -1;

   //Read the arguments. This method assumes it has one String and Integer value
   //and returns one string value to the requester
   if (!dbus_message_iter_init(msg, &args)) 
   {
       log4c_category_log(logcat, LOG_ERROR,"[SystemServerD] Message has no arguments!\n");
       return;
   }
   else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args)) 
   {
       log4c_category_log(logcat, LOG_ERROR,"[SystemServerD] Argument is not string!\n");
       return;
   }
   else 
   {
       dbus_message_iter_get_basic(&args, &param);
       log4c_category_log(logcat, LOG_NOTICE, "[SystemServerD] METHOD received string is %s\n", param);
       if (!strcmp(param, "This must not be null")) 
	   {
    	   retVal = 1;
       }
       else {
    	   retVal = 2;
       }
   }

   // create a reply from the message
   reply = dbus_message_new_method_return(msg);

   // add the arguments to the reply
   dbus_message_iter_init_append(reply, &args);

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &retVal)) 
   {
      log4c_category_log(logcat, LOG_ERROR,"[SystemServerD] Out Of Memory!\n");
      exit(1);
   }

   // send the reply && flush the connection
   if (!dbus_connection_send(conn, reply, &serial)) 
   {
      log4c_category_log(logcat, LOG_ERROR,"[SystemServerD] Out Of Memory!\n");
      exit(1);
   }
   dbus_connection_flush(conn);
   log4c_category_log(logcat, LOG_NOTICE, "[SystemServerD] METHOD replied INT \n");
   //Unref is done below
   //dbus_message_unref(reply);
}

void listen() 
{
	DBusMessage* msg;
	DBusMessageIter args;
	DBusConnection* conn;
	DBusError err;
	int ret = 0;

	//The bus name must be unique to use DBus in any case
	const char* new_bus_name = "my.system_server.bus.name";

	//Client will add the interface name for add_match
	//e.g., "type='signal',interface='test.signal.Type'
	const char* interface_name_of_the_signal = "request.to.launcherdaemon";

	//Once interface name is filtered, then name of signal is used
	//This value will be used by client with dbus_message_is_signal
    const char* name_of_the_signal = "launch_new_application";

	//Client will add the interface name of the method for add_match
	//e.g., "type='signal',interface='test.method.Type'
	const char* interface_name_of_the_method = "my.methodinterface.name";

	//Once interface name is filtered, then name of method is used
	//This value will be used by client with dbus_message_is_signal
    const char* name_of_the_method = "my_method_name";

	//initialize the error
	dbus_error_init(&err);

	//connect to the bus and check for errors
	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

	//Check for dbus error
	if (dbus_error_is_set(&err)) 
	{
		log4c_category_log(logcat, LOG_ERROR, "Connection Error (%s)\n", err.message);
		dbus_error_free(&err);
	}

	if (NULL == conn) 
	{
		log4c_category_log(logcat, LOG_ERROR, "Connection Null\n");
		exit(1);
	}

	//request our name on the bus and check for errors
	ret = dbus_bus_request_name(conn, new_bus_name, DBUS_NAME_FLAG_REPLACE_EXISTING , &err);

	//For request name, check error
	if (dbus_error_is_set(&err)) 
	{
		log4c_category_log(logcat, LOG_ERROR, "Name Error (%s)\n", err.message);
		dbus_error_free(&err);
	}

	//Check for primary for the requested name
	if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) 
	{
		log4c_category_log(logcat, LOG_ERROR, "Not Primary Owner (%d)\n", ret);
		exit(1);
	}

	//The below two line are very important steps to received this signal "request.to.launcherdaemon"
	dbus_bus_add_match(conn, "type='signal',interface='request.to.launcherdaemon'", &err); // see signals from the given interface
	dbus_connection_flush(conn);

	//Wait for new message
	while (true) 
	{
		int received_val = 0;
		char *received_str = NULL;
		int current_type;

		//non blocking read of the next available message
		dbus_connection_read_write(conn, 0);

		msg = dbus_connection_pop_message(conn);

    	//loop again if we haven't got a message
		if (NULL == msg) 
		{
			//fprintf(stdout, "[SystemServerD] Received null message, just continue....\n");
			continue;
		}

		//check this is a method call for the right interface & method
		if (dbus_message_is_method_call(msg, interface_name_of_the_method, name_of_the_method)) 
		{
		     //reply_to_method_call(msg, conn);
			log4c_category_log(logcat, LOG_NOTICE, "[SystemServerD] Method received request for %s\n", name_of_the_method);
			reply_to_method_call(msg, conn);
		}
		//if not a method, then signal?
		else if (dbus_message_is_signal(msg, interface_name_of_the_signal, name_of_the_signal)) 
		{
			log4c_category_log(logcat, LOG_NOTICE, "[SystemServerD] SIGNAL received request for %s\n", name_of_the_signal);
			int still_left = FALSE;

			if (!dbus_message_iter_init(msg, &args)) 
			{
				log4c_category_log(logcat, LOG_ERROR, "[SystemServerD] SIGNAL has no message to get \n");
				continue;
			}
 
			do 
			{
				//read the parameters
				int args_type = dbus_message_iter_get_arg_type(&args);

				switch(args_type) {
				case DBUS_TYPE_UINT32 :
					dbus_message_iter_get_basic(&args, &received_val);
					log4c_category_log(logcat, LOG_NOTICE, "[SystemServerD] SIGNAL parsed int %d\n", received_val);
					break;
				case DBUS_TYPE_DOUBLE:
					break;
				case DBUS_TYPE_STRING:
					dbus_message_iter_get_basic(&args, &received_str);
					log4c_category_log(logcat, LOG_NOTICE, "[SystemServerD] SIGNAL parsed string %s\n", received_str);
					break;
				default:
					break;
				}
				still_left = dbus_message_iter_next(&args); //TRUE = 1 , FALSE = 0
			} while (still_left == TRUE);

			invoke_app_process(received_str); //launch a new app 
		}
		else 
		{
			log4c_category_log(logcat, LOG_WARN, "DBus type others\n");
			//Ignore something not filtered. May think about what can be placed here.
		}

		// free the message
		dbus_message_unref(msg);
	}

	// close the connection
	dbus_connection_close(conn);
}
#endif 
/**
 * Main function for the System Server Daemon
 */
int init(int argc, char** argv)
{
   printf("Hoot, I am system_server...\n");
   
//   LOGVC_INIT("c3po.log");
//   LOGVC( vc_debug, "[System Server]Bus name %s\n", NEW_BUS_NAME);    
//   dbus_server_init(DBUS_SIGNAL, REPLACE_OPTION_1, NEW_BUS_NAME, INTERFACE_NAME_OF_SIGNAL, NAME_OF_SIGNAL, INTERFACE_NAME_OF_METHOD, NAME_OF_METHOD);
   return 0;
}
