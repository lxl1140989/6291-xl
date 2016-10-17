#include <errno.h>
#include <stdlib.h>
#include <stdio.h>          
#include <ctype.h>
#include <time.h>           
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>      
#include <setjmp.h>

#include <netinet/in.h>
#include <linux/wireless.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include <sys/mman.h>
#include <sys/types.h>        
#include <sys/socket.h>      
#include <sys/stat.h>         

#define GET_RESET_BTN			0x30
#define GET_DEC_BTN				0x31



#define JZ_GPIO "/proc/jz_gpio"

#define SHORT_PRESS 	1
#define LONG_PRESS 		2

//长按的时间定义，单位为秒
#define LONG_PRESS_TIME  3

int check_reset_button()
{
	int fd;
	unsigned char btn_status;
	int time_count=0;
	int ret;
	fd=open(JZ_GPIO,O_RDWR);
	if(fd==-1)
		return -1;

	ioctl(fd, GET_RESET_BTN, &btn_status);
	if(btn_status==1)
	{
		close(fd);
		return 0;
	}
	usleep(10000); //按键消抖
	do {
		sleep(1);
		time_count++;
		ioctl(fd, GET_RESET_BTN, &btn_status);


	} while(btn_status!=1);
	usleep(10000); //按键消抖
	
	if(time_count > LONG_PRESS_TIME)
		ret = LONG_PRESS;
	else
		ret = SHORT_PRESS;

	close(fd);
	return ret;

}

int check_dec_button()
{
	int fd;
	unsigned char btn_status;
	int time_count=0;
	int ret;
	fd=open(JZ_GPIO,O_RDWR);
	if(fd==-1)
		return -1;

	ioctl(fd, GET_DEC_BTN, &btn_status);
	if(btn_status==1)
	{
		close(fd);
		return 0;
	}
	usleep(10000); //按键消抖
	do {
		sleep(1);
		time_count++;
		ioctl(fd, GET_DEC_BTN, &btn_status);


	} while(btn_status!=1);
	usleep(10000); //按键消抖
	
	if(time_count > LONG_PRESS_TIME)
		ret = LONG_PRESS;
	else
		ret = SHORT_PRESS;

	close(fd);
	return ret;

}



int main(int argc, char** argv)
{

	int button_status;

	while(1)
	{
		button_status = check_reset_button();
		if( button_status == SHORT_PRESS )
		{
			system("echo 1 > /sys/class/leds/system\:led\:green/brightness");
			system("echo 0 > /sys/class/leds/system\:led\:blue/brightness");
			system("echo 0 > /sys/class/leds/system\:led\:red/brightness");
		}
		button_status = check_dec_button();
		if( button_status == SHORT_PRESS )
		{
			system("echo 1 > /sys/class/leds/system\:led\:red/brightness");
			system("echo 0 > /sys/class/leds/system\:led\:blue/brightness");
			system("echo 0 > /sys/class/leds/system\:led\:green/brightness");
		}
		usleep(100000);

	}

}

