#include <stdio.h>
#include <stdlib.h>

void troca(int a[], int x,int y)
{
    int w;
    w=a[x];
    a[x]=a[y];
    a[y]=w;
}
void bubbleSort(int v[],int n)
{
    int m=n-1;// variavel m é o ultimo indice do vetor
    int aux; // variavel para auxiliar na troca de elementos
    int contador=1;// conta quantas trocas foram feitas, =1 para nao cair no if na primeira vez no laço
    for(int i=0;i<n;i++)// vai rodar o vetor n vezes
    {
        if(contador==0)// se contador == 0 significa que ele nao fez nenhuma troca, ou seja, esta ordenado
        {
            break;// se esta ordenado acaba o algoritimo
        }
        contador=0;// reinicia o contador
        for(int j=0;j<m;j++)// roda o vetor inteiro
        {
            if(v[j]>v[j+1])// se o elemento for maior do que o da frente, troca eles
            {
                aux = v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
                contador++;// se trocou, conta no contador
            }
        }
        m--;//o ultimo elemento esta ordenado, entao nao precisa compara-lo
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

void merge(int v[],int p, int meio, int q)
{
    int n1=meio+1-p; // tamanho da primeira metade do vetor
    int n2=q-meio; // tamanho da segunda metade do vetor
    int temp1[n1]; // vetor temporario que armazenara a primeira parte do vetor principal
    int temp2[n2]; // vetor temporario que armazenará a segunda parte do vetor principal
    for(int i=0;i<n1;i++) // preencher o vetor temporario 1
    {
        temp1[i]=v[p+i];
    }
    for(int i=0;i<n2;i++) // preencher o vetor temporario 2
    {
        temp2[i]=v[meio+1+i];
    }
    int i=0; // indice para rodar no vetor temporario 1
    int j=0; // indice para rodar no vetor temporario 2
    int k=p;// indice para rodar no vetor principal
    while(i<n1 && j<n2) // se sair da condicao é pq pelo menos 1 vetor temporario chegou ao fim
    {
        if(temp1[i]<temp2[j])// se o elemento do vetor1 for menor do que o do vetor2
        {
            v[k++]=temp1[i++]; // coloca o menor no vetor principal e incrementa os 2
        }
        else// ou o elemento do vetor2 é menor ou sao iguais
        {
            v[k++]=temp2[j++];//coloca o elemento no principal e incrementa os 2
        }
    }
    while(i<n1)// se um vetor chegou ao final e o outro nao aqui coloca o ultimo elemento
    {
        v[k++]=temp1[i++];
    }
    while(j<n2)// se o outro vetor chegou ao final e esse nao coloca o ultimo elemento
    {
        v[k++]=temp2[j++];
    }
}
void mergeSort(int v[],int p,int q)
{
    if(p<q) // se sair da condicao é pq o vetor é de 1 posicao
    {
        int meio=(p+q)/2; // definir o meio do vetor
        mergeSort(v,p,meio); // dividir a primeira parte do vetor
        mergeSort(v,meio+1,q); // dividir a segunda parte do vetor
        merge(v,p,meio,q); // vetor dividido basta combina-lo ordenando
    }
}

int particiona (int*v, int inicio, int fim)
{
    int pivo= (v[inicio] + v[fim] + v[(inicio + fim) / 2]) / 3;
    while(inicio<fim)
    {
        while(inicio < fim && v[inicio] <= pivo)
        {
            inicio++;
        }
        while(inicio<fim && v[fim]>pivo)
        {
            fim--;
        }
        int aux= v[inicio];
        v[inicio] =v[fim];
        v[fim]= aux;
    }
    return inicio;
}

void quickSort(int *v, int inicio, int fim)
{
    if(inicio<fim)
    {
       int pos= particiona(v, inicio, fim);
       quickSort(v,inicio , pos-1);
       quickSort(v,pos,fim);
    }    
}