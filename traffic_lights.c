#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

/* >>> Colors immitation by bits;
 * BIT 0: MAIN RED
 * BIT 1: MAIN AMBER YELLOW
 * BIT 2: MAIN GREEN
 * BIT 4: SIDE RED
 * BIT 5: SIDE AMBER
 * BIT 6: SIDE GREEN
 * */

// >>> issuing instruction bits 
enum{
    main_red = 1u << 0,
    main_amber_yellow = 1u << 1,
    main_green = 1u << 2,
    side_red = 1 << 4,
    side_amber_yellow = 1u << 5,
    side_green = 1u << 6
};

// storing traffics states condition
typedef struct {
    const char* main_label;
    const char* side_label;
    uint8_t port_val;
    uint8_t units;
}traffic_state;

// Traffic light sequences 
static const traffic_state cycle[] = {
    {"RED","AMBER",main_red | side_amber_yellow, 1},
    {"RED","GREEN",main_red | side_green,2},
    {"AMBER YELLOW","AMBER YELLOW",main_amber_yellow | side_amber_yellow,1},
    {"GREEN","RED",main_green | side_red,2},
    {"AMBER YELLOW","RED",main_amber_yellow | side_red,1}
};

// >>> looping through the traffic light sequence
static void traffic_lights_binary(uint8_t val){
    for (int b = 7; b >= 0;b--){
        putchar(( val & (1u << b ) ? '1' : '0'));
    }
}

// >>> linking the system together
int main(){
    const size_t light_state = sizeof(cycle)/sizeof(cycle[0]);
    const unsigned int unit_second=10;
    unsigned int count_cycle=0;
    printf("\n=============== • SLIM • TRAFFIC • LIGHTS • EMULATOR • ================\n");
    while (1){
        unsigned int total_counts=0;
        count_cycle++;
        for (size_t i=0;i < light_state;i++){
            uint8_t port_out = cycle[i].port_val;
            for (size_t x=0;x<cycle[i].units;x++){
                total_counts++;
                printf("[Unit %u/9 | Port 0x%02X",total_counts,port_out);
                traffic_lights_binary(port_out);
                printf("]\n>>> Main : %-5s | SIDE : %-5s\n",cycle[i].main_label,cycle[i].side_label);
                fflush(stdout);
                sleep(unit_second);
            }
        }
    }
    return 0;
}

