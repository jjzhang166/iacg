#include <DH21.h>

//���ݶ���
U8  U8FLAG,k;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;
U8  outdata[6];  //���巢�͵��ֽ���	   
U8  count;
U16 U16temp1,U16temp2;

void DH21_sendData(U8* a) {
	outdata[0] = a[0]; 
	outdata[1] = a[1];
	outdata[2] = a[2];
	outdata[3] = a[3];
	outdata[4] = a[4];
	outdata[5] = a[5];
	count = 1;
	SBUF=outdata[0];
}

void DH21_COM(void) {
	U8 i;
	for(i=0;i<8;i++) {
		U8FLAG=2;	
	   	while((!P2_0)&&U8FLAG++);
		Delay_10us();
		Delay_10us();
		Delay_10us();
		U8temp=0;
		if(P2_0)U8temp=1;
			U8FLAG=2;
		while((P2_0)&&U8FLAG++);
	   	//��ʱ������forѭ��		  
		if(U8FLAG==1)break;
	   	//�ж�����λ��0����1	 
	   	   
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1 
		U8comdata<<=1;
		U8comdata|=U8temp;
	 }
}

void DH21_collData(void) {
	//��������18ms 
	P2_0=0;
	Delay(180);
	P2_0=1;
	//������������������ ������ʱ20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//������Ϊ���� �жϴӻ���Ӧ�ź� 
	P2_0=1;
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
	if(!P2_0) {
		U8FLAG=2;
		//�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
		while((!P2_0)&&U8FLAG++);
		U8FLAG=2;
		//�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
		while((P2_0)&&U8FLAG++);
		//���ݽ���״̬		 
		DH21_COM();
		U8RH_data_H_temp=U8comdata;
		DH21_COM();
		U8RH_data_L_temp=U8comdata;
		DH21_COM();
		U8T_data_H_temp=U8comdata;
		DH21_COM();
		U8T_data_L_temp=U8comdata;
		DH21_COM();
		U8checkdata_temp=U8comdata;
		P2_0=1;
		//����У�� 
		U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
		if(U8temp==U8checkdata_temp) {
			U8RH_data_H=U8RH_data_H_temp;
			U8RH_data_L=U8RH_data_L_temp;
			U8T_data_H=U8T_data_H_temp;
			U8T_data_L=U8T_data_L_temp;
			U8checkdata=U8checkdata_temp;
		}
   }
}

void Delay(U16 j) {
	U8 i;
	for(;j>0;j--) { 	
		for(i=0;i<27;i++);
	}
}

void  Delay_10us(void) {
	U8 i;
	i--;
	i--;
	i--;
	i--;
	i--;
	i--;
}
