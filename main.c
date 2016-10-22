/*!
 * Trabalho I de MATA54 - Estruturas de Dados e Algoritmos II
 *
 * Implementação Hashing Duplo
 *
 * Aluno:
 * 	Jeferson Lima de Almeida
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

/* Constantes do Trabalho */

/* Sair do Programa */
#define SAIR_PROGRAMA           'e'

/* Buscar Padrão */
#define BUSCAR_PADRAO			's'

/* Impressão de Tabela */
#define IMPRIME_TABELA			'u'

/* Tamanho do alfabeto */
#define TAMANHO_ALFABETO 		29

/* Ultimo caractere do nosso alfabeto */
#define ULTIMO_CARACTERE 		122

/* Deletar \n do computador */
#define clear_newline()			scanf("%*c")

/* Uncomment for debug or use -DDEBUG in compilations process */
//#define DEBUG

/* Alfabeto */
char alfabeto[] = "abcdefghijklmnopqrstuvwxyz., ";

/**
 * Retorna true se o ESTADO for igual ao ESTADO_FINAL.
 *
 * @param ESTADO Estado Atual.
 * @param ESTADO_FINAL Estado final.
 * @return Retorna true se for o estado final.
 */
#define isEstadoFinal(ESTADO, ESTADO_FINAL)	(ESTADO == ESTADO_FINAL)

/**
 * Retorna a posicao atual do texto que corresponde a posição atual menos o
 * tamanho do padrão mais 1 já que estamos indexando esses valores a partir do 1.
 *
 * @param POSICAO_ATUAL Posicao Atual.
 * @param TAMANHO_PADRAO Tamanho do padrao.
 * @return A posição do texto atual.
 */
#define posicaoDoTexto(POSICAO_ATUAL, TAMANHO_PADRAO) ((POSICAO_ATUAL - TAMANHO_PADRAO) + 1)

/**
 * Cria a tabela delta que representa a execução do automato representado pelo padrão.
 *
 * @param texto_len Tamanho do texto.
 * @param texto Vetor com o texto.
 * @param padrao_len Tamanho do padrão.
 * @param delta_table Tabela delta com o automato gerado.
 */
void criaAutomato(int padrao_len, char padrao[],
		uint8_t delta_table[][ULTIMO_CARACTERE]) {
	/* Variaveis Auxiliares */
	int i, j, aux;

	/* Estado atual */
	int estado;

	/* Deslocamento efetuado */
	int deslocamento;

	/* Cria a tabela delta */
	for(estado = 0; estado <= padrao_len; estado++) {
		for (i = 0; i < TAMANHO_ALFABETO; i++) {
			/* Se o estado ... */
			if (estado < padrao_len && alfabeto[i] == padrao[estado]) {
				delta_table[estado][alfabeto[i]] = estado + 1;
			} else {
				/* Inicializa o deslocamento */
				deslocamento = 1;

				/* Enquanto o deslocamento for menor que o estado atual */
				while (deslocamento <= estado) {
					/* Procura por ... */
					for (j = 0;
							(j <= (estado - deslocamento))
									&& ((j + deslocamento) < padrao_len)
									&& (padrao[j] == padrao[j + deslocamento]);

							j++)
						;

					/* Se ... */
					if (j == (estado - deslocamento)
							&& (padrao[j] == alfabeto[i])) {
						delta_table[estado][alfabeto[i]] = j + 1;
						deslocamento = estado + 1;
					}

					deslocamento += 1;
				}
			}
		}
	}
}

/**
 * Imprime a tabela delta, auxiliar a busca com automato.
 *
 * @param texto_len Tamanho do texto.
 * @param padrao_len Tamanho do padrão.
 * @param delta_table Tabela delta.
 */
