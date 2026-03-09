#include <stdio.h>
#include "functions/mainf.h"
#include "functions/buscaf.h"
#include "functions/ordenaf.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>



int main()
{

    FILE *fp = NULL; // arquivo nao aberto ainda
    FILE *log = NULL; //arquivo de log
    int tam=1; // tamanho inicial do vetor
    int *vet=(int*)malloc(tam*sizeof(int));
    int i=0; // variavel para rodar o vetor ao ser editado
    int elemento; // elemento a ser procurado no vetor
    int *temp = (int*)realloc(vet, tam * sizeof(int));
    char arq[50]; // nome do arquivo
    int resultado;
    int opcao = 0, subop = 0;//arquivo a ser carregado
    int contAlg = 0; //conta quantas vezes um algoritmo foi executado
    
    //implementar vetor de doubles para armazenar varios tempos de execução.
    LARGE_INTEGER frequency;
    LARGE_INTEGER inicio,fim;
    double elapsedtime;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&inicio);


    while (opcao!=5)
    {
  
        menu();
        if (scanf("%d", &opcao) != 1) 
        { // se o que o usuario digitar não for um numero inteiro 
            printf("Entrada invalida!\n");
            while (getchar() != '\n'); // limpa buffer
            opcao = 0;
        }
        switch (opcao)
        { //switch tem um menor tempo de execução do que varios if's
        
            case 1:
               
                printf("Insira o nome do arquivo:\n ");
                getchar(); //limpa o buffer
                fgets(arq, 50, stdin);
                arq[strcspn(arq, "\n")] = 0; // Substitui o \n por um terminador nulo, para nao ler por exemplo: "dados.txt" e tentar abrir o arquivo "dados.txt\n"
                fp = fopen(arq,"r");

                if (fp == NULL) {
                    printf("Erro: Arquivo '%s' nao encontrado.\n", arq);
                    break; // Sai do case 1 se nao abrir
                }

                i=0; // Reinicia o indice caso carregue outro arquivo
                
                while(fscanf(fp,"%d",&vet[i])!=EOF) // pegar os dados dentro do arquivo e passar para o vetor
                {
                    i++; // rodar o vetor
                    tam++; // aumentar o tamanho
                    vet = (int*)realloc(vet,tam*sizeof(int));
                }
                vet = (int*) realloc(vet,(tam-1)*sizeof(int));//reajustar o tamanho para nao sobrar nada
                break;

            case 2:
            
                if(fp == NULL){ //não abriu o arquivo
                    printf("Erro ao abrir arquivo, carregue a opcao 1 e tente novamente.\n");
                    break;
                }
                else
                {
                    submenu2();
                    printf("Insira uma opcao: \n"); // escolha de qual tipo de busca
                    scanf("%d",&subop);
                    printf("Qual elemento voce deseja procurar?\n"); // escolha do que buscar
                    scanf("%d",&elemento);

                    switch(subop)
                    {
                        case 1: // usar a busca linear
                    
                            resultado = buscaLinear(vet,elemento,tam); //resultado da busca
                            
                            switch(resultado)
                            {
                                case -1:  // funcao retorna -1 caso o numero nao fora achado                           
                                    printf("Esse numero nao esta no array!\n");
                                    break;                           
                                default :// retornou um positivo, ou seja, a posicao dele no vetor                           
                                    printf("O numero esta na posicao %d do vetor\n",resultado+1);
                                    contAlg++;
                                    break;                                
                            }
                            break;
                        
                        case 2: // usar a busca binaria
                        
                            resultado = buscaBin(vet,elemento,tam); //realiza a busca binaria
                            switch(resultado)
                            { 
                                case -2: // funcao retorna -2 caso o array nao esteja ordenado
                                
                                    printf("array nao ordenado!\n");
                                    break;                           
                                
                                case -1:// funcao retorna -1 caso o valor nao esteja                           
                                    
                                    printf("Valor nao encontrado no array\n");
                                    break;                                                    
                                
                                default:// ultima opcao de retorno da função, um numero positivo, ou seja, a posicao no vetor
                                
                                    printf("Valor na posicao %d do vetor\n",resultado+1);   
                                    contAlg++;
                                    break;   
                                
                            }
                            break;
                            
                            
                        default :                   
                            printf("Opcao inexistente\n");
                            break;              
                    }
                }

            case 3:
                
                if(fp == NULL) // nao abriu o arquivo
                {    
                    printf("Erro ao abrir arquivo, carregue a opção 1 e tente novamente.\n");
                }

                submenu3();
                scanf("%d",&subop);
                
                switch (subop)
                {
                case 1: //InsertSort
                    
                    insertSort(vet,tam-1);
                    printf("Vetor ordenado por Insert Sort!\n");
                    contAlg++;

                    break;
                case 2: //Bubble

                    bubbleSort(vet,tam-1);
                    printf("Vetor ordenado por Bubble Sort!\n");
                    contAlg++;

                    break;
                case 3: //Selection

                    selectionSort(vet,tam-1);
                    printf("Vetor ordenado por Selection Sort!\n");
                    contAlg++;
                    
                    break;
                case 4: //Merge
                    /* code */
                    break;
                case 5: //Quick
                    /* code */
                    break;
                case 6: //algoritmo adicional
                    /* code */
                    break;
                
                default:
                    printf("Opcao inexistente\n");
                    break;
                }

                break;
            
            case 4:
                
                if(contAlg>0){//esta opcao so pode ser executada se algum algoritmo for executado anteriormente.
                    log = fopen("log.txt","w");//criar arquivo de log
                    fprintf(log, "arquivo log: \n");



                }else{

                    printf("Para gerar algum log execute algum algoritmo antes!\n");

                }
                break;
        
            case 5:
                printf("Saindo\n");
                break;


            default:
                
                printf("Opcao invalida!\n");
                break;
        }
    }
    
    if(fp!=NULL){ //verifica se o arquivo foi aberto
        fclose(fp); //fecha o arquivo aberto
        if(log!=NULL){
            fclose(log);
        }
    }
        
        free(vet); //A opção 5, antes de ser executada, deverá liberar toda a memora alocada
        return 0;
}
