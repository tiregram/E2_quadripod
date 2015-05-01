#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_struct.h"
#include "../include/basic.h"
#include "data_modelUart.h"
#include <fcntl.h>

int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);



uart_instance * init_uart(char *  portname ){
	uart_instance * this = malloc(sizeof(uart_instance));
	this->nom = portname;
	this->file = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (this->file < 0)
	{	
		this->work = 0;
		return this;
	}
	
	set_interface_attribs (this->file, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
	set_blocking (this->file, 0);   
	this->work = 1;
	return this;
}






	int
set_interface_attribs (int fd, int speed, int parity)
{
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0)
	{
		//error_message ("error %d from tcgetattr", errno);
		return -1;
	}

	cfsetospeed (&tty, speed);
	cfsetispeed (&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // disable break processing
	tty.c_lflag = 0;                // no signaling chars, no echo,
	// no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN]  = 0;            // read doesn't block
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
	// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
	{
		// error_message ("error %d from tcsetattr", errno);
		return -1;
	}
	return 0;
}

	void
set_blocking (int fd, int should_block)
{
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0)
	{
		//error_message ("error %d from tggetattr", errno);
		return;
	}

	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
		;
	// error_message ("error %d setting term attributes", errno);
}


// nepta define la fonction void (*varname)(uar_instancez*, struct circular_...);
void uart_sendOneFrame(uart_instance * this,struct circular_vector_mouv * mouv){
	char  a[20];	
	write (this->file, "F", 1);

	sprintf(a,"%ld",mouv->delay);
	write (this->file, a, strlen(a));

	write (this->file, "P", 1);

	write (this->file,a,6);
	for(int i= 0;i <nb_servo;i++){

		sprintf(a,"%2ld%3ld",mouv->mouv[i].pin,mouv->mouv[i].pos);
		write (this->file, "a",5); 
	}
	write (this->file, "#", 1);

}


void uart_sendAllFrame(uart_instance * this ,circular_vector * sequence){
	struct circular_vector_mouv * first =sequence->first;
	uart_sendOneFrame(this,first);
	struct circular_vector_mouv * ite = first->next;
	while(ite!=first){
		uart_sendOneFrame(this,ite);
		ite = first->next;
	}
}


int uart_sendNew(uart_instance * this, circular_vector * sequence){
	char a[3];
	write (this->file, "N", 1);
	uart_sendAllFrame(this,sequence);
	write (this->file, "$", 1);
	read(this->file,a,2);
	return atoi(a);
}

void uart_sendModif(uart_instance * this, circular_vector * sequence,int indice){
	write (this->file, "M", 1);
	char a[3];
	sprintf(a,"%i",indice);
	write(this->file, a, 2);
	uart_sendAllFrame(this,sequence);
	write (this->file, "$", 1);
}

void uart_sendJouer(uart_instance * this , int indice){
	write (this->file, "J", 1);
	char a[3];
	sprintf(a,"%i",indice);
	write(this->file, a, 2);
}





/*
   char *portname = "/dev/ttyUSB1"
   int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
   if (fd < 0)
   {
   error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
   return;
   }

   set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
   set_blocking (fd, 0);                // set no blocking

   write (fd, "hello!\n", 7);           // send 7 character greeting

   usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
// receive 25:  approx 100 uS per char transmit
char buf [100];
int n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read
*/
