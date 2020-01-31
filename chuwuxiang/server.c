#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "duoji.h"
#include <unistd.h>


int xiugaimima(int num,char *recv_msg){
    
	int fd;
    char *p=malloc(1024);
    char *data=malloc(1024);
        if((fd=serialOpen("/dev/ttyUSB0",115200))<0){
            printf("open serial fail\n");
            return 1;
        }
        p=strtok(recv_msg,":");
        p=strtok(NULL,":");

    if(num==1){   
        sprintf(data,"02,%s,003,$",p);
		printf("%s\n",data);
    }else if(num==2){
        sprintf(data,"03,%s,004,$",p);
    }
    int flag=1;
    char *buf=malloc(1024);

    while(flag){
        write(fd,data,strlen(data));
	printf("0\n");
	if(serialDataAvail(fd)>0){
		printf("1\n");
			
	}
	if(strcmp(buf,"D0B4C8EBB3C9B9A6A3A10D0A")==0){
		flag==0;
	}
    }
	printf("change success\n");

    return 0;
}

void handle_cmd(int cmd,char *recv_msg) {

    switch (cmd) {
        case 1:
            duoji(29,90);
            break;
        case 2:
            duoji(29,0);
            break;
        case 3:
            xiugaimima(1,recv_msg);
            break;
        case 4:
            xiugaimima(2,recv_msg);
            break;
        default:
            break;
    }
}

int server() {

    int s_fd;
    int c_fd;

    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;
    memset(&s_addr, 0, sizeof(struct sockaddr_in));
    memset(&c_addr, 0, sizeof(struct sockaddr_in));

    char recv_msg[200];
   
    int cmd;

    // 1.socket
    s_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s_fd == -1) {
        perror("socket");
        exit(-1);
    }

    int on = 1;
    setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    // 2.bind
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(8889);
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr_in));
    // 3.listen
    listen(s_fd, 10);
    // 4.accept
    int clen = sizeof(struct sockaddr_in);

    while (1) {

        c_fd = accept(s_fd, (struct sockaddr *)&c_addr, &clen);
        if (c_fd == -1) {
            perror("accept");
        }

        //printf("server connected\n");

         
            memset(recv_msg,'\0',200);
            recv(c_fd,recv_msg,200,0);
            cmd=0;

            printf("%s\n",recv_msg);
            if(strcmp(recv_msg,"open")==0){
                cmd=1;
            }else if(strcmp(recv_msg,"close")==0){
                cmd=2;
            }else if(memcmp(recv_msg,"mi_kai",6)==0){
                cmd=3;
            }else if(memcmp(recv_msg,"mi_guan",7)==0){
                cmd=4;
            }

            handle_cmd(cmd,recv_msg);
           // send(c_fd,msg_send,sizeof(struct send_Msg),0);
        close(c_fd);
    }
    return 0;
}
