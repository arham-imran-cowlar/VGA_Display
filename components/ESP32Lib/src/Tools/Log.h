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
//#include "Arduino.h"
#include "esp_log.h"

#define DEBUG_PRINT_NUM_LN(a) printf("%d\n", a)
#define DEBUG_PRINTLN(a) printf("%s\n", a)

#define DEBUG_PRINT_NUM(a) printf("%d", a)
#define DEBUG_PRINT(a) printf("%s", a)

//#define DEBUG_PRINTLNF(a, f) printf("%s, %s\n", a, f)
//#define DEBUG_PRINTF(a, f) printf("%s, %s", a, f)

/*
#define DEBUG_PRINTLN(a) ;
#define DEBUG_PRINT(a) ;
#define DEBUG_PRINTLNF(a, f) ;
#define DEBUG_PRINTF(a, f) ;
*/
#define ERROR(a) ESP_LOGE("ERROR", "%s", a);
