#include "I2C_LCD.h"
#include "I2C_LCD_cfg.h"
#include "../Util/Util.h"

/////////_INTERNAL DEFINITIONS_////////////////////////////////////////
//CMD
#define LCD_CLEARDISPLAY        0x01    
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNTIONSET          0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80
//DISPLAY ENTRY
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00
//DISPLAY CONTROL
#define LCD_DISPLAYON           0x04
#define LCD_DISPLAYOFF          0x00
#define LCD_CURSORON            0x02
#define LCD_CURSOROFF           0x00
#define LCD_BLINKON             0x01
#define LCD_BLINKOFF            0x00
//CURSOR MOTION
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00
//FUNCTION SET
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5X10DOTS            0x04
#define LCD_5X8DOTS             0x00
//BACKLIGHT CONTROL
#define LCD_BACKLIGHT           0x08
#define LCD_NOBACKLIGHT         0x00
#define LCD_EN                  0b00000100  //Enable bit
#define LCD_RW                  0b00000010  //ReadWrite bit
#define LCD_RS                  0b00000001  //Register select bit

/////////_INTERNAL VARIABLES_//////////////////////////////////////////

typedef struct I2C_LCD_InfoParam_s
{
    uint8_t DisplayCtrl;
    uint8_t BacklightVal;
}I2C_LCD_InforParam_t;

static I2C_LCD_InfoParam_t I2C_LCD_InfoParam_g[I2C_LCD_MAX];

///////////////////////////////////////////////////////////////////////
/////////_STATIC INTERNAL FUNTIONS_////////////////////////////////////

static void I2C_LCD_ExpandedWrite(uint8_t I2C_LCD_InstanceIndex, uint8_t DATA)
{
    uint8_t TxData = (DATA) | I2C_LCD_InfoParam_g[I2C_LCD_InstanceIndex].BacklightVal;
    HAL_I2C_Master_Transmit(I2C_LCD_CfgParam[I2C_LCD_InstanceIndex].I2C_Handle, (I2C_LCD_CfgParam[I2C_LCD_InstanceIndex].I2C_LCD_Adress<<1), &TxData, sizeof(TxData), 100);
}

static void I2C_LCD_EnPulse(uint8_t I2C_LCD_InstanceIndex, uint8_t DATA)
{
    I2C_LCD_ExpandedWrite(I2C_LCD_InstanceIndex, (DATA | EN));  //En high
    DELAY_US(2);    //enable pulse must be >450ns

    I2C_LCD_ExpandedWrite(I2C_LCD_InstanceIndex, (DATA & ~EN));  //En low
    DELAY_US(50);    //commands need >37us to settle
}

static void I2C_LCD_Write4Bits(uint8_t I2C_LCD_InstanceIndex, uint8_t Val)
{
    I2C_LCD_ExpandedWrite(uint8_t I2C_LCD_InstanceIndex, Val);
    I2C_LCD_EnPulse(uint8_t I2C_LCD_InstanceIndex, Val);
}

static void I2C_LCD_Send(uint8_t I2C_LCD_InstanceIndex, uint8_t Val, uint8_t Mode)
{
    uint8_t HighNib = Val & 0xF0;
    uint8_t LowNib = (Val << 4) & 0xF0;
    I2C_LCD_Write4Bits(uint8_t I2C_LCD_InstanceIndex, (HighNib) | Mode);
    I2C_LCD_Write4Bits(uint8_t I2C_LCD_InstanceIndex, (LowNib) | Mode);   
}

static void I2C_LCD_Cmd(uint8_t I2C_LCD_InstanceIndex, uint8_t CMD)
{
    I2C_LCD_Send(uint8_t I2C_LCD_InstanceIndex, CMD, 0);
}

static void I2C_LCD_Data(uint8_t I2C_LCD_InstanceIndex, uint8_t DATA)
{
    I2C_LCD_Send(uint8_t I2C_LCD_InstanceIndex, DATA, 1);
}

///////////////////////////////////////////////////////////////////////
/////////_USER EXTERNAL FUNCTIONS_/////////////////////////////////////

void I2C_LCD_Init(uint8_t I2C_LCD_InstanceIndex)
{

}