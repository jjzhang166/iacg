#include <I2C.h>
#include <DH21.h>

#define PCF8591 0x90    //PCF8591 addr 

unsigned char light;	//亮度数据
unsigned char scale;	//亮度控制级别
unsigned char PWM;		//占空比

volatile unsigned char autoControl;

void autoControlLight(unsigned _on,unsigned char _s);

void rs_intr() interrupt 4 {
	if(TI == 1) { //发送中断
		TI = 0;
		if(count != 6) {
			SBUF = outdata[count];
			count++;
		}
	}
	
	if(RI == 1) {
		unsigned char inchar;
		inchar = SBUF;
		indata[count_r] = inchar;
		count_r++;
		RI = 0;
		if(count_r == 3) {
			count_r = 0;
			if(indata[0]!=0xff)
				return;
			autoControlLight(indata[1],indata[2]);
		}
	}
}

void timer0_intr() interrupt 1 {
	PWM += 10;
	if(PWM == 40) {
		PWM = 0;
		P1 = 0x00;
	}
	if(scale == PWM)
		P1 = 0xff;
}

void autoControlLight(unsigned _on,unsigned char _s) {
	if(_on == 0x01) {
		autoControl = 1;
		return;
	}
	autoControl = 0;
	scale = _s;
}

void sys_init() {
	//LED自动改变亮度
	autoControl = 1;
	//定时器工作方式初始化
	TMOD = 0x22;
	//定时器0初始化
	TH0 = 0X06;
	TL0 = 0X06;
	//定时器1初始化
	TH1 = 0xfd;
	TL1 = 0xfd;
	//串口初始化
	SCON = 0x50;
	PCON = 0X00;
	TI = 0;		//发送FLAG
	RI = 0;		//接收FLAG
	//总中断及定时器串口中断允许
	ET0 = 1;
	ES = 1;	
	EA = 1;
	//启动定时器
	TR0 = 1;
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
		if(autoControl) {
			if(light > 0xe6)
				scale = 40;
			else if(light > 0x8c)
				scale = 20;
			else if(light > 0x64)
				scale = 10;
			else
				scale = 0;
		}
		Delay(20000);
	}
}
