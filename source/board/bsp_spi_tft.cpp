#include "hc32_ddl.h"
#include "bsp_spi_tft.h"
#include "bsp_logo_data.h"

void Show_logo_secreen()
{
	u32 i,j; 
  u8 p;
  uint8_t  R1,G1,B1;  

	LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);//设置显示范围
	for(i=0;i<76800;i++)
	{													   	 	

      p=_ac[i];
      R1=GUI_COLOR_Colors4[p]>>16;
      G1=(GUI_COLOR_Colors4[p]>>8)&0xff;
      B1=(GUI_COLOR_Colors4[p])&0xff;
    
      R1=R1>>3;
      G1=G1>>2;
      B1=B1>>3;
			LCD_WR_DATA((B1<<11)+ (G1<<5)+R1);
      p++;

	} 	
}
//***************临时测试需要，延时不准确的*******************************
void delay_ms(u16 count)
{
  u16 i;
  for(i=0;i<count;i++)
  {
  //  __NOP();
  }
}

static void Spi_DmaConfig(void)
{
//    stc_dma_config_t stcDmaCfg;

//    /* configuration structure initialization */
//    MEM_ZERO_STRUCT(stcDmaCfg);

//    /* Configuration peripheral clock */
//    PWC_Fcg0PeriphClockCmd(SPI_DMA_CLOCK_UNIT, Enable);
//    PWC_Fcg0PeriphClockCmd(PWC_FCG0_PERIPH_AOS, Enable);

//    /* Configure TX DMA */
//    stcDmaCfg.u16BlockSize = 1u;
//    stcDmaCfg.u16TransferCnt = u16BufferLen;
//    stcDmaCfg.u32SrcAddr = (uint32_t)(&u8TxBuffer[0]);
//    stcDmaCfg.u32DesAddr = (uint32_t)(&SPI_UNIT->DR);
//    stcDmaCfg.stcDmaChCfg.enSrcInc = AddressIncrease;
//    stcDmaCfg.stcDmaChCfg.enDesInc = AddressFix;
//    stcDmaCfg.stcDmaChCfg.enTrnWidth = Dma8Bit;
//    stcDmaCfg.stcDmaChCfg.enIntEn = Disable;
//    DMA_InitChannel(SPI_DMA_UNIT, SPI_DMA_TX_CHANNEL, &stcDmaCfg);

//    /* Configure RX DMA */
//    stcDmaCfg.u16BlockSize = 1u;
//    stcDmaCfg.u16TransferCnt = u16BufferLen;
//    stcDmaCfg.u32SrcAddr = (uint32_t)(&SPI_UNIT->DR);
//    stcDmaCfg.u32DesAddr = (uint32_t)(&u8RxBuffer[0]);
//    stcDmaCfg.stcDmaChCfg.enSrcInc = AddressFix;
//    stcDmaCfg.stcDmaChCfg.enDesInc = AddressIncrease;
//    stcDmaCfg.stcDmaChCfg.enTrnWidth = Dma8Bit;
//    stcDmaCfg.stcDmaChCfg.enIntEn = Disable;
//    DMA_InitChannel(SPI_DMA_UNIT, SPI_DMA_RX_CHANNEL, &stcDmaCfg);

//    DMA_SetTriggerSrc(SPI_DMA_UNIT, SPI_DMA_TX_CHANNEL, SPI_DMA_TX_TRIG_SOURCE);
//    DMA_SetTriggerSrc(SPI_DMA_UNIT, SPI_DMA_RX_CHANNEL, SPI_DMA_RX_TRIG_SOURCE);

//    /* Enable DMA. */
//    DMA_Cmd(SPI_DMA_UNIT, Enable);
}
void LCD_GPIO_Init(void)
{
   uint8_t index;
  stc_spi_init_t stcSpiInit;
  stc_port_init_t stcPortInit;
    MEM_ZERO_STRUCT(stcPortInit);
  
  #ifndef moni_spi
  
  
  
  
  
  
     tft_RS_L(); 
     PORT_SetFunc(tft_RS_PORT, tft_RS_PIN, Func_Gpio, Disable);
    stcPortInit.enPinMode = Pin_Mode_Out;
    PORT_Init(tft_RS_PORT, tft_RS_PIN, &stcPortInit);
    tft_RS_H();
  
//      stcPortInit.enPinMode = Pin_Mode_In;
//    PORT_Init(tft_RES_PORT, tft_RES_PIN, &stcPortInit);
//    tft_RES_L() ;
//    for(index=0;index<50;index++)
//              {
//               delay_ms(50000);
//              }
//     tft_RES_H();
//    for(index=0;index<200;index++)
//              {
//               delay_ms(50000);
//              }
//    tft_RES_L() ;
//    for(index=0;index<50;index++)
//              {
//               delay_ms(50000);
//              }
//     tft_RES_H();
//    for(index=0;index<200;index++)
//              {
//               delay_ms(50000);
//              }   



  
    PORT_Init(BL_port, BL_pin, &stcPortInit);
    //BL_ON;
    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcSpiInit);

    /* Configuration peripheral clock */
    PWC_Fcg1PeriphClockCmd(SPI_UNIT_CLOCK, Enable);

    /* Configuration SPI pin */
    PORT_SetFunc(SPI_SCK_PORT, SPI_SCK_PIN, SPI_SCK_FUNC, Disable);
    PORT_SetFunc(tft_CS_PORT, tft_CS_PIN, Func_Spi2_Nss0, Disable);
    PORT_SetFunc(SPI_MOSI_PORT, SPI_MOSI_PIN, SPI_MOSI_FUNC, Disable);
 //   PORT_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, SPI_MISO_FUNC, Disable);

    /* Configuration SPI structure */
    stcSpiInit.enClkDiv = SpiClkDiv2;
    stcSpiInit.enFrameNumber = SpiFrameNumber1;
    stcSpiInit.enDataLength = SpiDataLengthBit8;
    stcSpiInit.enFirstBitPosition = SpiFirstBitPositionMSB;
    stcSpiInit.enSckPolarity = SpiSckIdleLevelLow;
    stcSpiInit.enSckPhase = SpiSckOddSampleEvenChange;
    stcSpiInit.enReadBufferObject = SpiReadReceiverBuffer;
    stcSpiInit.enWorkMode = SpiWorkMode4Line;
    stcSpiInit.enTransMode = SpiTransFullDuplex;
    stcSpiInit.enCommAutoSuspendEn = Disable;
    stcSpiInit.enModeFaultErrorDetectEn = Disable;
    stcSpiInit.enParitySelfDetectEn = Disable;
    stcSpiInit.enParityEn = Disable;
    stcSpiInit.enParity = SpiParityEven;


    stcSpiInit.enMasterSlaveMode = SpiModeMaster;
    stcSpiInit.stcDelayConfig.enSsSetupDelayOption = SpiSsSetupDelayCustomValue;
    stcSpiInit.stcDelayConfig.enSsSetupDelayTime = SpiSsSetupDelaySck1;
    stcSpiInit.stcDelayConfig.enSsHoldDelayOption = SpiSsHoldDelayCustomValue;
    stcSpiInit.stcDelayConfig.enSsHoldDelayTime = SpiSsHoldDelaySck1;
    stcSpiInit.stcDelayConfig.enSsIntervalTimeOption = SpiSsIntervalCustomValue;
    stcSpiInit.stcDelayConfig.enSsIntervalTime = SpiSsIntervalSck6PlusPck2;
    stcSpiInit.stcSsConfig.enSsValidBit = SpiSsValidChannel0;
    stcSpiInit.stcSsConfig.enSs0Polarity = SpiSsLowValid;


