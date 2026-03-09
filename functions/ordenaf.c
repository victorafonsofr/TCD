#include <stdio.h>
#include <stdlib.h>

void troca(int a[], int x,int y)
{
    int w;
    w=a[x];
    a[x]=a[y];
    a[y]=w;
}
void bubbleSort(int a[],int n)
{
     int contador = 1;
    int m=n;
    for(int j=0;j<n;j++)
    {
        if(contador==0)
        {
            break;
        }
        contador = 0;
        for(int i=0;i<m;i++)
        {
            if(a[i]>a[i+1])
            {
                troca(a,i,i+1);
                contador++;
            }
        
        }
        m--;
    }
}
void insertSort(int v[],int n)
{
    int aux,j; // variavel auxiliar para troca 
    for(int i=1;i<n;i++)//controla o indice do vetor, o qual esta sendo ordenado
    {
        int key=v[i]; // variavel que esta sendo ordenada é a key
        int j=i-1;  // variavel j para rodar pelo vetor fazendo comparacoes
        while(j>=0 && v[j]>key) // condicao para j ser um indice do vetor e o numero sendo comparado tem que ser maior do qual a gente esta ordenando
        {
            v[j+1]=v[j]; // copia a variavel para a da frente  
            j--; // se copiou no da frente o indice do vetor volta comparando com os de tras
        }
        v[j+1]=key; // saiu da condicao while entao achou o menor e colocou na posicao que esta sendo ordenado
    }
}


void selectionSort(int vetor[], int size){

    int temp;

    for(int i = 0; i<size-1; i++){ 
 
        int min = i;

        for(int j = i+1; j<size; j++){
        
            if(vetor[j] < vetor[min]){ //verifica qual o menor elemento do vetor na iteração i-ésima
                min = j; //a posição j-ésima é a menor, daí, agora se compara o próximo elemento 
            }
         }
         if(min!=i){ //so realiza a troca de valores se não estiver ordenado
            temp = vetor[i]; // troca de valores
            vetor[i] = vetor[min];
            vetor[min] = temp;      
         }
         
    }

}

void mergeSort(int *ini, int *slow, int *fim){
    int tamanho = (fim-ini)+1;
    int *temp = malloc(tamanho * sizeof(int));

    int *l1 = ini;
    int *l2 = slow + 1;

    int k = 0;


    while(l1 <= slow && l2 <= fim){
        if(*l1 <= *l2){
            temp[k] = *l1; 
            l1++;
        }
        else{
            temp[k] = *l2; 
            l2++;
        }
        k++;
    } 

    while(l1 <= slow){
        temp[k] = *l1;
        l1++;
        k++;
    }

    while(l2 <= fim){
        temp[k] = *l2;
        l2++;
        k++;
    }


    for(int i = 0; i < k; i++){
        ini[i] = temp[i];
    }


    free(temp); 
}

void merge(int *ini, int *fim){
    if(ini >= fim){
        return;
    }

    int *slow = ini;
    int *fast;

    // A Corrida
    for(fast = ini+1; fim >= fast; fast += 2){
        if(fast+2 <= fim){
            slow++;
        }
    }


   merge(ini, slow);
   merge(slow+1, fim);


   mergeSort(ini, slow, fim); 

}
