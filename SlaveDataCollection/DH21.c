#include <DH21.h>

//数据定义
U8  U8FLAG,k;
U8  U8count,U8temp;
U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8  U8comdata;
U8  outdata[6];  //定义发送的字节数	   
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
	   	//超时则跳出for循环		  
		if(U8FLAG==1)break;
	   	//判断数据位是0还是1	 
	   	   
		// 如果高电平高过预定0高电平值则数据位为 1 
		U8comdata<<=1;
		U8comdata|=U8temp;
	 }
}

void DH21_collData(void) {
	//主机拉低18ms 
	P2_0=0;
	Delay(180);
	P2_0=1;
	//总线由上拉电阻拉高 主机延时20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//主机设为输入 判断从机响应信号 
	P2_0=1;
	//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	if(!P2_0) {
		U8FLAG=2;
		//判断从机是否发出 80us 的低电平响应信号是否结束	 
		while((!P2_0)&&U8FLAG++);
		U8FLAG=2;
		//判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
		while((P2_0)&&U8FLAG++);
		//数据接收状态		 
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
		//数据校验 
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
