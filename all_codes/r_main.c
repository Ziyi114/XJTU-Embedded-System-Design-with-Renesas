/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V2.02.01.01 [30 May 2014]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 2015-1-21
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_digtalLED.h"
#include "r_cg_pclbuz.h"
#include "r_cg_KeyScan.h"
#include "r_cg_lcd.h"
#include <string.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#define  Clear_WDT()  WDTE = 0xAC
extern volatile uint8_t num_keyboard;
extern volatile uint8_t num;
uint8_t num_10;
bit bit_control;
uint8_t array_key[2];
int i,j;
unsigned char date[64]="    自  动  化      2185011736        钟子逸        年  月  日  ";
unsigned int fp=0;
unsigned int wait=0;
#define  Clear_WDT()  WDTE = 0xAC

uint8_t  Lcd_Flashlight;

uint16_t  time_lenth = 0;
int flag_b=0;
int flag_a=0;
int flag_c=0;
int count=0;
int a=0;
int b=0;
int d=0;
int e=0;
int z=0;
uint16_t  buzzle_time = 0;
uint16_t  buzzle_cycle = 0;

/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);
void dispaly(void);
void delaya(void);
void delayb(void);
void display_lcd();
void BUZZLE_Delay(void);
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)

{
   	hdwinit();
	R_PCLBUZ0_Create();
	R_TAU0_Create();
	R_TAU0_Channel0_Start();
	R_MAIN_UserInit();
	lcd_init( );
    /* Start user code. Do not edit comment generated here */
	while (1U)
	{
	//LCD输入	
	 Keyboard_scan();  //键盘扫描函数 
	 if(num_keyboard==0)
	 {
		 
	 	display_lcd();
	 	lcd_display(0,"14--退出循环    ");
	 	lcd_display(16,"13--初始界面    ");
	 	lcd_display(32,"12--循环显示");
		lcd_display(48,"11--信息重置    ");
	 }


	 if(num_keyboard>=1 && num_keyboard<=12)//显示lcd
	 {
	 	display_lcd();
	 	lcd_display(0,date);   //显示个人信息
	 }
	 
	 
         if(num_keyboard==13) a=1;  
	 if(num_keyboard==15) 
	 {
		LcdClear();   //清屏
	 	a=0;
	 	display_lcd();
	 	lcd_display(0,"14--退出循环    ");
	 	lcd_display(16,"13--初始界面    ");
	 	lcd_display(32,"12--循环显示");
		lcd_display(48,"11--信息重置    ");
		
	 }
         if(a==1)    //循环显示
	 {
		time_lenth++;

		if(time_lenth == 3)
		{	
		    lcd_write(0x01,0); 		
			switch(Lcd_Flashlight)
			{
			case 0: lcd_display(0,date);
					Clear_WDT();
					delaya();
			Lcd_Flashlight++;
			break;
			case 1:       LcdFill_REC1();  //显示校徽
			        lcd_display(21,"可  以  ");
					Clear_WDT();
					delaya();
			Lcd_Flashlight++;
			break;
			case 2:LcdFill_REC2();
			      lcd_display(21,"很  强  ");
					Clear_WDT();
					delaya();
			Lcd_Flashlight++;
			break;
#if 0
			case 3:			 
            LcdFill_Vertical();
			Lcd_Flashlight++;
			break;
			
			case 4:				 
			LcdFill_Level();
			Lcd_Flashlight=0;
			R_PCLBUZ0_Start();
			BUZZLE_Delay();
			R_PCLBUZ0_Stop();
			break;
#endif			
			default: Lcd_Flashlight = 0;
            break;
			}
			
			Keyboard_scan();
			if(num_keyboard==15) 
			{
			
			R_PCLBUZ0_Start();
			BUZZLE_Delay();
			R_PCLBUZ0_Stop();
			R_PCLBUZ0_Start();
			BUZZLE_Delay();
			R_PCLBUZ0_Stop();
			R_PCLBUZ0_Start();
			BUZZLE_Delay();
			R_PCLBUZ0_Stop();a=0;
			}
		}	 
	 
	 	 
	 
	 
	 }
	 //计数
	 
		flag_b=flag_a;
	        if(num_keyboard==14)// start circle
		{
			flag_a=1;

		}
		if(flag_b==0 && flag_a==1)
		{
			num=0;
			num_10=0;
		}

		else if(flag_b==1 && flag_a==1)
		{
			num_10 = num/10;
			flag_c=0;
		}
		if(flag_a==1 && num == 30)
		{ 
			R_PCLBUZ0_Start();
			BUZZLE_Delay();
			R_PCLBUZ0_Stop();
			R_TAU0_Channel0_Stop();
			num_10=0;
		}		
		
		dispaly();
	}
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void dispaly(void)        //DIGTAL_LED display
{
	array_key[0]=3-num_10%10;    //the second char
	array_key[1]=num_10/10;    //the front char
	if(count<2)
	{
		if(count==0)bit_control=1;    //from bit2 to bit1
		if(count==1)bit_control=0;
		//testvalue1 = Getcode(array_key[count]);
		//DIGTAL_PORT = testvalue1;
		DIGTAL_LED_D4 = ~bit_control;
		DIGTAL_LED_D3 = ~bit_control;


		DIGTAL_PORT = Getcode(array_key[count]);

		DIGTAL_LED_D4 = bit_control;
		DIGTAL_LED_D3 = ~bit_control;
		count++;
	}
	else
	{
		count=0;
	}
}
void display_lcd()
{
	if(num_keyboard!=0）wait++;
	if(wait>50)
	{
	if(fp==4||fp==8)fp=fp+2;
	if(fp==12) fp=0;
	if(num_keyboard==11)
		{if(fp==6||fp==10)fp=fp-3;
		else if(fp==0)fp=11;
		else fp=fp-1;
		date[fp]=' ';}
	else if(num_keyboard==12)
		{date[48]=' ';
		date[49]=' ';
		date[50]=' ';
		date[51]=' ';
		date[54]=' ';
		date[55]=' ';
		date[58]=' ';
		date[59]=' ';
		fp=0;}
		
	else{
		date[fp+48]=num_keyboard+47;
		fp++;}
	wait=0;
	num_keyboard=16;
	}
}
void delaya(void)
{
	int i,j;
	for(i=0;i<5000;i++)
	   for(j=0;j<200;j++);
}
void delayb(void)
{
	int i,j;
	for(i=0;i<1000;i++)
	   for(j=0;j<200;j++);
}
void BUZZLE_Delay(void)
{
	for(buzzle_time = 0; buzzle_time <50000; buzzle_time++)
		for(buzzle_cycle = 0; buzzle_cycle <20; buzzle_cycle++);
}
/* End user code. Do not edit comment generated here */
