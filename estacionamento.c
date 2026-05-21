#include<stdio.h>
#include<string.h>

#include "estacionamento.h"
#include "arquivo.h"

Veiculo estacionamento[MAX_VEICULOS];

int quantidadeVeiculo = 0;

int calcular_tempo(int horaEntrada, int minutoEntrada, int horaSaida, int minutoSaida){
    
    int entrada = horaEntrada * 60 + minutoEntrada;

    int saida = horaSaida * 60 + minutoSaida;

    return saida - entrada;
}

float calcular_valor(int minutos){

    if(minutos <= 60){
        return 5.0;
    }

    else if(minutos <= 120){
        return 8.0;
    }

    else if(minutos <= 180){
        return 10.0;
    }

    else{
        return 15.0;
    }
}

    void registrarEntrada(){

        if(quantidadeVeiculo>= MAX_VEICULOS){
            printf("\nEstacionamento Lotado!\n");
            return;
        }

        printf("\n========== ENTRADA ==========\n");

        printf("Placa: ");
        scanf("%s", estacionamento[quantidadeVeiculo].placa);

        printf("Modelo: ");
        scanf("%s", estacionamento[quantidadeVeiculo].modelo);

        printf("Hora de Entrada (0-23): ");
        scanf("%d", &estacionamento[quantidadeVeiculo].horaEntrada);

        printf("Minuto de Entrada (0-59): ");
        scanf("%d", &estacionamento[quantidadeVeiculo].minutoEntrada);

        quantidadeVeiculo++;

        salvar_arquivo();

        printf("\nVeiculo cadastrado com sucesso!\n");
    }


void listarVeiculos(){

    if(quantidadeVeiculo == 0){
        printf("\nNenhum veiculo estacionado.\n");
        return;
    }

    printf("\n========== VEICULOS ==========\n");

    for(int i = 0; i < quantidadeVeiculo; i++){

        printf("\nVeiculo %d\n", i + 1);

        printf("Placa: %s\n", estacionamento[i].placa);

        printf("Modelo: %s\n", estacionamento[i].modelo);

        printf("Entrada: %02d:%02d\n", estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);

        printf("----------------------------------\n");
    }
}

void registrarSaida(){

    char placa[10];

    printf("\n========== SAIDA ==========\n");

    printf("Digite a placa do veiculo: ");
    scanf("%s", placa);

    for(int i = 0; i < quantidadeVeiculo; i++){

        if(strcmp(estacionamento[i].placa, placa) == 0){

            int horaSaida;
            int minutoSaida;

            printf("Hora da saida: ");
            scanf("%d", &horaSaida);
            
            printf("Minuto da Saida: ");
            scanf("%d", &minutoSaida);

            int tempo = calcular_tempo(estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada, horaSaida, minutoSaida);

            float valor = calcular_valor(tempo);

            printf("\nTempo estacionado: %d minutos\n", tempo);

            printf("Valor a pagar: R$ %2.f\n", valor);

            for(int j = i; j < quantidadeVeiculo - 1; j++){

                estacionamento[j] = estacionamento[j + 1];
            }
            quantidadeVeiculo--;

            salvar_arquivo();

            printf("\nSaida registrada com sucesso!\n");

            return;
        }
    }

    printf("\nVeiculo nao encontrado.\n");
}


















