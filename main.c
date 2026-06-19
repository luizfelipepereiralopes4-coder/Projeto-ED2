#include<stdio.h>
#include<stdlib.h>

#include "estacionamento.h"
#include "arquivo.h"

int main(){

    int opcao;

    carregar_arquivo();

    do{

        printf("\n");
        printf(NEGRITO CIANO "==============================\n" RESET);
        printf(NEGRITO CIANO "   SISTEMA DE ESTACIONAMENTO\n" RESET);
        printf(NEGRITO CIANO "==============================\n" RESET);

        if(quantidadeVeiculo >= MAX_VEICULOS){
            printf(VERMELHO " Vagas: %d/%d Disponiveis\n" RESET,
                   MAX_VEICULOS - quantidadeVeiculo, MAX_VEICULOS);
        }
        else{
            printf(AMARELO " Vagas: %d/%d Disponiveis\n" RESET,
                   MAX_VEICULOS - quantidadeVeiculo, MAX_VEICULOS);
        }

        printf(NEGRITO CIANO "==============================\n" RESET);

        printf(BRANCO "1 - Registrar entrada\n" RESET);
        printf(BRANCO "2 - Registrar saida\n" RESET);
        printf(BRANCO "3 - Listar Veiculos\n" RESET);
        printf(BRANCO "4 - Buscar por modelo\n" RESET);
        printf(BRANCO "5 - Busca por placa\n" RESET);
        printf(BRANCO "6 - Limpar Tela\n" RESET);
        printf(BRANCO "0 - Encerrar sistema\n" RESET);
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){

            case 1: registrarEntrada();
            break;

            case 2: registrarSaida();
            break;

            case 3: 
                listarVeiculos();
                printf(AMARELO"\nPressione Enter para voltar ao menu..." RESET);
                getchar();
                getchar();
            break;

            case 4: busca_por_modelo();
            break;  
            
            case 5: busca_por_placa();
            break;
            
            case 6:
                system("cls");
            break;    

            case 0: printf(AMARELO "\nEncerrando sistema...\n" RESET);
            break;

            default: printf(VERMELHO "\nOpcao invalida!\n" RESET);
        }

    } while(opcao != 0);

    return 0;
}