#include <Arduino.h>
#include "PinDefinitionsAndMore.h" //Define macros for input and output pin etc.
#include <IRremote.hpp>
#include <arduino-timer.h>

#define USER_SOUND_ANALOG_MICRO_VALUE_LIMIT 376
#define USER_HIGH_SOUD_COUNTER_LIMIT 5

int analogPin = A0;
int sound_lvl_value = 0;
int high_sound_counter = 0;
auto timer = timer_create_default();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    IrSender.begin();
    timer.every(500, check_sound_level);
    timer.every(7000, clear_high_sound_counter_value);
}

uint16_t sAddress = 0xDF00;
uint8_t sCommand = 0x4F;
uint8_t sRepeats = 0;

void loop() {
    timer.tick();
}

void check_sound_level(void)
{
  sound_lvl_value = analogRead(analogPin);
  Serial.println(sound_lvl_value);
  if(sound_lvl_value >= USER_SOUND_ANALOG_MICRO_VALUE_LIMIT)
  {
    high_sound_counter++;
  }
  if(high_sound_counter > USER_HIGH_SOUD_COUNTER_LIMIT)
  {
    high_sound_counter = 0;
    IrSender.sendNEC(sAddress, sCommand, sRepeats);
  }
}

void clear_high_sound_counter_value(void)
{
  high_sound_counter = 0;
}
