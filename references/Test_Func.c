#include "bk2425.h"
////////////////////////////////////////////////////////////////////
//This function is only used for Carrier Tx output power and RX BER test!!!!!!!!!!
////////////////////////////////////////////////////////////////////

extern code UINT8 RX0_Address[];
extern code unsigned long Bank1_Reg0_13[];


/**************************************************         
Function: SPI_Bank1_Write_Reg();                                  
                                                            
Description:                                                
	write a Bank1 register
/**************************************************/        
void SPI_Bank1_Write_Reg(UINT8 reg, UINT8 *pBuf)    
{
	SwitchCFG(1);
	SPI_Write_Buf(reg,pBuf,4);
	SwitchCFG(0);
}

/**************************************************         
Function: SPI_Bank1_Read_Reg();                                  
                                                            
Description:                                                
	read a Bank1 register
/**************************************************/ 
void SPI_Bank1_Read_Reg(UINT8 reg, UINT8 *pBuf)
{
	SwitchCFG(1);
	SPI_Read_Buf(reg,pBuf,4);
	SwitchCFG(0);
}


/**************************************************
Function: CarrierTest();
                                                            
Description:
    carrier wave output power

Parameter:
    b_enable    1:start 
	            0:stop
Return:
     None
/**************************************************/
void Carrier_Test(UINT8 b_enable)
{
	UINT8 j;
	UINT8 WriteArr[4];

	SwitchToTxMode();

	for(j=0;j<4;j++)
		WriteArr[j]=(Bank1_Reg0_13[0]>>(8*(j) ) )&0xff;

	if(b_enable)
	{
		if(WriteArr[3]&0x02 ) //bit 1
		{
			WriteArr[3]=WriteArr[3]&0xfd;
		}
		else
		{
			WriteArr[3]=WriteArr[3]|0x02;
		}

		if(WriteArr[3]&0x08 ) //bit 3
		{
			WriteArr[3]=WriteArr[3]&0xf7;
		}
		else
		{
			WriteArr[3]=WriteArr[3]|0x08;
		}

		if(WriteArr[3]&0x20 ) //bit 5
		{
			WriteArr[3]=WriteArr[3]&0xdf;
		}
		else
		{
			WriteArr[3]=WriteArr[3]|0x20;
		}

	}

//write REG4
	SPI_Bank1_Write_Reg((WRITE_REG|4),WriteArr);

}

/**************************************************
Function: BER_Test();
                                                            
Description:
    bit error rate test

In Parameter:
	ms: the millisecond for hardware bits receive

Out Parameter:
	received_total_bits:received total bits
	received_error_bits:received error bits

Return:
     None
/**************************************************/
void BER_Test(UINT16 ms,UINT32* received_total_bits,UINT32* received_error_bits)
{
	UINT8 WriteArr[5];

////////////////////////////////////////////////////////
//change pipe0 address
////////////////////////////////////////////////////////
	WriteArr[4]=0x02;
	WriteArr[3]=0x95;
	WriteArr[2]=0xe5;
	WriteArr[1]=0xdc;
	WriteArr[0]=0x0e;

	SPI_Write_Buf((WRITE_REG|10),WriteArr,5);//change RX0 address for BER test

	SwitchToRxMode();

////////////////////////////////////////////////////////
//start BER receive,set REG12<5>=1 start
////////////////////////////////////////////////////////
	SPI_Bank1_Read_Reg(12,&(WriteArr[0]));
	WriteArr[0]=WriteArr[0]|0x20;
	SPI_Bank1_Write_Reg((WRITE_REG|12),&(WriteArr[0]));

	DelayMs(ms);//delay ms for hardware receive

////////////////////////////////////////////////////////
//Hold BER value for read,set REG12<6>=1, 
////////////////////////////////////////////////////////
	SPI_Bank1_Read_Reg(12,&(WriteArr[0]));
	WriteArr[0]=WriteArr[0]|0x40;
	SPI_Bank1_Write_Reg((WRITE_REG|12),&(WriteArr[0]));

//read BER
	SPI_Bank1_Read_Reg(0,&(WriteArr[0]));//read REG0
	
	(*received_total_bits)=WriteArr[3];
	(*received_total_bits)=	(*received_total_bits)<<8;
	(*received_total_bits)|=WriteArr[2];
	(*received_total_bits)=	(*received_total_bits)<<8;
	(*received_total_bits)|=WriteArr[1];
	(*received_total_bits)=	(*received_total_bits)<<8;
	(*received_total_bits)|=WriteArr[0];

	SPI_Bank1_Read_Reg(1,&(WriteArr[0]));//read REG1
	(*received_error_bits)=WriteArr[3];
	(*received_error_bits)=	(*received_error_bits)<<8;
	(*received_error_bits)|=WriteArr[2];
	(*received_error_bits)=	(*received_error_bits)<<8;
	(*received_error_bits)|=WriteArr[1];
	(*received_error_bits)=	(*received_error_bits)<<8;
	(*received_error_bits)|=WriteArr[0];

////////////////////////////////////////////////////////
//stop BER receive,,clear REG12<5>=0 stop
////////////////////////////////////////////////////////
	SPI_Bank1_Read_Reg(12,&(WriteArr[0]));
	WriteArr[0]=WriteArr[0]&0xdf;
	SPI_Bank1_Write_Reg((WRITE_REG|12),&(WriteArr[0]));

////////////////////////////////////////////////////////
//not Hold BER value,set REG12<6>=0
////////////////////////////////////////////////////////
	SPI_Bank1_Read_Reg(12,&(WriteArr[0]));
	WriteArr[0]=WriteArr[0]&0xbf;
	SPI_Bank1_Write_Reg((WRITE_REG|12),&(WriteArr[0]));

//restore RX0 address
	SPI_Write_Buf((WRITE_REG|10),RX0_Address,5);//restore RX0 address

}


