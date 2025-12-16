#include "HALAL/HALAL.hpp"
#include "ST-LIB.hpp"
#include "HALAL/Services/ADC/ADC.hpp"
#include <stdio.h>

using ST_LIB::DMA_Domain;

constexpr auto dma1_0 = DMA_Domain::DMA<DMA_Domain::Stream::dma1_stream0>(DMA_Domain::Instance::none);

int main(void) {
    using myBoard = ST_LIB::Board<dma1_0>;
    
    myBoard::init();

    auto &dma = myBoard::instance_of<dma1_0>();
    
   // Memoria NO cacheada y alineada
    alignas(32) volatile uint32_t* src =
        (uint32_t*)MPUManager::allocate_non_cached_memory(sizeof(uint32_t));
    alignas(32) volatile uint32_t* dst =
        (uint32_t*)MPUManager::allocate_non_cached_memory(sizeof(uint32_t));

    *src = 0xDEADBEEF;
    *dst = 0x00000000;

    // MUY IMPORTANTE: alignment 32 bits
    dma.start(
        (uint32_t)src,
        (uint32_t)dst,
        1
    );
    
    for (int i = 0; i < 10000000; i++ ){
        __NOP();
    }
    while (1) {
        *dst = *dst;
    }
    
    return 0;
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}