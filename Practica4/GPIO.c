#include "lib/include.h"
/* ConfigurarGPIOD()
 * Configura el PORTD para poder usar UN BOTON
 * EN EL PIN PD7.
 * RECUERDA QUE EN EL CIRCUITO SE LE DEBE
 * AGREGAR UNA RESISTENCIA PARA NO PONER EN CORTO
 * ESE PIN AL MOMENTO DE PRESIONAR EL BOTON
 */
extern void ConfigurarGPIOD(void)
{
    SYSCTL->RCGCGPIO|= (1<<3);
    GPIOD->LOCK      = 0x4C4F434B;
    GPIOD->CR        = (1<<7);
    GPIOD->DIR      |= (0<<7); // PD7 ENTRADA
    GPIOD->DEN      |= (1<<7);
    GPIOD->AFSEL    |= (0<<7);
    GPIOD->PUR      |= (1<<7);
   

    NVIC_SetPriority(GPIOD_IRQn, 4); //PRI=4 el 0 con mayor prioridad el 7 con menos
    NVIC_EnableIRQ(GPIOD_IRQn);
    GPIOD->IM  |= (0<<7); // Masked
    GPIOD->IS  |= (0<<7); // Edge-sensitive
    GPIOD->IBE |= (1<<7); // Both edges
//    GPIOF->IEV |= (0<<7); //FLANCO DE BAJADA
    GPIOD->RIS |= (0<<7); // Registro de estado
    GPIOD->IM  |= (1<<7); // Send
}

/*extern void Delay(void)
{
  unsigned long volatile time;
  time = 1600000;
  while(time)
  {
		time--;
  }
}
*/