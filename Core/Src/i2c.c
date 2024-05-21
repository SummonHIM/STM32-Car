

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
void i2c_start(void) // I2C起始信号
{
  sda_output(1);      // SDA=1
  delay1(DELAY_TIME); // 延时2us
  scl_output(1);      // SCL=1
  delay1(DELAY_TIME); // 延时2us
  sda_output(0);      // SDA=0,保证SDA下降沿信号
  delay1(DELAY_TIME);
  scl_output(0); // SCL=0
  delay1(DELAY_TIME);
}

//
void i2c_stop(void) // I2C停止信号
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
unsigned char i2c_wait_ack(void) // 主机等待应答信号
{
  unsigned short cErrTime = 5;

  sda_mode_input(); // 读取SDA引脚状态
  delay1(DELAY_TIME);
  scl_output(1); // SCL=1
  delay1(DELAY_TIME);
  while (sda_input()) // 如果读取SDA=1,非应答信号
  {
    cErrTime--;
    delay1(DELAY_TIME);
    if (0 == cErrTime) // 延时等待后
    {
      sda_mode_output(); // 输出模式
      i2c_stop();        // 停止I2C
      return ERROR;
    }
  }
  sda_mode_output(); // 输出模式
  scl_output(0);     // SCL=0
  delay1(DELAY_TIME);
  return SUCCESS;
}

//
void i2c_send_ack(void) // 主机发送应答信号
{
  sda_output(
      0); // 输出 发送SDA=0即ACK=0，表明主机成功接收，发送给从机ACK=0的应答信号
  delay1(DELAY_TIME);
  delay1(DELAY_TIME);
  scl_output(1); // SCL=1
  delay1(DELAY_TIME);
  scl_output(0); // SCL=0
  delay1(DELAY_TIME);
}

//
void i2c_send_noack(void) // 主机发送非应答信号
{
  sda_output(1);
  delay1(
      DELAY_TIME); // 输出
                   // 发送SDA=1即ACK=1，表明主机未成功接收，发送给从机ACK=1的非应答信号
  scl_output(1);
  delay1(DELAY_TIME);
  scl_output(0);
  delay1(DELAY_TIME);
}

//
void i2c_send_byte(unsigned char cSendByte) // 主机I2C发送1个字节
{
  unsigned char i = 8;
  while (i--) {
    scl_output(0); // SCL=0
    delay1(DELAY_TIME);
    sda_output(cSendByte & 0x80); // 最高位先发送
    delay1(DELAY_TIME);
    cSendByte += cSendByte; // 乘以2，相当于cSendByte左移了1位
    delay1(DELAY_TIME);
    scl_output(1); // SCL=1
    delay1(DELAY_TIME);
  }
  scl_output(0); // 1个字节发送完，SCL=0
  delay1(DELAY_TIME);
}

//
unsigned char i2c_receive_byte(void) // 主机经I2C接收1个字节
{
  unsigned char i = 8;
  unsigned char cR_Byte = 0;

  sda_mode_input(); // 输入模式
  while (i--) {
    cR_Byte += cR_Byte; // cR_Byte =2cR_Byte ,cR_Byte 左移了1位
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
