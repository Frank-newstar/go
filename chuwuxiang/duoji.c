#include<stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#define RANGE 200  // 1 means 100 us , 200 means 20 ms 1等于100微妙，200等于20毫秒
    void duoji(int pin,int jiaodu) {
    int i;
    int degree;
    degree = 5 +jiaodu / 180.0 * 20.0;
    softPwmCreate(pin, 15, RANGE);  //创建一个使舵机转到90的pwm输出信号
    delay(1000);



//        softPwmWrite(pin, 5);  //将pwm输出复写为使舵机转到0

//        delay(1000);

        softPwmWrite(pin, degree);  //再次复写pwm输出

        delay(1000);


  //  softPwmWrite(pin, 15);
}
/*
int main(){

    char a;
    wiringPiSetup();
    while(1){
    printf("input:\n");
    scanf("%c",&a);
    switch(a){
        case'k':
            duoji(29,90);
            break;
        case'g':
            duoji(29,0);
            break;
        default:
            break;
    }
    }
    return 0;
}
*/
