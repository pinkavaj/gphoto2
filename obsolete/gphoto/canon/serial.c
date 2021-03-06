/****************************************************************************
 *
 * File: serial.c 
 *
 * Serial communication layer.
 *
 ****************************************************************************/

/****************************************************************************
 *
 * include files
 *
 ****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>

#include "util.h"
#include "psa50.h"
#include "../src/gphoto.h"

/****  new stuff ********/
#include <gpio.h>
extern struct Model *Camera;  
int gpio_usb_find_device(int idvendor, int idproduct, struct usb_device **device);
int gpio_usb_msg_write(gpio_device *dev, int value, char *bytes, int size);
int gpio_usb_msg_read(gpio_device *dev, int value, char *bytes, int size);
int gpio_usb_read(gpio_device *dev, char *bytes, int size);
int gpio_usb_write(gpio_device *dev, char *bytes, int size);
/*******  new stuff *********/


/****************************************************************************
 *
 * static global storage area
 *
 ****************************************************************************/

gpio_device *iodev;
gpio_device_settings settings;


void serial_flush_input(void)
{
}

void serial_flush_output(void)
{
}

/*****************************************************************************
 *
 * canon_serial_change_speed
 *
 * change the speed of the communication.
 *
 * speed - the new speed
 *
 * Returns 1 on success.
 * Returns 0 on any error.
 *
 ****************************************************************************/

int canon_serial_change_speed(int speed)
{
         /* set speed */
  gpio_get_settings(iodev, &settings);
  settings.serial.speed = speed;
  gpio_set_settings(iodev, settings);

	usleep(70000);

    return 1;
}
 

/*****************************************************************************
 *
 * canon_serial_get_cts
 *
 * Gets the status of the CTS (Clear To Send) line on the serial port.
 *
 * CTS is "1" when the camera is ON, and "0" when it is OFF.
 *
 * Returns 1 on CTS high.
 * Returns 0 on CTS low.
 *
 ****************************************************************************/
int canon_serial_get_cts(void)
{
	return gpio_get_pin(iodev,PIN_CTS);
}


/*****************************************************************************
 *
 * canon_serial_init
 *
 * Initializes the given serial or USB device.
 *
 * devname - the name of the device to open 
 *
 * Returns 0 on success.
 * Returns -1 on any error.
 *
 ****************************************************************************/

int canon_serial_init(const char *devname)
{
#ifdef GPIO_USB
    char msg[65536];
    char buffer[65536];
    gpio_device_settings settings;
    struct usb_device *udev;
#endif

    debug_message("Initializing the camera.\n");

  switch (canon_comm_method) {
  case CANON_USB:
#ifdef GPIO_USB
    
    if (gpio_usb_find_device(Camera->idVendor,
			     Camera->idProduct, &udev)) {
      printf("found '%s' @ %s/%s\n", Camera->name,
	     udev->bus->dirname, udev->filename);
    }
    else
      {
	printf("Found no camera!\n");
	exit(1);
      }
    iodev = gpio_new(GPIO_DEVICE_USB);
    if (!iodev)
      {
	 return -1; 
      }
      
    
    settings.usb.udev = udev;

	settings.usb.inep = 0x81;
	settings.usb.outep = 0x02;
	settings.usb.config = 1;
	settings.usb.interface = 0;
	settings.usb.altsetting = 0;

	/*	canon_send = canon_usb_send;
		canon_read = canon_usb_read; */

	gpio_set_settings(iodev, settings);
	if (gpio_open(iodev) < 0) {
	  fprintf(stderr,"Camera used by other USB device!\n");
	  exit(1);
	  /* return -1; */
	}

	gpio_usb_msg_read(iodev,0x55,msg,1);
	//	fprintf(stderr,"%c\n",msg[0]);
	gpio_usb_msg_read(iodev,0x1,msg,0x58);
	gpio_usb_msg_write(iodev,0x11,msg+0x48,0x10);
	gpio_read(iodev, buffer, 0x44);
	//	fprintf(stderr,"Antal b: %x\n",buffer[0]);
	if (buffer[0]==0x54)
	  gpio_read(iodev, buffer, 0x40);
	return 0;
	/* #else
	   return -1;*/ 
#else
	fprintf(stderr,"This computer does not support USB, please try to select 'RS-232'\n"
		       " in the configuration panel (Configure/Configure camera...).\n");
	return -1;
#endif
	break;
  case CANON_SERIAL_RS232:
  default:
    
    if (!devname)
      {
	fprintf(stderr, "INVALID device string (NULL)\n");
	return -1;
      }
    
    debug_message("canon_init_serial(): Using serial port on %s\n", devname);
    
    iodev = gpio_new(GPIO_DEVICE_SERIAL);
    
    strcpy(settings.serial.port, devname);
    settings.serial.speed = 9600;
    settings.serial.bits = 8;
    settings.serial.parity = 0;
    settings.serial.stopbits = 1;
    
    gpio_set_settings(iodev, settings); /* Sets the serial device name */
    if ( gpio_open(iodev) == GPIO_ERROR) {	/* open the device */
      perror("Unable to open the serial port");
	return -1;
    }

    return 0;
  }
}

/*****************************************************************************
 *
 * canon_serial_restore
 *
 * Restores the saved settings for the serial device
 * 
 * Returns 0 on success.
 * Returns -1 on any error.
 *
 ****************************************************************************/

int canon_serial_restore()
{

    gpio_close(iodev);

    return 0;
}

/*****************************************************************************
 *
 * canon_serial_send
 *
 * Send the given buffer with given length over the serial line.
 *
 * buf   - the raw data buffer to send
 * len   - the length of the buffer
 * sleep - time in usec to wait between characters
 *
 * Returns 0 on success, -1 on error.
 *
 ****************************************************************************/

int canon_serial_send(char *buf, int len, int sleep)
{
	int i;
    dump_hex("canon_serial_send()", buf, len);

    if (sleep>0) {
      for(i=0;i<len;i++) {
    	gpio_write(iodev,buf,1);
	buf++;
	usleep(sleep);
      }
    }
    else {
      gpio_write(iodev,buf,len);
    }
    
    return 0;
}


/**
 * Sets the timeout, in miliseconds.
 */
void serial_set_timeout(int to)
{
  gpio_set_timeout(iodev,to);
}

/*****************************************************************************
 *
 * canon_serial_get_byte
 *
 * Get the next byte from the serial line.
 * Actually the fucntion reads chunks of data and keeps them in a cache.
 * Only one byte per call will be returned.
 *
 * Returns the byte on success, -1 on error.
 *
 ****************************************************************************/
int canon_serial_get_byte()
{
    static unsigned char cache[512];
    static unsigned char *cachep = cache;
    static unsigned char *cachee = cache;
    int recv;

    /* if still data in cache, get it */
    if (cachep < cachee)
    {
	return (int) *cachep++;
    }


    recv = gpio_read(iodev, cache, 1);
    if (recv == GPIO_ERROR || recv == GPIO_TIMEOUT)
	return -1;
	cachep = cache;
	cachee = cache + recv;

	if (recv)
	{
	    return (int) *cachep++;
	}
    
    return -1;
}

/****************************************************************************
 *
 * End of file: serial.c
 *
 ****************************************************************************/
