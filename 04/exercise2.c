#include <stdio.h>
#include <stdint.h>

#define REG_PICR   (*(volatile uint32_t *)0x400C0A04) 
#define REG_PIDATA (*(volatile uint32_t *)0x400C0A00) 
#define PI4_INPUT_MASK (1 << 4)
#define PI4_DATA_MASK (1 << 4)

void init_PI4_as_input() {
   
    REG_PICR &= ~PI4_INPUT_MASK;  
}

int read_PI4_level() {
    
    return (REG_PIDATA & PI4_DATA_MASK) ? 1 : 0; 
}

int main() {
    init_PI4_as_input();
    
    int level = read_PI4_level();
    
    if (level) {
        printf("PI4 level: H\n");
    } else {
        printf("PI4 level: L\n");
    }
    
    return 0;
}
