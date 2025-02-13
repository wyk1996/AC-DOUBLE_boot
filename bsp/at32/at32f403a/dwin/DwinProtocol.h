
#ifndef __DWINPROTOCOL_H_
#define __DWINPROTOCOL_H_

#include <rtthread.h>
#include "stdint.h"

#define LCD_SEND_BUF_LEN            (200u)

#define DWIN_LCD_HEAD       	    (0x5AA5)                    //迪文屏数据帧头
#define KEY_VARI_ADDR       	    (0x1000)                    //键值变量地址
#define REGISTER_WRITE      	    (0x80)		                //写寄存器指令
#define REGISTER_READ       	    (0x81)		                //读寄存器指令
#define VARIABLE_WRITE      	    (0x82)		                //写变量存储器指令
#define VARIABLE_READ       	    (0x83)		                //读变量存储器指令

#define DWIN_RTC_REGISTER   	    (0x20)		                //RTC寄存器地址

#define DWIN_RESET_REGISTER   	    (0xEE)		                //复位寄存器地址
#define DWIN_KEY_CONTROL_REGISTER   (0x4F)		                //键控寄存器地址
#define DWIN_LED_STA_REGISTER       (0x1E)		                //背光亮度寄存器地址
#define DWIN_LED_OFF_VALUE          (0x00)		                //息屏状态背光亮度值（该值要与屏幕系统设置里的R7保持一致，修改时请慎重）
#define DWIN_INPUT_STATUS_REGISTER  (0xE9)		                //触摸屏录入状态寄存器地址

#define DWIN_RESET_CMD   	        (0x5AA5)		            //复位指令
#define DWIN_HIDE_CMD   	        (0xFF00)		            //隐藏指令
#define DWIN_LCD_COVER       	    (0xFFFF)                    //覆盖指令，在文本显示和ASCII显示时在帧尾添加，可以免去擦除操作

typedef enum
{
    DISP_UART_BUSY = 0,
    DISP_UART_IDLE,
    DISP_UART_MAX,
} _DISP_UART_STATUS;
typedef struct
{
    uint8_t Buf[LCD_SEND_BUF_LEN];
    uint8_t Len;
} _LCD_SEND_CONTROL;

typedef enum
{
    BLACK  = 0x0000,
    WHITE  = 0xFFFF,
    YELLOW = 0xFFE0,
    RED    = 0xF800,
    GREEN  = 0x07E0,
} _SHOW_COLOR;

/***********************************************************************************************
* Function		: printBackImage
* Description	: 显示背景图片(这里画面ID和图片保存在屏上的顺序保持一致)
* Input			:
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void PrintBackImage(uint8_t Image);

/***********************************************************************************************
* Function		: PrintNum32uVariable
* Description	: 显示类型为INT32的数字变量
* Input			: uint16_t VariableAddress  变量地址
                  uint32_t num			  显示数据
* Output		:
* Note(s)		:
* Contributor	: 2018年6月14日
***********************************************************************************************/
void PrintNum32uVariable(uint16_t VariableAddress,uint32_t num);

/***********************************************************************************************
* Function		: PrintNum16uVariable
* Description	: 显示类型为INT16的数字变量
* Input			: uint16_t VariableAddress  变量地址
                  uint16_t num			  显示数据
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void PrintNum16uVariable(uint16_t VariableAddress,uint16_t num);
void simulation_Print(uint32_t Xaxis,uint32_t Yaxis);
/***********************************************************************************************
* Function		: PrintNum16uVariable
* Description	: 显示类型为uint8_t的数字变量
* Input			: uint16_t VariableAddress  变量地址
                  uint8_t num			  	  显示数据
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void PrintNum8uVariable(uint16_t VariableAddress,uint8_t num);

/***********************************************************************************************
* Function		: PrintDecimalVariable
* Description	: 显示2位小数变量(范围0-99999.99)
* Input			: uint16_t VariableAddress  变量地址
                  FP32 num			  	  显示数据
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void PrintDecimalVariable(uint16_t VariableAddress,uint32_t num);

/***********************************************************************************************
* Function		: PrintIcon
* Description	: 显示图标变量
* Input			: uint16_t VariableAddress  变量地址
                  uint16_t num			  图标位置
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void PrintIcon(uint16_t VariableAddress,uint16_t num);


/***********************************************************************************************
* Function		: PrintTime
* Description	: 显示时间变量
* Input			: uint32_t VariableAddress  变量地址
                  _BSPRTC_TIME gRTC       RTC数据
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void PrintTime(uint16_t VariableAddress,void * gRTC);


/***********************************************************************************************
* Function		: PrintStr
* Description	: 显示字符串
* Input			: uint16_t VariableAddress  变量地址
                  uint8_t *s  			  字符串内容
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void PrintStr(uint16_t VariableAddress,uint8_t *s,uint8_t len);
void PrintStr123(uint16_t VariableAddress,uint8_t *s,uint8_t len);
/***********************************************************************************************
* Function		: PrintMAC
* Description	: 显示MAC地址
* Input			: uint16_t VariableAddress  变量地址
                  uint8_t *s  			  字符串内容
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void PrintMAC(uint16_t VariableAddress,uint8_t *s,uint8_t len);

/***********************************************************************************************
* Function		: SetVariHide
* Description	: 隐藏变量
* Input			: uint16_t DescrPointer  	  描述指针地址
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void SetVariHide(uint16_t DescrPointer);

/***********************************************************************************************
* Function		: SetVariCancelHide
* Description	: 取消隐藏变量
* Input			: uint16_t DescrPointer  	  描述指针地址
                  uint16_t VariableAddress  变量实际地址
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void SetVariCancelHide(uint16_t DescrPointer,uint16_t VariableAddress);

/***********************************************************************************************
* Function		: DisplayQRCode
* Description	: 显示二维码
* Input			: uint16_t VariableAddress  变量地址
                  uint8_t *str,			  ASCII地址
                  uint8_t len               ASCII长度
* Output		:
* Note(s)		:
* Contributor	: 20201013 显示二维码
***********************************************************************************************/
void DisplayQRCode(uint16_t VariableAddress, uint8_t *str, uint8_t len);

