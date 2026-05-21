#include<stdio.h>

#include "estacionamento.h"
#include "arquivo.h"

void salvar_arquivo(){

    FILE *arquivo;

    arquivo = fopen("veiculos.dat", "wb");

    if(arquivo == NULL){

        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    fwrite(&quantidadeVeiculo, sizeof(int), 1, arquivo);

    fwrite(estacionamento, sizeof(Veiculo), quantidadeVeiculo, arquivo);

    fclose(arquivo);
}

void carregar_arquivo(){

    FILE *arquivo;

    arquivo = fopen("veiculos.dat", "rb");

    if(arquivo == NULL){
        return;
    }

    fread(&quantidadeVeiculo, sizeof(int), 1, arquivo);

    fread(estacionamento, sizeof(Veiculo), quantidadeVeiculo, arquivo);

    fclose(arquivo);

    printf("\n%d Veiculo(s) carregado(s) do arquivo.\n", quantidadeVeiculo);
}