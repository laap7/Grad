#include <stdio.h>
#include <stdlib.h>

int *LerVetor(int b){
  int *a = malloc(sizeof(int) * b);
  if(a == NULL){
    printf("Erro de alocacao do vetor\n");
    exit(-1);
  }
  int i;
  for(i=0;i<b;i++){
    scanf("%d", &a[i]);
  }
  return a;
}

void LiberarVetor(int *a){
  free(a);
}

void PrintVetor(int *a,int b){
    int i;
    for(i=0;i<b;i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int *ShellSort(int *a, int b){
  int temp;
  int gap = 1;
  while(gap <= b){
    gap *= 2;
  }
  gap = (gap/2) - 1;
  while(gap > 0){
    for(int i = gap; i < b; i++){
      temp = a[i];
      int ii = i - gap;
      while(ii >= 0 && a[ii] > temp){
        a[ii+gap] = a[ii];
        ii -= gap;
      }
      a[ii+gap] = temp;
    } 
    gap /= 2;
  }
  return a;
}

// a = vetor, t = tamanho do vetor, c = numero a ser buscado
void BuscaBinaria(int *a, int t, int x){
  int c = 0;
  int f = t-1;
  while (c <= f){
    int m = (c+f)/2;
    if (a[m] == x){
      printf("1\n");
      return;
    }
    else {
      if (a[m] < x){
        c = m + 1;  
      }
      else{
        f = m - 1;
      }
    } 
  }
  printf("0\n");
  return;
}

int main(void) {
  int tam1, tam2;
  scanf("%d", &tam1);
  int *vetor1, *vetor2;
  vetor1 = LerVetor(tam1);
  scanf("%d", &tam2);
  vetor2 = LerVetor(tam2);
  vetor1 = ShellSort(vetor1, tam1);
  for (int i = 0; i < tam2 ; i++) {
    BuscaBinaria(vetor1, tam1, vetor2[i]);
  }
  LiberarVetor(vetor1);
  LiberarVetor(vetor2);
  return 0;
}
