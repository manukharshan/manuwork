
#include "analog.h"

uint16_t adcdata[4];
float value[4];

void intitADC(void)
{
    int i;
    uint64_t scanbits = 0;

    // <editor-fold defaultstate="collapsed" desc="setup pins">
//
//    // B4 (AN4) --> PIN 30 (AN4) on HEADER J11
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_4 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_4 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_4, PORTS_PIN_MODE_ANALOG );

//    // E6 (AN16) --> PIN 6 (PMD6) on HEADER J10
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6, PORTS_PIN_MODE_ANALOG );

//    // B11 (AN6) --> PIN 18 (T2CLK) on HEADER J10
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11, PORTS_PIN_MODE_ANALOG );

//    // C4 (AN19) --> PIN 13 (PMPRD) on HEADER J10
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4, PORTS_PIN_MODE_ANALOG );

//    // RB1 (AN1) --> PIN 33 (AN1) on HEADER J11
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1, PORTS_PIN_MODE_ANALOG );

    // G15 (AN23) --> PIN 1 (RG15) on HEADER J10
    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15 );
    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15 );
    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15, PORTS_PIN_MODE_ANALOG );

//    // E8 (AN25) --> PIN 37 (INT1) on HEADER J10
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_8 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_8 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_8, PORTS_PIN_MODE_ANALOG );

//    // B15 (AN10) --> PIN 46 (U2RX) on HEADER J11
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15, PORTS_PIN_MODE_ANALOG );

//    // B10 (AN5) --> PIN 52 (CVREF) on HEADER J11
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10, PORTS_PIN_MODE_ANALOG );

//    // F12 (AN31) --> PIN 54 (TDO) on HEADER J11
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_12 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_12 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_12, PORTS_PIN_MODE_ANALOG );

//    // F13 (AN30) --> PIN 56 (TDI) on HEADER J11
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_13 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_13 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_13, PORTS_PIN_MODE_ANALOG );
//
//    // A1 (AN29) --> PIN 56 (TCK) on HEADER J11
//    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1 );
//    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1 );
//    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1, PORTS_PIN_MODE_ANALOG );

    // A0 (AN24) --> PIN 56 (TMS) on HEADER J11
    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0 );
    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0 );
    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0, PORTS_PIN_MODE_ANALOG );
    
    // D14 (AN32) --> PIN 47 (TMS) on HEADER J11
    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_14 );
    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_14 );
    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_14, PORTS_PIN_MODE_ANALOG );
    
     // E9 (AN26) --> PIN 19 (TMS) on HEADER J11
    PLIB_PORTS_PinDirectionInputSet( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_9 );
    PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_9 );
    PLIB_PORTS_PinModePerPortSelect( PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_9, PORTS_PIN_MODE_ANALOG );

//    for (i = 0; i < ADC_NUM_ANX_PINS; i++)
//    {
//        scanbits |= (uint64_t)(1 << ANx_Pins[i]);
//    }


    // configure ADC
//   PLIB_ADCP_Configure(ADCP_ID_1, ADCP_VREF_AVDD_AVSS, false, false, false, ADCP_CLK_SRC_SYSCLK, (SYS_CLK_SystemFrequencyGet() / ADC_TAD / 2), 32, 0, 32);
// PLIB_ADCP_Configure(ADCP_ID_1, ADCP_VREF_VREFP_AVSS, false, false, false, ADCP_CLK_SRC_SYSCLK, (SYS_CLK_SystemFrequencyGet() / ADC_TAD / 2), 32, 0, 32);
// PLIB_ADCP_Configure(ADCP_ID_1, ADCP_VREF_AVDD_VREFN, false, false, false, ADCP_CLK_SRC_SYSCLK, (SYS_CLK_SystemFrequencyGet() / ADC_TAD / 2), 32, 0, 32);
// PLIB_ADCP_Configure(ADCP_ID_1, ADCP_VREF_VREFP_VREFN, false, false, false, ADCP_CLK_SRC_SYSCLK, (SYS_CLK_SystemFrequencyGet() / ADC_TAD / 2), 32, 0, 32);

