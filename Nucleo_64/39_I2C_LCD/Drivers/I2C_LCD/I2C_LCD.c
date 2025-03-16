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
}I2C_LCD_InfoParam_t;

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
    I2C_LCD_ExpandedWrite(I2C_LCD_InstanceIndex, Val);
    I2C_LCD_EnPulse(I2C_LCD_InstanceIndex, Val);
}

static void I2C_LCD_Send(uint8_t I2C_LCD_InstanceIndex, uint8_t Val, uint8_t Mode)
{
    uint8_t HighNib = Val & 0xF0;
    uint8_t LowNib = (Val << 4) & 0xF0;
    I2C_LCD_Write4Bits(I2C_LCD_InstanceIndex, (HighNib) | Mode);
    I2C_LCD_Write4Bits(I2C_LCD_InstanceIndex, (LowNib) | Mode);   
}

static void I2C_LCD_Cmd(uint8_t I2C_LCD_InstanceIndex, uint8_t CMD)
{
    I2C_LCD_Send(I2C_LCD_InstanceIndex, CMD, 0);
}

static void I2C_LCD_Data(uint8_t I2C_LCD_InstanceIndex, uint8_t DATA)
{
    I2C_LCD_Send(I2C_LCD_InstanceIndex, DATA, 1);
}

///////////////////////////////////////////////////////////////////////
/////////_USER EXTERNAL FUNCTIONS_/////////////////////////////////////

void I2C_LCD_Init(uint8_t I2C_LCD_InstanceIndex)
{
//Acc. to datasheet we must wait at least 40ms after powerUp before interacting with the LCD module
while(HAL_GetTick() < 50);
I2C_LCD_Cmd(I2C_LCD_InstanceIndex, 0x30);
DELAY_MS(5);    //Delay > 4,1ms
I2C_LCD_Cmd(I2C_LCD_InstanceIndex, 0x30);
DELAY_MS(5);    //Delay > 4,1ms
I2C_LCD_Cmd(I2C_LCD_InstanceIndex, 0x30);
DELAY_MS(150);    //Delay > 4,1ms
I2C_LCD_Cmd(I2C_LCD_InstanceIndex, 0x02);

//Configure the LCD
I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_FUNTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5X8DOTS);
I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
I2C_LCD_InfoParam_g[I2C_LCD_InstanceIndex].DisplayCtrl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
I2C_LCD_InfoParam_g[I2C_LCD_InstanceIndex].BackLightVal = LCD_BACKLIGHT;

//Clear the LCD
I2C_LCD_Clear(I2C_LCD_InstanceIndex);
}

void I2C_LCD_Clear(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_CLEARDISPLAY);
    DELAY_MS(2);
}

void I2C_LCD_Home(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_RETURNHOME);

}

void I2C_LCD_SetCursor(uint8_t I2C_LCD_InstanceIndex, uint8_t Col, uint8_t Row)
{
    int Row_Offsets[] = {0x00, 0x40, 0x14, 0x54};
    if(Row > I2C_LCD_CfgParam[I2C_LCD_InstanceIndex].I2C_LCD_nRow)
    {
        Row = I2C_LCD_CfgParam[I2C_LCD_InstanceIndex].I2C_LCD_nRow - 1;
    }
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex,LCD_SETDDRAMADDR | (Col + Row_Offsets[Row]));
}

void I2C_LCD_WriteChar(uint8_t I2C_LCD_InstanceIndex, char Ch)
{
    I2C_LCD_Data(I2C_LCD_InstanceIndex, Ch);
}

void I2C_LCD_WriteString(uint8_t I2C_LCD_InstanceIndex, char *Str)
{
    while(*Str)
    {
        I2C_LCD_Data(I2C_LCD_InstanceIndex, *Str++);
    }
}

void I2C_LCD_ShiftLeft(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void I2C_LCD_ShiftRight(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void I2C_LCD_Backlight(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].BackLight = LCD_BACKLIGHT;
    I2C_LCD_ExpandedWrite(I2C_LCD_InstanceIndex, 0);
}

void I2C_LCD_NoBacklight(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].BackLight = LCD_NOBACKLIGHT;
    I2C_LCD_ExpandedWrite(I2C_LCD_InstanceIndex, 0);
}

void I2C_LCD_Display(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl |= LCD_DISPLAYON;
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_DISPLAYCONTROL | I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl);
}

void I2C_LCD_NoDisplay(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DispalyCtrl &= ~LCD_DISPLAYON;
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_DISPLAYCONTROL | I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl);
}

void I2C_LCD_Cursor(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl |= LCD_CURSORON;
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_DISPLAYCONTROL | I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl);
}

void I2C_LCD_NoCursor(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl &= ~LCD_CURSORON;
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_DISPLAYCONTROL | I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl);
}

void I2C_LCD_Blink(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl |= LCD_BLINKON;
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_DISPLAYCONTROL | I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl);
}

void I2C_LCD_NoBlink(uint8_t I2C_LCD_InstanceIndex)
{
    I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl &= ~LCD_BLINKON;
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_DISPLAYCONTROL | I2C_LCD_CfgParam_g[I2C_LCD_InstanceIndex].DisplayCtrl);
}

void I2C_LCD_CreateCustomChar(uint8_t I2C_LCD_InstanceIndex, uint8_t CharIndex, const uint8_t* CharMap)
{
    CharIndex &= 0x07;
    I2C_LCD_Cmd(I2C_LCD_InstanceIndex, LCD_SETCGRAMADDR | (CharIndex << 3));
    for(int i = 0 ; i < 8 ; i++)
    {
        I2C_LCD_Send(I2C_LCD_InstanceIndex, CharMap[i], RS);
    }
}

void I2C_LCD_PrintCustomChar(uint8_t I2C_LCD_InstanceIndex, uint8_t CharIndex)
{
    I2C_LCD_Send(I2C_LCD_InstanceIndex, CharIndex, RS);
}