/***********************************************************************************************
* Function		: CleanSomePlace
* Description	: 清空某一地址段数据
* Input			: uint16_t VariableAddress  变量地址
                  uint8_t len  			  地址长度
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void CleanSomePlace(uint16_t VariableAddress,uint8_t len);

/***********************************************************************************************
* Function		: KeyControl
* Description	: 键控函数
* Input			: uint8_t keyval 键控值
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void KeyControl(uint8_t keyval);

/***********************************************************************************************
* Function		: ReadDwinInputStatus
* Description	: 读迪文屏输入状态
* Input			:
* Output		:
* Note(s)		:
* Contributor	: 2018年6月14日
***********************************************************************************************/
void ReadDwinInputStatus(void);

/***********************************************************************************************
* Function		: ReadLcdBackLight
* Description	: 读迪文屏背光亮度值
* Input			:
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void ReadLcdBackLight(void);

/***********************************************************************************************
* Function		: LCD_Reset
* Description	: 显示屏复位
* Input			:
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void LCD_Reset(void);

/***********************************************************************************************
* Function		: HEXtoBCD
* Description	: 将uint8_t的HEX转换为对应的BCD码
* Input			: uint8_t value   0~99
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
uint8_t HEXtoBCD(uint8_t value);

/***********************************************************************************************
* Function		: BCDtoHEX
* Description	: 将uint8_t的BCD码转换为对应的HEX
* Input			: uint8_t value   0~0x99
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
uint8_t BCDtoHEX(uint8_t value);

/*****************************************************************************
* Function     : CmpNBuf
* Description  : 比较换成是否一致
* Input        :
* Output       :
* Return       :
* Note(s)      :
* Contributor  : 2021年3月19日
*****************************************************************************/
uint8_t  CmpNBuf(uint8_t*  pbuf1,uint8_t*  pbuf2,uint8_t len);

/***********************************************************************************************
* Function		: ReadDwinVariable
* Description	: 读取变量
* Input			: uint32_t VariableAddress  变量起始地址
                  uint8_t len               读取数据长度（字节），每个单位长度内有2个字节数据，
                                            如：len == 6 ,则从变量开始地址连续读取12字节数据
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void ReadDwinVariable(uint16_t VariableAddress,uint8_t len);

/***********************************************************************************************
* Function		: SetVariColor
* Description	: 设置变量颜色
* Input			: uint16_t DescrPointer  	  描述指针地址
                  _SHOW_COLOR color  		  字符串颜色
* Output		:
* Note(s)		:
* Contributor	: 2018年6月14日
***********************************************************************************************/
void SetVariColor(uint16_t DescrPointer,_SHOW_COLOR color);

/***********************************************************************************************
* Function		: ReadDWRTC
* Description	: 读取迪文RTC
* Input			:
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void ReadDWRTC(void);

/***********************************************************************************************
* Function		: ReadDWRTC
* Description	: 设置迪文RTC
* Input			:
* Output		:
* Note(s)		:
* Contributor	:  2018年6月14日
***********************************************************************************************/
void SetDWRTC(uint8_t * ptime,uint8_t len);
#endif
