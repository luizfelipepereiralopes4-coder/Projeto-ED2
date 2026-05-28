#include<stdio.h>

#include "estacionamento.h"
#include "arquivo.h"

int main(){

    int opcao;

    carregar_arquivo();

    do{
        
        printf("\n");
        printf("==============================\n");
        printf("    SISTEMA DE ESTACIONAMENTO\n");
        printf("==============================\n");

        printf(" Vagas: %d/%d Disponiveis\n", MAX_VEICULOS - quantidadeVeiculo, MAX_VEICULOS);

        printf("==============================\n");
        printf("1 - Registrar entrada\n");
        printf("2 - Registrar saida\n");       
        printf("3 - Listar Veiculos\n");
        printf("0 - Encerrar sistema\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){

            case 1: registrarEntrada();
            break;

            case 2: registrarSaida();
            break;

            case 3: listarVeiculos();
            break;

            case 0: printf("\nEncerrando sistema...\n");
            break;

            default: printf("\nOpcao invalida!\n");

      }
    } while(opcao != 0);

return 0;

}





