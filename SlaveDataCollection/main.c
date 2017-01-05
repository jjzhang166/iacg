#include <I2C.h>
#include <DH21.h>

#define PCF8591 0x90    //PCF8591 addr 

unsigned char light;

void rs_intr() interrupt 4 {
	if(TI==1) { //发送中断
		TI=0;
		if(count!=6) {
			SBUF= outdata[count];
			count++;
		}
	}
}

void sys_init() {
	//定时器初始化
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	//串口初始化
	SCON = 0x50;
	PCON = 0X00;
	TI = 0;		//发送FLAG
	RI = 0;		//接收FLAG
	//总中断及串口中断允许
	ES = 1;	
	EA = 1;
	//启动定时器
	TR1 = 1;
}

void main() {
	sys_init();
	while(1) {
		//收集光照数据
		ISendByte(PCF8591, 0x42);
		light = IRcvByte(PCF8591);
		//收集温度、湿度数据
		DH21_collData();
		//向上位机发送收集到的数据
		outdata[0] = 0xff;
		outdata[1] = U8RH_data_L;
		outdata[2] = U8RH_data_H;
		outdata[3] = U8T_data_L;
		outdata[4] = U8T_data_H;
		outdata[5] = light;
		DH21_sendData(outdata);
		Delay(20000);
	}
}

