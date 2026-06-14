#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#define MAX_VEICULOS 50

#define RESET   "\033[0m"
#define NEGRITO "\033[1m"
#define VERDE   "\033[32m"
#define VERMELHO    "\033[31m"  
#define AMARELO "\033[33m"
#define CIANO   "\033[36m"
#define BRANCO  "\033[37m"


typedef struct{
    char placa[10];
    char modelo[30];
    int tipo;
    int horaEntrada;
    int minutoEntrada;
}Veiculo;

extern Veiculo estacionamento[MAX_VEICULOS];
extern int quantidadeVeiculo;

void registrarEntrada();
void registrarSaida();
void listarVeiculos();
void busca_por_modelo();

int calcular_tempo(int horaEntrada, int minutoEntrada, int horaSaida, int minutoSaida);

float calcular_valor(int minutos, int tipo);

#endif