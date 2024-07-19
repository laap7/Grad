#include <stdio.h>      //scanf, printf
#include <stdlib.h>     //exit,malloc,free

int *TamanhoVetores(int n){                            //n=numero de vetores
    int *a = malloc(sizeof(int) * n);
    if(a == NULL){
        printf("Erro de alocacao do vetor de tamanhos\n");
        exit(-1);
    }
    for(int i = 0 ; i < n ; i++){
        scanf("%d", &a[i]);
    }
    return a;
}

int *ExtrairVetor(int **a, int b, int c){              //a= matriz de vetores, b = tamanho do vetor, c=indice do vetor a ser extraido
    int *v = malloc(sizeof(int) * b);
    if(v == NULL){
        printf("Erro de alocacao do vetor temporario\n");
        exit(-1);
    }
    for(int i = 0; i < b ; i++){
            v[i]=a[c][i];
    }
    return v;
}

int **PegarVetores(int a, int b[]){                    //a=numero de vetores, b=vetor de tamanho
    int **matv = malloc(a * sizeof(int *));
	for(int i = 0; i < a; i++)
		matv[i] = malloc(b[i] * sizeof(int));
    if(matv == NULL){
        printf("Erro de alocacao da matriz de vetores\n");
        exit(-1);
    }
    for(int i = 0; i < a ; i++){
        for(int ii = 0 ; ii<b[i] ; ii++){
            scanf("%d", &matv[i][ii]);
        }
    }
    return matv;
}

void PrintMatrizVetores(int **a, int *b, int c){       //a= matriz de vetores, b = vetor de tamanho, c=numero de vetores
    for(int i = 0 ; i < c ; i++){
        for(int ii = 0 ; ii < b[i] ; ii++){
            printf("%d ", a[i][ii]);
        }
        printf("\n");
    }
}

void PrintVetor(int *a,int b){                         //a=matriz de vetores, b=tamanho do vetor
    int i;
    for(i=0;i<b;i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

void FreeVetor(int *a){                                //a=vetor de tamanho
    free(a);
}

void FreeMatriz(int **a, int b){                       //a=matriz de vetores, b=numero de vetores
    for(int i = 0; i < b; i++){
		free((void *)a[i]);
    }
	free((void *)a);
}

void ChecarOrdenacao(int *a, int b){                   //a=vetor extraido, b=tamanho do vetor
    for(int i = 0; i < b-1; i++){
        if(a[i]>a[i+1]){
            printf("Nao esta ordenado \n");
            return;
        }
    }
    printf("Esta ordenado \n");
}

int *InsertionSort(int *a, int b){                    //a=matriz de vetores, b=vetor de tamanho, c=indice do vetor a ser ordenado, d=numero de vetores
    int comp = 0;
    int troc = 0;
    int temp;
    for(int i = 1 ; i < b ; i++){
        temp = a[i];
        troc++;
        int ii = i - 1;
        if(a[ii]<=temp) {
            comp++;
        }
        else {
            while(ii >= 0 && a[ii] > temp){
                a[ii+1] = a[ii];
                ii--;
                comp++;
                troc++;
                
            }
            if(ii+1 > 0) {
                comp++;
            }
        }
        a[ii+1] = temp;
        troc++;
    }
    printf("I %d %d %d \n", b, troc, comp);
    // ChecarOrdenacao(a, b);
    return a;
}

void MergeVetores(int *a, int c1, int f1, int c2, int f2, int *aux, int tc[]){     //a=vetor extraido, c1,c2=comeco da primeira/segunda parte, f1,f2= fim da primeira/segunda parte, aux=vetor auxiliar
    int i = c1;
    int ii = c2;
    int iii = 0;
    while(i <= f1 && ii <= f2){
        if(a[i] <= a[ii]){
            aux[iii]=a[i];
            iii++;
            i++;
        }
        else{
            aux[iii]=a[ii];
            iii++;
            ii++;
        }
        tc[0]++;
        tc[1]++;
    }
    while(i <= f1){
        aux[iii]=a[i];
        iii++;
        i++;
        tc[0]++;
    }
    while(ii <= f2){
        aux[iii]=a[ii];
        iii++;
        ii++;
        tc[0]++;
    }
    iii = 0;
    for(i = c1 ; i <= f2 ; i++, iii++){
        a[i]=aux[iii];
        tc[0]++;
    }

}

void Merge(int *a, int c, int f, int *aux, int tc[]){            //a=vetor extraido, b=indice come�o do vetor, f=indice fim do vetor, aux=vetor auxiliar
    if (c>=f){
        return;
    }
    int m = (c + f)/2;
    Merge(a,c,m,aux, tc);
    Merge(a,m+1,f,aux, tc);
    MergeVetores(a,c,m,m+1,f,aux, tc);
}

void MergeSort(int *a, int b, int tc[]){                          //a=vetor extraido, b=tamanho do vetor
    int *x = malloc(sizeof(int) * b);
    if(x == NULL){
        printf("Erro de alocacao do vetor de auxiliar merge\n");
        exit(-1);
    }
    Merge(a,0,b-1,x, tc);
    FreeVetor(x);
}


int main(){
    int q; //numero de vetores
    int tc[] = {0, 0};
    // printf("Digite o numero de vetores \n");
    scanf("%d", &q);
    // printf("Digite o tamanho dos vetores \n");
    int *tam = TamanhoVetores(q);
    // printf("Digite os vetores \n");
    int **vet = PegarVetores(q,tam);
    // PrintMatrizVetores(vet,tam,q);
    for(int i = 0 ; i < q ; i++){
        int *vetortemp1 = ExtrairVetor(vet,tam[i],i);
        int *vetortemp2 = ExtrairVetor(vet,tam[i],i);
        // printf("\nvetor %d : \n" , i+1);
        MergeSort(vetortemp1,tam[i],tc);
        // PrintVetor(vetortemp1,tam[i]);
        InsertionSort(vetortemp2,tam[i]);
        printf("M %d %d %d\n", tam[i], tc[0], tc[1]);
        // ChecarOrdenacao(vetortemp1,tam[i]);
        FreeVetor(vetortemp1);
        FreeVetor(vetortemp2);
        // printf("\n");
        tc[0] = 0;
        tc[1] = 0;
    }
    FreeVetor(tam);
    FreeMatriz(vet,q);
    return 0;
}
