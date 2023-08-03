#include "ESP32Lib.h"
#include "Ressources/Font6x8.h"

const int redPin = 18;
const int greenPin = 4;
const int bluePin = 5;
const int hsyncPin = 12;
const int vsyncPin = 15;

VGA3Bit vga;

extern "C"
{
    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_timer.h"
	#include <string.h>
}

extern "C"
{
    void app_main(void);
}


void app_main(void)
{
	vga.init(vga.MODE320x240, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
	ESP_LOGI("MAIN", "Hello World from main.cpp");
	vga.setFont(Font6x8);
	vga.println("Hello World!");

	while(true)
	{
		vTaskDelay(1);
	}
}
