#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "helpers.h"
#include "shared.h"
#include "cmd_parser.h"
#define ACTION_HOLD 0
#define ACTION_RELEASE 1
#define ARG_QUEUE_SIZE 32
uint16_t gpio_pin_queue[ARG_QUEUE_SIZE];
GPIO_TypeDef* gpio_port_queue[ARG_QUEUE_SIZE];

int32_t fill_lookup(char* cmd, int32_t index)
{
  if(index >= ARG_QUEUE_SIZE)
    return 1;

  if(strncmp(cmd, "a", 1) == 0)
  {
    // puts("a button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }

  else if(strncmp(cmd, "b", 1) == 0)
  {
    // puts("b button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "x", 1) == 0)
  {
    // puts("x button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "y", 1) == 0)
  {
    // puts("y button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "du", 2) == 0)
  {
    // puts("up button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "dd", 2) == 0)
  {
    // puts("down button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "dl", 2) == 0)
  {
    // puts("left button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "dr", 2) == 0)
  {
    // puts("right button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "ls", 2) == 0)
  {
    // puts("L button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "rs", 2) == 0)
  {
    // puts("R button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "zl", 2) == 0)
  {
    // puts("ZL button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "zr", 2) == 0)
  {
    // puts("ZR button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "sl", 2) == 0)
  {
    // puts("SL button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "sr", 2) == 0)
  {
    // puts("SR button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "sbl", 3) == 0)
  {
    // puts("SBL button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "sbr", 3) == 0)
  {
    // puts("SBR button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "syncl", 5) == 0)
  {
    // puts("SYNCL button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "syncr", 5) == 0)
  {
    // puts("SYNCR button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "+", 1) == 0)
  {
    // puts("PLUS button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "-", 1) == 0)
  {
    // puts("MINUS button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "h", 1) == 0)
  {
    // puts("HOME button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else if(strncmp(cmd, "cap", 3) == 0)
  {
    // puts("CAPTURE button");
    gpio_port_queue[index] = DEBUG_LED_GPIO_Port;
    gpio_pin_queue[index] = DEBUG_LED_Pin;
  }
  else
  {
    return 1;
  }
  return 0;
}

char* goto_next_arg(char* buf)
{
  char* curr = buf;
  if(curr == NULL)
    return NULL;
  char* buf_end = curr + strlen(curr);
  if(curr >= buf_end)
    return NULL;
  while(curr < buf_end && *curr != ' ')
      curr++;
  while(curr < buf_end && *curr == ' ')
      curr++;
  if(curr >= buf_end)
    return NULL;
  return curr;
}

int32_t process_multiarg(char* args)
{
  char* arg_ptr = args;
  int32_t count = 0;
  memset(gpio_port_queue, 0, ARG_QUEUE_SIZE * sizeof(GPIO_TypeDef*));
  memset(gpio_pin_queue, 0, ARG_QUEUE_SIZE * sizeof(uint16_t));
  while(1)
  {
    arg_ptr = goto_next_arg(arg_ptr);
    if(arg_ptr == NULL)
      break;
    if(fill_lookup(arg_ptr, count) == 0)
      count++;
    else
      return 1;
  }
  if(count <= 0)
    return 1;
  return 0;
}

void button_ctrl(int32_t action)
{
  for(int i = 0; i < ARG_QUEUE_SIZE; ++i)
  {
    if(gpio_port_queue[i] != NULL)
    {
      if(action == ACTION_HOLD)
        HAL_GPIO_WritePin(gpio_port_queue[i], gpio_pin_queue[i], GPIO_PIN_RESET);
      else
        HAL_GPIO_WritePin(gpio_port_queue[i], gpio_pin_queue[i], GPIO_PIN_SET);
    }
  }
}

void parse_cmd(char* cmd)
{
  if(strcmp(cmd, "test") == 0)
    puts("test OK");
  // button hold, multiple args allowed
  else if(strncmp(cmd, "bh ", 3) == 0)
  {
    if(process_multiarg(cmd) != 0)
    {
      puts("bh ERROR");
      return;
    }
    button_ctrl(ACTION_HOLD);
    puts("bh OK");
  }
  // button release, multiple args allowed
  else if(strncmp(cmd, "br ", 3) == 0)
  {
    if(process_multiarg(cmd) != 0)
    {
      puts("br ERROR");
      return;
    }
    button_ctrl(ACTION_RELEASE);
    puts("br OK");
  }
  // button release all
  else if(strcmp(cmd, "br") == 0)
  {
    puts("bra OK");
  }
  // stick hold, sh x y, x and y from 0 to 255
  else if(strncmp(cmd, "sh ", 3) == 0)
  {
    char* x_ptr = goto_next_arg(cmd);
    char* y_ptr = goto_next_arg(x_ptr);
    uint32_t x_8b = atoi(x_ptr);
    uint32_t y_8b = atoi(y_ptr);
    uint32_t x_12b = (uint32_t)((float)x_8b * 8.76);
    uint32_t y_12b = (uint32_t)((float)y_8b * 8.76);
    if(x_ptr == NULL || y_ptr == NULL || x_8b > 255 || y_8b > 255)
    {
      puts("sh ERROR");
      return;
    }
    if(stm32_dac_ptr->State == HAL_DAC_STATE_RESET)
      stm32_dac_init();
    HAL_DACEx_DualSetValue(stm32_dac_ptr, DAC_ALIGN_12B_R, x_12b, y_12b);
    puts("sh OK");
  }
  // stick release, to netural position 
  else if(strcmp(cmd, "sr") == 0)
  {
    if(stm32_dac_ptr->State == HAL_DAC_STATE_RESET)
      stm32_dac_init();
    HAL_DACEx_DualSetValue(stm32_dac_ptr, DAC_ALIGN_12B_R, 1117, 1117);
    puts("sr OK");
  }
  // stick disengage, gives control back to user
  else if(strcmp(cmd, "sd") == 0)
  {
    HAL_DAC_Stop(stm32_dac_ptr, DAC_CHANNEL_1);
    HAL_DAC_Stop(stm32_dac_ptr, DAC_CHANNEL_2);
    HAL_DAC_DeInit(stm32_dac_ptr);
    puts("sd OK");
  }
  else
  {
    puts("?");
  }
}