//    AD1CAL1 = 0xF8894530; // Use software calibration values into AD1CALx
//    AD1CAL2 = 0x01E4AF69;
//    AD1CAL3 = 0x0FBBBBB8;
//    AD1CAL4 = 0x000004AC;
//    AD1CAL5 = 0x02000002;
    
    AD1CAL1 = DEVADC1;                  // Writing Calibration-Data to ADC-Registers
    AD1CAL2 = DEVADC2;
    AD1CAL3 = DEVADC3;
    AD1CAL4 = DEVADC4;
    AD1CAL5 = DEVADC5;
    
    AD1CON1 = 0x0; // turn off and clear ADC
    //AD1CON1 = 0x00E0;
    AD1CON1bits.STRGSRC = 1; // Scan Trigger Src = Global Software Trigger (GSWTRG)
    
    AD1CON2 = 0x0;
    AD1CON2bits.ADCSEL = 0x01; // use system clock
    AD1CON2bits.ADCDIV = 0x04; // ADC clock divider
    AD1CON2bits.SAMC = 0x09; // sample time is x TAD
    
    AD1CON3 = 0x0;
    //AD1CON3 = 0x1F02;

    AD1IMOD = 0;                        // All SampleAndHold-Units set to Standard-values

    AD1GIRQEN1 = 0;                     // No Interrupts used
    AD1GIRQEN2 = 0;                     // No Interrupts used
    
    // clear channel-scan bits, then set the channels to scan
    AD1CSS1 = 0;
    AD1CSS2 = 0;
    AD1CSS1bits.CSS23 = 1;
    AD1CSS1bits.CSS26 = 1;
    AD1CSS1bits.CSS24 = 1;
    AD1CSS2bits.CSS32 = 1;
    
    AD1CMPCON1 = 0;                     // No Comperator-Functions
    AD1CMPCON2 = 0;
    AD1CMPCON3 = 0;
    AD1CMPCON4 = 0;
    AD1CMPCON5 = 0;
    AD1CMPCON6 = 0;
    
    AD1FLTR1 = 0;                       // No Filter / Oversampling
    AD1FLTR2 = 0;
    AD1FLTR3 = 0;
    AD1FLTR4 = 0;
    AD1FLTR5 = 0;
    AD1FLTR6 = 0;
    
    AD1TRG1 = 0;                        // No Triggers
    AD1TRG2 = 0;
    AD1TRG3 = 0;

    
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH0, ADCP_SH_MODE_DIFFERENTIAL_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH1, ADCP_SH_MODE_DIFFERENTIAL_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH2, ADCP_SH_MODE_DIFFERENTIAL_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH3, ADCP_SH_MODE_DIFFERENTIAL_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH4, ADCP_SH_MODE_DIFFERENTIAL_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH5, ADCP_SH_MODE_DIFFERENTIAL_UNIPOLAR);

// PLIB_ADCP_ChannelScanConfigure(ADCP_ID_1, 0, 0, ADCP_SCAN_TRG_SRC_SOFTWARE);
//    PLIB_ADCP_ChannelScanConfigure(ADCP_ID_1, (UINT32)scanbits, (UINT32)(scanbits >> 32), ADCP_SCAN_TRG_SRC_SOFTWARE);

    
    AD1CON1bits.ADCEN = 1;              // Enable ADC
//    PLIB_ADCP_Enable ( ADCP_ID_1 ) ; // enable ADC module
//    while(!PLIB_ADCP_ModuleIsReady ( ADCP_ID_1 )) ; // wait for ADC ready

//    PLIB_ADCP_CalibrationStart(ADCP_ID_1); // calibrate ADC module
//    while(!PLIB_ADCP_ModuleIsReady ( ADCP_ID_1 )) ; // wait for ADC ready

//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH0, ADCP_SH_MODE_SINGLE_ENDED_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH1, ADCP_SH_MODE_SINGLE_ENDED_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH2, ADCP_SH_MODE_SINGLE_ENDED_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH3, ADCP_SH_MODE_SINGLE_ENDED_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH4, ADCP_SH_MODE_SINGLE_ENDED_UNIPOLAR);
//    PLIB_ADCP_SHModeSelect(ADCP_ID_1, ADCP_SH5, ADCP_SH_MODE_SINGLE_ENDED_UNIPOLAR);
    
     while (AD1CON2bits.ADCRDY == 0);    // Wait for end of Calibration
  
     AD1CON3bits.GSWTRG = 1;
//    // triger an ADC sample
//    PLIB_ADCP_GlobalSoftwareTrigger ( ADCP_ID_1 ) ;

}

//double calculateVoltage(uint8_t channel)
//{
//    return ((double)ADCData.ADC_Data_Average[channel] - ADC_Intercept) * ADC_Slope_Inv;
//}

//double calculatePercentADC(uint8_t channel)
//{
//    return calculateVoltage(channel) * VDD_Inv;
//}

void ADCProcessValues(void)
{
    
//    if(AD1DSTAT1bits.ARDY23 == 0)
//    {
        adcdata[0] = AD1DATA23;
        value[0] = (float)((adcdata[0]/1024)*3.3);
//    }
//    if(AD1DSTAT1bits.ARDY26 == 0)
//    {
        adcdata[1] = AD1DATA26;
        value[1] = (float)((adcdata[1]/1024)*3.3);
//    }
//    if(AD1DSTAT2bits.ARDY32 == 0)
//    {
        adcdata[2] = AD1DATA32;
        value[2] = (float)((adcdata[2]/1024)*3.3);
//    }
//    if(AD1DSTAT1bits.ARDY24 == 0)
//    {
        adcdata[3] = AD1DATA24;
        value[3] = (float)((adcdata[3]/1024)*3.3);
//    }
      AD1CON3bits.GSWTRG = 1;
//    for ( i = 0 ; i < ADC_NUM_ANX_PINS ; i++ )
//    {
//        ADCData.AverageSums[i] -= ADCData.ADC_Raw_Data[i][ADCData.AveragePointer];
//        ADCData.ADC_Raw_Data[i][ADCData.AveragePointer] = PLIB_ADCP_ResultGet(ADCP_ID_1, ANx_Pins[i]);
//        ADCData.AverageSums[i] += ADCData.ADC_Raw_Data[i][ADCData.AveragePointer];
//        ADCData.ADC_Data_Average[i] = ADCData.AverageSums[i] >> ADC_Average_Bits;
//
//    }

    // incriment pointer
//    ADCData.AveragePointer = (ADCData.AveragePointer+1) & ((1<<ADC_Average_Bits)-1);

}