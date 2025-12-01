#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main()
{
    FILE *fp1,*fp2;
    int i,arr[100];
    fp1=fopen("input.txt","r");
    if (fp1 == NULL) {
        printf("Error opening input.txt\n");
        return 1;
    }
    for(i=0;i<7;i++)
    {
        fscanf(fp1,"%d",&arr[i]);
    }
    int largest,second_largest,smallest,second_smallest;
    largest=second_largest=INT_MIN;smallest=second_smallest=INT_MAX;
     for (i = 0; i < 7; i++) {
        if (arr[i] > largest) {
            second_largest = largest;
            largest = arr[i];
        }

        if (arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
        } else if (arr[i] < second_smallest && arr[i] != smallest) {
            second_smallest = arr[i];
        }
    }
    fp2=fopen("output.txt","w");
    fprintf(fp2,"%d  ",second_largest);
    fprintf(fp2,"%d",second_smallest);
    printf("the program is executed correctly \n");
}

