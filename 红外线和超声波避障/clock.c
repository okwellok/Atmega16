#include <iom16v.h>
#include <macros.h>

   
void clock_port_init(void)
{
   TCCR0|=0x02;//8Î»·Ö
   TIMSK|=0x01;
   SREG|=0X80; 
   TIFR|=0x01;
   TCNT0=0;
}