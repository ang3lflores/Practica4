#ifndef ADC_ADC_H_
#define ADC_ADC_H_


/*TIVA GRANDE
 * El micro contiene 2 modulos de ADC, ADC0 y ADC1
 * ambos comparten los mismos 12 canales de 12 bits.
 */
//Peripheral Configuration (ADCPC)
#define _125ksps              0x1
#define _250ksps              0x3
#define _500ksps              0x5
#define _1Msps                0x7
//#define SS3                   0x7
//#define SS2                   0x7
//#define SS1                   0x7
//#define SS0                   0x7
/*
 * Se configuran los pines a usar:
 * los secuenciadores pueden ser multicanales
 * SS3 --> realiza 1 muestra
 * SS2 --> realiza 4 muestras
 * SS1 --> realiza 4 muestras
 * SS0 --> realiza 8 muestras
 * Por lo que el SS0 el dato_adc0 = SS0/8;
 * Es decir que solo el SS3 no puede ser multicanal.
 */

    /* ADC Sample Sequence Control 3 (ADCSSCTL3)
     * TS0  = 1st Sample Temp Sensor Select
     * IE0  = Sample Interrupt Enable
     * END0 = End of Sequence
     * D0   = Sample Differential Input Select
     */

extern void Configurar_ADCM0SS3(void);
extern void Configurar_ADCM0SS2(void);
extern void Configurar_ADCM0SS1(void);
extern readADC0SS3( int  adc_data);
extern readADC0SS2( int  adc_data[]);
extern readADC0SS1( int  adc_data[]);

#endif /* ADC_ADC_H_ */