void imprimeTabela(int padrao_len, uint8_t delta_table[][ULTIMO_CARACTERE]) {
	/* Variaveis auxiliares */
	int i, j, aux;

	/* Texto de entrada */
	printf("Tabela Delta:\n");

	/* Percorre a tabela e imprime os valores para cada item de delta */
	for (i = 0; i <= padrao_len; i++) {
		for (j = 0; j < TAMANHO_ALFABETO; j++) {
			if (alfabeto[j] == ' ') {
				/* Se o carecter for ' ' imprime com apostrofe */
				printf("[%d, ' ']: %d\n", i, delta_table[i][alfabeto[j]]);
			} else {
				/* Caso contrário apenas imprime o caractere */
				printf("[%d, %c]: %d\n", i, alfabeto[j],
						delta_table[i][alfabeto[j]]);
			}
		}
	}
}

/**
 * Busca o padrão dentro do texto, tendo a tabela delta previamente gerada.
 *
 * @param texto_len Tamanho do texto.
 * @param texto Vetor com o texto.
 * @param padrao_len Tamanho do padrão.
 * @param delta_table Tabela delta.
 */
void buscaPadrao(int texto_len, char texto[], int padrao_len,
		uint8_t delta_table[][ULTIMO_CARACTERE]) {
	/* Variaveis auxiliares */
	int i, j;

	/* Estado atual */
	int estado;

	/* Estado Final */
	int estado_final = padrao_len;

	/* Procura pela existência de padrões no texto */
	for (i = 0, estado = 0; i < texto_len; i++) {
		/* Estado atual é igual ao estado do automato com a posição do texto verificado */
		estado = delta_table[estado][texto[i]];

		/* Se o estado atual for um estado final do automato então imprimimos a posição */
		if (isEstadoFinal(estado, estado_final)) {
			printf("%d\n", posicaoDoTexto(i, padrao_len));
		}
	}
}

/**
 * Aplicação Busca de Texto informado com automato.
 *
 * @return Code Execution Status.
 */
int main() {
	/* Menu de opções da aplicação */
    char opcao;

	/* Variaveis Auxiliares */
	int i, j;

	/* Lê o tamanho do texto */

	/* Tamanho do Texto */
	int texto_len;
	scanf(" %d", &texto_len);

	/* Lê o texto */

	/* Vetor com Texto */
	char texto[texto_len + 2];
	clear_newline();
	scanf("%[^\n]s", texto);
	clear_newline();

	/* Lê o padrão */
	/* Assume-se que o padrão não será maior que o tamanho da entrada */

	/* Vetor com o padrão */
	char padrao[texto_len + 2];
	clear_newline();
	scanf("%[^\n]s", padrao);
	clear_newline();

	/* Tamanho do Padrão */
	int padrao_len = strlen(padrao);

	/* Tabela delta */
	uint8_t delta_table[padrao_len][ULTIMO_CARACTERE];

	/* Inicialização da tabela */
	for (i = 0; i <= padrao_len; i++) {
		for (j = 0; j < ULTIMO_CARACTERE; j++) {
			delta_table[i][j] = 0;
		}
	}

	/* Cria automato */
	criaAutomato(padrao_len, padrao, delta_table);

    /* Executa a aplicação enquanto não for escolhida a opção para parar a execução */
    do{
		/* Lê a opção desejada */
        scanf(" %c", &opcao);

        /* Executa a opção informada pelo usuario */
        switch(opcao){
		case BUSCAR_PADRAO:
			/* Realiza a busca de padrões */
			buscaPadrao(texto_len, texto, padrao_len, delta_table);
			break;
		case IMPRIME_TABELA:
			/* Imprime a tabela delta (o") */
			imprimeTabela(padrao_len, delta_table);
			break;
		case SAIR_PROGRAMA:
			/* Termina o programa */
			break;
		default:
#ifdef DEBUG
			fprintf(stderr, "OPTION NOT FOUND => %c", opcao);
#endif
			break; // Opção não encontrada
        }

    } while(opcao != SAIR_PROGRAMA);

#ifdef DEBUG
    printf("EXECUTION FINISHED WITH SUCCESS!\n");
#endif

    return EXIT_SUCCESS;
}
