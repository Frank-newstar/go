#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "log.h"
#include "msg.h"
#include "split.h"

int handle_user_input(struct Msg *msg_send){
    char buf[32];

    enum FTP_CMD cmd;
    printf("please input cmd\n");
    fgets(buf,32,stdin);
    if(0==memcmp(buf,"open1",5)){
        cmd =OPEN1;
    }else if(0==memcmp(buf,"close1",6)){
        cmd =CLOSE1;
    }else if(0==memcmp(buf,"open2",5)){
        cmd=OPEN2;
    }else if(0==memcmp(buf,"close2",6)){
        cmd=CLOSE2;
    }else{
        cmd=FTP_CMD_ERROR;
    }
    if(cmd==FTP_CMD_ERROR){
        return -1;
    }
    msg_send->cmd=cmd;
    printf("%d\n",msg_send->cmd);
    strcpy(msg_send->args,buf);
    return 0;
}

int main(int argc, char **argv) {

    struct Msg *msg_send = NULL;
    struct Msg *msg_recv = NULL;
    msg_send = (struct Msg *)malloc(sizeof(struct Msg));
    msg_recv = (struct Msg *)malloc(sizeof(struct Msg));

    log_create("client.txt");

    int ret;
    int c_fd;
    struct sockaddr_in c_addr;
    memset(&c_addr, 0, sizeof(struct sockaddr_in));
    char md5sum[64];
    // 1.socket
    c_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (c_fd == -1) {
        perror("socket");
        exit(-1);
    }
    // 2.connect
    c_addr.sin_family = AF_INET;
    c_addr.sin_port = 8889;
    c_addr.sin_addr.s_addr = inet_addr("192.168.43.223");

    if (connect(c_fd, (struct sockaddr *)&c_addr, sizeof(struct sockaddr_in)) ==
        -1) {
        perror("connect");
        exit(-1);
    }
    printf("welcome!\n");
    while (1) {
        if(handle_user_input(msg_send)<0){
            continue;
        }

        //发送
        ret = send(c_fd, msg_send, sizeof(struct Msg), 0);
        log_write("send ret %d\n", ret);

        //接收
        ret = recv(c_fd, msg_recv, sizeof(struct Msg), 0);
        log_write("recv ret %d\n", ret);
    }

    log_destroy();
    return 0;
}
