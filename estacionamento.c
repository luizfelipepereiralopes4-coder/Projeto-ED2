#include<stdio.h>
#include<string.h>
#include<ctype.h>

#include "estacionamento.h"
#include "arquivo.h"

Veiculo estacionamento[MAX_VEICULOS];

int quantidadeVeiculo = 0;

int validar_PlacaMercosul(char *placa){

    if(strlen(placa) != 7){
        return 0;
    }

    if(!isalpha(placa[0]) || !isalpha(placa[1]) || !isalpha(placa[2])){
        return 0;
    }

    if(!isdigit(placa[3])){
        return 0;
    }

    if(!isalpha(placa[4])){
        return 0;
    }

    if(!isdigit(placa[5]) || !isdigit(placa[6])){
        return 0;
    }

    return 1;
}

int calcular_tempo(int horaEntrada, int minutoEntrada, int horaSaida, int minutoSaida){
    
    int entrada = horaEntrada * 60 + minutoEntrada;

    int saida = horaSaida * 60 + minutoSaida;

    return saida - entrada;
}

float calcular_valor(int minuto, int tipo){

    if(tipo == 2){
        if(minuto <= 60) return 8.0;
        else if(minuto <= 120) return 12.0;
        else if(minuto <= 180) return 15.0;
        else return 18.0;
    }

    else if(tipo == 3){
        if(minuto <= 60) return 12.0;
        else if(minuto <= 120) return 18.0;
        else if(minuto <= 180) return 25.0;
        else return 30.0;
    }

    else{
        if(minuto <= 60) return 10.0;
        else if(minuto <= 120) return 15.0;
        else if(minuto <= 180) return 18.0;
        else return 20.0;
    }
}

    void registrarEntrada(){

        if(quantidadeVeiculo>= MAX_VEICULOS){
            printf(VERMELHO "\nEstacionamento Lotado!\n" RESET);
            return;
        }

        printf(NEGRITO CIANO "\n========== ENTRADA ==========\n" RESET);

        // Validação da Placa
        do{
            printf("Placa - (Formato Mercosul):  ");
            scanf("%s", estacionamento[quantidadeVeiculo].placa);

            for(int i = 0; i < strlen(estacionamento[quantidadeVeiculo].placa); i++){

                estacionamento[quantidadeVeiculo].placa[i] = toupper(estacionamento[quantidadeVeiculo].placa[i]);
            }

            if(!validar_PlacaMercosul(estacionamento[quantidadeVeiculo].placa)){

                printf(VERMELHO"Placa Invalida! Insira Novamente.\n" RESET);
            }
        } while(!validar_PlacaMercosul(estacionamento[quantidadeVeiculo].placa));

        //Verificação da Placa Duplicada
        int placa_duplicada = 0;

        for(int i = 0; i < quantidadeVeiculo; i++){

            if(strcmp(estacionamento[i].placa, estacionamento[quantidadeVeiculo].placa) == 0){

                placa_duplicada = 1;
                break;
            }
        }

        if(placa_duplicada){
            
            printf(VERMELHO"\nVeiculo ja estacionado!\n" RESET);
            return;
        }

        printf("Modelo: ");

        getchar();
        fgets(estacionamento[quantidadeVeiculo].modelo, 30, stdin);

        int len = strlen(estacionamento[quantidadeVeiculo].modelo);

        if(estacionamento[quantidadeVeiculo].modelo[len - 1] == '\n'){
            estacionamento[quantidadeVeiculo].modelo[len - 1] = '\0';
        }

        //Validação do tipo 
        do{
            printf("Tipo (1- Carro / 2- Moto / 3- Caminhao): ");
            scanf(" %d", &estacionamento[quantidadeVeiculo].tipo);

            if(estacionamento[quantidadeVeiculo].tipo < 1 || estacionamento[quantidadeVeiculo].tipo > 3){

                printf(VERMELHO "Tipo Invalido! Digite 1, 2, ou 3.\n" RESET);
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

                printf(VERMELHO "Horario Invalido! Tente Novamente.\n" RESET);

            }
            else{
                horaValida = 1;
            }

        } while(horaValida == 0);

        quantidadeVeiculo++;

        salvar_arquivo();

        printf(VERDE "\nVeiculo cadastrado com sucesso!\n" RESET);

        printf(AMARELO "Vagas Disponiveis: %d/%d\n" RESET, MAX_VEICULOS - quantidadeVeiculo, MAX_VEICULOS);

        // Pausa após entrada
        printf(AMARELO"\nPressione Enter para voltar ao menu..." RESET);
        getchar();
        getchar();
    }