#ifdef SPI_SLAVE_MODE
    stcSpiInit.enMasterSlaveMode = SpiModeSlave;
    stcSpiInit.stcSsConfig.enSsValidBit = SpiSsValidChannel0;
    stcSpiInit.stcSsConfig.enSs0Polarity = SpiSsLowValid;
#endif

    SPI_Init(SPI_UNIT, &stcSpiInit);
    SPI_Cmd(SPI_UNIT, Enable);
    
   #else
    PORT_SetFunc(tft_CS_PORT, tft_CS_PIN, Func_Gpio, Disable);
  
    stcPortInit.enPinMode = Pin_Mode_Out;
    PORT_Init(tft_CS_PORT, tft_CS_PIN, &stcPortInit);
    tft_CS_H();
       PORT_Init(BL_port, BL_pin, &stcPortInit);
    //BL_ON;
    PORT_SetFunc(tft_RS_PORT, tft_RS_PIN, Func_Gpio, Disable);
    stcPortInit.enPinMode = Pin_Mode_Out;
    PORT_Init(tft_RS_PORT, tft_RS_PIN, &stcPortInit);
    
    
     PORT_Init(SPI_SCK_PORT, SPI_SCK_PIN, &stcPortInit);
     tft_SCK_H();
     PORT_Init(SPI_MOSI_PORT, SPI_MOSI_PIN, &stcPortInit);
    #endif
}


