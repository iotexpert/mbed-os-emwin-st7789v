
#include "mbed.h"


static DigitalOut TFTRD(P12_3);
static DigitalOut TFTWR(P12_0);
static DigitalOut TFTDC(P12_1);
static DigitalOut TFTRST(P12_2);

static BusOut lcdBus(P9_0,P9_1,P9_2,P9_4,P9_5,P0_2,P13_0,P13_1);


void Cy_TFT_CTRL_Write(unsigned char data)
{
    lcdBus.write(data);
}

void Cy_TFT_writeCommand(unsigned char command)
{
    TFTDC = 0;

    Cy_TFT_CTRL_Write(command);
        
    TFTWR = 0;
    TFTWR = 1;
}

void Cy_TFT_writeData(unsigned char data)
{
    TFTDC = 1;

    Cy_TFT_CTRL_Write(data);
    TFTWR = 0;
    TFTWR = 1;
}

void Cy_TFT_Init(void)
{

    TFTDC = 0;
    TFTRD = 1;
    TFTWR = 0;

    TFTRST = 0; // reset the chip[]
    wait_ms(100);
    TFTRST = 1; // take it out of reset
    wait_ms(100);

    Cy_TFT_writeCommand(0x11);    /* exit SLEEP mode*/

    wait_ms(300);
  

    Cy_TFT_writeCommand(0x36);
    Cy_TFT_writeData(0xA0);      /* MADCTL: memory data access control*/
    Cy_TFT_writeCommand(0x3A);
    Cy_TFT_writeData(0x65);      /* COLMOD: Interface Pixel format*/
    Cy_TFT_writeCommand(0xB2);
    Cy_TFT_writeData(0x0C);
    Cy_TFT_writeData(0x0C);
    Cy_TFT_writeData(0x00);
    Cy_TFT_writeData(0x33);
    Cy_TFT_writeData(0x33); /*PORCTRK: Porch setting*/
    Cy_TFT_writeCommand(0xB7);
    Cy_TFT_writeData(0x35); /*GCTRL: Gate Control*/
    Cy_TFT_writeCommand(0xBB);
    Cy_TFT_writeData(0x2B); /*VCOMS: VCOM setting*/
    Cy_TFT_writeCommand(0xC0);
    Cy_TFT_writeData(0x2C); /*LCMCTRL: LCM Control*/
    Cy_TFT_writeCommand(0xC2);
    Cy_TFT_writeData(0x01);
    Cy_TFT_writeData(0xFF); /*VDVVRHEN: VDV and VRH Command Enable*/
    Cy_TFT_writeCommand(0xC3);
    Cy_TFT_writeData(0x11); /*VRHS: VRH Set*/
    Cy_TFT_writeCommand(0xC4);
    Cy_TFT_writeData(0x20); /*VDVS: VDV Set*/

    Cy_TFT_writeCommand(0xC6);
    Cy_TFT_writeData(0x0F); /*FRCTRL2: Frame Rate control in normal mode*/
    Cy_TFT_writeCommand(0xD0);
    Cy_TFT_writeData(0xA4);
    Cy_TFT_writeData(0xA1); /*PWCTRL1: Power Control 1*/
    Cy_TFT_writeCommand(0xE0);
    Cy_TFT_writeData(0xD0);
    Cy_TFT_writeData(0x00);
    Cy_TFT_writeData(0x05);
    Cy_TFT_writeData(0x0E);
    Cy_TFT_writeData(0x15);
    Cy_TFT_writeData(0x0D);
    Cy_TFT_writeData(0x37);
    Cy_TFT_writeData(0x43);
    Cy_TFT_writeData(0x47);
    Cy_TFT_writeData(0x09);
    Cy_TFT_writeData(0x15);
    Cy_TFT_writeData(0x12);
    Cy_TFT_writeData(0x16);
    Cy_TFT_writeData(0x19); /*PVGAMCTRL: Positive Voltage Gamma control*/
    Cy_TFT_writeCommand(0xE1);
    Cy_TFT_writeData(0xD0);
    Cy_TFT_writeData(0x00);
    Cy_TFT_writeData(0x05);
    Cy_TFT_writeData(0x0D);
    Cy_TFT_writeData(0x0C);
    Cy_TFT_writeData(0x06);
    Cy_TFT_writeData(0x2D);
    Cy_TFT_writeData(0x44);
    Cy_TFT_writeData(0x40);
    Cy_TFT_writeData(0x0E);
    Cy_TFT_writeData(0x1C);
    Cy_TFT_writeData(0x18);
    Cy_TFT_writeData(0x16);
    Cy_TFT_writeData(0x19); /*NVGAMCTRL: Negative Voltage Gamma control*/
    Cy_TFT_writeCommand(0x2A);
    Cy_TFT_writeData(0x00);
    Cy_TFT_writeData(0x00);
    Cy_TFT_writeData(0x01);
    Cy_TFT_writeData(0x3F); /*X address set*/
    Cy_TFT_writeCommand(0x2B);
    Cy_TFT_writeData(0x00);
    Cy_TFT_writeData(0x00);
    Cy_TFT_writeData(0x00);
    Cy_TFT_writeData(0xEF); /*Y address set*/

    wait_ms(10);
    Cy_TFT_writeCommand(0x29); /*Enable Display*/

}

void Cy_TFT_writeDataStream(unsigned char * pData, int numBytes)
{
    for(int i=0;i<numBytes;i++)
    {
        Cy_TFT_writeData(pData[i]);
    }
}

unsigned char readData()
{
    printf("read one\n");
    return 0;
}
void readDataStream(unsigned char *data,int numItems)
{
    printf("Read stream\n");

}