#include "HALAL/HALAL.hpp"
#include "ST-LIB.hpp"
#include "HALAL/Services/ADC/ADC.hpp"
#include <stdio.h>

using ST_LIB::DMA_Domain;

constexpr auto dma1_0 = DMA_Domain::DMA<DMA_Domain::Stream::dma1_stream0>(DMA_Domain::Instance::adc1);

int main(void) {
    using myBoard = ST_LIB::Board<dma1_0>;
    
    myBoard::init();
    
    uint8_t adc1_ch0 = ADC::inscribe(PA0);
    
    auto &dma1_inst = myBoard::instance_of<dma1_0>();
    
    dma1_inst.setDMAHandle(ADC::peripherals[0].handle);
    MPUManager::start();
    HAL_Init();
    HALconfig::system_clock();
    HALconfig::peripheral_clock();

    ADC::start();
    
    ADC::turn_on(adc1_ch0);
    
    while (1) {
        float voltage_adc1 = ADC::get_value(adc1_ch0);
        if (voltage_adc1){

        }
    }
    
    return 0;
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}