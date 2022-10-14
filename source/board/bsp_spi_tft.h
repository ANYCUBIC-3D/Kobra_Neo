 #ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "stdint.h"

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
//#define WHITE         	 0xFFFF
//#define BLACK         	 0x0000	  
//#define BLUE           	 0x001F  
//#define BRED             0XF81F
//#define GRED 			       0XFFE0
//#define GBLUE			       0X07FF
//#define RED           	 0xF800
//#define MAGENTA       	 0xF81F
//#define GREEN         	 0x07E0
//#define CYAN          	 0x7FFF
//#define YELLOW        	 0xFFE0
//#define BROWN 			     0XBC40 //棕色
//#define BRRED 			     0XFC07 //棕红色
//#define GRAY  			     0X8430 //灰色
//#define DARKBLUE      	 0X01CF	//深蓝色
//#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
//#define GRAYBLUE       	 0X5458 //灰蓝色
//#define LIGHTGREEN     	 0X841F //浅绿色
//#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
//#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
//#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

//#define moni_spi
#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 320
#define LCD_H 480

#else
#define LCD_W 320
#define LCD_H 240
#endif


//-----------------LCD端口定义---------------- 
#define LCD_GPIO_PORRC               ((M4_PORT_TypeDef *)M4_PORT + 0x2A)
#define LCD_GPIO_POSRC               ((M4_PORT_TypeDef *)M4_PORT + 0x28)


#define SCLK          			   Pin05
#define MOSI					   	Pin04

#define  BL_port                   PortC
#define  BL_pin                    Pin00

#define  BL_ON                    (PORT_SetBits(BL_port, BL_pin))   


#define tft_CS_PORT                     (PortB)
#define tft_CS_PIN                      (Pin01)
#define tft_CS_H()                      (PORT_SetBits(tft_CS_PORT, tft_CS_PIN))
#define tft_CS_L()                      (PORT_ResetBits(tft_CS_PORT, tft_CS_PIN))


/* Rs Port/Pin definition */
#define tft_RS_PORT                       (PortB)
#define tft_RS_PIN                        (Pin00)
#define tft_RS_H()                        (PORT_SetBits(tft_RS_PORT, tft_RS_PIN))
#define tft_RS_L()                        (PORT_ResetBits(tft_RS_PORT, tft_RS_PIN))

/* Rs Port/Pin definition */
#define tft_RES_PORT                       (PortB)
#define tft_RES_PIN                        (Pin04)
#define tft_RES_H()                       (PORT_SetBits(tft_RS_PORT, tft_RES_PIN))
#define tft_RES_L()                       (PORT_ResetBits(tft_RS_PORT, tft_RES_PIN))

/* SPI_SCK Port/Pin definition */
#define SPI_SCK_PORT                    (PortC)
#define SPI_SCK_PIN                     (Pin05)
#define SPI_SCK_FUNC                    (Func_Spi2_Sck)

#define tft_SCK_H()                      (PORT_SetBits(SPI_SCK_PORT, SPI_SCK_PIN))
#define tft_SCK_L()                      (PORT_ResetBits(SPI_SCK_PORT, SPI_SCK_PIN))

/* SPI_MOSI Port/Pin definition */
#define SPI_MOSI_PORT                   (PortC)
#define SPI_MOSI_PIN                    (Pin04)
#define SPI_MOSI_FUNC                   (Func_Spi2_Mosi)

#define tft_MOSI_H()                      (PORT_SetBits(SPI_MOSI_PORT, SPI_MOSI_PIN))
#define tft_MOSI_L()                      (PORT_ResetBits(SPI_MOSI_PORT, SPI_MOSI_PIN))

///* SPI_MISO Port/Pin definition */
//#define SPI_MISO_PORT                   (PortE)
//#define SPI_MISO_PIN                    (Pin03)
//#define SPI_MISO_FUNC                   (Func_Spi3_Miso)

/* SPI unit and clock definition */
#define SPI_UNIT                        (M4_SPI2)
#define SPI_UNIT_CLOCK                  (PWC_FCG1_PERIPH_SPI2)

/* Choose SPI master or slave mode */
#define SPI_MASTER_MODE
//#define SPI_SLAVE_MODE
void delay_ms(u16 count);

void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);


void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey);
void Show_logo_secreen(void);
#endif
