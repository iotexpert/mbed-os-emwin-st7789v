
#include "mbed.h"
#include "GUI.h"

static DigitalOut TFTRD(MBED_CONF_ST7789V_TFT_TFTRD);
static DigitalOut TFTWR(MBED_CONF_ST7789V_TFT_TFTWR);
static DigitalOut TFTDC(MBED_CONF_ST7789V_TFT_TFTDC);
static DigitalOut TFTRST(MBED_CONF_ST7789V_TFT_TFTRST);

static BusOut lcdBus(MBED_CONF_ST7789V_TFT_DB8,
                        MBED_CONF_ST7789V_TFT_DB9,
                        MBED_CONF_ST7789V_TFT_DB10,
                        MBED_CONF_ST7789V_TFT_DB11,
                        MBED_CONF_ST7789V_TFT_DB12,
                        MBED_CONF_ST7789V_TFT_DB13,
                        MBED_CONF_ST7789V_TFT_DB14,
                        MBED_CONF_ST7789V_TFT_DB15);


void ST7789V_CTRL_Write(unsigned char data)
{
    lcdBus.write(data);
}

void ST7789V_writeCommand(unsigned char command)
{
    TFTDC = 0;

    ST7789V_CTRL_Write(command);
        
    TFTWR = 0;
    TFTWR = 1;
}

void ST7789V_writeData(unsigned char data)
{
    TFTDC = 1;

    ST7789V_CTRL_Write(data);
    TFTWR = 0;
    TFTWR = 1;
}

void ST7789V_Init(void)
{

    TFTDC = 0;
    TFTRD = 1;
    TFTWR = 0;

    TFTRST = 0; // reset the chip[]
    GUI_X_Delay(100);
    TFTRST = 1; // take it out of reset
    GUI_X_Delay(100);

    ST7789V_writeCommand(0x11);    /* exit SLEEP mode*/

    GUI_X_Delay(300);
  

    ST7789V_writeCommand(0x36);
    ST7789V_writeData(0xA0);      /* MADCTL: memory data access control*/
    ST7789V_writeCommand(0x3A);
    ST7789V_writeData(0x65);      /* COLMOD: Interface Pixel format*/
    ST7789V_writeCommand(0xB2);
    ST7789V_writeData(0x0C);
    ST7789V_writeData(0x0C);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x33);
    ST7789V_writeData(0x33); /*PORCTRK: Porch setting*/
    ST7789V_writeCommand(0xB7);
    ST7789V_writeData(0x35); /*GCTRL: Gate Control*/
    ST7789V_writeCommand(0xBB);
    ST7789V_writeData(0x2B); /*VCOMS: VCOM setting*/
    ST7789V_writeCommand(0xC0);
    ST7789V_writeData(0x2C); /*LCMCTRL: LCM Control*/
    ST7789V_writeCommand(0xC2);
    ST7789V_writeData(0x01);
    ST7789V_writeData(0xFF); /*VDVVRHEN: VDV and VRH Command Enable*/
    ST7789V_writeCommand(0xC3);
    ST7789V_writeData(0x11); /*VRHS: VRH Set*/
    ST7789V_writeCommand(0xC4);
    ST7789V_writeData(0x20); /*VDVS: VDV Set*/

    ST7789V_writeCommand(0xC6);
    ST7789V_writeData(0x0F); /*FRCTRL2: Frame Rate control in normal mode*/
    ST7789V_writeCommand(0xD0);
    ST7789V_writeData(0xA4);
    ST7789V_writeData(0xA1); /*PWCTRL1: Power Control 1*/
    ST7789V_writeCommand(0xE0);
    ST7789V_writeData(0xD0);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x05);
    ST7789V_writeData(0x0E);
    ST7789V_writeData(0x15);
    ST7789V_writeData(0x0D);
    ST7789V_writeData(0x37);
    ST7789V_writeData(0x43);
    ST7789V_writeData(0x47);
    ST7789V_writeData(0x09);
    ST7789V_writeData(0x15);
    ST7789V_writeData(0x12);
    ST7789V_writeData(0x16);
    ST7789V_writeData(0x19); /*PVGAMCTRL: Positive Voltage Gamma control*/
    ST7789V_writeCommand(0xE1);
    ST7789V_writeData(0xD0);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x05);
    ST7789V_writeData(0x0D);
    ST7789V_writeData(0x0C);
    ST7789V_writeData(0x06);
    ST7789V_writeData(0x2D);
    ST7789V_writeData(0x44);
    ST7789V_writeData(0x40);
    ST7789V_writeData(0x0E);
    ST7789V_writeData(0x1C);
    ST7789V_writeData(0x18);
    ST7789V_writeData(0x16);
    ST7789V_writeData(0x19); /*NVGAMCTRL: Negative Voltage Gamma control*/
    ST7789V_writeCommand(0x2A);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x01);
    ST7789V_writeData(0x3F); /*X address set*/
    ST7789V_writeCommand(0x2B);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0x00);
    ST7789V_writeData(0xEF); /*Y address set*/

    GUI_X_Delay(10);
    ST7789V_writeCommand(0x29); /*Enable Display*/

}

void ST7789V_writeDataStream(unsigned char * pData, int numBytes)
{
    for(int i=0;i<numBytes;i++)
    {
        ST7789V_writeData(pData[i]);
    }
}

unsigned char ST7789V_readData()
{
    MBED_ASSERT(0); // This function should never be called by emWin
}
void ST7789V_readDataStream(unsigned char *data,int numItems)
{
    MBED_ASSERT(0); // This function should never be called by emWin
}