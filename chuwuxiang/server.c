#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>




int server(int **cmd) {

    int ml;
    *cmd=&ml;    
    int s_fd;
    int c_fd;
	
    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;
    memset(&s_addr, 0, sizeof(struct sockaddr_in));
    memset(&c_addr, 0, sizeof(struct sockaddr_in));

    char recv_msg[200];
    

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
          	

            printf("%s\n",recv_msg);
            if(strcmp(recv_msg,"1")==0){
                ml=1;
            }
	    else if(strcmp(recv_msg,"2")==0){
                ml=2;
            }
	    else if(strcmp(recv_msg,"3")==0){
                ml=3;
            }
	    else if(strcmp(recv_msg,"4")==0){
                ml=4;
            }
	    else if(strcmp(recv_msg,"5")==0){
                ml=5;
            }
	    else if(strcmp(recv_msg,"6")==0){
                ml=6;
            }
	    else if(strcmp(recv_msg,"7")==0){
                ml=7;
            }
	    else if(strcmp(recv_msg,"8")==0){
	    	ml=8;
	    }

           // send(c_fd,msg_send,sizeof(struct send_Msg),0);
        close(c_fd);
    }
    return 0;
}
