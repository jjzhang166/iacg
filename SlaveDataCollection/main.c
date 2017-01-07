#include <I2C.h>
#include <DH21.h>

#define PCF8591 0x90    //PCF8591 addr 

unsigned char light;	//��������
unsigned char scale;	//���ȿ��Ƽ���
unsigned char PWM;		//ռ�ձ�

volatile unsigned char autoControl;

void autoControlLight(unsigned _on,unsigned char _s);

void rs_intr() interrupt 4 {
	if(TI == 1) { //�����ж�
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
	//LED�Զ��ı�����
	autoControl = 1;
	//��ʱ��������ʽ��ʼ��
	TMOD = 0x22;
	//��ʱ��0��ʼ��
	TH0 = 0X06;
	TL0 = 0X06;
	//��ʱ��1��ʼ��
	TH1 = 0xfd;
	TL1 = 0xfd;
	//���ڳ�ʼ��
	SCON = 0x50;
	PCON = 0X00;
	TI = 0;		//����FLAG
	RI = 0;		//����FLAG
	//���жϼ���ʱ�������ж�����
	ET0 = 1;
	ES = 1;	
	EA = 1;
	//������ʱ��
	TR0 = 1;
	TR1 = 1;
}

void main() {
	sys_init();
	while(1) {
		//�ռ���������
		ISendByte(PCF8591, 0x42);
		light = IRcvByte(PCF8591);
		//�ռ��¶ȡ�ʪ������
		DH21_collData();
		//����λ�������ռ���������
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
