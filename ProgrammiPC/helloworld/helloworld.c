

#include <stdio.h>

int main(){
    for(int i = 1; i < 1000; i ++){

        int primo = 1;

        for (int j = 2; j < i; j++) {
            
            if (i % j == 0) {
                primo = 0;
                break;
            }           
        }

        if (primo) {
            printf("%03d Hello, World!\n", i);
        } 

    }
    
}