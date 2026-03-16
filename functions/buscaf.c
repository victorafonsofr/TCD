#include <stdio.h>

int ordenado(int vetor[],int size)
{
    for(int i=0 ; i < (size-1) ; i++) //laço nao chega no ultimo elemento do vetor, pois se ele chegar ao ultimo e comparar com o proximo entrará em uma memoria que nao eh minha
    {
        if(vetor[i] > vetor[i+1]) // comparando o elemento com o proximo
        {
            return -1; // se o elemento for maior que o da sua frente ele nao esta ordenado, retorna -1
        }
    }
    return 1;// se ele passou pelo laço de repetição, ele esta ordenado, entao retorna 1
}
int buscaLinear(int array[], int number, int size){
    for(int i=0;i<size;i++) //laço para percorrer o array inteiro
    {
        if(array[i]==number) 
        {
            return i; //se o numero que esta sendo conferido for o numero procurado retorna sua posição
        }
    }
    return -1; // se nao retornar nenhuma posição isso significa que o elemento nao esta no array, entao retorna um negativo
}
int buscaBin(int array[], int number, int size)
{
    if(ordenado(array,size) == 1)
    {
        int esquerda = 0; // primeiro indice do array
        int direita = size-1; // ultimo indice do array

        while(esquerda<=direita) // se eles se igualarem ou inverterem é porque nao achou o numero
        {
            int meio = (esquerda + direita)/2; // meio do array - correção pois o codigo estava em loop infinito por conta do meio continuar sempre o mesmo

            if(array[meio]==number)
            {
                return meio; //retorna a posição que o numero esta
            }
            else if(array[meio]<number)
            {
                esquerda = meio + 1; // muda o começo do vetor para o meio
            }
            else
            {
                direita = meio - 1; // muda o fim do vetor para o meio
            }        
        }
        return -1; // saiu do laço, significa que o valor nao esta no array
    }
    else
    {
        return -2; // retorno de -2 significa que o vetor nao esta ordena
    }
}
