#ifndef DMA_H
#define DMA_H

#include "stm32f103c6.h"

#define DMA1 ((DMA_TypeDef *)DMA1_BASE)
#define DMA1_Channel1 ((DMA_Channel_TypeDef *)DMA1_Channel1_BASE)
#define DMA1_Channel2 ((DMA_Channel_TypeDef *)DMA1_Channel2_BASE)
#define DMA1_Channel3 ((DMA_Channel_TypeDef *)DMA1_Channel3_BASE)
#define DMA1_Channel4 ((DMA_Channel_TypeDef *)DMA1_Channel4_BASE)
#define DMA1_Channel5 ((DMA_Channel_TypeDef *)DMA1_Channel5_BASE)
#define DMA1_Channel6 ((DMA_Channel_TypeDef *)DMA1_Channel6_BASE)
#define DMA1_Channel7 ((DMA_Channel_TypeDef *)DMA1_Channel7_BASE)

/**
 * @brief Direction of DMA transfer.
 *
 */
typedef enum
{
    DMA_DIR_PERTOMEM, /* Transfer from peripheral to memory. */
    DMA_DIR_MEMTOPER  /* Transfer from memory to peripheral. */
} DMA_direction;

/**
 * @brief Priority of DMA channel (4 priority levels).
 *
 */
typedef enum
{
    DMA_PRI_LOW,
    DMA_PRI_MEDIUM,
    DMA_PRI_HIGH,
    DMA_PRI_VERY_HIGH,
} DMA_priority;

/**
 * @brief Size of data in source or destination, not necessarily the same. 
 * 
 */
typedef enum
{
    DMA_DATA_8,  /* One byte. */
    DMA_DATA_16, /* Two bytes. */
    DMA_DATA_32, /* Four bytes. */
} DMA_data_alignment;

/**
 * @brief Parameters for the initialization of a DMA channel.
 * 
 */
typedef struct
{
    DMA_TypeDef* dma_base;                      /* Base address for the DAM module. */
    DMA_Channel_TypeDef* dma_channel;           /* Base adderss for the DMA channel. */
    uint32_t peripheral_register;               /* Address of peripheral register. */
    uint32_t memory_address;                    /* Memory address. */
    uint8_t data_count;                         /* Number of data units to be transfered. */
    DMA_direction direction;                    /* Direction of DMA transfer. */
    DMA_priority priority;                      /* Priority of DMA channel. */
    uint8_t periph_inc;                         /* Increment peripheral address. */
    uint8_t mem_inc;                            /* Increment memory address. */
    uint8_t circular_en;                        /* Enable circular buffer. */
    DMA_data_alignment periph_alignment;        /* Size of data in peripheral register. */
    DMA_data_alignment mem_alignment;           /* Size of data in memory location. */
} DMA_init_typedef;

void DMA_channel_init(DMA_init_typedef* dma_init_handle);

#endif