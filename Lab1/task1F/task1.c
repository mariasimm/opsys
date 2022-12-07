#include "task1.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct point {
    int x, y, weight;
};
int size;

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	int n;
	do {
		printf("Enter the amount of points: ");
		scanf("%d", &n);
		if(n < 5) printf("\nThe number can't be less than 5! Try again!\n");
	} while (n < 5);
	size = n;
	struct point points [size];
	printf("\n1 - Random array\n2 - Enter the array\n");
	int choice;
	do {
		printf("Enter the number: ");
		scanf("%d", &choice);
  		if(choice != 1 && choice != 2) break;
	} while (choice != 1 && choice != 2);
	if(choice == 1) {
		for(int i = 0; i < n; i++) {
			points[i].x = rand()%100;
			points[i].y = rand()%100;
			points[i].weight = rand()%100;
		}
	}
	else {
		for(int i = 0; i < n; i++) {
   			int x, y, weight;
   			printf("\nPoint number %d\n", i+1);
   			printf("Enter the x: ");
   			scanf("%d", &x);
   			printf("Enter the y: ");
   			scanf("%d", &y);
   			printf("Enter the weight: ");
   			scanf("%d", &weight);
   			points[i].x = x;
   			points[i].y = y;
   			points[i].weight = weight;
  		}
	}
	printf("\nYour array: \n[");
	for(int i = 0; i < n; i++) {
		if(i != 0) printf("\n");
		printf("x = %d, y = %d, weight = %d", points[i].x, points[i].y, points[i].weight);
	}
	printf("]\n");
	while(size != 1) {
		int indLightest = 0;
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				if(points[i].weight < points[indLightest].weight) 
					indLightest = i;
			}
		}
		printf("\nThe lightest point: x = %d, y = %d, weight = %d\n", points[indLightest].x, points[indLightest].y, points[indLightest].weight);
		point_disappear(&points[0], indLightest);
	}
	printf("\n_______________________________________________________\n");
	printf("\nThe final point is: x = %d, y = %d, weight = %d\n", points[0].x, points[0].y, points[0].weight);
	return 0;
}

void point_disappear(struct point* points, int index) {
	struct point ourPoint = points[index];
	int indClos = closest_point(points, index);
	if(indClos == index) return;
	struct point closP = points[indClos];
	printf("\nThe closest point: x = %d, y = %d, weight = %d\n", points[indClos].x, points[indClos].y, points[indClos].weight);
	points[indClos].weight += ourPoint.weight;
	printf("\nThe lightest point disappeared and gave its weight to closest point:\nx = %d, y = %d, weight = %d\n", points[indClos].x, points[indClos].y, points[indClos].weight);
	for(int i = index; i < size - 1; i++) {
		points[i] = points[i+1];
	}
	size--;

}

float distance(struct point pOne, struct point pTwo) {
	float dist = powf((powf(pTwo.x-pOne.x, 2)+powf(pTwo.y-pOne.y, 2)), 0.5);
	return dist;
}

int closest_point(struct point* points, int index) {
	struct point ourPoint = points[index];
	float closest;
	struct point closP;
	int indClos = 0;
	if(index != 0) {
		closest = distance(ourPoint, points[0]);
		closP = points[0];
		indClos = 0;
	}
	else if (index == 0 && size > 1) {
		closest = distance(ourPoint, points[1]);
		closP = points[1];
		indClos = 1;
	}
	else if (index == 0 && size == 1) return index; // if only one point left
	float dist = 0;
	for(int i = 0; i < size; i++){
		if (i != index) {
			dist = distance(ourPoint, points[i]);
			if (dist < closest) {
				closest = dist;
				closP = points[i];
				indClos = i;
			}
		}
	}
	return indClos;
}
