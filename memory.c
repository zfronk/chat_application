#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct Point {
	int x;
	int y;	
};

// Method to print points
void print_points(struct Point *certain_point, char *point_name){
	printf("Components contained in %s: %d, %d\n", point_name, certain_point -> x, certain_point -> y);
	
}

// Main entry point
int main(){
	struct Point *my_point = malloc(sizeof(struct Point)); // Allocate emmory
	my_point -> x = 5;
	my_point -> y = 10;

	struct Point *another_point = malloc(sizeof(struct Point));
	another_point -> x = 20;
	another_point -> y = 40;

	print_points(my_point, "my_point");
	print_points(another_point, "another_point");
	
	free(my_point); // Free memory 
	free(another_point);

	return 0;
}
