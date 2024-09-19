#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    float salario;
    char departamento[30];
} Registro;

void adicionarRegistro(const char *nomeArquivo, Registro reg) {
    FILE *arquivo = fopen(nomeArquivo, "ab"); 
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        exit(EXIT_FAILURE);
    }

    fwrite(&reg, sizeof(Registro), 1, arquivo); 
    fclose(arquivo);
}

Registro coletarDados() {
    Registro reg;
    printf("Digite o ID: ");
    scanf("%d", &reg.id);

    printf("Digite o Nome: ");
    while (getchar() != '\n');
    fgets(reg.nome, sizeof(reg.nome), stdin);
    reg.nome[strcspn(reg.nome, "\n")] = '\0';

    printf("Digite o Salário: ");
    scanf("%f", &reg.salario);

    printf("Digite o Departamento: ");
    while (getchar() != '\n');
    fgets(reg.departamento, sizeof(reg.departamento), stdin);
    reg.departamento[strcspn(reg.departamento, "\n")] = '\0';

    return reg;
}

void lerRegistros(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); 
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        exit(EXIT_FAILURE);
    }

    Registro reg;
    printf("\n--- Registros Armazenados ---\n");
    while (fread(&reg, sizeof(Registro), 1, arquivo) == 1) {
        printf("ID: %d\n", reg.id);
        printf("Nome: %s\n", reg.nome);
        printf("Salário: %.2f\n", reg.salario);
        printf("Departamento: %s\n", reg.departamento);
        printf("---------------------------\n");
    }

    fclose(arquivo);
}

int main() {
    int opcao;
    const char *nomeArquivo = "registros.dat";

    do {
        printf("\n--- Sistema de Registros ---\n");
        printf("1. Adicionar Novo Registro\n");
        printf("2. Visualizar Registros\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Registro novoReg = coletarDados();
                adicionarRegistro(nomeArquivo, novoReg);
                printf("Registro adicionado com sucesso!\n");
                break;
            }
            case 2:
                lerRegistros(nomeArquivo);
                break;
            case 3:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 3);

    return 0;
}
