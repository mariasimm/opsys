#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

int main(){

  int size;
  while(1){
    printf("Enter the start size: ");
    scanf("%d", &size);
    if(size < 1)
      printf("Array can't have less than 1 element\n");
    else
      break;
  }    
  struct array * arr = array_create(size);
  int choice;
  int act_size = 0;
  
  while(1){
    printf("1. Add to the end\n2. Insert\n3. Check the size\n4. Remove the element\n5. Set a new value\n6. Get value\n7. Print the array\n0. Exit\n Enter the number: ");
    scanf("%d", &choice);
    switch(choice){
      case 1:{
        int num;
        printf("Enter number: ");
        scanf("%d", &num);
        array_element_set(arr, act_size, &num, sizeof num);
        act_size++;
        break;
      }
      case 2:{
        if(act_size == 0) printf("\nEnter the element firstly\n");
        int num, pos;
        while(1){
          printf("Enter pos: ");
          scanf("%d", &pos);
          if(pos < 0 || pos > act_size)
            printf("Incorrect position\n");
          else
            break;
        }    
        printf("Enter number: ");
        scanf("%d", &num);
        for(int i = act_size + 1; i > pos; i--) {
          array_element_set(arr, i, array_element_get(i-1), sizeof array_element_get(i-1));
        }
        array_element_set(arr, pos, &num, sizeof num);
        act_size++;
        break;
      }
      case 3:{
        printf("\nSize: %d\n", array_size(arr));
        break;
      }
      case 4:{
        if(act_size == 0) printf("\nEnter the element firstly\n");
        int pos;
        while(1){
          printf("Enter pos: ");
          scanf("%d", &pos);
          if(pos < 0 || pos >= act_size)
            printf("Incorrect position\n");
          else
            break;
        }
        for(int i = pos; i < act_size - 1; i++) {
          array_element_set(arr, i, array_element_get(i+1), sizeof array_element_get(i+1));
        }
        act_size--;
        break;
      }
      case 5:{
        if(act_size == 0) printf("\nEnter the element firstly\n");
        int num, pos;
        while(1){
          printf("Enter pos: ");
          scanf("%d", &pos);
          if(pos < 0 || pos > act_size)
            printf("Incorrect position\n");
          else
            break;
        }    
        printf("Enter new number: ");
        scanf("%d", &num);
        array_element_set(arr, pos, &num, sizeof num);
        break;
      }
      case 6:{
        if(act_size == 0) printf("\nEnter the element firstly\n");
        int pos;
        while(1){
          printf("Enter pos: ");
          scanf("%d", &pos);
          if(pos < 0 || pos >= act_size)
            printf("Incorrect position\n");
          else
            break;
        }
        printf("\nElement: %d\n", array_element_get(arr, pos));
        break;
      }
      case 7:{
        printf("\nArray:\n");
        for(int i = 0; i < array_size(arr); i++) {
          printf(" %d ", array_element_get(arr, i));
        }
        break;
      }
      case 0:{
        return 0;
      }
      default:{
        printf("Error\n");
        break;
      }
    }
  }
}
