#include "main.h"
#include "ST-LIB.hpp"
#include <cstring>

using ST_LIB::DMA_Domain;

// Definir una DMA con Instance::none para transferencia memoria a memoria
constexpr DMA_Domain::DMA<DMA_Domain::Stream::dma1_stream0> mem2mem_dma{DMA_Domain::Instance::none};

int main(void) {
    HAL_Init();


    using myBoard = ST_LIB::Board<mem2mem_dma>;
    myBoard::init();


    auto &dma_direct = myBoard::instance_of<mem2mem_dma>();


    uint16_t* srcBuffer = (uint16_t*)MPUManager::allocate_non_cached_memory(16);
    uint16_t* dstBuffer = (uint16_t*)MPUManager::allocate_non_cached_memory(16);

    *dstBuffer = 0x0000;
    *srcBuffer = 0xDEAD;

    dma_direct.start((uint32_t)srcBuffer, (uint32_t)dstBuffer, 1);
    //HAL_DMA_Start_IT(&dma_direct.dma, (uint32_t)srcBuffer, (uint32_t)dstBuffer, 1);

    //HAL_DMA_PollForTransfer(&dma_direct.dma, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
    // Wait for completion
    while (HAL_DMA_GetState(&dma_direct.dma) != HAL_DMA_STATE_READY) {
        __NOP();
    }

    // Verify transfer
    [[maybe_unused]]bool success = (*srcBuffer == *dstBuffer);

    while (1) {
        HAL_Delay(100);
    }
}