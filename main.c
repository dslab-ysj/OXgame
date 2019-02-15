#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "artik.h"
#include "udelay.h"
#include <net/lwip/sockets.h>
#include <string.h>
#include <stdlib.h>
#include <readline.h>

#define BACKLOG 10
#define MAX_DATA_SIZE 100
#define PORT 1234
#define ip_addr "192.168.1.4"

int main() {
	int s, i;
	int ret, len;
	struct sockaddr_in server_addr;
	char recv_data[MAX_DATA_SIZE];
	char str[MAX_DATA_SIZE];
	char NUM[MAX_DATA_SIZE];

	wifi_main();

	printf("Set up address...\n");
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_len = sizeof(server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT); //port
	server_addr.sin_addr.s_addr = inet_addr(ip_addr); //host

	// create the socket
	printf("Create the socket...\n");
	s = lwip_socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
    	printf("[Error] lwip_socket()\n");
    	return -1;
    }

    // connect
    printf("Connect to server...\n");


    while(1){

        ret = lwip_connect(s, (struct sockaddr*)&server_addr, sizeof(server_addr));

        if (ret == -1) {

        	printf("[Error] lwip_connect()\n");

        	return -1;
        }

		ret = lwip_recv(s, recv_data, MAX_DATA_SIZE, MSG_WAITALL);

		if(ret > 0){

					recv_data[ret] = '\0';

					printf("%s\n",recv_data);

		}

		int num = 0;

		printf("%d\n",num);

		while(1){

			if(gpio_read(46) == 1){

				num++;

				if(num == 6)
					num = 1;

				printf("%d\n",num);

				while(gpio_read(46) == 1);

			}

			if(gpio_read(47) == 1){

				if(num == 0){
					printf("Please write right number!\n");
					while(gpio_read(47));
				}
				else{
					printf("Group : %d\n",num);

					len = strlen(itoa(num,NUM,10));

					ret = lwip_write(s, NUM, len);

					num = 9999;

					if (ret != (int)len) {
						printf("[Error] lwip_write()\n");

						ret = lwip_close(s);

						if (ret == -1) {
							printf("[Error] lwip_close()\n");
							return -1;
						}

						return -1;
					}

					else
						break;
				}
			}

		}

		if(num == 9999)
			break;
	}

		ret = lwip_recv(s, recv_data, MAX_DATA_SIZE, MSG_WAITALL);

   		if(ret > 0){

   					recv_data[ret] = '\0';

   					printf("%s\n",recv_data);

   		}

   	while(gpio_read(47));

    while(1){

   		int num = 0;

   		printf("%d\n",num);

   		while(1){

   			if(gpio_read(46) == 1){

   				num++;

   				if(num == 5)
   					num = 1;

   				printf("%d\n",num);

   				while(gpio_read(46) == 1);

   			}

   			if(gpio_read(47) == 1){

   				if(num == 0){
   					printf("Please write right number!\n");
   					while(gpio_read(47));
   				}

   				else{

					printf("Number : %d\n",num);

					len = strlen(itoa(num,NUM,10));

					ret = lwip_write(s, NUM, len);

					num = 9999;

					if (ret != (int)len) {
						printf("[Error] lwip_write()\n");

						ret = lwip_close(s);

						if (ret == -1) {
							printf("[Error] lwip_close()\n");
							return -1;
						}

						return -1;
					}

					else
						break;
				}
   			}

   		}

   		if(num == 9999)
   			break;
   	}

   	while(gpio_read(47));

    while(1) {

    	ret = lwip_recv(s, recv_data, MAX_DATA_SIZE, MSG_DONTWAIT);

    	if(ret > 0){

    		recv_data[ret] = '\0';
    		printf("%s\n",recv_data);
    	}

    	if(gpio_read(46) == 1){
        	len = 1;
        	ret = lwip_write(s, "O", len);
        	if (ret != (int)len) {
        		printf("[Error] lwip_write()\n");
        	    return -1;
        	}
        	while(gpio_read(46));
    	} else if(gpio_read(47) == 1){
        	len = 1;
        	ret = lwip_write(s, "X", len);
        	if (ret != (int)len) {
        		printf("[Error] lwip_write()\n");
        	    return -1;
        	}
        	while(gpio_read(47));
    	} else if(gpio_read(48) == 1){
        	len = 4;
        	ret = lwip_write(s, "good" , len);

        	if (ret != (int)len) {
        		printf("[Error] lwip_write()\n");
        	    return -1;
        	}
        	while(gpio_read(48));
    	} else if(gpio_read(50) == 1){
        	len = 3;
        	ret = lwip_write(s, "bad\r" , len);
        	if (ret != (int)len) {
        		printf("[Error] lwip_write()\n");
        	    return -1;
        	}while(gpio_read(50));
    	}




    	if ((str[0] == 'q')) {
        	// close
        	printf("Close socket...\n");
        	ret = lwip_close(s);
        	if (ret == -1) {
        	    printf("[Error] lwip_close()\n");
        	    return -1;
        	}
        	break;
    	}
    }
    return 0;
}

