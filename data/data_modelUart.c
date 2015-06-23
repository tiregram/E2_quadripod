#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_struct.h"
#include "data_Sequence.h"
#include "../include/basic.h"
#include "../interface/ncurses_MessageBox.h"
#include "data_modelUart.h"
#include <fcntl.h>


int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);



uart_struct * uart_init(char *  portname ){
	uart_struct * this = malloc(sizeof(uart_struct));
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
		return;
	// error_message ("error %d setting term attributes", errno);
}



int uart_sendNew(uart_struct * this, list_sequence *sequence,MessBox *mess){
	if(sequence->curent->send){
		messageBox_print(mess,MESBOX_BASIC,"\nla sequence est deja sur le robot");		
		return 1;
	}
	messageBox_print(mess,MESBOX_BASIC,"\nenvoie de la sequence");		

	char a[2];
	write (this->file, "C", 1);
	sequence_export_command_all(this->file,sequence->curent->seq);
	write (this->file, "$", 1);
	read(this->file,a,2);
	sequence->curent->send=1;
	messageBox_print(mess,MESBOX_VALID,"\nsequence envoie");
	return atoi(a);
}

int uart_sendModif(uart_struct * this, list_sequence * sequence,MessBox *mess){
	uart_sendModifBasic(this->file,sequence->curent ,mess);
	return 0;
}

int uart_sendModifBasic(int file,sequenc * sequence,MessBox *mess){
	
	if(sequence->send){
		messageBox_print(mess,MESBOX_BASIC,"\nla sequence est deja sur le robot");		
		return 1;
	}

	messageBox_print(mess,MESBOX_BASIC,"\nenvoie de la sequence");
	write (file, "M", 1);
	char a[2];
	sprintf(a,"%2i",sequence->num);
	write(file, a, 2);
	sequence_export_command_all(file,sequence->seq);
	sequence_tool_replace(a,' ','0');
	write (file, "$", 1);
	sequence->send = 1;
	messageBox_print(mess,MESBOX_VALID,"\nsequence send");
	return 1;
}



int uart_sendJouer(uart_struct * this ,list_sequence * sequence,MessBox * mess){
	messageBox_print(mess,MESBOX_VALID,"\ndebut de la sequence");
	write (this->file, "J", 1);
	char a[3];
	sprintf(a,"%2i\n",sequence->curent->num);
	sequence_tool_replace(a,' ','0');
	write(this->file, a, 3);
	return 1;
}

int uart_sendSet(uart_struct * this ,unsigned long pin ,unsigned long pos){
	char b[7];
	sprintf(b,"S%2ld%3ld\n",pin,pos);
	sequence_tool_replace(b,' ','0');
	write(this->file, b, 7);

	return 1;
}

int uart_ping_cpp(int file){
	write(file,"T",1);	
	return 0;
}

int uart_ping(uart_struct * this){
	uart_ping_cpp(this->file);
	

	return 1;
}

int uart_sendJouer_cpp(int file ,char num){
	write (file, "J", 1);
	char a[3];
	sprintf(a,"%2i\n",num);
	sequence_tool_replace(a,' ','0');
	write(file, a, 3);
	return 1;
}







