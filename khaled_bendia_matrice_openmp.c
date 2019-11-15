//KHALED BENDIA

//gcc -fopenmp  khaled_bendia_matrice_openmp.c -o test -lm

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

#define NB_LINE_A  12
#define NB_COLUMN_A 5

#define NB_LINE_B  5
#define NB_COLUMN_B 10


int a[NB_LINE_A][NB_COLUMN_A]
   ,b[NB_LINE_B][NB_COLUMN_B]

   ,c[NB_LINE_A][NB_COLUMN_B];

void afficher(int NB_LINE,int NB_COLUMN,int x[NB_LINE][NB_COLUMN])
{
   for (int i = 0; i < NB_LINE; ++i)
   {
       for (int j = 0; j < NB_COLUMN; ++j)
       {
           printf("%d ", x[i][j]); 
       }
       printf("\n"); 
   }
}
int main (int argc, char *argv[]) { 
   pthread_t threads[NB_LINE_A]; 
   int rc; 
   long th; 
   void *ret ;
   double debut,fin;
   srand(time(NULL));

   for (int i = 0; i < NB_LINE_A; ++i)
   {
       for (int j = 0; j < NB_COLUMN_A; ++j)
       {
           a[i][j] = rand()%NB_LINE_A;
       }
   }
   for (int i = 0; i < NB_LINE_B; ++i)
   {
       for (int j = 0; j < NB_COLUMN_B; ++j)
       {
           b[i][j] = rand()%NB_LINE_B;
       }
   }
   printf("Matrice A :\n"); 
   afficher(NB_LINE_A,NB_COLUMN_A,a);
   printf("\n"); 
   printf("Matrice B :\n"); 
   afficher(NB_LINE_B,NB_COLUMN_B,b);
   //parallele
   debut=clock();

   #pragma omp parallel shared(a,b,c)  num_threads(2)  
   {
       #pragma omp for  
       for (int k = 0; k < NB_LINE_A; ++k)
       {
          for (int i = 0; i < NB_COLUMN_B; ++i)
          {
             int t=0;
             for (int j = 0; j < NB_LINE_B; ++j)
             {    
                t+=a[k][j]*b[j][i];
             }
             c[k][i]=t;
         }
      }
   }

   fin=clock();
   printf("\n"); 
   printf("temps parallele=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC); 
   printf("Matrice C en parallele :\n"); 
   afficher(NB_LINE_A,NB_COLUMN_B,c);
  

   //sequentielle
   debut=clock();
   for (int k = 0; k < NB_LINE_A; ++k)
   {
       for (int i = 0; i < NB_COLUMN_B; ++i)
       {
          int t=0;
          for (int j = 0; j < NB_LINE_B; ++j)
          {    
             t+=a[k][j]*b[j][i];
          }
          c[k][i]=t;
       } 
   } 
   fin=clock();
   printf("\n"); 
   printf("temps seq=%f\n",  (double)(fin-debut)/CLOCKS_PER_SEC); 
   printf("Matrice C en sequencielle :\n");
   afficher(NB_LINE_A,NB_COLUMN_B,c);
}

