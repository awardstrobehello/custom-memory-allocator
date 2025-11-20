#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "mymalloc.h"

int main(int argc, char **argv){
    int x, *p, *z, *v, *m;
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int val = 120;
    void *arr[val];
    char *arr2[val];
    int mallocNum = 0;
    int freeNum = 0;

    double start = clock();

    switch (test) {
    default:
        puts("Missing or invalid test number");
        return EXIT_FAILURE;
    
    case 1:
        free(&x);
        break;

    case 2:
        p = (int *) malloc(sizeof(int) * 10);
        free(p + 1);
        break;
    
    case 3:
        p = (int *) malloc(sizeof(int) * 10);
        free(p);
        free(p);
        break;

    // malloc() and immediately free() a 1-byte chunk
    case 4:
        for (int j = 0; j < 5000; j++){
            for (int i = 0; i < val; i++){
                void *p = malloc(1);
                free(p);
            }
        }
        break;

    // Use malloc() to get 1-byte chunks, storing the pointers in an array, then use free() to
    // deallocate the chunks
    case 5:
        for (int j = 0; j < 1000; j++){
            for (int i = 0; i < val; i++){
                arr[i] = malloc(1);
            }
            for (int i = 0; i < val; i++){
                free(arr[i]);
            }
        }
        break;

    // Randomly choose between
    // • Allocating a 1-byte chunk and storing the pointer in an array
    // • Deallocating one of the chunks in the array (if any)
    // Repeat until you have called malloc() 120 times, then free all remaining allocated chunks
    case 6:
        for (int j = 0; j < 50; j++){
            while (mallocNum < 120){
                if(rand() % 2 == 1){
                    arr2[mallocNum] = malloc(1);
                    mallocNum++;
                    freeNum++;
                } else if (freeNum == 0){
                    continue;
                }
                freeNum--;
                free(arr2[freeNum]);
                arr2[freeNum] == NULL;
                }
        }
        break;
            // 50/50 change of allocating and deallocating

    // Two more stress tests
    case 7:
        for (int i = 0; i < 50; i++){
            for (int j = 0; j < 15; j++){

                p = malloc(1);

                v = malloc(32);

                m = malloc(100);
                z = malloc(42);

                free(v);
                free(z);
                free(m);
            }
        }
        break;
        
    case 8:
        for (int j = 0; j < 50; j++){
        	p = malloc(1000);
	        free(p);
        }
        break;

    // Coalescing verification
    case 9:
        printf("Coalescing\n");
        p = malloc(100);
        z = malloc(100);
        v = malloc(100);
        printf("Blocks created\n");
        
        free(p);
        free(v);
        free(z);
        printf("Blocks freed\n");
        
        m = malloc(300);  // Should work
        if (m == NULL) {
            printf("Couldn't allocate\n");
        } else {
            printf("Success\n");
            free(m);
        }
        break;

    // Memory reuse
    case 10:
        printf("Memory Reuse\n");
        p = malloc(50);
        printf("Allocation at %p\n", p);
        free(p);
        
        z = malloc(50);  // Should reuse the same space
        printf("Allocation at %p\n", z);
        
        if (p == z) {
            printf("Success. Memory reused at same address\n");
        } else {
            printf("Memory not reused\n");
        }
        free(z);
        break;

    }

    double end = clock();
    double total = end - start;
    total/=CLOCKS_PER_SEC;

        printf("%s %f %s \n", "Time:", total, "seconds.");

    return EXIT_SUCCESS;
}