/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	


  #ifndef moni_spi
      //SPI_ReceiveData8(SPI_UNIT);   //读上次的数据
      //SPI_UNIT->DR;
	  //SPI_UNIT->DR = dat;
      SPI_SendData8(SPI_UNIT, dat);
            /* Wait rx buffer full */
      while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSendBufferEmpty))
	  {
	  	
	  }
            
            
      
  #else
  char i;
 	tft_CS_L();
	//LCD_GPIO_PORRC |= SCLK;
  	for(i=0;i<8;i++)
	{		
     delay_ms(1);	  
	 tft_SCK_L();
	 //LCD_GPIO_PORRC |= SCLK;
		if(dat&0x80)
		{
		   tft_MOSI_H();
		   //LCD_GPIO_POSRC |= MOSI;
		}
		else
		{
		   tft_MOSI_L();
		   //LCD_GPIO_PORRC |= MOSI
		}
		tft_SCK_H();
		//LCD_GPIO_POSRC |= SCLK;
		dat<<=1;
	}	
  tft_CS_H();
	//LCD_GPIO_POSRC |= SCLK;
  #endif

}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{

	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	tft_RS_L();//写命令

	LCD_Writ_Bus(dat);
  	delay_ms(1);
	tft_RS_H();//写数据

}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
}

