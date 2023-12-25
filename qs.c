#include <stdio.h>      //scanf, printf
#include <math.h>       //rand
#include <stdlib.h>     //free, malloc

int opQuick = 0;
int opShell = 0;

void ChecarOrdenacao(int *a, int b){
    for(int i = 0; i < b-1; i++){
        if(a[i]>a[i+1]){
            printf("Nao esta ordenado \n");
            return;
        }
    }
    printf("Esta ordenado \n");
}

int LerTamanhoVetor(){
  int b;
  scanf("%d", &b);
  return b;
}

//b = tamanho do vetor
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

void PrintVetor(int *a,int b){
  int i;
  for(i=0;i<b;i++){
    printf("%d ", a[i]);
  }
  printf("\n");
}


void LiberarVetor(int *a){
  free(a);
}

int *ExtrairVetor(int *a, int b){
  int *v = malloc(sizeof(int) * b);
  if(v == NULL){
    printf("Erro de alocacao do vetor temporario\n");
    exit(-1);
  }
  for(int i = 0; i < b ; i++){
    v[i]=a[i];
  }
  return v;
}


void ShellSort(int *a, int b){
  opShell = 0;
  int temp;
  int gap = 1;
  while(gap <= b){
    gap *= 2;
  }
  gap = (gap/2) - 1;
  while(gap > 0){
    for(int i = gap; i < b; i++){
      temp = a[i];
      opShell++;
      int ii = i - gap;
      while(ii >= 0 && a[ii] > temp){
        opShell++;
        a[ii+gap] = a[ii];
        opShell++;
        ii -= gap;
      }
      if(ii >= 0){
        opShell++;
      }
      a[ii+gap] = temp;
      opShell++;
    }
    gap /= 2;
  }
}


void Quick(int *a, int b){
  opQuick = 0;
  QuickSort(a,0,b-1);
}


void QuickSort(int *a, int c, int f){
  if(c>=f){
    return;
  }
  int m = (c + f)/2;
  int pivo = a[m];
  opQuick++;
  int i = c;
  int ii = f;
  while(1){
    while(a[i] < pivo){
      i++;
      opQuick++;
    }
    opQuick++;
    while(a[ii] > pivo){
      ii--;
      opQuick++;
    }
    opQuick++;
    if(ii <= i) {
      break;
    }
    int temp = a[i];
    a[i] = a[ii];
    a[ii] = temp;
    opQuick += 3;
    i++;
    ii--;
  }
  QuickSort(a,c,ii);
  QuickSort(a,ii+1,f);
}

int main(){
  int tam;
  tam = LerTamanhoVetor();
  int *vetor;
  int *vetorquick, *vetorshell;
  vetor = LerVetor(tam);
  for(int i = 1; i <= tam ;i++){
    vetorquick = ExtrairVetor(vetor, i);
    vetorshell = ExtrairVetor(vetor, i);
    Quick(vetorquick,i);
    ShellSort(vetorshell,i);
    if(opQuick == opShell){
      printf("-");
    }
    else{
      if(opQuick < opShell){
        printf("Q");
      }
      else{
        printf("S");
      }
    }
  }
  //("\nContador Quick %d contador Shell %d", opQuick, opShell);
  LiberarVetor(vetor);
  LiberarVetor(vetorquick);
  LiberarVetor(vetorshell);
  return 0;
}
