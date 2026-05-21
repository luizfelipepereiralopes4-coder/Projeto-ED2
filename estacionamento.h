#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#define MAX_VEICULOS 50

typedef struct{
    char placa[10];
    char modelo[30];
    int horaEntrada;
    int minutoEntrada;
}Veiculo;

extern Veiculo estacionamento[MAX_VEICULOS];
extern int quantidadeVeiculo;

void registrarEntrada();
void registrarSaida();
void listarVeiculos();

int calcular_tempo(int horaEntrada, int minutoEntrada, int horaSaida, int minutoSaida);

float calcular_valor(int minutos);

#endif