/**************************************************
Function: Set_LowPower_Mode();

Description:
	set low power mode
/**************************************************/
void Set_LowPower_Mode()
{

	UINT8 j;
	UINT8 WriteArr[4];
	for(j=0;j<4;j++)
		WriteArr[j]=(Bank1_Reg0_13[0]>>(8*(j) ) )&0xff;

	WriteArr[1]=WriteArr[1]&0xef;  //REG4<20>

//write REG4
	SPI_Bank1_Write_Reg(WRITE_REG|0x04,WriteArr);
}

/**************************************************
Function: Set_Sen_Mode();

Description:
	set sensitivity mode
	
Parameter:
    b_enable    1:high sensitivity mode 
	            0:normal sensitivity mode
/**************************************************/
void Set_Sen_Mode(UINT8 b_enable)
{

	UINT8 j;
	UINT8 WriteArr[4];
	for(j=0;j<4;j++)
		WriteArr[j]=(Bank1_Reg0_13[0]>>(8*(j) ) )&0xff;

	if (b_enable)
		WriteArr[1]=WriteArr[1]|0x20;  //REG4<21>
	else
		WriteArr[1]=WriteArr[1]&0xdf;  //REG4<21>

//write REG4
	SPI_Bank1_Write_Reg(WRITE_REG|0x04,WriteArr);
}
/**************************************************
Function: Close_CD_Detect();

Description:
	if doesn't use CD function and want to save power,please close CD detect function,which could decrease electrical current 1mA
/**************************************************/
void Close_CD_Detect()
{
	UINT8 j;
	UINT8 WriteArr[4];

	for(j=0;j<4;j++)
		WriteArr[j]=(Bank1_Reg0_13[1]>>(8*(j) ) )&0xff;

	WriteArr[1]=WriteArr[1]|0x04; //REG5<18>

//write REG5
	SPI_Bank1_Write_Reg(WRITE_REG|0x05,WriteArr);
}

/**************************************************
Function: PN9_TX();

Description:
	send PN9
Parameter:
    b_enable    1:start 
	            0:stop
/**************************************************/
void PN9_TX(UINT8 b_enable)
{
	UINT8 j;
	UNIT8 WriteArr[4];
	
	if (b_enable)//start send PN9
	{
		WriteArr[0] = 0x0C;
		WriteArr[1] = 0x4B;	
		WriteArr[2] = 0x00;
		WriteArr[3] = 0x00;
		SPI_Bank1_Write_Reg(WRITE_REG|0x01,WriteArr); //write bank1_reg1
		
		WriteArr[0] = 0xA0;
		WriteArr[1] = 0xFC;	
		WriteArr[2] = 0x8C;
		WriteArr[3] = 0x02;
		SPI_Bank1_Write_Reg(WRITE_REG|0x02,WriteArr); //write bank1_reg2
		
		WriteArr[0] = 0x10;
		WriteArr[1] = 0x12;	
		WriteArr[2] = 0x73;
		WriteArr[3] = 0x00;
		SPI_Bank1_Write_Reg(WRITE_REG|0x0C,WriteArr); //write bank1_reg12
	}
	else//stop send PN9
	{
		WriteArr[0] = 0xC0;
		WriteArr[1] = 0x4B;	
		WriteArr[2] = 0x00;
		WriteArr[3] = 0x00;
		SPI_Bank1_Write_Reg(WRITE_REG|0x01,WriteArr); //write bank1_reg1
		
		WriteArr[0] = 0xD0;
		WriteArr[1] = 0xFC;	
		WriteArr[2] = 0x8C;
		WriteArr[3] = 0x02;
		SPI_Bank1_Write_Reg(WRITE_REG|0x02,WriteArr); //write bank1_reg2
		
		WriteArr[0] = 0x00;
		WriteArr[1] = 0x12;	
		WriteArr[2] = 0x73;
		WriteArr[3] = 0x00;
		SPI_Bank1_Write_Reg(WRITE_REG|0x0C,WriteArr); //write bank1_reg12		
	}
	
}


/**************************************************
Function: Get_Chip_ID();

Description:
	Get chip ID
/**************************************************/
UINT8 Get_Chip_ID()
{
	UINT8 ReadArr[4];
	SPI_Bank1_Read_Reg(0x08,ReadArr);
	return ReadArr[0];
}




