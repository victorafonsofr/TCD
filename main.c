#include <stdio.h>
#include "functions/mainf.h"
#include "functions/buscaf.h"
#include "functions/ordenaf.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <windows.h>



int main()
{
    typedef struct{
        char tipo_algoritimo[25];
        double temp;
        char hora[15];
    } LogVet;

    FILE *fp = NULL; // arquivo nao aberto ainda
    FILE *log = NULL; //arquivo de log
    int tam=1; // tamanho inicial do vetor
    int *vet=(int*)malloc(tam*sizeof(int)); //vetor para armazenar elementos do arquivo
    int i=0; // variavel para rodar o vetor ao ser editado
    int elemento; // elemento a ser procurado no vetor
    char arq[50]; // nome do arquivo
    int resultado;
    int opcao = 0, subop = 0;//arquivo a ser carregado
    int contAlg = 0; //conta quantas vezes um algoriinfo_tempoo foi executado e além disso serve como índice para o vetLog
    int cont_logs = 0;
    LogVet *vetLog = (LogVet *) malloc((contAlg+1) * sizeof(LogVet)); //vetor para armazenar os tempos de execução de cada arquivo
    

    LARGE_INTEGER frequency;
    LARGE_INTEGER inicio,fim;
    double elapsedtime;

    time_t hora_atual; 
    struct tm info_tempo ;

    QueryPerformanceFrequency(&frequency);
    


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

                if (fp != NULL) fclose(fp); // Fecha anterior se existir
                if (vet != NULL) free(vet); // Limpa memória anterior

                tam = 1; 
                vet=(int*)malloc(tam*sizeof(int));

                printf("Insira o nome do arquivo:\n ");
                getchar(); //limpa o buffer
                fgets(arq, 50, stdin);
                arq[strcspn(arq, "\n")] = 0; // Substitui o \n por um terminador nulo, para nao ler por exemplo: "dados.txt" e tentar abrir o arquivo "dados.txt\n"
                fp = fopen(arq,"r");

                if (fp == NULL) {
                    printf("Erro: Arquivo '%s' nao encontrado.\n", arq);
                    break; // Sai do case 1 se nao abrir
                }else{
                    printf("Arquivo aberto com sucesso!\n");
                }

                i=0; // Reinicia o indice caso carregue outro arquivo
                
                while(fscanf(fp,"%d",&vet[i])!=EOF) // pegar os dados dentro do arquivo e passar para o vetor
                {
                    i++; // rodar o vetor
                    tam++; // aumentar o tamanho
                    vet = (int*)realloc(vet,tam*sizeof(int));
                }
                tam=i;
                vet = (int*) realloc(vet,tam*sizeof(int));//reajustar o tamanho para nao sobrar nada
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
                            QueryPerformanceCounter(&inicio);
                            resultado = buscaLinear(vet,elemento,tam); //resultado da busca
                            QueryPerformanceCounter(&fim);
                            switch(resultado)
                            {
                                case -1:  // funcao retorna -1 caso o numero nao fora achado                           
                                    printf("Esse numero nao esta no array!\n");
                                    break;                            
                                default :// retornou um positivo, ou seja, a posicao dele no vetor                           
                                    printf("O numero esta na posicao %d do vetor\n",resultado+1);
                                    hora_atual  = time(NULL);
                                    info_tempo = *localtime(&hora_atual);
                                    sprintf(vetLog[contAlg].hora, "%02d:%02d:%02d", info_tempo.tm_hour, info_tempo.tm_min, info_tempo.tm_sec);
                                    strcpy(vetLog[contAlg].tipo_algoritimo, "busca linear");
                                    vetLog[contAlg].temp = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequency.QuadPart;
                            
                                    contAlg++;

                                    vetLog = (LogVet *) realloc(vetLog, (contAlg+1)*sizeof(LogVet));

                                    break;                                
                            }
                            
                            break;
                        
                        case 2: // usar a busca binaria
                            QueryPerformanceCounter(&inicio);
                            resultado = buscaBin(vet,elemento,tam); //realiza a busca binaria
                            QueryPerformanceCounter(&fim);
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
                                    hora_atual  = time(NULL);
                                    info_tempo = *localtime(&hora_atual);
                                    sprintf(vetLog[contAlg].hora, "%02d:%02d:%02d", info_tempo.tm_hour, info_tempo.tm_min, info_tempo.tm_sec);  
                                    strcpy(vetLog[contAlg].tipo_algoritimo, "Busca binaria");
                                    vetLog[contAlg].temp = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequency.QuadPart;
                                    contAlg++;
                                    vetLog = (LogVet *) realloc(vetLog, (contAlg+1)*sizeof(LogVet));

                                    break;   
                                
                            }
                            break;
                            
                            
                        default :                   
                            printf("Opcao inexistente\n");
                            break;              
                    } break;
                }

            case 3:
                
                if(fp == NULL) // nao abriu o arquivo
                {    
                    printf("Erro ao abrir arquivo, carregue a opcao 1 e tente novamente.\n");
                    break;
                }

                submenu3();
                scanf("%d",&subop);
                
                switch (subop)
                {
                    case 1: //InsertSort
                        QueryPerformanceCounter(&inicio);
                        insertSort(vet,tam);
                        QueryPerformanceCounter(&fim);

                        printf("Vetor ordenado por Insert Sort!\n");
                        hora_atual  = time(NULL);
                        info_tempo = *localtime(&hora_atual);
                        sprintf(vetLog[contAlg].hora, "%02d:%02d:%02d", info_tempo.tm_hour, info_tempo.tm_min, info_tempo.tm_sec);
                        strcpy(vetLog[contAlg].tipo_algoritimo, "Insert Sort: ");
                        vetLog[contAlg].temp = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequency.QuadPart;
                        
                        contAlg++;
                        vetLog = (LogVet *) realloc(vetLog, (contAlg+1)*sizeof(LogVet));


                        break;
                    case 2: //Bubble
                        QueryPerformanceCounter(&inicio);
                        bubbleSort(vet,tam-1);
                        QueryPerformanceCounter(&fim);

                        printf("Vetor ordenado por Bubble Sort!\n");
                        hora_atual  = time(NULL);
                        info_tempo = *localtime(&hora_atual);
                        sprintf(vetLog[contAlg].hora, "%02d:%02d:%02d", info_tempo.tm_hour, info_tempo.tm_min, info_tempo.tm_sec);
                        strcpy(vetLog[contAlg].tipo_algoritimo, "Bubble Sort: ");
                        vetLog[contAlg].temp = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequency.QuadPart;

                        contAlg++;
                        vetLog = (LogVet*) realloc(vetLog, (contAlg+1)*sizeof(LogVet));


                        break;
                    case 3: //Selection
                        QueryPerformanceCounter(&inicio);
                        selectionSort(vet,tam-1);
                        QueryPerformanceCounter(&fim);
                        
                        printf("Vetor ordenado por Selection Sort!\n");
                        hora_atual  = time(NULL);
                        info_tempo = *localtime(&hora_atual);
                        sprintf(vetLog[contAlg].hora, "%02d:%02d:%02d", info_tempo.tm_hour, info_tempo.tm_min, info_tempo.tm_sec);
                        strcpy(vetLog[contAlg].tipo_algoritimo, "Selection Sort: ");
                        vetLog[contAlg].temp = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequency.QuadPart;

                        contAlg++;
                        vetLog = (LogVet*) realloc(vetLog, (contAlg+1)*sizeof(LogVet));

                        
                        break;
                    case 4: //Merge
                        QueryPerformanceCounter(&inicio);
                        mergeSort(vet,0,tam-1);
                        QueryPerformanceCounter(&fim);

                        printf("Vetor ordenado por Merge Sort!\n");
                        hora_atual  = time(NULL);
                        info_tempo = *localtime(&hora_atual);
                        sprintf(vetLog[contAlg].hora, "%02d:%02d:%02d", info_tempo.tm_hour, info_tempo.tm_min, info_tempo.tm_sec);
                        strcpy(vetLog[contAlg].tipo_algoritimo, "Merge Sort: ");
                        vetLog[contAlg].temp = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequency.QuadPart;
                        
                        contAlg++;
                        vetLog = (LogVet*) realloc(vetLog, (contAlg+1)*sizeof(LogVet));


                        break;
                    case 5: //Quick
                        
                        QueryPerformanceCounter(&inicio);
                        quickSort(vet,0,tam-1);
                        QueryPerformanceCounter(&fim);

                        printf("Vetor ordenado por Quick Sort!\n");
                        hora_atual  = time(NULL);
                        info_tempo = *localtime(&hora_atual);
                        sprintf(vetLog[contAlg].hora, "%02d:%02d:%02d", info_tempo.tm_hour, info_tempo.tm_min, info_tempo.tm_sec);
                        strcpy(vetLog[contAlg].tipo_algoritimo, "Quick Sort: ");
                        vetLog[contAlg].temp = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequency.QuadPart;
                        contAlg++;
                        vetLog = (LogVet*) realloc(vetLog, (contAlg+1)*sizeof(LogVet));

                        break;
                    case 6: //algoriinfo_tempoo adicional - SinistroSort

                        
                        #pragma omp parallel 
                        { }

                        QueryPerformanceCounter(&inicio);
                        introsort(vet,tam);
                        QueryPerformanceCounter(&fim);

                        printf("Vetor ordenado por Sinistro Sort\n");
                        hora_atual  = time(NULL);
                        info_tempo = *localtime(&hora_atual);
                        sprintf(vetLog[contAlg].hora, "%02d:%02d:%02d", info_tempo.tm_hour, info_tempo.tm_min, info_tempo.tm_sec);
                        strcpy(vetLog[contAlg].tipo_algoritimo, "Sinistro Sort: ");
                        vetLog[contAlg].temp = (fim.QuadPart - inicio.QuadPart) * 1000.0 / frequency.QuadPart;
                        contAlg++;
                        vetLog = (LogVet*) realloc(vetLog, (contAlg+1)*sizeof(LogVet));

                        break;
                    
                    default:
                        printf("Opcao inexistente\n");
                        break;
                }

                break;
            
            case 4:
                
                if(contAlg>cont_logs){//esta opcao so pode ser executada se algum algoriinfo_tempoo for executado anteriormente.
                    log = fopen("log.txt","a");//criar arquivo de log
                    fprintf(log, "arquivo log: \n");

                    for(int k = cont_logs; k < contAlg; k++){
                        fprintf(log,"[%s] %2d - %s - Time: %.9lf ms\n", vetLog[k].hora, k, vetLog[k].tipo_algoritimo, vetLog[k].temp);
                    }

                    fclose(log);
                    cont_logs = contAlg;
                    printf("log gerado com sucesso!\n");
                }else{

                    printf("Para gerar algum log execute algum algoriinfo_tempoo antes!\n");

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
        free(vetLog);
        return 0;
}
