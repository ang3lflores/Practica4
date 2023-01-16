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
//    GPIOD->LOCK     = 0x11111111; //lock

//    // GPIO Initialization and Configuration
//    // 1. Habilitar reloj para los módulos GPIO (SYSCTL->RCGCGPIO |= (_PORTs);)
//    SYSCTL->RCGCGPIO |= 0x08; // |= (1<<3)
//    // Dar tiempo para que el reloj se estabilice (SYSCTL->PRGPIO)
//    while((SYSCTL->PRGPIO & (0x08) ) != (0x08) ){};
//    // 2. Desbloquee GPIO solo PD7, PF0 en TM4C123G; (GPIOx->LOCK = 0x4C4F434B; and GPIOx->CR = _PINs;)
//    GPIOD->LOCK = 0x4C4F434B;
//    GPIOD->CR    |= 0x80;    // |= (1<<7);
//    // 3. Establecer bits de selección de modo analógico para cada puerto (GPIOn->AMSEL 0=digital, 1=analog)
//    GPIOD->AMSEL |= 0x00;    // |= (0<<7);
//    // 4. Establecer registro de control de puerto para cada puerto (GPIOn->PCTL = PMCn, check the PCTL table)
//    GPIOD->PCTL  |= 0x00;    // |= (0<<7);
//    // 5. Establecer bits de selección de funciones alternativas para cada puerto (GPIOn->AFSEL 0=regular I/O, 1=PCTL peripheral)
//    GPIOD->AFSEL |= 0x00;    // |= (0<<7);
//    // 6. Establezca los pines de salida para cada puerto (Dirección de los pines: GPIOn->DIR 0=input, 1=output)
//    GPIOD->DIR   |= 0x00;    // |= (0<<7);
//    // 7. Juego de brocas PUR para pull-up interno, PDR para registro pull-down, ODR para drenaje abierto (0: disable, 1=enable)
//    GPIOD->PUR   |= 0x80;    // |= (1<<7);
//    // 8. Configure el registro Digital ENable en todos los pines GPIO (GPIOn->DEN 0=disable, 1=enable)
//    GPIOD->DEN   |= 0x80;    // |= (1<<7);

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
