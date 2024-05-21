

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* USER CODE BEGIN 0 */
#define DELAY_TIME 2

//
static void delay1(unsigned int n) {
  unsigned int i;
  for (i = 0; i < n; ++i)
    ;
}

void sda_mode_input(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void sda_mode_output(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void sda_output(uint16_t val) {
  if (val) {
    HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_RESET);
  }
}
void scl_output(uint16_t val) {
  if (val) {
    HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET);

  } else {
    HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET);
  }
}

uint8_t sda_input(void) {
  return (HAL_GPIO_ReadPin(OLED_SDA_PORT, OLED_SDA_PIN));
}

//
void i2c_start(void) // I2C��ʼ�ź�
{
  sda_output(1);      // SDA=1
  delay1(DELAY_TIME); // ��ʱ2us
  scl_output(1);      // SCL=1
  delay1(DELAY_TIME); // ��ʱ2us
  sda_output(0);      // SDA=0,��֤SDA�½����ź�
  delay1(DELAY_TIME);
  scl_output(0); // SCL=0
  delay1(DELAY_TIME);
}

//
void i2c_stop(void) // I2Cֹͣ�ź�
{
  scl_output(0); // SCL=0
  delay1(DELAY_TIME);
  sda_output(0); // SDA=0
  delay1(DELAY_TIME);
  scl_output(1); // SCL=1
  delay1(DELAY_TIME);
  sda_output(1); // SDA=1
  delay1(DELAY_TIME);
}

//
unsigned char i2c_wait_ack(void) // �����ȴ�Ӧ���ź�
{
  unsigned short cErrTime = 5;

  sda_mode_input(); // ��ȡSDA����״̬
  delay1(DELAY_TIME);
  scl_output(1); // SCL=1
  delay1(DELAY_TIME);
  while (sda_input()) // �����ȡSDA=1,��Ӧ���ź�
  {
    cErrTime--;
    delay1(DELAY_TIME);
    if (0 == cErrTime) // ��ʱ�ȴ���
    {
      sda_mode_output(); // ���ģʽ
      i2c_stop();        // ֹͣI2C
      return ERROR;
    }
  }
  sda_mode_output(); // ���ģʽ
  scl_output(0);     // SCL=0
  delay1(DELAY_TIME);
  return SUCCESS;
}

//
void i2c_send_ack(void) // ��������Ӧ���ź�
{
  sda_output(
      0); // ��� ����SDA=0��ACK=0�����������ɹ����գ����͸��ӻ�ACK=0��Ӧ���ź�
  delay1(DELAY_TIME);
  delay1(DELAY_TIME);
  scl_output(1); // SCL=1
  delay1(DELAY_TIME);
  scl_output(0); // SCL=0
  delay1(DELAY_TIME);
}

//
void i2c_send_noack(void) // �������ͷ�Ӧ���ź�
{
  sda_output(1);
  delay1(
      DELAY_TIME); // ���
                   // ����SDA=1��ACK=1����������δ�ɹ����գ����͸��ӻ�ACK=1�ķ�Ӧ���ź�
  scl_output(1);
  delay1(DELAY_TIME);
  scl_output(0);
  delay1(DELAY_TIME);
}

//
void i2c_send_byte(unsigned char cSendByte) // ����I2C����1���ֽ�
{
  unsigned char i = 8;
  while (i--) {
    scl_output(0); // SCL=0
    delay1(DELAY_TIME);
    sda_output(cSendByte & 0x80); // ���λ�ȷ���
    delay1(DELAY_TIME);
    cSendByte += cSendByte; // ����2���൱��cSendByte������1λ
    delay1(DELAY_TIME);
    scl_output(1); // SCL=1
    delay1(DELAY_TIME);
  }
  scl_output(0); // 1���ֽڷ����꣬SCL=0
  delay1(DELAY_TIME);
}

//
unsigned char i2c_receive_byte(void) // ������I2C����1���ֽ�
{
  unsigned char i = 8;
  unsigned char cR_Byte = 0;

  sda_mode_input(); // ����ģʽ
  while (i--) {
    cR_Byte += cR_Byte; // cR_Byte =2cR_Byte ,cR_Byte ������1λ
    scl_output(0);      // SCL=0
    delay1(DELAY_TIME);
    delay1(DELAY_TIME);
    scl_output(1); // SCL=1
    delay1(DELAY_TIME);
    cR_Byte |= sda_input(); // cR_Byte=sda_input()|cR_Byte
  }
  scl_output(0); // SCL=0
  delay1(DELAY_TIME);
  sda_mode_output();

  return cR_Byte;
}
