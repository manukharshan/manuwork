/* 
 * File:   analog.h
 * Author:Manu K Harshan
 *
 * Created on August 1, 2017, 4:44 PM
 */

#ifndef ANALOG_H
#define	ANALOG_H

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "peripheral/ports/plib_ports.h"
#include "peripheral/int/plib_int.h"
//#include <drv_adc.h>

#ifdef	__cplusplus
extern "C" {
#endif
//----------------- BEGIN ADC DEFINES ----------------------------
#define ADC_TAD 4000000 // Desired TAD clock Frequency (Use only interger value) (1MHz - 16MHz)
#define ADC_TAD_Sample_Time 8 // For shared S/H_5 chan, how many TAD clks to sample (SAMC: 1-256)
#define ADC_NUM_ANX_PINS 3 // How many shared channels will be used
#define ADC_Average_Bits 5 // will average (2^ADC_Average_Bits) samples
#define ADC_PINS_TO_SAMPLE {24, 26, 32} // Which ANx inputs will be sampled during the run
#define ADC_Slope 1155.0
#define ADC_Intercept 467.0
//----------------- END ADC DEFINES ------------------------------

typedef enum
{
    MULTIPORT_CH1, // red
    MULTIPORT_CH2, // green
    MULTIPORT_CH3, // blue
    MULTIPORT_CH4, // white || amber
    FRONT_CH1,
    THERMISTOR,
    FAN_SPEED,
    FREQUENCY,
    MULTIPORT_CH1_STROBE, // red
    MULTIPORT_CH2_STROBE, // green
    MULTIPORT_CH3_STROBE, // blue
    MULTIPORT_CH4_STROBE, // white || amber
    FRONT_CH1_STROBE,
} ADC_CHANNEL_NAMES;

typedef volatile struct
{
    uint16_t ADC_Raw_Data[ADC_NUM_ANX_PINS][1<<ADC_Average_Bits];
    uint32_t AverageSums[ADC_NUM_ANX_PINS];
    uint32_t AverageSumsCheck[ADC_NUM_ANX_PINS];
    uint16_t ADC_Data_Average[ADC_NUM_ANX_PINS];
    uint8_t AveragePointer;
} ADC_DATA;

//----------------- USER DEFINES ERROR CHECKING ------------------
#if (ADC_TAD > 16000000) || (ADC_TAD < 1000000) || (ADC_TAD_Sample_Time < 3)
 #error "Invalid ADC_TAD or ADC_TAD_Sample_Time"
#endif
#if ((ADC_TAD / ADC_TAD_Sample_Time / ADC_NUM_ANX_PINS) < 4000)
 #warning "Samples will take longer than the control cycle"
#endif
//----------------- END USER DEFINES ERROR CHECKING --------------

//----------------- BEGIN OTHER DEFINES --------------------------
//typedef uint8_t ANx_Array[ADC_NUM_ANX_PINS];
//ANx_Array ANx_Pins = ADC_PINS_TO_SAMPLE;
//double ADC_Slope_Inv = 1.0 / ADC_Slope;
//double VDD_Inv = 1.0 / 3.3;
//ADC_DATA ADCData;
//----------------- END OTHER DEFINES ----------------------------    

void intitADC(void);
//double calculateVoltage(uint8_t channel);
//double calculatePercentADC(uint8_t channel);
void ADCProcessValues(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ANALOG_H */

