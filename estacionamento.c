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

float calcular_valor(int minuto, int tipo){

    if(tipo == 2){
        if(minuto <= 60) return 3.0;
        else if(minuto <= 120) return 5.0;
        else if(minuto <= 180) return 7.0;
        else return 10.0;
    }

    else if(tipo == 3){
        if(minuto <= 60) return 8.0;
        else if(minuto <= 120) return 12.0;
        else if(minuto <= 180) return 16.0;
        else return 20.0;
    }

    else{
        if(minuto <= 60) return 5.0;
        else if(minuto <= 120) return 8.0;
        else if(minuto <= 180) return 10.0;
        else return 15.0;
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

        //Validação do tipo 
        do{
            printf("Tipo (1- Carro / 2- Moto / 3- Caminhao): ");
            scanf(" %d", &estacionamento[quantidadeVeiculo].tipo);

            if(estacionamento[quantidadeVeiculo].tipo < 1 || estacionamento[quantidadeVeiculo].tipo > 3){

                printf("Tipo Invalido! Digite 1, 2, ou 3.\n");
            }

        } while(estacionamento[quantidadeVeiculo].tipo < 1 || estacionamento[quantidadeVeiculo].tipo > 3);

        int horaValida = 0;

        //Validação de Horário
        do{
            printf("Hora de Entrada (0-23): ");
            scanf(" %d", &estacionamento[quantidadeVeiculo].horaEntrada);

            printf("Minuto de Entrada (0-59): ");
            scanf(" %d", &estacionamento[quantidadeVeiculo].minutoEntrada);

            if(estacionamento[quantidadeVeiculo].horaEntrada < 0 || estacionamento[quantidadeVeiculo].horaEntrada > 23 || estacionamento[quantidadeVeiculo].minutoEntrada < 0 || estacionamento[quantidadeVeiculo].minutoEntrada > 59){

                printf("Horario Invalido! Tente Novamente.\n");

            }
            else{
                horaValida = 1;
            }

        } while(horaValida == 0);

        quantidadeVeiculo++;

        salvar_arquivo();

        printf("\nVeiculo cadastrado com sucesso!\n");

        printf("Vagas Disponiveis: %d/%d\n", MAX_VEICULOS - quantidadeVeiculo, MAX_VEICULOS);
    }


void listarVeiculos(){

    if(quantidadeVeiculo == 0){
        printf("\nNenhum veiculo estacionado.\n");
        return;
    }

    printf("\n========== VEICULOS ==========\n");
    printf("Vagas Ocupadas: %d | Vagas Disponiveis: %d\n", quantidadeVeiculo, MAX_VEICULOS - quantidadeVeiculo);

    for(int i = 0; i < quantidadeVeiculo; i++){

        printf("\nVeiculo %d\n", i + 1);

        printf("Placa: %s\n", estacionamento[i].placa);

        printf("Modelo: %s\n", estacionamento[i].modelo);

        if(estacionamento[i].tipo == 1)
            printf("Tipo: Carro\n");
        else if(estacionamento[i].tipo == 2)
            printf("Tipo: Moto\n");
        else if(estacionamento[i].tipo == 3)
            printf("Tipo: Caminhao\n");


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
            int horaValida = 0;

            do{
                printf("Hora da Saida: ");
                scanf(" %d", &horaSaida);

                printf("Minutos da Saida: ");
                scanf(" %d", &minutoSaida);

                int tempoVerificado = calcular_tempo(estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada, horaSaida, minutoSaida);

                if(tempoVerificado < 0){

                    printf("Horario de Saida Invalido! ");
                    printf("Deve ser apos %02d:%02d.\n", estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);
                }
                else{
                    horaValida = 1;
                }
            } while(horaValida == 0);

            int tempo = calcular_tempo(estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada, horaSaida, minutoSaida);

            float valor = calcular_valor(tempo, estacionamento[i].tipo);

            printf("\nTempo estacionado: %d minutos\n", tempo);

            printf("Valor a pagar: R$ %2.f\n", valor);

            for(int j = i; j < quantidadeVeiculo - 1; j++){

                estacionamento[j] = estacionamento[j + 1];
            }
            quantidadeVeiculo--;

            salvar_arquivo();

            printf("\nSaida registrada com sucesso!\n");

            printf("Vagas Disponiveis: %d/%d\n", MAX_VEICULOS - quantidadeVeiculo, MAX_VEICULOS);

            return;
        }
    }

    printf("\nVeiculo nao encontrado.\n");
}


















