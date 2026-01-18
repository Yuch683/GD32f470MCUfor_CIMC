#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "timer.h"
#include "ADC.h"
#include "usart.h"
#include "gpio.h"
#include "Instruction_set.h"

extern volatile uint8_t adc_capture_flag;
uint16_t Voltage = 0;

int main(void)
{
	/* 设置向量表基地址 */
	nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x00000U);
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
	
    systick_config();
	Timer1_Init();
	ADC0_Init();
	Usart2_Init();
	Usart2_NVIC();
	SD_Card_Init();
	SD_SPI_Init();
	
	
	delay_1ms(20);
	
    for(;;) {
		// --- 处理串口指令 ---
		if(rx_complete_flag == 1) {

            // test
            if(strcmp((const char*)rx_buffer, "test") == 0){
				Test();
            }
            // RTC_Config
            else if(strcmp((const char*)rx_buffer, "RTC_Config") == 0) {
				
            }
            // 
            else {

            }

            // 清除标志位，准备接收下一条指令
            rx_complete_flag = 0; 
        }
		
		
		if(adc_capture_flag == 1){	//执行电压采集
			Voltage = (float) ADC_Get_Value() * Voltage_Resolution;
		}
    }
}