void listarVeiculos(){

    if(quantidadeVeiculo == 0){
        printf(AMARELO "\nNenhum veiculo estacionado.\n" RESET);
        return;
    }

    printf(NEGRITO CIANO "\n========== VEICULOS ==========\n" RESET);
    printf(AMARELO "Vagas Ocupadas: %d | Vagas Disponiveis: %d\n" RESET, quantidadeVeiculo, MAX_VEICULOS - quantidadeVeiculo);

    printf(NEGRITO AMARELO "\n---------- CARROS ----------\n" RESET);

    int contador = 0;

    for(int i = 0; i < quantidadeVeiculo; i++){

        if(estacionamento[i].tipo == 1){
            contador++;

            printf(NEGRITO "\nVeiculo %d\n" RESET, contador);
            printf(VERDE "Placa: %s\n" RESET, estacionamento[i].placa);
            printf(VERDE "Modelo %s\n" RESET, estacionamento[i].modelo);
            printf(VERDE "Entrada: %02d:%02d\n" RESET, estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);

            printf(CIANO"----------------------------------\n" RESET);
        }
    }

    if(contador == 0){
        printf(AMARELO "Nenhum veivulo encontrado.\n" RESET);
    }

    printf(NEGRITO AMARELO "\n---------- MOTOS ----------\n" RESET);

    contador = 0;

    for(int i = 0; i < quantidadeVeiculo; i++){

        if(estacionamento[i].tipo == 2){
            contador++;

            printf(NEGRITO "\nVeiculo %d\n" RESET, contador);
            printf(VERDE "Placa: %s\n" RESET, estacionamento[i].placa);
            printf(VERDE "Modelo %s\n" RESET, estacionamento[i].modelo);
            printf(VERDE "Entrada: %02d:%02d\n" RESET, estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);

            printf(CIANO "-------------------------------------\n" RESET);
        }
    }

    if(contador == 0){
        printf(AMARELO "Nenhuma moto encontrada.\n" RESET);
    }

    printf(NEGRITO AMARELO "\n----------- CAMINHAO ----------\n" RESET);

    contador = 0;

    for(int i = 0; i < quantidadeVeiculo; i++){

        if(estacionamento[i].tipo == 3){
            contador++;

            printf(NEGRITO "\nVeiculo %d\n" RESET, contador);
            printf(VERDE "Placa: %s\n" RESET, estacionamento[i].placa);
            printf(VERDE "Modelo %s\n" RESET, estacionamento[i].modelo);
            printf(VERDE "Entrada: %02d:%02d\n" RESET, estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);

            printf(CIANO "-------------------------------------\n" RESET);
        }
    }

    if(contador == 0){
        printf(AMARELO "Nenhum caminhao encontrado.\n" RESET);
    }
}


// Busca por Modelo
void busca_por_modelo(){

    if(quantidadeVeiculo == 0){
        printf(VERMELHO "\nNenhum veiculo estacionado.\n" RESET);
        return;
    }

    char modelo[30];

    printf(NEGRITO CIANO "\n========== BUSCA POR MODELO ==========\n" RESET);

    printf("Digite o modelo: ");


    while(getchar() != '\n');

    fgets(modelo, 30, stdin);

    int len = strlen(modelo);
    if(modelo[len - 1] == '\n'){
        modelo[len - 1] = '\0';
    }

    int encontrados = 0;

    for(int i = 0; i < quantidadeVeiculo; i++){

        if(strcmp(estacionamento[i].modelo, modelo) == 0){
            encontrados++;

            printf(NEGRITO"\nVeiculo %d\n" RESET, encontrados);
            printf(VERDE "Placa: %s\n" RESET, estacionamento[i].placa);
            printf(VERDE "Modelo: %s\n" RESET, estacionamento[i].modelo);

            if(estacionamento[i].tipo == 1)
                printf(VERDE"Tipo: Carro\n" RESET);
            else if(estacionamento[i].tipo == 2)
                printf(VERDE"Tipo: Moto\n" RESET);
            else if(estacionamento[i].tipo == 3)
                printf(VERDE"Tipo: Caminhao\n" RESET);  
                
            printf(VERDE"Entrada: %02d:%02d\n" RESET, estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);
            
            printf(CIANO"------------------------------------\n" RESET);
        }
    }

    if(encontrados == 0){
        printf(VERMELHO"\nNenhum veiculo do modelo \"%s\" encontrado.\n" RESET, modelo);
    }
    else{
        printf(AMARELO"\n%d veiculo(s) do modelo \"%s\" encontrado(s).\n" RESET, encontrados, modelo);
    }

    printf(AMARELO"\nPressione Enter para voltar ao menu..." RESET);
    getchar();
    getchar();
}

