/*
    Bruteforce Bootloader Unlocker for HUAWEI Related smartphones
    This is intended to be the fastest ever created bootloader unlocker
    Modified to try 4 codes then reboot to bootloader
*/
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#define LEN 60  // Increased length for longer commands
#define ATTEMPTS_BEFORE_REBOOT 4

unsigned long long base_start = 1000000000000000;
unsigned int attempt_counter = 0;

void resumer(){
    printf("\n\nLast used code was: %llu", base_start);
    FILE * fp = fopen("lastcode","w");
    fprintf(fp,"%llu",base_start);
    fclose(fp);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        char *base = argv[1];
        base_start = atoll(base);
    } else {
        FILE * fp;
        if(fp = fopen("lastcode","r")) {  // Fixed 'w' to 'r' for reading
            fscanf(fp,"%llu",&base_start);
            fclose(fp);
        }
    }
    
    signal(SIGINT, resumer);
    signal(SIGTERM, resumer);
    
    char fou[LEN] = "fastboot oem unlock ";
    char reboot_cmd[LEN] = "fastboot reboot bootloader";
    char TOTAL[LEN];
    
    int result = 1;
    while (1) {
        // Try up to ATTEMPTS_BEFORE_REBOOT codes
        for (int i = 0; i < ATTEMPTS_BEFORE_REBOOT; i++) {
            sprintf(TOTAL, "%s%llu", fou, base_start);
            result = system(TOTAL);
            
            if (result == 0) {
                // Success - unlock code found
                printf("Your unlock code is: %llu\n", base_start);
                return 0;
            }
            
            base_start++;
            attempt_counter++;
        }
        
        // After ATTEMPTS_BEFORE_REBOOT attempts, reboot to bootloader
        printf("Rebooting to bootloader after %d attempts (last code: %llu)\n", 
               ATTEMPTS_BEFORE_REBOOT, base_start - 1);
        
        // Save current code before reboot
        FILE * fp = fopen("lastcode","w");
        fprintf(fp,"%llu",base_start);
        fclose(fp);
        
        // Execute reboot command - fastboot will naturally wait for the device
        system(reboot_cmd);
        
        printf("Continuing with next set of codes...\n");
    }
    
    return 1;
}
