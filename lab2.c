#include<stdio.h>
#include<omp.h>
int main(){
    int num_iter;
    printf("Enter the number of iterations:");
    scanf("%d",&num_iter);
    #pragma omp parallel
    {
        #pragma omp for schedule(static,2)
        for(int i=0;i<num_iter;i++){
            printf("Thread %d: Iteration %d\n",omp_get_thread_num(),i);

        }
    }
    return 0;
}