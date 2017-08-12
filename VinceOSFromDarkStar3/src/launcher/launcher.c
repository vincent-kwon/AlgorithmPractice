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
#if 0
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include <Evas.h>
#include <Evas_Engine_Buffer.h>

#define WIDTH (320)
#define HEIGHT (240)

extern int object_example(void);

int main (int argv, char **argsv) {
   object_example();
 }
#endif

#include <Elementary.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>


#define APP_FIRST_PATH "/usr/games/gbrainy"

#define APP_FIRST_TITLE "GBrainy"

#define APP_SECOND_PATH "/usr/games/mahjongg"

#define APP_SECOND_TTLE "Mahjong"

#define APP_LAUNCHER_PORT "10102"

#define APP_LAUNCHER_IP "127.0.0.1"

static void 
send_socket_request_for_app_launch(char *app_name)
{
	char *server_port = APP_LAUNCHER_PORT;
	char *server_ip = APP_LAUNCHER_IP;

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;

	char buffer[256];

	//define socket fd
	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 
	{
		printf("[Launcher Client] some error to handle....\n");
		// Write log here. 
	    //log4c_category_log(logcat, LOG_ERROR, "[System Server Client] ERROR opening socket");
	}
	
	//get hostent
	//server = gethostbyname("localhost");
	
	//initialize serv_addr
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//Internet
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(server_ip);
	serv_addr.sin_port = htons(atoi(server_port));

	printf("[Launcher Client] ip: %s, port %d,%d\n", server_ip, serv_addr.sin_port, atoi(server_port));

	//copy hostent info into sockaddr for address, length
	//serv_addr.sin_port = htons(portno);
	//log4c_category_log(logcat, LOG_NOTICE, "[System Server Client] Now wait for connection made...\n");

	//try to connect, thus wait on here
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
	    printf("[Launcher Client]  ERROR connecting can't by some reason\n");
		exit(1);
		return;
	}
	else {
		printf("[Launcher Client]  CONNECTED>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	}

	//wait here
	bzero(buffer,256);
	//fprintf(stderr, "[System Server Client]  rEnter message to send\n");
	//fgets(buffer,255,stdin);
	sprintf(buffer, "%s","new app request");

	printf("[Launcher Client] About to write message %s\n", buffer);

		
	n = write(sockfd,buffer,strlen(buffer));

	if (n < 0) {
	     printf("[Launcher Client] ERROR writing to socket");
		 return;
	}
	printf("[Laucnher Client] sent message %s\n", buffer);
	
	bzero(buffer,256);
	n = read(sockfd,buffer,255);

	if (n < 0) {
	     printf("[Launcher Client] ERROR reading from socket");
		 return;
	}
	
	printf("[Launcher Client]  read %d byte from socket %s\n",n, buffer);

	//const char* application_path = "/home/vince15/development/DarkStar/out/X86/bin/SLP3.0";

	n = write(sockfd, app_name, strlen(app_name));
	
	close(sockfd);

	printf("[Launcher Client] socket fd is now closed\n");
	//exit(1);
	return;
}


static void 
on_app_launch_request (void *data, Evas_Object *obj, void *event_info)
{
	char *param_str = (char *)data;
	
	
	if (strcmp(param_str, APP_FIRST_PATH) == 0) 
	{
		printf("In strcmp, now start launching the first app %s\n", param_str);
		send_socket_request_for_app_launch(param_str);
	}

	else if (strcmp(param_str, APP_SECOND_PATH) == 0) 
	{
		printf("In strcmp, now start launching the second app %s\n", param_str);
		send_socket_request_for_app_launch(param_str);
	}
}

static void
on_done(void *data, Evas_Object *obj, void *event_info)
{
	// quit the mainloop (elm_run function will return)
	elm_exit();
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
    Evas_Object *win, *lab, *btn, *box_top, *btn_app1, *btn_app2;

    // new window - do the usual and give it a name (hello) and title (Hello)
    win = elm_win_util_standard_add("hello", "Hello");
    // when the user clicks "close" on a window there is a request to delete
    evas_object_smart_callback_add(win, "delete,request", on_done, NULL);

    // add a box_top object - default is vertical. a box_top holds children in a row,
    // either horizontally or vertically. nothing more.
    box_top = elm_box_add(win);
    // make the box_top horizontal
    elm_box_horizontal_set(box_top, EINA_FALSE);
	
	elm_win_resize_object_add(win, box_top);
    // add object as a resize object for the window (controls window minimum
    // size as well as gets resized if window is resized)

    evas_object_show(lab);
	//create inner box_top to show.

    // add a label widget, set the text and put it in the pad frame
    lab = elm_label_add(win);
    // set default text of the label
    elm_object_text_set(lab, "Hello out there world!");
    // pack the label at the end of the box_top
    elm_box_pack_end(box_top, lab);
	
    evas_object_show(lab);


	/**************** OK button ********************/

    // add an ok button
    btn = elm_button_add(win);

	//evas_object_resize(btn, 450, 300); //not working at all
	//evas_object_size_hint_min_set
	
    // set default text of button to "OK"
    elm_object_text_set(btn, "OK");
    // pack the button at the end of the box_top
    elm_box_pack_end(box_top, btn);

	// Finally increase size of the window
	//evas_object_resize(win, 800, 600);

    evas_object_show(btn);
    // call on_done when button is clicked
    evas_object_smart_callback_add(btn, "clicked", on_done, NULL);

    /**************** App1 button  ********************/

    // add the lauch first app  button
    btn_app1 = elm_button_add(win);

	//evas_object_resize(btn, 450, 300); //not working at all
	//evas_object_size_hint_min_set
	
    // set default text of button to "OK"
    elm_object_text_set(btn_app1, APP_FIRST_TITLE);
    // pack the button at the end of the box_top
    elm_box_pack_end(box_top, btn_app1);

	// Finally increase size of the window
	//evas_object_resize(win, 800, 600);

    evas_object_show(btn_app1);
    // call on_done when button is clicked
    evas_object_smart_callback_add(btn_app1, "clicked", on_app_launch_request, APP_FIRST_PATH);

	// [VC] If you don't call this box_top is not showing. 
    evas_object_show(box_top);

/**************** App2 button  ********************/

   // add the lauch first app  button
   btn_app2 = elm_button_add(win);

   //evas_object_resize(btn, 450, 300); //not working at all
   //evas_object_size_hint_min_set
   
   // set default text of button to "OK"
   elm_object_text_set(btn_app2, APP_SECOND_TTLE);
   // pack the button at the end of the box_top
   elm_box_pack_end(box_top, btn_app2);

   // Finally increase size of the window
   //evas_object_resize(win, 800, 600);

   evas_object_show(btn_app2);
   // call on_done when button is clicked
   evas_object_smart_callback_add(btn_app2, "clicked", on_app_launch_request, APP_SECOND_PATH);

   // [VC] If you don't call this box_top is not showing. 
   evas_object_show(box_top);


/**************** Button ********************/

    // now we are done, show the window
    evas_object_show(win);

    // run the mainloop and process events and callbacks
    elm_run();
    elm_shutdown();
    return 0;
}
ELM_MAIN()

