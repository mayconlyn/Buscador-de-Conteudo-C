/**
 * @author Maycon Lyncoln Garcia
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define diretorio "C:\\Users\\Mayco\\Documents\\PUCPR\\Estrutura de Dados\\Arq\\"

/*
*Estrutura Responsável por armazenar os termos que serão pesquisados na arvore
*/
struct palavras
{
    char termo[50];

} palavras[100];

struct ListaArquivos
{

    char nome_arquivo[50];
    int frequencia;
    struct lista* prox;

};
typedef struct ListaArquivos Lista;

struct Arvore
{
    char dado[50];
    Lista* listaArqFreq;
    struct noArvore* dir;
    struct noArvore* esq;

};
typedef struct Arvore no;

Lista* listaArquivo;

Lista* init_lista (void);
void insere_ordenado(int freq, char* nomeArq);
void imprime(Lista* listaArv);
void le_arquivo(char* nomeArq, char* palavra2);
void le_diretorio(char * palavra);
void menu();

/*metodos da árvore*/
Lista* buscar_ordenada(no* a, char * termo);
no* insereArvore(char * termo, no* a, Lista * lis);
no* init_arvore(void);

int main(void)
{
    int cont=0, i;
    no* arv = init_arvore();
    Lista* auxLista = init_lista();
    Lista* obj;

    menu();

    while(1)
    {

        fflush(stdin);
        scanf("%s", &palavras[cont].termo);

        if(strcmp(palavras[cont].termo, "0")==0)
            break;

        listaArquivo = init_lista();// inicia a lista
        le_diretorio(palavras[cont].termo); // abre os arquivos
        arv = insereArvore(palavras[cont].termo, arv, listaArquivo); // insere na árvore o termo e a lista com os arquivos

        cont++;
    }

    /*Busca os termos na arvore e insere em uma lista somando
    as frequencias dos arquivos de mesmo nome*/

    listaArquivo = init_lista();
    for(i=0; i<cont; i++)
    {

        auxLista = buscar_ordenada(arv, palavras[i].termo);
        for(obj = auxLista; obj != NULL; obj = obj->prox)
        {
            insere_ordenado(obj->frequencia, obj->nome_arquivo);
        }
    }

    //Ordena a lista final
    auxLista = init_lista();
    auxLista = listaArquivo;

    obj = init_lista();
    listaArquivo = init_lista();
    for(obj = auxLista; obj != NULL; obj = obj->prox)
    {
        insere_ordenado(obj->frequencia, obj->nome_arquivo);
    }
    imprime(listaArquivo);

    return 0;
}

void menu()
{

    printf("\n          _______________________________________\n");
    printf("         |        ----- PUC - PR -----           |\n");
    printf("         | ANALISE E DESENVOLVIMENTO DE SISTEMAS |\n");
    printf("         |         MAYCON LYNCOLN GARCIA         |\n");
    printf("         |_______________________________________|\n");

    printf("\nDigite os termos a serem buscados (separados pela tecla ENTER)\nou digite 0 para Sair\n\n");
}

no* init_arvore(void)
{
    return NULL;

}

Lista* buscar_ordenada(no* a, char * termo)
{

    if(a==NULL)
        return NULL;
    if(strcmp(a->dado, termo)==0) //Localizou
    {
        return a->listaArqFreq;
    }
    if(termo[0]<=a->dado[0]) //Percorre pela esquerda, caso o numero seja menor do que a raiz
    {
        buscar_ordenada(a->esq,termo);
    }
    else
    {
        buscar_ordenada(a->dir,termo);
    }
}

