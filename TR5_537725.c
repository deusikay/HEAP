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
            heap->elems[0] = newelem; //para colocar o valor na primeira posição
            heap->P++; //para aumentar o tam da heap
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
    void *aux = heap->elems[0]; //ponteiro auxiliar que recebe a primeira posicao
    heap->elems[0] = heap->elems[heap->P - 1]; //o valor da primeira posicao é subtituida pelo proximo
    heap->elems[heap->P - 1] = NULL; 
    heap->P--;

    int pos = 0;
    int f1, f2; //variavel que indicam os filhos
    int menor;

    while(2*pos+1 < heap->P){ //para pecorrer a heap
        f1 = 2*pos+1;
        f2 = 2*pos+2;
        if(heap->elems[f1] != NULL && heap->elems[f2] != NULL){ 
            menor = heap->elems[f1] < heap->elems[f2] ? f1 : f2; //recebe o menor filho
            if(heap->elems[menor] < heap->elems[pos]){ 
                void* aux = heap->elems[menor];
                heap->elems[menor] = heap->elems[pos];
                heap->elems[pos] = aux;
                pos = menor;
            }else break;
            }else{
                if(heap->elems[f1] != NULL){
                    if(heap->elems[f1] < heap->elems[pos]){
                        void* aux = heap->elems[f1];
                        heap->elems[f1] = heap->elems[pos];
                        heap->elems[pos] = aux;
                        pos = f1;
                    }else break;
                }else{
                    if(heap->elems[f2] < heap->elems[pos]){
                        void* aux = heap->elems[f2];
                        heap->elems[f2] = heap->elems[pos];
                        heap->elems[pos] = aux;
                        pos = f2;
                    } else break;
                }
            }
        }return aux; //retorna o valor excluido
}
  
