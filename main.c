
#include <msp430f249.h>
#define uchar unsigned char
#define uint unsigned int
#define SHIFT_NUM 8 //共八个灯


/*软件延迟ms主程序*/
 
void delayus(uint t)
{
    uint i;
    while(t--){
        for(i=1300;i>0;i--);
  }
}

void main( void )
{
    uchar mask1 = 0x01;
    uchar mask2 = 0x80;
    uchar val1 = 0x03;
    uchar val2 = 0x00;
    uchar val5 = 0x0F;
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = 0xFF;
    P1SEL = 0x00;
    P1OUT = 0xFF;
    P2DIR = 0x00;
    while (1)
    {
      if ((P2IN&0x1F) == 0x1E)
      {
        P1OUT =~ val1;
        val1 <<= 2;
        delayus(10);
        if (val1 == 0x00)
        {
          val1 = 0x03;
        }
      }
      if ((P2IN&0x1F) == 0x1D)
      {
        P1OUT =~ val2;
        ++val2;
        delayus(10);
      }
      if ((P2IN&0x1F) == 0x1B)
      {
        P1OUT =~ 0x0F;
        delayus(10);
        P1OUT =~ 0xF0;
        delayus(10);
        P1OUT =~ 0x33;
        delayus(10);
        P1OUT =~ 0xCC;
        delayus(10);
        P1OUT =~ 0x2D;
        delayus(10);
        P1OUT =~ 0xAA;
        delayus(10);
      }
      if ((P2IN&0X1F) == 0x17)
      {
        P1OUT =~ (mask1|mask2);
        delayus(10);
        mask1 <<= 1;
        mask2 >>= 1;
        if ((mask1|mask2) == 0x00)
        {
          mask1 = 0x01;
          mask2 = 0x80;
        }
      }
      if ((P2IN&0X1F) == 0x0F)
      {
        P1OUT =~ val5;
        delayus(10);
        val5 <<= 1;
        if ((((val5 & 0x80) == 0x80)&((val5 & 0x10) == 0x00))|((val5 & 0xFF) ==0x0E)) // 00001110
        {
          ++val5;
        }
      }
      P1OUT = 0XFF;    
    }

}