// Função para buscar a placa do veículo
void busca_por_placa(){

    if(quantidadeVeiculo == 0){
        printf(VERMELHO "\nNenhum veiculo estacionado.\n" RESET);
        return;
    }

    char placa[10];

    printf(NEGRITO CIANO "\n========== BUSCA POR PLACA =========\n" RESET);

    printf("Digite a placa: ");
    scanf("%s", placa);

    for(int i = 0; i < strlen(placa); i++){
        placa[i] = toupper(placa[i]);
    }

    for(int i = 0; i < quantidadeVeiculo; i++){

        if(strcmp(estacionamento[i].placa, placa) == 0){
            printf(NEGRITO CIANO "\n========== VEICULO ENCONTRADO ==========\n" RESET);

            printf("Placa: " VERDE "%s\n" RESET, estacionamento[i].placa);
            printf("Modelo: " VERDE "%s\n" RESET, estacionamento[i].modelo);


            if(estacionamento[i].tipo == 1)
                printf("Tipo:" VERDE "Carro\n" RESET);
            else if(estacionamento[i].tipo == 2)
                printf("Tipo:" VERDE "Moto\n" RESET);
            else if(estacionamento[i].tipo == 3)
                printf("Tipo:" VERDE "Caminhao\n" RESET);                
            printf("Entrada:" VERDE "%02d:%02d\n" RESET, estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);
            
            printf(CIANO "----------------------------------------------\n" RESET);
            
            printf(AMARELO "Pressione Enter para voltar ao menu..." RESET);
            getchar();
            getchar();

            return;
        }
    }

    printf(VERMELHO "\nVeiculo com placa \"%s\" nao encontrado.\n" RESET, placa);

    printf(AMARELO "\nPressione Enter para voltar ao menu..." RESET);
    getchar();
    getchar();

}

void registrarSaida(){

    if(quantidadeVeiculo == 0){
        printf(VERMELHO"\nNenhum veiculo estacionado para registrar saida!\n" RESET);
        return;
    }

    char placa[10];

    printf(NEGRITO CIANO"\n========== SAIDA ==========\n" RESET);

    printf("Digite a placa do veiculo: ");
    scanf("%s", placa);

    for(int i = 0; i < strlen(placa); i++){
        placa[i] = toupper(placa[i]);
    }

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

                    printf(VERMELHO"Horario de Saida Invalido! " RESET);
                    printf(VERMELHO"Deve ser apos %02d:%02d.\n" RESET, estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada);
                }
                else{
                    horaValida = 1;
                }
            } while(horaValida == 0);

            int tempo = calcular_tempo(estacionamento[i].horaEntrada, estacionamento[i].minutoEntrada, horaSaida, minutoSaida);

            float valor = calcular_valor(tempo, estacionamento[i].tipo);

            printf(AMARELO"\nTempo estacionado: %d minutos\n" RESET, tempo);

            printf(NEGRITO VERDE"Valor a pagar: R$ %.2f\n" RESET, valor);

            for(int j = i; j < quantidadeVeiculo - 1; j++){

                estacionamento[j] = estacionamento[j + 1];
            }
            quantidadeVeiculo--;

            salvar_arquivo();

            printf(VERDE"\nSaida registrada com sucesso!\n" RESET);

            printf(AMARELO"Vagas Disponiveis: %d/%d\n" RESET, MAX_VEICULOS - quantidadeVeiculo, MAX_VEICULOS);

            printf(AMARELO"\nPressione Enter para voltar ao menu..." RESET);
            getchar();
            getchar();

            return;
        }
    }

    printf(VERMELHO"\nVeiculo nao encontrado.\n" RESET);
}


















