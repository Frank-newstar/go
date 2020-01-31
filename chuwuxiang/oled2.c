#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int fd;
//const unsigned char zi[];
unsigned char yi[10] = {
    "          "
};                       
   
void init(void)  //��ʼ��
{
    wiringPiSetup();
    fd = wiringPiI2CSetup(0x3c);  // i2c��ʼ�� 0x3c��oled�Ĵӻ���ַ
    wiringPiI2CWriteReg8(fd, 0x00, 0xa1);  //ͼ�����޸ĳ�0xa0
    wiringPiI2CWriteReg8(fd, 0x00, 0xc8);  //����������޸ĳ�0xc0
    wiringPiI2CWriteReg8(fd, 0x00, 0x8d);  //�����ɱ�
    wiringPiI2CWriteReg8(fd, 0x00, 0x14);
    wiringPiI2CWriteReg8(fd, 0x00, 0xa6);  //�뷴����ʾ�ĳ�0xa7
    wiringPiI2CWriteReg8(fd, 0x00, 0x21);  //�����е�ַ
    wiringPiI2CWriteReg8(fd, 0x00, 0x00);
    wiringPiI2CWriteReg8(fd, 0x00, 0x7f);
    wiringPiI2CWriteReg8(fd, 0x00, 0xaf);  //����ʾ
}
void qingping(void)  //����
{
    char zt1, zt2;
    for (zt1 = 0; zt1 < 8; zt1++) {
        wiringPiI2CWriteReg8(fd, 0x00, 0xb0 + zt1);
        for (zt2 = 0; zt2 < 128; zt2++) wiringPiI2CWriteReg8(fd, 0x40, 0x00);
    }
}
void ascii(void)  //��ʾASCII��8*16
{
    int zt;
    char zt3, zt4;
    //for (zt3 = 0; zt3 < 4; zt3++) {
      
    wiringPiI2CWriteReg8(fd, 0x00, 0xb0 + (zt3 * 2));
        //for (zt4 = 0; zt4 < 14; zt4++)
            for (zt = 0; zt < 14; zt++)
                wiringPiI2CWriteReg8(fd, 0x40, zi[yi[0] * 14 + zt]);
        wiringPiI2CWriteReg8(fd, 0x00, 0xb0 + (zt3 * 2) + 1);
        //for (zt4 = 0; zt4 < 14; zt4++)
            for (zt = 0; zt < 14; zt++)
                wiringPiI2CWriteReg8(fd, 0x40, zi[yi[0] * 14 + zt + 14]);
    
}
/*void shijian(void)  //��ǰʱ��
{
    struct tm *ptr;
    time_t lt;
    lt = time(&lt);
    ptr = localtime(&lt);
  //  strftime(yi[1], 16, "%m/%d %a", ptr);  //��/�� �ܼ�
    strftime(yi[0], 16, "%R %p", ptr);     //ʱ:�� am��pm
}*/

/*
void wendu(){
    int fd,size;
    char buf[1024]={'\0'};
    char *pbuf=buf;
    char buf2[1024]={'\0'};
    char *pbuf2=buf2;
    char *p;
    char key[128]={'\0'};
    float scores;
    fd =open("/sys/bus/w1/devices/28-01144df107aa/w1_slave",O_RDONLY);
    size=lseek(fd,0,SEEK_END);
    lseek(fd,0,SEEK_SET);
    read(fd,buf,size);
//    printf("%s",buf);
    while(*pbuf!='\n'){
        pbuf++;
    }
    pbuf++;
    while(*pbuf!='\0'){
        *pbuf2++=*pbuf++;
    }
    p=strtok(buf2,"=");
    p=strtok(NULL,"=");
    scores=(atof(p)/1000);
    sprintf(yi[1],"tmp=%0.3f",scores);

}
*/

int main(){
	init();
	qingping();

	while(1){
		//shijian();
		ascii();
		delay(100);
	}
}
const unsigned char zi[]={

 0x20,0x21,0xE6,0x00,0x20,0xAA,0xAA,0xAA,0xBF,0xAA,0xAA,0xAA,0x20,0x00,0x00,0x00,
 0x1F,0x08,0x04,0x3F,0x0A,0x0A,0x0A,0x2A,0x2A,0x3F,0x00,0x00,/*"�",0*/
 /* (14 X 14 , �� )*/

 0x74,0x4F,0xE4,0x44,0x10,0xC8,0x54,0x52,0xD1,0x12,0x94,0x08,0xD0,0x00,0x04,0x04,
 0x3F,0x02,0x00,0x3F,0x05,0x25,0x3F,0x00,0x2F,0x20,0x3F,0x00,/*"�",1*/
 /* (14 X 14 , �� )*/

 0x00,0x00,0x00,0x00,0x81,0x66,0x18,0x60,0x80,0x00,0x00,0x00,0x00,0x00,0x20,0x10,
 0x08,0x06,0x01,0x00,0x00,0x00,0x01,0x06,0x08,0x10,0x20,0x00,/*"�",2*/
 /* (14 X 14 , �� )*/

 0x08,0x08,0xFF,0x88,0x48,0x00,0x9F,0xA4,0xA4,0xA4,0xA2,0xA2,0x38,0x00,0x21,0x21,
 0x3F,0x00,0x00,0x00,0x3F,0x24,0x24,0x24,0x24,0x3F,0x00,0x00,/*"�",3*/
 /* (14 X 14 , �� )*/

 0x98,0x54,0x33,0x18,0x00,0x08,0xF8,0x09,0x0E,0x08,0xF8,0x08,0x08,0x00,0x11,0x11,
 0x09,0x09,0x20,0x20,0x10,0x0B,0x04,0x0B,0x10,0x20,0x20,0x00,/*"�",4*/
 /* (14 X 14 , �� )*/
};
