//Ҫ�㣺
//1.IO����Ҫ��ȷ
//2.checksum����ʱ,ע��unit 8�Ķ���,��8λ ,checksum & 0x00ff  �����㣬ȡ��8λ��
//3.����ʱ�����,1G���ϵ����ܻ�ϵͳ,Ҫ��remote_IC_driver_MBIO_V1.9.c�е�V1.9���ϵİ汾
//4.Ӳ���Ӻ�
//5.��ѹ����:2.4-3.6V,200mA����


//readdata |= GetDINStatus();  //wjs;��ѧϰ������ʱ���������ԣ�readdata |= GetDINStatus()?0x01:0x00;

#define I2CERR_NO_ERROR	0
#define  DELAY_TIME  550	//H: 25uS-35uS
#define  DELAY_ST  19	//18mS-25mS

#ifndef UINT8
typedef unsigned char UINT8;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

//���������ɣ�===================================================================================================

/*******************************************
	SDA_PIN 
*******************************************/
void Set_SDA_IO(void)
{
    /* Set this port to IO port of SDA */
	GPIO_ModeSetup(REMOTE_DIN_PIN, 0x00);	//������SDAͨѶ�Ĺܽ�Ϊ�ɣ�ģʽ������AD���жϵ�����ģʽ
}

void SetSDAInput(void)
{
    /* It set SDA port as an input */	
	GPIO_InitIO(0,REMOTE_DIN_PIN);			///������SDAͨѶ�Ĺܽ�Ϊ����ģʽ���ر�����
}

void SetSDAOutput(void)
{
    /* It set SDA port as an output */	
	GPIO_InitIO(1,REMOTE_DIN_PIN);			//������SDAͨѶ�Ĺܽ�Ϊ���ģʽ
}

void SetSDAHigh(void)
{
    /* It output a High level to SDA here. */	
	GPIO_WriteIO(1,REMOTE_DIN_PIN);		//������SDAͨѶ�Ĺܽ�Ϊ���1���ߵ�ƽ
}

void SetSDALow(void)
{
    /* It output a Low level to SDA here. */	
	GPIO_WriteIO(0,REMOTE_DIN_PIN);		//������SDAͨѶ�Ĺܽ�Ϊ���0���͵�ƽ
}

UINT8 GetACKStatus(void)
{
	return GPIO_ReadIO(REMOTE_DIN_PIN);      ///���ӣģ���״̬
}

UINT8 GetDINStatus(void)
{
	return GPIO_ReadIO(REMOTE_DIN_PIN);		//���ӣģ���״̬
}

/*******************************************
	SCK_PIN  ͬ�ϣ��ο�SDA
*******************************************/
void Set_SCL_IO(void)
{
	/* Set this port to IO port of SCL */
	GPIO_ModeSetup(REMOTE_CLK_PIN, 0x00);	
}

void SetSCLOutput(void)
{
    /* It set SCL port as an output */
	GPIO_InitIO(1,REMOTE_CLK_PIN); 	
}

void SetSCLInput(void)
{
    /* It set SCL port as an Input */
	GPIO_InitIO(0,REMOTE_CLK_PIN); 	
}


void SetSCLHigh(void)
{
    /* It output a High level to SCL here. */	
	GPIO_WriteIO(1,REMOTE_CLK_PIN);
}

void SetSCLLow(void)
{
    /* It output a Low level to SCL here. */	
	GPIO_WriteIO(0,REMOTE_CLK_PIN);
}




/*******************************************
	BUSY_PIN  =============ͬ�ϣ��ο�SDA
*******************************************/
void Set_BUSY_IO(void)
{
	/* Set this port to IO port of BUSY */
	GPIO_ModeSetup(REMOTE_BUSY_PIN, 0x00);
}

void SetBUSYInput(void)
{
	 /* It set BUSY port as an input */	
	GPIO_InitIO(0,REMOTE_BUSY_PIN);
}

void SetBUSYOutput(void)
{
	 /* It set BUSY port as an output */	
	GPIO_InitIO(1,REMOTE_BUSY_PIN);
}

void SetBUSYHigh(void)
{

    /* It output a High level to BUSY here. */
	GPIO_WriteIO(1,REMOTE_BUSY_PIN);
	
}

void SetBUSYLow(void)
{
    /* It output a Low level to BUSY here. */	
	GPIO_WriteIO(0,REMOTE_BUSY_PIN);
}

