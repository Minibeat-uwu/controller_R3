#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

bool Running = false;
SDL_Event ev;
int Start=0;
//int LXJ, LYJ, RXJ, RYJ, A,B,X,Y, Back, RSB, LSB, DPU, DPD, DPL, DPR, SPL, SPR, RT, LT, Guide;
int Back, RSB, LSB;
int dick;
char a[10];
char b[10];
char c[10];
char d[10];



int main(int args, char* argv[]){

	char server_message[256]="You have reached the server!";
	char test[10];
	
	//create the server socket
	int server_socket;
	server_socket=socket(AF_INET,SOCK_STREAM,0);

	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket to our specificed IP and port
	bind (server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	//listening for the connection	
	listen(server_socket,5);


	int client_socket;
	client_socket=
	accept(server_socket, NULL, NULL);

	//Connection has been set!
	
	strcpy(server_message,"Connection has been made :3\n");
	send(client_socket,server_message,sizeof(server_message),0);
	




	//Now set up the controller :3

	if(SDL_Init(SDL_INIT_JOYSTICK)!=0){
		fprintf(stderr,"Joystick Connection Error \n");
		exit;
	}

	//open the first joystick
	if(SDL_NumJoysticks()<1){
		fprintf(stderr,"No Joystick Found \n");
		exit;
	}

	SDL_GameController* controller = NULL;

	for (int i=0;i<SDL_NumJoysticks();i++){
		if (SDL_IsGameController(i)){
			controller=SDL_GameControllerOpen(i);
			fprintf(stderr, SDL_GameControllerMapping(controller));
			fprintf(stderr,"\n");
			break;
		}
		fprintf(stderr,"\n");
	}
	

	Running=true;

	SDL_PollEvent(&ev);
	int counter=0;

	while(Running){

		if(SDL_PollEvent(&ev)!=0){
			if(ev.type==SDL_QUIT){
				Running=false;
			}
		}//end of pollev


		
		else{
			Back=SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_BACK);
			
			if(counter==0){
				//Joystick Axis
dick=SDL_GameControllerGetAxis(controller,SDL_CONTROLLER_AXIS_LEFTX);
//sprintf(a,"%d",dick);
//printf("%d\n",dick);
sprintf(a,"%d",SDL_GameControllerGetAxis(controller,SDL_CONTROLLER_AXIS_LEFTX));
sprintf(b,"%d",SDL_GameControllerGetAxis(controller,SDL_CONTROLLER_AXIS_LEFTY));
sprintf(c,"%d",SDL_GameControllerGetAxis(controller,SDL_CONTROLLER_AXIS_RIGHTX));
sprintf(d,"%d",SDL_GameControllerGetAxis(controller,SDL_CONTROLLER_AXIS_RIGHTY));

sprintf(server_message, "LAX: %s 	LAY: %s		RAX: %s		RAY: %s\n", a,b,c,d);	

			}//end of if counter0

			
			else if(counter==1){
				// Trigger Axis
sprintf(a,"%d",SDL_GameControllerGetAxis(controller,SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
sprintf(b,"%d",SDL_GameControllerGetAxis(controller,SDL_CONTROLLER_AXIS_TRIGGERLEFT));

sprintf(server_message, "Left Trigger: %s 	Right Trigger: %s\n",a,b);			

			}//end of if counter1

			else if(counter==2){
				//Button base
sprintf(a,"%d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_LEFTSTICK));
sprintf(b,"%d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_RIGHTSTICK));
sprintf(c,"%d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_LEFTSHOULDER));
sprintf(d,"%d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_RIGHTSHOULDER));


sprintf(server_message, "LJB: %s	RJB: %s		LB: %s		RB: %s\n", a,b,c,d);

			}// end of if counter 2

			else if(counter==3){
				//Button base RIGHT
sprintf(a,"%d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_A));
sprintf(b,"%d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_B));
sprintf(c,"%d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_X));
sprintf(d,"%d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_Y));


sprintf(server_message, "A: %s	B: %s	X: %s	Y: %s\n", a,b,c,d);

			}//end of if counter 3

			else if(counter==4){
				//Button Base D-Pad
sprintf(a,"$d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_DPAD_UP));
sprintf(b,"$d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_DPAD_DOWN));
sprintf(c,"$d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_DPAD_LEFT));
sprintf(d,"$d",SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_DPAD_RIGHT));


sprintf(server_message, "DPU: %s	DPD: %s		DPL: %s		DPR: %s\n", a,b,c,d);


			}//end of if counter4

		}// end of else
		
		send(client_socket,server_message,sizeof(server_message),0);
		

		if(Back==1){
			if (counter==0){
				counter++;
				strcpy(server_message,"Mode: Trigger Axis\n");
				send(client_socket,server_message,sizeof(server_message),0);
			}//end counter0

			else if (counter==1){
				counter++;
				strcpy(server_message,"Mode: Joystick Button\n");
				send(client_socket,server_message,sizeof(server_message),0);
			}//end counter1

			else if (counter==2){
				counter++;
				strcpy(server_message,"Mode: Letter Button\n");
				send(client_socket,server_message,sizeof(server_message),0);
			}//end counter2

			else if (counter==3){
				counter++;
				strcpy(server_message,"Mode: D-Pad\n");
				send(client_socket,server_message,sizeof(server_message),0);
			}//end counter3

			else{
				counter++;
				strcpy(server_message,"Mode: Joystick Axis\n");
				send(client_socket,server_message,sizeof(server_message),0);
			}//end else			
			SDL_Delay(1000);
		}
		

		SDL_Delay(250);
		
		RSB=SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_RIGHTSTICK);
		LSB=SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_LEFTSTICK);
		if(RSB==1 && LSB==1){
			strcpy(server_message,"999999999999");
			send(client_socket,server_message,sizeof(server_message),0);
			Running=false;
		}
		

	}

	if(controller!=NULL){
		SDL_GameControllerClose(controller);
	}


//Controller side finished



	
	
/*
	// send the message
	for(int i=0;i<10;i++){
	
	sprintf(test,"%d",i);
	fprintf(stderr,"value of i: %d",i);
	send(client_socket,test,sizeof(test),0);	
	}
	
*/

	//close the socket
	close(server_socket);	
	return 0;
}

