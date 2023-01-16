#include "lib/include.h"
extern void configuracionuart(int clock, int baudrate)

{
    int BRD_I;
    float BRD_F;
    int data = 0x3;


        SYSCTL->RCGCUART|= (1<<0); // habilita el Uart0 
        
        SYSCTL->RCGCGPIO|= (1<<0); // habilita el puerto A
        //                 Tx       Rx
        GPIOA->AFSEL  |= (1<<1) | (1<<0);
        GPIOA->DIR    |= (1<<1) | (0<<0);
        GPIOA->PUR    |= (0<<1) | (0<<0);
        GPIOA->PDR    |= (0<<1) | (0<<0);
        GPIOA->AMSEL  |= (0<<1) | (0<<0);
        GPIOA->DEN    |= (1<<1) | (1<<0);
        GPIOA->PCTL   &= 0xFFFFFF00;
        GPIOA->PCTL   |= 0x00000011;
        GPIOA->CR     |= 0x00000000; // lock
        /*
         * Baudrate 19200 frecuencia reloj 16 000 000
         * BRD = 16 000 000 / ( 16 * 19200 ) = 52.08333
         * UARTFBRD[DIVFRAC] = integer( 0.08333 * 64 + 0.5 ) = 6
         */
        //    int ck = 16000000;
        //    int ck = 25000000;
        BRD_I = clock/(16 * baudrate);
        BRD_F = clock/(16.0 * baudrate) - BRD_I;
        BRD_F = lround(BRD_F * 64 + 0.5);

        // Control      RXE     TXE     UARTEN
        UART0->CTL  = (0<<9) | (0<<8) | (0<<0);
        UART0->IBRD = BRD_I;      // Integer Baud-Rate Divisor
        UART0->FBRD = (int)BRD_F; // Fractional Baud-Rate Divisor
        UART0->LCRH = (data<<5) | (1<<4); //bits data & Enable FIFOs
        //The UART has two 16x8 FIFOs; one for transmit and one for receive
        UART0->CC   = 0x0; // Clock Configuration = System clock
        UART0->CTL  = (1<<9) | (1<<8) | (1<<0); //send

        

}
extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART0->FR & (1<<4)) != 0 );
    v = UART0->DR & 0xFF;
    c = v;
    return c;
}
extern void printChar(char c)
{
    while((UART0->FR & (1<<5)) != 0 );
    UART0->DR = c;
}
extern void printString(char* string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}

extern void readString(char UART0_Sring[], char delimitador)
{

   int i=0;
//   char string [20]; //= (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       (UART0_Sring[i]) = c;
       i++;
       /*if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       */

       c = readChar();
   }

   //UART7_Sring = string;
     UART0_Sring[i]= '\0';

}