UINT8 GetBUSYStatus(void)
{
	return GPIO_ReadIO(REMOTE_BUSY_PIN);
}



//=====================================================�ϵ��ʼ���������أɣ����ú���
void remote_poweron_init(void)			////??????
{

	Set_SDA_IO();
	SetSDAHigh();
	SetSDAOutput();

	Set_SCL_IO();
	SetSCLHigh();
	SetSCLOutput();


	Set_BUSY_IO();
	SetBUSYInput();				

}






void DelayTime( UINT16 lTime )
{
	UINT16 i;

	for(i=0;i<lTime;i++)
	{
		;
	}
}

void RemoteDelayms(UINT16 data)
{
	UINT16 i;
	while(data--)
	{
		for(i=0;i<5000;i++){}// 1msÿ��ѭ��5000 �� 	
	}
}
//===========

UINT8 GetACKSign(void) 
{
	UINT8 ACKSign;
	UINT16 dataRead=0;

	SetSDAInput();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	SetSCLHigh();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	ACKSign = GetDINStatus();			//???????

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	SetSCLLow();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	return ACKSign;

}

void SendACKSign(void)
{
	SetSDAOutput();
	DelayTime(DELAY_TIME);
	SetSDALow();					///wjs;��ӵ�SDA_Low,û����֤��
	DelayTime(DELAY_TIME);

	SetSCLHigh();					//��9�ε�CLK�ĸ�
	DelayTime(DELAY_TIME);			//;1mS
	
	SetSCLLow(); 
							//1mS
}

UINT16 I2COpen(void)
{	
	Set_SDA_IO(); 
	Set_SCL_IO(); 

	SetSDAOutput(); 
	SetSCLOutput(); 

	SetSCLHigh();  
	SetSDAHigh();

	return I2CERR_NO_ERROR; 
}

UINT16 I2CClose(void)   
{
	SetSDAOutput(); 
	SetSCLOutput(); 

	SetSCLHigh();
	SetSDAHigh();

	return I2CERR_NO_ERROR; 
}

UINT16 I2CStart(void) 
{
	int i;
	UINT8 Data_Bit,ACKSign,TmpDat;
	Data_Bit = 8;

	SetSDAOutput();
	SetSCLOutput();
	SetSCLHigh();
	SetSDAHigh();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	SetSDALow();
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	SetSCLLow();  
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);

	return 1;

}


UINT16 I2CStop(void)
{
	SetSDAOutput();
	SetSCLOutput();
	SetSCLLow();
	SetSDALow();
	DelayTime(DELAY_TIME);

	SetSCLHigh();
	DelayTime(DELAY_TIME);

	SetSDAHigh();
	DelayTime(DELAY_TIME);  

	return I2CERR_NO_ERROR; 
}


UINT16 I2CWriteData( char bData )
{
	UINT8 Data_Bit,ACKSign,TmpDat;
	int 8 i;	//kal_int8 i;

	SetSDAOutput();
	SetSCLLow();
	DelayTime(DELAY_TIME);
    
	for(i=7;i>=0;i--)
	{
		DelayTime(DELAY_TIME);
		
		Data_Bit=(bData>>i)& 0x01;

		if(Data_Bit)
		SetSDAHigh();
		else
		SetSDALow();

		DelayTime(DELAY_TIME);
		SetSCLHigh();
		DelayTime(DELAY_TIME);
		SetSCLLow();		
	}
	
	ACKSign=GetACKSign();

	return ACKSign;
}

///urc_send
void writeI2C(char* data, UINT8 count)		//wjs;ͨ��д��
{
	UINT8 i;
	UINT8 j = 0;
	char iBuffer;

	I2COpen();
	DelayTime(DELAY_TIME);

	SetSCLLow();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	SetSCLHigh();
	
	RemoteDelayms(DELAY_ST); //20ms	//14

	I2CStart();
	DelayTime(DELAY_TIME);
	
	
	for(i = 0; i < count; i++)	//count=7,��ֵ
	{
		iBuffer = data[i];
		I2CWriteData(iBuffer);
		DelayTime(DELAY_TIME);
	}


	DelayTime(DELAY_TIME);

	I2CStop();
	DelayTime(DELAY_TIME);

	I2CClose();
	DelayTime(DELAY_TIME);

}
///================================================wjs;

