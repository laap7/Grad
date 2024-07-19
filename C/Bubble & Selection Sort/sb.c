#include <stdio.h>      //scanf, printf
#include <string.h>     //strcmp,
#include <stdlib.h>     //exit,malloc,free

int readtype(){
    char tp[6];
    char s[] = "selecao";
    char b[] = "bolha";
    int res;
    scanf("%s", tp);

    if(strcmp(tp,s)==0){
        res = 1;
    }
    else{
        if(strcmp(tp,b)==0){
            res = 0;
        }
        else{
            res = 2;
        }
    }
    return res;
}

int readvectorsize(){
    int b;
    scanf("%d", &b);
    return b;
}

int *readvector(int b){
    int *a = malloc(sizeof(int) * b);
    if(a == NULL){
        printf("Erro\n");
        exit(-1);
    }
    int i;
    for(i=0;i<b;i++){
        scanf("%d", &a[i]);
    }
    return a;
}

void freevector(int *a){
    free(a);
}

void printvector(int *a,int b){
    int i;
    for(i=0;i<b;i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int *selection(int *a,int b){
   int min,min_index,i,ii=1,temp;
   for (i=0;i<b-1;i++){
        ii = i+1;
        min = a[i];
        min_index = i;
        while(ii<b){
           if(min>a[ii]){
                printf("C %d %d \n", min_index,ii);
                min_index = ii;
                min = a[ii];
                ii = ii+1;
           }
           else{
               printf("C %d %d \n", min_index,ii);
               ii = ii+1;
           }
        }
        if(i != min_index){
                printf("T %d %d \n", i, min_index);
                temp = a[i];
                a[i] = a[min_index];
                a[min_index] = temp;
        }
   }
   printvector(a,b);
return a;
}

int *bubble(int *a,int b){
    int i,ii,iii,temp,sentinel,sentinel_temp;
    int unsort = 0;
    sentinel = b;
    sentinel_temp = sentinel;
    for(i=0;i<b;i++){
        unsort = 0;
        sentinel = sentinel_temp;
        for(ii=0;ii<sentinel-1;ii++){
            printf("C %d %d \n", ii,ii+1);
            if(a[ii]>a[ii+1]){
                unsort = 1;
                temp = a[ii];
                a[ii] = a[ii+1];
                a[ii+1] = temp;
                sentinel_temp = ii+1;
                printf("T %d %d \n", ii, ii+1);
            }
        }
        if(unsort==0){
            break;
        }

    }
    printvector(a,b);
    return a;
}

int main (){
    int teste,tamanho,tipo;
    tipo = readtype();
    tamanho = readvectorsize();
    int *vetor = readvector(tamanho);
    if(tipo==1){
        selection(vetor,tamanho);
    }
    else{
        if(tipo==0){
            bubble(vetor,tamanho);
        }
        else{
            exit(-1);
        }
    }
    freevector(vetor);
	exit(0);
}
