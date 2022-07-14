#include <stdio.h>

int global_var2 = 10;
int global_var = 10;

int function123(){
	return global_var2*global_var;
}

int main(int argc, char* argv[]){
    int multiplier = 2;
    
    return global_var * multiplier;
}
