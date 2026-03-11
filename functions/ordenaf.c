#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

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

int particiona (int*v, int inicio, int fim)// organiza os elementos em torno de um pivo
{
    int pivo= (v[inicio] + v[fim] + v[(inicio + fim) / 2]) / 3; // Calcula o pivo como a media aritmetica entre o primeiro, o último e o elemento central , determina um valor medio, facilitando nas divisoes
    while(inicio<fim)
    {
        while(inicio < fim && v[inicio] <= pivo)// Move 'inicio' para a direita enquanto o valor for menor ou igual ao pivo e pula quem esta do lado certo
        
        {
            inicio++;
        }
        while(inicio<fim && v[fim]>pivo) // Move 'fim' para a esquerda enquanto o valor for maior que o pivo
        {
            fim--;
        }
        int aux= v[inicio];// inicio e fim trocam de valores 
        v[inicio] =v[fim];
        v[fim]= aux;
    }
    return inicio;
}

void quickSort(int *v, int inicio, int fim)
{
    if(inicio<fim)
    {
       int pos= particiona(v, inicio, fim);// 'pos' recebe o indice onde o vetor foi particionado
       quickSort(v,inicio , pos-1);//  elementos menores que o pivô (a esquerda)
       quickSort(v,pos,fim);// elementos maiores que o pivo (a direita)
    }    
}
static inline void troca2(int *a, int *b) { //função de troca otimizada, static usado para evitar confusão se tiver outra troca, inline para o processador não ficar tendo saltas quando a função for chamada procurando a função na memoria então copiando a penas o conteudo da função
    int temp = *a;
    *a = *b;
    *b = temp;
}

static inline int mediana(int *a, int *b, int *c) { // pegar o pivo mais equilibrado
    if (*a < *b) {
        if (*b < *c) return *b;
        return (*a < *c) ? *c : *a;
    } else {
        if (*a < *c) return *a;
        return (*b < *c) ? *c : *b;
    }
}

void insertion_sort(int *inicio, int *fim) { //insertion sort com ponteiros
    for (int *i = inicio + 1; i <= fim; i++) { // for para ler o vetor
        int valor = *i; //valor para ser inserido
        int *j = i - 1; //aponta para o proximo elemento anterior
        while (j >= inicio && *j > valor) { //comparação para troca
            *(j + 1) = *j; //sobreposição do maior elemneto para direita
            j--; //voltar para verificar o proximo elemento a esquerda
        }
        *(j + 1) = valor; // insere o valor na posição
    }
}

void heapify(int *dados, int tamanho, int pai) {
    int maior = pai; //assumir que o maior valor é do pai
    int filho_esq = 2 * pai + 1; //calcular os filho a esquerda
    int filho_dir = 2 * pai + 2; //calcular os filho a direita
    
    // Se o filho da esquerda existir e for maior que o atual maior
    if (filho_esq < tamanho && *(dados + filho_esq) > *(dados + maior)) {
        maior = filho_esq;
    }
    
    // Se o filho da direita existir e for maior que o atual maior
    if (filho_dir < tamanho && *(dados + filho_dir) > *(dados + maior)) {
        maior = filho_dir;
    }
    
    // se o maior não for o pai trocacom os filhos
    if (maior != pai) {
        troca2(dados + pai, dados + maior);
        heapify(dados, tamanho, maior); // chamada recursiva para fazer esse processo
    }
}

void heap_sort(int *base, int tamanho) {
    //organizar elemnos em forma de arvore binaria
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        heapify(base, tamanho, i);
    }
    
    //pegar elementos um a um da arvore
    for (int i = tamanho - 1; i > 0; i--) {
        troca2(base, base + i); // coloca a raiz para o final da arvore
        heapify(base, i, 0); // reconstroi o heap com elementos restantes
    }
}

static inline int* particiona2(int *inicio, int *fim) { //trocas e pivo do quick sort
    int *meio = inicio + (fim - inicio) / 2;
    int pivo = mediana(inicio, meio, fim); //escolhe o pivo
    
    int *i = inicio - 1; 
    int *j = fim + 1; // coloca um ponteiro no começo e no final horae
    
    while (1) {
        do { i++; } while (*i < pivo); // avança com i quando tiver numeros menores que o pivo
        do { j--; } while (*j > pivo); // recua o j com valores maiores que o pivo
        
        if (i >= j) return j; // se cruzarem houve, termina os avanços
        
        troca2(i, j); // troca elementos para ficar a esquerda menores que o pivo e a direita maiores
    }
}

#define LIMITE_THREADS 10000 

void introsort_recursivo(int *inicio, int *fim, int profundidade) {
    while (fim - inicio > 16) { // usar o quick para tamanhos maiores que 16
        if (profundidade == 0) { // quando a pronfudidade chegar a 0 chama o heap
            heap_sort(inicio, (int)(fim - inicio + 1)); // heap sort
            return;
        }
        profundidade--; //diminui a profundidade
        
        int *p = particiona2(inicio, fim); //divide o vetor
        
        if (fim - inicio > LIMITE_THREADS) { // joga pra outra thread se for muito grande
            #pragma omp task shared(inicio, p)
            introsort_recursivo(inicio, p, profundidade); // recursão para o lado esquerdo
            inicio = p + 1; // continua na thread atual pro lado direiro
        } else {
            if (p - inicio < fim - (p + 1)) {
                introsort_recursivo(inicio, p, profundidade);
                inicio = p + 1;
            } else {
                introsort_recursivo(p + 1, fim, profundidade);
                fim = p;
            }
        }
    }
    
    if (inicio < fim) {
        insertion_sort(inicio, fim); // roda o insertion em valores pequenos no final
    }
}

void introsort(int *vetor, int tamanho) {
    if (tamanho < 2) return; //caso tenha so dois elementos ja esta ordenado
    int profundidade_maxima = 2 * (int)log2((double)tamanho); //limite maximo para não chegar a n2
    
    #pragma omp parallel if(tamanho > 50000) // so usa threads se o vetor for grande
    {
        #pragma omp single
        introsort_recursivo(vetor, vetor + tamanho - 1, profundidade_maxima); //roda quick e heap sort
    }
}