/*Metódo recursivo responsável por inserir na arvore ordenadamente
onde os termos menores que raiz (comparadas pela primeira letra)
são colocados à esquerda e os maiores a direita
*/
no* insereArvore(char * termo, no* arvore, Lista* listaArqFreq)
{

    if(arvore==NULL) //Se não houver nó
    {
        arvore = (no *) malloc(sizeof(no)); //cria
        strcpy(arvore->dado, termo);
        arvore->listaArqFreq = listaArqFreq; //Insere o valor
        arvore->esq=NULL; //Cria filho esquerdo
        arvore->dir=NULL; //Cria filho direito
    }
    else if(termo[0]<=arvore->dado[0]) //Se o numero for menor do que a raiz, percorre a esquerda.
    {

        arvore->esq = insereArvore(termo, arvore->esq, listaArqFreq);
    }
    else
    {
        arvore->dir = insereArvore(termo, arvore->dir, listaArqFreq);
    }
    return arvore;
}

/*metódo responsável por inicializar a lista*/
Lista* init_lista (void)
{
    return NULL;

}

/*Método responsável por inserir um elemento dentro da lista
de forma ordenada pela frequência da palavra*/
void insere_ordenado(int freqDoTermo, char* nomeArq)
{
    //cria um novo nodo
    Lista* novoElemento = (Lista*) malloc(sizeof(Lista));
    novoElemento->frequencia = freqDoTermo;
    strcpy(novoElemento->nome_arquivo, nomeArq);

    Lista* ant = NULL;
    Lista* aux = listaArquivo;

    while(aux != NULL && strcmp(aux ->nome_arquivo, nomeArq)!=0)
    {

        ant = aux;
        aux = aux->prox;
    }
    /*caso exista o nome do arquivo na lista, soma-se a frequencia*/
    if(aux!=NULL)
    {

        aux->frequencia+=freqDoTermo;
    }

    else
    {
        ant = NULL;
        aux = listaArquivo;
        //verifica a posição até encontrar uma frequencia menor
        while(aux != NULL && aux ->frequencia > freqDoTermo)
        {
            ant = aux;
            aux = aux->prox;
        }
        //se anterior for null, insere na primeira posição
        if(ant == NULL)
        {
            novoElemento->prox = listaArquivo;
            listaArquivo = novoElemento;
        }
        /*se não o novo elemento -> prox recebe o o proximo do anterior
        e o anterior recebe o novo como proximo*/
        else
        {
            novoElemento ->prox = ant->prox;
            ant->prox = novoElemento;
        }
    }
}

//metodo responsável por mostrar na tela a lista
void imprime(Lista* listaArv)
{
    Lista* imprime;
    printf("\n            |-------- Lista Ordenada --------|\n");
    for(imprime = listaArv; imprime!= NULL; imprime = imprime->prox)
        printf("            |Arquivo: %s  Relevancia: %d|\n", imprime->nome_arquivo, imprime->frequencia);
}

// metodo responsável por ler um arquivo
void le_arquivo(char* nomeArq, char * termoDigitado)
{
    char termoDoArquivo[30];
    char destino[100] = diretorio;
    int freqDoTermo = 0, i, flag = 0;
    FILE *arq;

    strcat(destino,nomeArq);
    arq = fopen(destino, "r");/*abre arquivo para leitura e escrita r+*/

    if(arq != NULL)
    {

        while((fscanf(arq, "%s", termoDoArquivo))!=EOF)
        {
            //conta quantas vezes a palavra aparece no arquivo comparando letra por letra

            for(i=0; i<strlen(termoDigitado); i++)
            {
                if(termoDoArquivo[i]==termoDigitado[i])
                {
                    flag=1;

                }
                else
                {
                    flag=0;
                    break;
                }
            }
            if(flag==1)
                freqDoTermo++;
        }
        insere_ordenado(freqDoTermo, nomeArq);
    }
}

void le_diretorio(char * termoDigitado)
{
    DIR *dir;
    struct dirent *lsdir;

    dir = opendir(diretorio);

    /* encontra os arquivos da pasta e passa por parâmetro o nome do arquivo */
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        le_arquivo(lsdir->d_name, termoDigitado);

    }
    closedir(dir);

}
