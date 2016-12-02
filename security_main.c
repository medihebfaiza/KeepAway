#include <stdio.h>
#include <stdlib.h>
#include "library/grovepi.h"

//Compilation : gcc security_main.c library/grovepi.c -o security_main
//Execution : sudo ./security_main

#define us_cmd 7

int main(void)
{
	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);

	int PIN = 4; // Capteur branché sur le port D4 (digital 4)
	int data;

	//Augmenter le son au maximum
	system("amixer -D pulse sset Master 100%")

	while(1) // boucle infinie
	{
	  write_block(us_cmd, PIN, 0, 0);
	  pi_sleep(200);
	  read_byte();
	  read_block();
	  data=r_buf[1]* 256 + r_buf[2];
	  printf("%d %d\n", r_buf[1], r_buf[2]);
	  printf("Distance : %d cm\n", data);
		if ((data>100.0) && (data<=150.0)){
			system("omxplayer resources/alarme_boosted.wav") ; //lit le message audio
		}
		else if (data<=100.0){
			system("raspistill -v -o photo.jpg") ; //prend en photo
			//récuperer le fichier via ssh avec : scp faizabenchraa@162.38.111.124:photo.jpg ~
		}
	  pi_sleep(500); // attend 500ms
	}
   	return 1;
}