void LCD_Init(void)
{
 
	LCD_GPIO_Init();//初始化GPIO


	
//	LCD_BLK_Set();//打开背光
//  delay_ms(100);
//	
//	//************* Start Initial Sequence **********//
//	LCD_WR_REG(0x11); //Sleep out 
//	delay_ms(120);    //Delay 120ms 
//	//************* Start Initial Sequence **********// 
//	LCD_WR_REG(0Xf0);
//	LCD_WR_DATA8(0xc3);
//	LCD_WR_REG(0Xf0);
//	LCD_WR_DATA8(0x96);
//	LCD_WR_REG(0x36);    // Memory Access Control 
//	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x40);
//	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0x80);
//	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0xB0);
//	else LCD_WR_DATA8(0xE0);
//	
//	LCD_WR_REG(0x3A);
//	LCD_WR_DATA8(0x55);
//	
//	LCD_WR_REG(0Xe8);
//	LCD_WR_DATA8(0x40);
//	LCD_WR_DATA8(0x82);
//	LCD_WR_DATA8(0x07);
//	LCD_WR_DATA8(0x18);
//	LCD_WR_DATA8(0x27);
//	LCD_WR_DATA8(0x0a);
//	LCD_WR_DATA8(0xb6);
//	LCD_WR_DATA8(0x33);
//	
//	LCD_WR_REG(0Xc5);
//	LCD_WR_DATA8(0x27);
//	
//	LCD_WR_REG(0Xc2);
//	LCD_WR_DATA8(0xa7);
//	
//	LCD_WR_REG(0Xe0);
//	LCD_WR_DATA8(0xf0);
//	LCD_WR_DATA8(0x01);
//	LCD_WR_DATA8(0x06);
//	LCD_WR_DATA8(0x0f);
//	LCD_WR_DATA8(0x12);
//	LCD_WR_DATA8(0x1d);
//	LCD_WR_DATA8(0x36);
//	LCD_WR_DATA8(0x54);
//	LCD_WR_DATA8(0x44);
//	LCD_WR_DATA8(0x0c);
//	LCD_WR_DATA8(0x18);
//	LCD_WR_DATA8(0x16);
//	LCD_WR_DATA8(0x13);
//	LCD_WR_DATA8(0x15);
//	
//	LCD_WR_REG(0Xe1);
//	LCD_WR_DATA8(0xf0);
//	LCD_WR_DATA8(0x01);
//	LCD_WR_DATA8(0x05);
//	LCD_WR_DATA8(0x0a);
//	LCD_WR_DATA8(0x0b);
//	LCD_WR_DATA8(0x07);
//	LCD_WR_DATA8(0x32);
//	LCD_WR_DATA8(0x44);
//	LCD_WR_DATA8(0x44);
//	LCD_WR_DATA8(0x0c);
//	LCD_WR_DATA8(0x18);
//	LCD_WR_DATA8(0x17);
//	LCD_WR_DATA8(0x13);
//	LCD_WR_DATA8(0x16);
//	
//	LCD_WR_REG(0Xf0);
//	LCD_WR_DATA8(0x3c);
//	
//	LCD_WR_REG(0Xf0);
//	LCD_WR_DATA8(0x69);
//	
//	LCD_WR_REG(0X29);	 

//LCD_WR_REG(0x11);
//delay_ms(20000);	
//LCD_WR_REG(0x21);
//LCD_WR_REG(0x29); 	
//delay_ms(10000);
//	
//LCD_WR_REG(0x3A);
//LCD_WR_DATA8(0x55);//55是565，也就是16位；66是666，也就是18位，77则是888，即24位(注意：需要能支持24位的液晶屏才可设置77)
//LCD_WR_REG(0x36);
//LCD_WR_DATA8(0xE8);// D3位取反，RGB中RB交换；D5位取反，是切换横竖屏；D6，D7位是x与y轴的镜像

//***********************************************
//-----------------------------------ST7789V reset sequence------------------------------------//
//LCD_RESET=1;
//Delayms(1); //Delay 1ms
//LCD_RESET=0;
//Delayms(10); //Delay 10ms
//LCD_RESET=1;
//Delayms(120);  //Delay 120ms
//---------------------------------------------------------------------------------------------------//
      LCD_WR_REG( 0x11);
      Ddl_Delay1ms(120);
              //------------------------------display and color format setting--------------------------------//
      LCD_WR_REG( 0x36);    //dir
      LCD_WR_DATA8(0xb0);


      LCD_WR_REG( 0x3a);
      LCD_WR_DATA8( 0x5);
              //--------------------------------ST7789V Frame rate setting----------------------------------//
      LCD_WR_REG( 0xb2);
//      LCD_WR_DATA8( 0x0c);
//      LCD_WR_DATA8( 0x0c);
      LCD_WR_DATA8( 0x05);
      LCD_WR_DATA8( 0x05);
      LCD_WR_DATA8( 0x00);
      LCD_WR_DATA8( 0x33);
      LCD_WR_DATA8( 0x33);
			
      LCD_WR_REG( 0xb7);
      LCD_WR_DATA8( 0x35);
    
                //---------------------------------ST7789V Power setting--------------------------------------//
      LCD_WR_REG( 0xbb);
      LCD_WR_DATA8( 0x28);
			
      LCD_WR_REG( 0xc0);
      LCD_WR_DATA8( 0x2c);
			
      LCD_WR_REG( 0xc2);
      LCD_WR_DATA8( 0x01);
			
      LCD_WR_REG( 0xc3);
      LCD_WR_DATA8( 0x0b);
			
      LCD_WR_REG( 0xc4);
      LCD_WR_DATA8( 0x20);
			
      LCD_WR_REG( 0xc6);
      LCD_WR_DATA8( 0x0f);
			
      LCD_WR_REG( 0xd0);
      LCD_WR_DATA8( 0xa4);
      LCD_WR_DATA8( 0xa1);
         //--------------------------------ST7789V gamma setting---------------------------------------//
      LCD_WR_REG( 0xe0);
      LCD_WR_DATA8( 0xd0);
      LCD_WR_DATA8( 0x01);
      LCD_WR_DATA8( 0x08);
      LCD_WR_DATA8( 0x0f);
      LCD_WR_DATA8( 0x11);
      LCD_WR_DATA8( 0x2a);
      LCD_WR_DATA8( 0x36);
      LCD_WR_DATA8( 0x55);
      LCD_WR_DATA8( 0x44);
      LCD_WR_DATA8( 0x3a);
      LCD_WR_DATA8( 0x0b);
      LCD_WR_DATA8( 0x06);
      LCD_WR_DATA8( 0x11);
      LCD_WR_DATA8( 0x20);
			
      LCD_WR_REG( 0xe1);
      LCD_WR_DATA8( 0xd0);
      LCD_WR_DATA8( 0x02);
      LCD_WR_DATA8( 0x07);
      LCD_WR_DATA8( 0x0a);
      LCD_WR_DATA8( 0x0b);
      LCD_WR_DATA8( 0x18);
      LCD_WR_DATA8( 0x34);
      LCD_WR_DATA8( 0x43);
      LCD_WR_DATA8( 0x4a);
      LCD_WR_DATA8( 0x2b);
      LCD_WR_DATA8( 0x1b);
      LCD_WR_DATA8( 0x1c);
      LCD_WR_DATA8( 0x22);
      LCD_WR_DATA8( 0x1f);
      LCD_WR_REG( 0x29);   //
	  //LCD_Fill(0,320,0,240,0x0000);
	  //SysTick_Delay(120);
      
} 




