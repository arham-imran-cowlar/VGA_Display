#include "ESP32Lib.h"
#include <Ressources/Font6x8.h>

const int redPin = 14;
const int greenPin = 19;
const int bluePin = 27;
const int hsyncPin = 32;
const int vsyncPin = 33;

VGA3Bit vga;

extern "C"
{
    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
}

extern "C"
{
    void app_main(void);
}

void app_main(void)
{
    vga.init(vga.MODE320x480, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
    vga.setFont(Font6x8);
    vga.println("Hello World");
    
    while(true)
        vTaskDelay(1);
}
