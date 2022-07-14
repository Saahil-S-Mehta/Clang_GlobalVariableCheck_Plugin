#include <stdio.h>

int global_var = 10;

int multiply(int b){
	return b * global_var;
}

int main(int argc, char* argv[]){
    int multiplier = 2;
    while (multiplier != 5){ multiplier++;}
    return global_var * multiplier;
}
