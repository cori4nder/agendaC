#include <stdio.h>
#include <stdlib.h> // limpa o cabeçalho
#include <string.h>

#define MAXNOME 30
#define MAXAGENDA 5

typedef struct {
    int matricula;
    char nome[MAXNOME + 1];
} Aluno;

int proxInd = 0; // -> [posição livre da agenda]
                 // ## (possui caráter global.é uma variável definida fora de uma função que é interpretada em todo programa.)

Aluno initAgenda [MAXAGENDA];

void telaPrincipal() {
    printf("\n\t\t** MENU **\n");
    printf("\t\t----------\n");
    printf("[I] - Incluir\n");
    printf("[L] - Listar\n");
    printf("[C] - Carregar Informacoes do disco para RAM\n");
    printf("[G] - Gravar da RAM para o Disco\n");
    printf("[F] - Finalizar\n\n");
    printf("[*]   Digite a opcao: ");
}

void opcIncluir() {
    printf("\n\t\t** INCLUIR **\n");
    printf("\t\t-------------\n\n");

    printf("[*]   Matricula? ");
    scanf("%d", &initAgenda[proxInd].matricula);

    printf("[*]   Nome? ");
    gets(initAgenda[proxInd].nome);  // por conta do retorno que o scanf deixou
    gets(initAgenda[proxInd].nome);

    printf("\n[%d - %s] incluido na agenda!\n\n", initAgenda[proxInd].matricula, initAgenda[proxInd].nome );

    proxInd++;
}

void carregaDiscoRam() {
    int i;
    char linhaLidaArquivo[MAXNOME + 1];

    FILE *gancho;

    printf( "\n\t\t** Carregar **\n");
    printf( "\t\t--------------\n");

    gancho = fopen("dados.txt", "r");

    if(gancho == NULL) {
        printf("Arquivo indisponivel para leitura!\n");
        return;
    }

    proxInd = 0; // zera a tabela para carregar do arquivo aberto acima

    for (i = 0; fgets(linhaLidaArquivo, MAXNOME, gancho) != NULL; i++) {

        printf("%s", linhaLidaArquivo);

        initAgenda[i].matricula = atoi(linhaLidaArquivo);
        printf("%.d", initAgenda[i].matricula);

        fgets(linhaLidaArquivo, MAXNOME, gancho);

        strcpy(initAgenda[i].nome, linhaLidaArquivo);
        printf("%s", initAgenda[i].nome);

        printf("\n");
    }

    proxInd = i;

    fclose( gancho );
}

void gravarDiscoTxt() {
    FILE *gancho;

    printf("\n\t\t** GRAVAR **\n");
    printf("\t\t------------\n\n");

    if( proxInd == 0){
        printf ("\nLista vazia!\n");
        return ;
    }

    gancho = fopen("dados.txt" , "w");

    if( gancho == NULL ){
        printf ("\nNao foi possivel abrir o arquivo!\n");
        return ;
    }

    printf("[*]   ");

    for (int i = 0; i < proxInd; i++) {
        fprintf(gancho, "Matricula:\t\tNome:");
        fprintf(gancho, "\n");
        fprintf(gancho, "%d\t\t\t%s", initAgenda[i].matricula, initAgenda[i].nome);
        fprintf(gancho, "\n");
        printf(" Gravando no arquivo [%s].", initAgenda[i].nome);

    }

    printf("\n");

    fclose(gancho);
}

void telaListar() {
    printf("\n\t\t** LISTAR **\n");
    printf("\t\t------------\n");

    if (proxInd == 0) {
        printf("\t\tLista vazia!\n");
        printf("\t\t ---------------\n\n");
    }

    for (int i = 0; i < proxInd; i++) {
        printf("[*]   [%d] - %s\n", initAgenda[i].matricula, initAgenda[i].nome);
    }
}

int main() {
    
    char opc;

    do {
        telaPrincipal();

        fflush(stdin);
        scanf("%c", &opc);
        fflush(stdin);

        switch (opc) {
            case 'i':
            case 'I':
                opcIncluir();
                break;

            case 'l':
            case 'L':
                telaListar();
                break;

            case 'c':
            case 'C':
                carregaDiscoRam();
                break;

            case 'g':
            case 'G':
                gravarDiscoTxt();
                break;

            case 'f':
                printf("\n[*]   Digite F maiusculo para sair!\n");
                break;

            case 'F':
                printf("\n[*]   Obrigado, ate mais!\n\n");
                break;

            default:
                printf("Opcao [%c] invalida!\n", opc);
                break;
        }
    } while(opc != 'F');

    return 0;
}
