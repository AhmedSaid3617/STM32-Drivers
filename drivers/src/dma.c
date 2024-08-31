#include "dma.h"

void DMA_channel_init(DMA_init_typedef* dma_init_handle){
    dma_init_handle->dma_channel->CPAR = dma_init_handle->peripheral_register;
    dma_init_handle->dma_channel->CMAR = dma_init_handle->memory_address;
    dma_init_handle->dma_channel->CNDTR = dma_init_handle->data_count;
    dma_init_handle->dma_channel->CCR |= dma_init_handle->priority << 12;
    dma_init_handle->dma_channel->CCR |= dma_init_handle->mem_inc << 7;
    dma_init_handle->dma_channel->CCR |= dma_init_handle->periph_inc << 6;
    dma_init_handle->dma_channel->CCR |= dma_init_handle->direction << 4;
    dma_init_handle->dma_channel->CCR |= dma_init_handle->circular_en << 5;
    dma_init_handle->dma_channel->CCR |= dma_init_handle->periph_alignment << 8;
    dma_init_handle->dma_channel->CCR |= dma_init_handle->mem_alignment << 10;
    dma_init_handle->dma_channel->CCR |= 1<<0; // Enable channel.
}
