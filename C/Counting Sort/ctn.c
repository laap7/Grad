#include <stdio.h>
#include <stdlib.h> 

void LiberarVetor(int *a){
  free(a);
  return;
}

int *CriarVetor(int b){
    int *a = malloc(sizeof(int) * b);
    if(a == NULL){
      printf("Erro\n");
      exit(-1);
    }
    int i;
    for(i=0;i<b;i++){
      a[i] = 0;
    }
    return a;
}

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

int *CountingSort(int *a, int n, int k){
  int i, j, pos;
  int *count = CriarVetor(k);
  int *aux = CriarVetor(k);
  int *aux2 = CriarVetor(n);
  for(i=0;i<n;i++){
    count[a[i]] += 1;
  }
  for(i=0;i<n;i++){
    pos = 0;
    j = 0;
    while(j<a[i]){
      pos += count[j];
      j++;
    }
    pos += aux[a[i]];
    aux2[pos]=a[i];
    aux[a[i]]++;
    printf("%d %d\n", a[i], pos);
  }
  for(i=0;i<n;i++){
    a[i] = aux2[i];
  }
  LiberarVetor(count);
  LiberarVetor(aux);
  LiberarVetor(aux2);
  return a;
}

int main(){
  int max, tam;
  scanf("%d", &max);
  scanf("%d", &tam);
  int *vetor;
  vetor = LerVetor(tam);
  CountingSort(vetor, tam, max);
  PrintVetor(vetor,tam);
  LiberarVetor(vetor);
  return 0;
}
