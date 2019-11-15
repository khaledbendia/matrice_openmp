//KHALED BENDIA

//gcc  -pthread -fopenmp  khaled_bendia_pi.c -o test -lm

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h> 

#define NSTEPS 1241860000

int main (int argc, char *argv[]) { 

   double debut,fin;
   srand(time(NULL));
   double pi_diviser_par_4=0;
   double pi_part;

   //parallele
   debut=clock();
   #pragma omp parallel private(pi_part)  reduction(+: pi_diviser_par_4) num_threads(2)  
   {
       #pragma omp for  
       for (int n = 0; n < NSTEPS ; ++n)
       {
          pi_part+=pow(-1,n) /(2 * n + 1);
       } 

       pi_diviser_par_4+=pi_part;
   }
   fin=clock();
   printf("temps parallele=%f\n",  (double)(fin-debut)/CLOCKS_PER_SEC); 
   printf("PI : %f\n",pi_diviser_par_4*4);   

   //sequentielle
   pi_diviser_par_4=0;
   debut=clock();
   for (int n = 0; n < NSTEPS ; ++n)
   {
       pi_diviser_par_4+=pow(-1,n) /(2 * n + 1);
   } 
   fin=clock();
   printf("temps sequentielle=%f\n",  (double)(fin-debut)/CLOCKS_PER_SEC); 
   printf("PI : %f\n",pi_diviser_par_4*4);
}
