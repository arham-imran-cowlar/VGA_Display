/*
	Author: bitluni 2019
	License: 
	Creative Commons Attribution ShareAlike 4.0
	https://creativecommons.org/licenses/by-sa/4.0/
	
	For further details check out: 
		https://youtube.com/bitlunislab
		https://github.com/bitluni
		http://bitluni.net
*/

#pragma once
#include "driver/gpio.h"
#include "rom/ets_sys.h"
#define HIGH (uint32_t) 1
#define LOW (uint32_t) 0
const int MAX_CONTROLLERS = 10;
  
class GameControllers
{
  public:

  enum Type
  {
    NES = 0,
    SNES = 1,
  };

  enum Button
  {
    B = 0,
    Y = 1,
    SELECT = 2,
    START = 3,
    UP = 4,
    DOWN = 5,
    LEFT = 6,
    RIGHT = 7,
    A = 8,
    X = 9,
    L = 10,
    R = 11,
  };

  Type types[MAX_CONTROLLERS];
  int latchPin;
  int clockPin;
  int dataPins[MAX_CONTROLLERS];
  int buttons[MAX_CONTROLLERS][12];

  ///This has to be initialized once for the shared pins latch and clock
  void init(int latch, int clock)
  {
    latchPin = latch;
    clockPin = clock;
    gpio_set_direction((gpio_num_t)latchPin, GPIO_MODE_OUTPUT); //pinMode(latchPin, OUTPUT);
    gpio_set_level((gpio_num_t)latchPin, HIGH); //digitalWrite(latchPin, LOW);
    gpio_set_direction((gpio_num_t)clockPin, GPIO_MODE_OUTPUT); //pinMode(clockPin, OUTPUT);
    gpio_set_level((gpio_num_t)clockPin, HIGH); //digitalWrite(clockPin, HIGH);
    for(int c = 0; c < MAX_CONTROLLERS; c++)
    {
      for(int i = 0; i < 12; i++)
        buttons[c][i] = -1;
      types[c] = NES;
      dataPins[c] = -1;
    }
  }

  ///This sets the controller type and initializes its individual data pin
  void setController(int controller, Type type, int pin)
  {
    types[controller] = type;
    dataPins[controller] = pin;
    //pinMode(dataPins[controller], INPUT_PULLUP);
    gpio_set_pull_mode((gpio_num_t)dataPins[controller], GPIO_PULLUP_ONLY); 
    gpio_set_direction((gpio_num_t)dataPins[controller], GPIO_MODE_INPUT); 
  }
  
  ///This sets the controller type and initializes its individual data pins
  void setControllers(Type type, int count, const int *pins)
  {
	for(int i = 0; i < count; i++)
	{
		types[i] = type;
		dataPins[i] = pins[i];
		//pinMode(dataPins[i], INPUT_PULLUP);
    gpio_set_pull_mode((gpio_num_t)dataPins[i], GPIO_PULLUP_ONLY); 
    gpio_set_direction((gpio_num_t)dataPins[i], GPIO_MODE_INPUT);
	}
  }
  
  void poll()
  {
    gpio_set_level((gpio_num_t)latchPin, HIGH); //digitalWrite(latchPin, HIGH);
    ets_delay_us(12); //delayMicroseconds(12);
    gpio_set_level((gpio_num_t)latchPin, LOW); //digitalWrite(latchPin, LOW);  
    ets_delay_us(6); //delayMicroseconds(6);
    for(int i = 0; i < 12; i++)
    {
      for(int c = 0; c < MAX_CONTROLLERS; c++)
        if(dataPins[c] > -1)
        {
          if(gpio_get_level((gpio_num_t)dataPins[c]))  //digitalRead(dataPins[c])
            buttons[c][i] = -1;
          else
            buttons[c][i]++;
        }
      gpio_set_level((gpio_num_t)clockPin, LOW); //digitalWrite(clockPin, LOW);
      ets_delay_us(12); //delayMicroseconds(6);
      gpio_set_level((gpio_num_t)clockPin, LOW); //digitalWrite(clockPin, HIGH);
      ets_delay_us(6); //delayMicroseconds(6);
    }
  }

  int translate(int controller, Button b) const
  {
    if(types[controller] == SNES) return b;
    static const int translateToNES[] = {1, 8, 2, 3, 4, 5, 6, 7, 0, 8, 8, 8};
    return translateToNES[b];
  }

  ///button will be unpressed until released again
  void clear(int controller, Button b)
  {
    buttons[controller][translate(controller, b)] = 0x80000000;
  }

  ///returns if button is currently down
  bool down(int controller, Button b) const
  {
    return buttons[controller][translate(controller, b)] >= 0;
  }

  ///returns true if button state changed to down since previous poll. repeatAfterTics can be used to repeat after button was hold down for sme time
  bool pressed(int controller, Button b, int repeatAfterTics = 0x7fffffff) const
  {
    return buttons[controller][translate(controller, b)] == 0 || (buttons[controller][translate(controller, b)] >= repeatAfterTics);
  }

  ///returns the type of controller configured
  Type getType(int controller)
  {
    return types[controller];
  }
};

