#include <I2C.h>
#include <DH21.h>

#define PCF8591 0x90    //PCF8591 addr 

unsigned char light;

void rs_intr() interrupt 4 {
	if(TI==1) { //�����ж�
		TI=0;
		if(count!=6) {
			SBUF= outdata[count];
			count++;
		}
	}
}

void sys_init() {
	//��ʱ����ʼ��
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	//���ڳ�ʼ��
	SCON = 0x50;
	PCON = 0X00;
	TI = 0;		//����FLAG
	RI = 0;		//����FLAG
	//���жϼ������ж�����
	ES = 1;	
	EA = 1;
	//������ʱ��
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
		Delay(20000);
	}
}

