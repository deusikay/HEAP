#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HEAP* HEAP_create(int n, COMP* compara){ //para criar a heap 
    HEAP *novo = malloc(sizeof(HEAP)); //ponteiro to tipo HEAP
    novo->N = n;
    novo->P = 0;
    novo->elems = malloc(sizeof(void *) * n); //alocando memoria para os elementos

    for (int i = 0; i < n; i++){ //para setar null em todas as posicoes
        novo->elems[i] = NULL;
    }
    novo->comparador = compara;
    return novo; //retorna o ponteiro da heap criada
}

void HEAP_add(HEAP* heap, void* newelem){
    if(heap->P < heap->N){
        if(heap->P == 0){ //se num de elemento é zero
            heap->elems[0] = newelem; //coloca o valor na primeira posição
            heap->P++; //aumenta o tam da heap
        }else{ //se já houver elementos

            int pos = heap->P; //variavel que recebe a quantidade de elementos
            int pai = (pos - 1)/2; //indice do pai
            heap->elems[pos] = newelem; //adiciona o elemento

            while (heap->comparador(heap->elems[pos], heap->elems[pai]) == 1){//para saber se elemento é menor que o pai dele
                void *aux = heap->elems[pai]; //para guardar valor pai
                heap->elems[pai] = heap->elems[pos]; //para trocar os valores do pai pelo valor pos
                heap->elems[pos] = aux; //pos recebe o valor pai
                pos = pai; //pos se torna o pai
                pai = (pos - 1)/2;
                if (pai < 0) break;
            }
            heap->P++;
        }
    }
}

void* HEAP_remove(HEAP* heap){
    void *aux = heap->elems[0]; //ponteiro auxiliar que recebe o elemento a ser removido
    heap->elems[0] = heap->elems[heap->P - 1]; //o valor da primeira posicao é subtituida pelo último valor
    heap->elems[heap->P - 1] = NULL;  //ultima posição recebe null
    heap->P--;

    int pos = 0; //variavel de iteração
    int f1, f2; //variavel que indicam os filhos
    int menor;

    while(2*pos+1 < heap->P){ //para pecorrer a heap
        f1 = 2*pos+1; //indices
        f2 = 2*pos+2;
        if(heap->elems[f1] != NULL && heap->elems[f2] != NULL){ //caso o pai tenha dois filhos
            menor = heap->elems[f1] < heap->elems[f2] ? f1 : f2; //recebe o menor filho
            if(heap->elems[menor] < heap->elems[pos]){ //caso o filho seja menor que o pai, elementos são trocados
                void* aux = heap->elems[menor]; //aux recebe o menor filho
                heap->elems[menor] = heap->elems[pos]; //o filho menor recebe o pai
                heap->elems[pos] = aux; //o que era o pai se torna o filho menor
                pos = menor;
            }else break;
            }else{ //caso o pai tenha apenas um filho
                if(heap->elems[f1] != NULL){ //se apenas o filho 1 existir
                    if(heap->elems[f1] < heap->elems[pos]){ //se o filho for menor que pai, então ocorre a mudança entre eles
                        void* aux = heap->elems[f1];
                        heap->elems[f1] = heap->elems[pos];
                        heap->elems[pos] = aux;
                        pos = f1;
                    }else break;
                }else{ //se apenas o filho 2 existir
                    if(heap->elems[f2] < heap->elems[pos]){ ////se o filho for menor que pai, então ocorre a mudança entre eles
                        void* aux = heap->elems[f2];
                        heap->elems[f2] = heap->elems[pos];
                        heap->elems[pos] = aux;
                        pos = f2;
                    } else break;
                }
            }
        }return aux; //retorna o valor excluido
}
  
