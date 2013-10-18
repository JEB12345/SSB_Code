#include "sensor_memdebug.h"
#include "sensor_pindefs.h"
#include "sensor_led.h"
#include <xc.h>
#include <stddef.h>

uint8_t data[MEMDBG_SIZE];
mem_element mem;
mem_element mem_end;
mem_element mem_pool[MEMDBG_POOLSIZE];
uint8_t     mem_pool_used[MEMDBG_POOLSIZE];
volatile uint8_t mem_lock;
uint16_t t_sizes[MEMDBG_POOLSIZE+1];
uint16_t t_offsets[MEMDBG_POOLSIZE+1];
uint8_t t_tags[MEMDBG_POOLSIZE+1];

void init_memory()
{
    unsigned i;
    mem.freed = 0;
    mem.next = &mem_end;
    mem.prev = &mem;
    mem.mem_ptr = data;
    mem.size = 0;
    mem.offset = 0;
    mem.tag = 0;
    mem_end.freed = 0;
    mem_end.next = &mem_end;
    mem_end.prev = &mem;
    mem_end.mem_ptr = NULL;
    mem_end.size = 0;
    mem_end.offset = MEMDBG_SIZE;
    mem_end.tag = 0;
    mem_lock = 0;
    for(i=0;i<MEMDBG_POOLSIZE;++i){
        mem_pool_used[i] = 0;
        mem_pool[i].mem_pool_idx = i;
    }
    for(i=0;i<MEMDBG_GUARDSIZE;++i){
        data[i] = 0;
    }
}

void* malloc_dbg(size_t size, uint8_t tag)
{
    return malloc(size);
    ++mem_lock;
    if(mem_lock>1){
        led_rgb_set(100,50,0);
        LED_2 = 1;
        LED_4 = 1;
        --mem_lock;
        return NULL;
    }
    //memcheck();
    //loop over the memory and try to find a 'hole' big enough to fit the data
    mem_element* cur = &mem;
    mem_element* next = NULL;
    unsigned found = 0;
    unsigned i;
    uint16_t size_to_alloc = size+MEMDBG_GUARDSIZE;
    uint16_t cur_end, next_start;
    while(cur!=&mem_end && !found){ //end of list
        //compute end of cur
        cur_end = cur->offset+cur->size+MEMDBG_GUARDSIZE;
        //and the start of the next block
        next_start = cur->next->offset;
        //check if there is enough room for the new block
        if(next_start-cur_end>=size_to_alloc){
            //allocate a block after cur
            found = 1;
        } else {
            //continue the search
            cur = cur->next;
        }
    }

    if(!found){
        //couldn't allocate memory
        LED_4 = 1;
        while(1);
        --mem_lock;
        return NULL;
    } else {
        //add to list if we can find an empty memory structure
        for(i=0;i<MEMDBG_POOLSIZE;++i){
            if(!mem_pool_used[i]){
                next = &mem_pool[i];
                mem_pool_used[i] = 1;
                break;
            }
        }
        if(next==NULL){
            //no more memory structures available
            LED_4 = 1;
            --mem_lock;
            return NULL;
        } else {
            //assign memory space in between cur and cur->next
            next->size = size;
            next->freed = 0;
            next->tag = tag;
            next->prev = cur;
            next->next = cur->next;
            cur->next->prev = next;
            cur->next = next;
            next->offset = cur->offset+cur->size+MEMDBG_GUARDSIZE;
            next->mem_ptr = data+next->offset;
            //zero out the guard space
            for(i=0;i<MEMDBG_GUARDSIZE;++i){
                next->mem_ptr[size+i]=0;
            }
            --mem_lock;
            //memcheck();
            return next->mem_ptr;
        }
    }
    --mem_lock;
}

void free_dbg(void* ptr, uint8_t tag)
{
    free(ptr);return;
    LED_2 = 1;
    while(mem_lock);
    ++mem_lock;
    LED_2 = 0;
    //memcheck();
    //loop over the blocks 
    mem_element* cur;
    cur = mem.next;
    unsigned found = 0;
    while(cur!=&mem_end && !found){ //end of list
        if(cur->mem_ptr==ptr){
            found = 1;
        } else {
            //continue the search
            cur = cur->next;
        }
    }
    if(!found){
        LED_2 = 1;//double free
    } else {
        cur->freed = 1;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        //allow cur to be reused
        mem_pool_used[cur->mem_pool_idx] = 0;
    }
    --mem_lock;
}

int memcheck()
{ 
    return 1;
    mem_element* cur = &mem;
    uint16_t offset_inc = 0;
    uint16_t i;
    uint8_t* ptr;
    uint16_t j;
    j=0;
    for(j=0;j<MEMDBG_POOLSIZE+1;++j){
        t_sizes[j]=0;
        t_offsets[j]=0;
        t_tags[j]=0;
    }
    j=0;
    while(cur!=&mem_end){

        t_sizes[j] = cur->size;
        t_offsets[j] = cur->offset;
        t_tags[j] = cur->tag;
        ++j;
        //check data
        if(cur->next==NULL||cur->prev==NULL){
            LED_3 = 1;LED_2=1;
            while(1);
        }
        if(cur->freed){
            //error
            LED_3 = 1;LED_2=1;
            while(1);
        }
        if(cur!=&mem && cur->mem_ptr == NULL){
            LED_3 = 1;LED_2=1;
            while(1);//null pointer in allocated memory
        }
        if(cur!=&mem && mem_pool_used[cur->mem_pool_idx]==0){
            LED_3 = 1;LED_2=1;
            while(1);
        }
        if(cur!=&mem){
            ptr = cur->mem_ptr;
            if(ptr!=data+cur->offset){
                LED_3 = 1;LED_2=1;
                while(1);
            }

        }
        for(i=0;i<MEMDBG_GUARDSIZE;++i){
            //check if we wrote beyond the buffer
            for(i=0;i<MEMDBG_GUARDSIZE;++i){
                if(cur->mem_ptr[cur->size+i]!=0){
                    LED_3 = 1;LED_2=1;
                    while(1);
                }
            }
        }
        if(cur->offset<offset_inc){
            //not increasing!!!
            LED_3 = 1;LED_2=1;
            while(1);
        }
        offset_inc = cur->offset;
        //next block
        cur = cur->next;        
    }
    return 1;
}


void memtest()
{
    uint8_t* t1,*t2,*t3,*t4,*t5;
    uint16_t i;
    t1 = malloc_dbg(100,1);
    for(i=0;i<100;++i){
        t1[i]=1;
    }
    t2 = malloc_dbg(1000,2);
    for(i=0;i<1000;++i){
        t2[i] = 2;
    }
    free_dbg(t1,1);
    t3 = malloc_dbg(30,3);
    for(i=0;i<30;++i){
        t3[i] = 3;
    }
    t4 = malloc_dbg(30,4);
    for(i=0;i<30;++i){
        t4[i] = 4;
    }
    free_dbg(t4,4);
    t5 = malloc_dbg(20,5);
    for(i=0;i<20;++i){
        t5[i] = 5;
    }
    memcheck();
    free_dbg(t5,5);
    free_dbg(t3,3);
    free_dbg(t2,2);
}