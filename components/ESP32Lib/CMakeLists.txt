set(VGA_SRCS
    src/VGA/VGA.cpp
)

set(LED_SRCS
    src/LED/ParallelLED.cpp
    src/LED/ParallelLEDGraphics.cpp
    src/LED/SerialLED.cpp
)

set(I2S_SRCS
    src/I2S/I2S.cpp
)

set(COMPOSITE_SRCS
    src/Composite/Composite.cpp
)

set(includedirs
    src/Composite
    src/Controller
    src/Graphics
    src/I2S
    src/LED
    src/Math
    src/Ressources
    src/Tools
    src/VGA
    src
)

set(srcs ${VGA_SRCS} ${LED_SRCS} ${I2S_SRCS} ${COMPOSITE_SRCS})
set(requires soc driver freertos esp_rom log spi_flash heap esp_common esp_hw_support)

idf_component_register(INCLUDE_DIRS ${includedirs} SRCS ${srcs} REQUIRES ${requires})
target_include_directories(${COMPONENT_LIB} PRIVATE soc/esp32s2)