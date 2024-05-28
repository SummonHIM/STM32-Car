#include <stdio.h>
#include "oled.h"
#include "adc.h"
#include "font.h"
#include "sr04.h"

//
void oled_write_command(uint8_t command) // OLEDд����
{
  i2c_start();         // I2C�����ź�
  i2c_send_byte(0x78); // ������SDA������д��ͨ�Ŵӻ�0LED��ַ0X78
  i2c_wait_ack();      // �����ȴ�Ӧ���ź�

  i2c_send_byte(0x00);    // I2C��������Ĵ�����ַ��0��
  i2c_wait_ack();         // �����ȴ�Ӧ���ź�
  i2c_send_byte(command); // I2C��������
  i2c_wait_ack();         // �����ȴ�Ӧ���ź�
  i2c_stop();             // I2C�����ź�
}

//
void oled_write_data(uint8_t data) // OLEDд����
{
  i2c_start();
  i2c_send_byte(0x78);
  i2c_wait_ack();

  i2c_send_byte(0x40);
  i2c_wait_ack();
  i2c_send_byte(data);
  i2c_wait_ack();
  i2c_stop();
}

//
void oled_display_on(void) // OLED��ʾ
{
  oled_write_command(0x8D); // ��ʾ����
  oled_write_command(0x14); // ������ɱ�
  oled_write_command(0xAF);
}

//
void oled_display_off(void) // OLED�ر�
{
  oled_write_command(0x8D);
  oled_write_command(0x10);
  oled_write_command(0xAE);
}

// x:0-127
// y:0-3
void oled_set_pos(uint8_t x, uint8_t y) // ����OLED��ʾλ��
{
  oled_write_command(0xb0 + y);
  oled_write_command(((x & 0xf0) >> 4) | 0x10);
  oled_write_command((x & 0x0f));
}

//
void oled_clear(void) // OLED����
{
  uint8_t i, n;

  for (i = 0; i < 8; i++) {
    oled_write_command(0xb0 + i);
    oled_write_command(0x00);
    oled_write_command(0x10);
    for (n = 0; n < 128; n++) {
      oled_write_data(0);
    }
  }
}

//
void oled_show_char(uint8_t x, uint8_t y, uint8_t chr) // OLED��ʾ�ַ�
{
  uint8_t c = 0, i = 0;
  c = chr - ' ';

  if (x > Max_Column - 1) // 128-1
  {
    x = 0;
    y = y + 2;
  }

  oled_set_pos(x, y);
  for (i = 0; i < 8; i++)
    oled_write_data(
        F8X16[c * 16 + i]); // дһ���ֽ�  (һ��1608 Ӣ���ַ����ߣ�16bit
                            // ����8bit,һ���ֽ� 8bit,һ����16�ֽ�.

  oled_set_pos(x, y + 1);
  for (i = 0; i < 8; i++)
    oled_write_data(F8X16[c * 16 + i + 8]);
}

//
void oled_show_string(uint8_t line, uint8_t *chr) // OLED��ʾ�ַ���
{
  unsigned char index = 0;
  unsigned char xpos = 0;

  while (chr[index] != 0) {
    oled_show_char(xpos, line, chr[index]);

    xpos += 8;

    if (xpos >= 128) {
      break;
    }

    index++;
  }
}

void oled_show_CH_char(uint8_t x, uint8_t y,
                       uint8_t chr) // OLED��ʾ�����ַ� 16*16,�贫��32�ֽڵ�����
{
  uint8_t i = 0;
  //    c = chr - ' ';

  if (x > Max_Column - 1) // 128-1
  {
    x = 0;
    y = y + 2;
  }

  oled_set_pos(x, y);
  for (i = 0; i < 16; i++)
    oled_write_data(Hzk1[chr][i]); // дһ���ֽ�

  oled_set_pos(x, y + 1);
  for (i = 0; i < 16; i++)
    oled_write_data(Hzk1[chr][i + 16]);
}

//
void oled_pin_config(void) // OLED��������
{
  GPIO_InitTypeDef GPIO_Init;

  __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_Init.Pin = OLED_SDA_PIN;
  GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_Init.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(OLED_SDA_PORT, &GPIO_Init);

  GPIO_Init.Pin = OLED_SCL_PIN;
  GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_Init.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(OLED_SCL_PORT, &GPIO_Init);

  GPIO_Init.Pin = OLED_PWR_PIN;
  GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_Init.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(OLED_PWR_PORT, &GPIO_Init);
}

//
void oled_init(void) // OLED��ʼ��
{
  oled_pin_config();
  HAL_Delay(10);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
  HAL_Delay(100);

  oled_write_command(0xAE);

  oled_write_command(0x00);
  oled_write_command(0x10);

  oled_write_command(0x40);
  oled_write_command(0x81);

  oled_write_command(0xCF);
  oled_write_command(0xA1);

  oled_write_command(0xC8);

  oled_write_command(0xA6);
  oled_write_command(0xA8);

  oled_write_command(0x3F);
  oled_write_command(0xD3);

  oled_write_command(0x00);
  oled_write_command(0xD5);
  oled_write_command(0x80);

  oled_write_command(0xD9);
  oled_write_command(0xF1);
  oled_write_command(0xDA);
  oled_write_command(0x12);
  oled_write_command(0xDB);
  oled_write_command(0x40);

  oled_write_command(0x20);
  oled_write_command(0x02);
  oled_write_command(0x8D);
  oled_write_command(0x14);
  oled_write_command(0xA4);
  oled_write_command(0xA6);

  oled_clear();
  oled_write_command(0xAF);

  HAL_Delay(100);
}
// void oled_init(void)//OLED��ʼ��
//{
//     oled_pin_config();
//     HAL_Delay(10);

//    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET );
//    HAL_Delay(100);

//    oled_write_command(0xAE);

//    oled_write_command(0xD5);
//    oled_write_command(0x80);

//    oled_write_command(0xA8);
//    oled_write_command(0x1F);

//    oled_write_command(0xD3);
//    oled_write_command(0x00);

//    oled_write_command(0x40);

//    oled_write_command(0x8D);
//    oled_write_command(0x14);

//    oled_write_command(0xA1);
//    oled_write_command(0xC8);

//    oled_write_command(0xDA);
//    oled_write_command(0x00);
//    oled_write_command(0x81);

//    oled_write_command(0x8F);
//    oled_write_command(0xD9);
//    oled_write_command(0x1F);
//    oled_write_command(0xDB);
//    oled_write_command(0x40);
//    oled_write_command(0xA4);

//    oled_clear();
//    oled_write_command(0xAF);

//    HAL_Delay(100);
//}

void OLED_Disp_CarInfo(float CCM, uint8_t Mode) {
  char strADCVoltage[20] = {0};
  char strSR04Dist[20] = {0};
  char strMode[20] = {0};

  sprintf(strADCVoltage, "V: %.2fv", ADC_GetVoltage());
  sprintf(strSR04Dist, "Dist: %.2fcm", SR04_Dist(CCM));
  sprintf(strMode, "Mode: %d", Mode);
  oled_show_string(1, (uint8_t *)strADCVoltage);
  oled_show_string(3, (uint8_t *)strSR04Dist);
  oled_show_string(5, (uint8_t *)strMode);
}