/////////////*/*******************************************************************/



/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA(color);
		}
	} 					  	    
}

/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_Address_Set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(color);
} 


/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   矩形的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
                color   圆的颜色
      返回值：  无
******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}

/******************************************************************************
      函数说明：显示汉字串
      入口数据：x,y显示坐标
                *s 要显示的汉字串
                fc 字的颜色
                bc 字的背景色
                sizey 字号 可选 16 24 32
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
//	while(*s!=0)
//	{
//		if(sizey==12) LCD_ShowChinese12x12(x,y,s,fc,bc,sizey,mode);
//		else if(sizey==16) LCD_ShowChinese16x16(x,y,s,fc,bc,sizey,mode);
//		else if(sizey==24) LCD_ShowChinese24x24(x,y,s,fc,bc,sizey,mode);
//		else if(sizey==32) LCD_ShowChinese32x32(x,y,s,fc,bc,sizey,mode);
//		else return;
//		s+=2;
//		x+=sizey;
//	}
}

/******************************************************************************
      函数说明：显示单个12x12汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese12x12(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
//	u8 i,j,m=0;
//	u16 k;
//	u16 HZnum;//汉字数目
//	u16 TypefaceNum;//一个字符所占字节大小
//	u16 x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	                         
//	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont12[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
//						else LCD_WR_DATA(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont12[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
} 

/******************************************************************************
      函数说明：显示单个16x16汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
//	u8 i,j,m=0;
//	u16 k;
//	u16 HZnum;//汉字数目
//	u16 TypefaceNum;//一个字符所占字节大小
//	u16 x0=x;
//  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont16[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
//						else LCD_WR_DATA(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont16[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
} 


/******************************************************************************
      函数说明：显示单个24x24汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
//	u8 i,j,m=0;
//	u16 k;
//	u16 HZnum;//汉字数目
//	u16 TypefaceNum;//一个字符所占字节大小
//	u16 x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont24[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
//						else LCD_WR_DATA(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont24[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
} 

/******************************************************************************
      函数说明：显示单个32x32汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese32x32(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode)
{
//	u8 i,j,m=0;
//	u16 k;
//	u16 HZnum;//汉字数目
//	u16 TypefaceNum;//一个字符所占字节大小
//	u16 x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont32[k].Msk[i]&(0x01<<j))LCD_WR_DATA(fc);
//						else LCD_WR_DATA(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont32[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
}


/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode)
{
//	u8 temp,sizex,t,m=0;
//	u16 i,TypefaceNum;//一个字符所占字节大小
//	u16 x0=x;
//	sizex=sizey/2;
//	TypefaceNum=16;
//	num=num-'0';    //得到偏移后的值
//	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
//	for(i=0;i<TypefaceNum;i++)
//	{ 
//		 if(sizey==16)temp=code0[num][i];		 //调用8x16字体
//      
//		for(t=0;t<8;t++)
//		{
//			if(!mode)//非叠加模式
//			{
//				if(temp&(0x01<<t))LCD_WR_DATA(fc);
//				else LCD_WR_DATA(bc);
//				m++;
//				if(m%sizex==0)
//				{
//					m=0;
//					break;
//				}
//			}
//			else//叠加模式
//			{
//				if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//画一个点
//				x++;
//				if((x-x0)==sizex)
//				{
//					x=x0;
//					y++;
//					break;
//				}
//			}
//		}
//	}   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 sizey,u8 mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp;
	u8 enshow=0;
	u8 sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,'0',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey)
{         	
	u8 t,temp,sizex;
	u16 num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}


/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组    
      返回值：  无
******************************************************************************/
void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[])
{
	u16 i,j;
	u32 k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			k++;
		}
	}			
}