//wjs;==============================================================
void Learn_start2(void)
{
		
	I2COpen();
	DelayTime(DELAY_TIME);

	SetSCLLow();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	SetSCLHigh();
	
	RemoteDelayms(DELAY_ST); //20ms	//14

	I2CStart();
	DelayTime(DELAY_TIME);
	
	I2CWriteData(0x30);
	DelayTime(DELAY_TIME);

	I2CWriteData(0x20);
	DelayTime(DELAY_TIME);
	
	I2CWriteData(0x50);
	DelayTime(DELAY_TIME);

	DelayTime(DELAY_TIME);	

	I2CStop();
	DelayTime(DELAY_TIME);

	I2CClose();
	DelayTime(DELAY_TIME);

}

//==================================

UINT16 I2CReadData(UINT8* pbData)
{
	UINT8 Data_Bit,ACKSign;
	UINT8 readdata = 0;
	UINT8 i=8;

	SetSDAInput(); 
	while (i--)
	{
		readdata<<=1;

		SetSCLHigh(); 
		DelayTime(DELAY_TIME);

		readdata |= GetDINStatus();  //������ʱ���������ԣ�readdata |= GetDINStatus()?0x01:0x00;

		SetSCLLow();
		DelayTime(DELAY_TIME);
		DelayTime(DELAY_TIME);		//wjs;��delay
	}
	SetSCLLow(); 
	DelayTime(DELAY_TIME);

	*pbData = readdata;

	SendACKSign();
	
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);		//wjs;1G���ϵ�ϵͳҪ��,test
	

	return I2CERR_NO_ERROR;
}


//=============================
//===================
kal_uint8 readI2C2(char* readtempbuf)     //UINT8
{
	UINT8 bValue;
	UINT8 i=0;
	UINT8 checksum;

	I2COpen();
	DelayTime(DELAY_TIME);

	SetSCLLow();
	DelayTime(DELAY_TIME);
	DelayTime(DELAY_TIME);
	SetSCLHigh();
	RemoteDelayms(DELAY_ST); //20ms	

	I2CStart();
	DelayTime(DELAY_TIME);

	//----------------------------------------
	//write
	I2CWriteData(0x30);
	DelayTime(DELAY_TIME);
	//address point
	I2CWriteData(0x62);
	DelayTime(DELAY_TIME);

	//---------------------------------------
	//read
	I2CStart();
	DelayTime(DELAY_TIME);

	I2CWriteData(0x31);
	DelayTime(DELAY_TIME);

	I2CReadData(&bValue);			//wjs;read:FCS(1B)
	DelayTime(DELAY_TIME);			//wjs;1G���ϵ�ϵͳҪ��	
	
	if(bValue != 0x00)
	{
		I2CStop();
		DelayTime(DELAY_TIME);
		I2CClose();
		DelayTime(DELAY_TIME);
	//	kal_prompt_trace(MOD_TST, "remote_study_type_error");
		return 0;
	}

	i = 0;
	readtempbuf[i] = bValue;
//	kal_prompt_trace(MOD_TST, "remote_I2C_data[%d] = %d",i,readtempbuf[i]);
	checksum = 0xc3;

	for(i = 1; i < 230; i++)			//wjs;read:learndata(109B)+120=230
	{
		I2CReadData(&bValue);
		DelayTime(DELAY_TIME);
		readtempbuf[i] = bValue;
	//	kal_prompt_trace(MOD_TST, "remote_I2C_data[%d] = %d",i,readtempbuf[i]);
		checksum += bValue;
	}
	
	I2CReadData(&bValue);		//wjs;read:CK(1B)	?????
	DelayTime(DELAY_TIME);
	//	kal_prompt_trace(MOD_MMI, "remote_read_checksum = %d",bValue);
	//	kal_prompt_trace(MOD_MMI, "remote_count_checksum = %d",checksum);

	I2CStop();
	DelayTime(DELAY_TIME);
	I2CClose();
	DelayTime(DELAY_TIME);
//��ʱ��У
//	if(bValue != checksum)
//	{
//	//	kal_prompt_trace(MOD_MMI, "remote_study_checksum_error");
//	return 0;lg,
//	}
//	else
//	{
//	//	kal_prompt_trace(MOD_MMI, "remote_study_checksum_ok");
//		return 1;
//	}

}


#endif


