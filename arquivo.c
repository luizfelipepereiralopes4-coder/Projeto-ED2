#include<stdio.h>

#include "estacionamento.h"
#include "arquivo.h"

void salvar_arquivo(){

    FILE *arquivo;

    arquivo = fopen("veiculos.txt", "w");

    if(arquivo == NULL){

        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "%d\n", quantidadeVeiculo);

    for(int i = 0; i < quantidadeVeiculo; i++){

        fprintf(arquivo, "%s %s %d %d %d\n", estacionamento[i].placa, estacionamento[i].modelo, estacionamento[i].tipo, estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);
    }

    fclose(arquivo);
}

void carregar_arquivo(){

    FILE *arquivo;

    arquivo = fopen("veiculos.txt", "r");

    if(arquivo == NULL){
        return;
    }

    fscanf(arquivo, "%d", &quantidadeVeiculo);

    for(int i = 0; i < quantidadeVeiculo; i++){

        fscanf(arquivo, "%s %s %d %d %d", estacionamento[i].placa, estacionamento[i].modelo, estacionamento[i].tipo, estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);
        
    }

    fclose(arquivo);

    printf("\n%d Veiculo(s) carregado(s) do arquivo.\n", quantidadeVeiculo);
}