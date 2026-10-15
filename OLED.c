#include "OLED.h"
#include "OLED_Font.h"

void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_WriteData(uint8_t Data);
void OLED_I2C_Init(void);

void OLED_I2C_Start(void);
void OLED_I2C_Stop(void);

void OLED_I2C_SendByte(uint8_t Byte);

void OLED_Init(void);
void OLED_WriteCommand(uint8_t Command);

void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
static void OLED_ShowUnsignedBase(uint8_t Line,
                                  uint8_t Column,
                                  uint32_t Number,
                                  uint8_t Length,
                                  uint8_t Base);
void OLED_ShowNum(uint8_t Line, uint8_t Column,
                  uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column,
                        int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column,
                     uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column,
                     uint32_t Number, uint8_t Length);

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);

void OLED_Clear(void);

#define OLED_W_SCL(x) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (x)?GPIO_PIN_SET:GPIO_PIN_RESET)
#define OLED_W_SDA(x) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (x)?GPIO_PIN_SET:GPIO_PIN_RESET)

void OLED_I2C_Init(void)
{
    OLED_W_SCL(1);
    OLED_W_SDA(1);
}

void OLED_I2C_Start(void)
{
    OLED_W_SDA(1);
    OLED_W_SCL(1);
    OLED_W_SDA(0);
    OLED_W_SCL(0);
}

void OLED_I2C_Stop(void)
{
    OLED_W_SDA(0);
    OLED_W_SCL(1);
    OLED_W_SDA(1);
}

void OLED_I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        OLED_W_SDA(Byte & (0x80>>i));
        OLED_W_SCL(1);
        OLED_W_SCL(0);
    }
    OLED_W_SCL(1);
    OLED_W_SCL(0);
}

void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//????
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//?????
	
	OLED_WriteCommand(0xAE);	//????
	
	OLED_WriteCommand(0xD5);	//?????????/?????
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//???????
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//??????
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//???????
	
	OLED_WriteCommand(0xA1);	//??????,0xA1?? 0xA0????
	
	OLED_WriteCommand(0xC8);	//??????,0xC8?? 0xC0????

	OLED_WriteCommand(0xDA);	//??COM??????
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//???????
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//???????
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//??VCOMH??????
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//????????/??

	OLED_WriteCommand(0xA6);	//????/????

	OLED_WriteCommand(0x8D);	//?????
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//????
		
	OLED_Clear();				//OLED??
}


void OLED_WriteCommand(uint8_t Command)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(0x78);
    OLED_I2C_SendByte(0x00);
    OLED_I2C_SendByte(Command);
    OLED_I2C_Stop();
}
/**
 * ?????
 * Line?Column ?????? OLED_ShowChar ??
 * ?????,???????????
 */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    if (String == 0)
    {
        return;
    }

    while (*String != '\0')
    {
        OLED_ShowChar(Line, Column, *String);
        String++;
        Column++;
    }
}

/**
 * ??????:????????????????
 * ????? 0,?????????
 * ??? OLED.h ???
 */
static void OLED_ShowUnsignedBase(uint8_t Line,
                                  uint8_t Column,
                                  uint32_t Number,
                                  uint8_t Length,
                                  uint8_t Base)
{
    static const char Digits[] = "0123456789ABCDEF";
    char Buffer[32];
    uint8_t i;

    if ((Length == 0U) || (Length > 32U) ||
        (Base < 2U) || (Base > 16U))
    {
        return;
    }

    /* ????????,??????? */
    for (i = 0U; i < Length; i++)
    {
        Buffer[Length - 1U - i] = Digits[Number % Base];
        Number /= Base;
    }

    /* ???????? */
    for (i = 0U; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Buffer[i]);
    }
}

/**
 * ?????????
 * Length:1~10
 * ??:123,?? 5 -> 00123
 */
void OLED_ShowNum(uint8_t Line, uint8_t Column,
                  uint32_t Number, uint8_t Length)
{
    if ((Length == 0U) || (Length > 10U))
    {
        return;
    }

    OLED_ShowUnsignedBase(Line, Column, Number, Length, 10U);
}

/**
 * ?????????
 * Length:???????,1~10,?????
 * ?????:Length + 1
 * ?????? +,???? -
 */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column,
                        int32_t Number, uint8_t Length)
{
    uint32_t Magnitude;

    if ((Length == 0U) || (Length > 10U))
    {
        return;
    }

    if (Number < 0)
    {
        OLED_ShowChar(Line, Column, '-');

        /* ????? INT32_MIN ?????? */
        Magnitude = (uint32_t)(-(Number + 1)) + 1U;
    }
    else
    {
        OLED_ShowChar(Line, Column, '+');
        Magnitude = (uint32_t)Number;
    }

    OLED_ShowUnsignedBase(Line, Column + 1U,
                          Magnitude, Length, 10U);
}

/**
 * ???????
 * Length:1~8,??? 0x ??
 * ??:0x1AF,?? 4 -> 01AF
 */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column,
                     uint32_t Number, uint8_t Length)
{
    if ((Length == 0U) || (Length > 8U))
    {
        return;
    }

    OLED_ShowUnsignedBase(Line, Column, Number, Length, 16U);
}

/**
 * ??????
 * Length:1~32,??? 0b ??
 * ??????????????????
 */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column,
                     uint32_t Number, uint8_t Length)
{
    if ((Length == 0U) || (Length > 32U))
    {
        return;
    }

    OLED_ShowUnsignedBase(Line, Column, Number, Length, 2U);
}

/**
 * ??????:128×64 OLED,8×16 ??
 * Line:1~4
 * Column:1~16
 * ??:OLED_F8x16,? ASCII ???????
 * OLED_SetCursor ????:??????????
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    uint8_t Index;

    if ((Line < 1U) || (Line > 4U) ||
        (Column < 1U) || (Column > 16U))
    {
        return;
    }

    /* ???? ASCII ??????? */
    if ((Char < ' ') || (Char > '~'))
    {
        Char = '?';
    }

    Index = (uint8_t)(Char - ' ');

    /* ?????? */
    OLED_SetCursor((Line - 1U) * 2U,
                   (Column - 1U) * 8U);

    for (i = 0U; i < 8U; i++)
    {
        OLED_WriteData(OLED_F8x16[Index][i]);
    }

    /* ?????? */
    OLED_SetCursor((Line - 1U) * 2U + 1U,
                   (Column - 1U) * 8U);

    for (i = 0U; i < 8U; i++)
    {
        OLED_WriteData(OLED_F8x16[Index][i + 8U]);
    }
}

/**
 * OLED ??????????
 * ????? HAL GPIO ?? I2C ??
 */
void OLED_WriteData(uint8_t Data)
{
    OLED_I2C_Start();

    OLED_I2C_SendByte(0x78);  /* OLED ???:7??? 0x3C ??1? */
    OLED_I2C_SendByte(0x40);  /* ????:??????? */
    OLED_I2C_SendByte(Data);

    OLED_I2C_Stop();
}

/**
 * ????:??? SSD1306 ??????
 * Y:???,0~7,???8??
 * X:??????,0~127
 * ??????? Y?X,?????? ShowChar ??
 */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    if ((Y > 7U) || (X > 127U))
    {
        return;
    }

    OLED_WriteCommand((uint8_t)(0xB0U | Y));
    OLED_WriteCommand((uint8_t)(0x10U | ((X >> 4) & 0x0FU)));
    OLED_WriteCommand((uint8_t)(X & 0x0FU));
}
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

