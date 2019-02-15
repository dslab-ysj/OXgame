#ifndef ARTIK_H_
#define ARTIK_H_
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <artik_module.h>
#include <artik_wifi.h>
#include <artik_network.h>
#include <fcntl.h>
#include <tinyara/gpio.h>

#define HIGH 1
#define LOW 0

#define WIFI_SCAN_TIMEOUT       15
#define WIFI_CONNECT_TIMEOUT    30
#define WIFI_DISCONNECT_TIMEOUT 10

struct callback_result {
	sem_t sem;
	artik_wifi_connection_info info;
	artik_error error;
};

void gpio_write(int port, int value);
int gpio_read(int port);
void wifi_connect_callback(void *result, void *user_data);
int wifi_connect(const char* ssid, const char* passphrase);
int start_dhcp_client(void);

#endif /*ARTIK_H_*/
