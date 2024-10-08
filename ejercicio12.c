#include "stdio.h"
#include "omp.h"

#define N 20

void main(){
    int a=0,b=1,c;
    int i=0;
    #pragma omp parallel private(i) shared(b, a)
    {
        #pragma omp for
        for(i=0; i<N;i++){
            printf("%d ",b);
            c=a+b;
            a=b;
            b=c;
        }
        printf("\n ");
    }
}
