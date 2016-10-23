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
//#define TAMANHO_ALFABETO 		2

/* Ultimo caractere do nosso alfabeto */
#define ULTIMO_CARACTERE 		122

/* Deletar \n do computador */
#define clear_newline()			scanf("%*c")

/* Uncomment for debug or use -DDEBUG in compilations process */
//#define DEBUG

/* Alfabeto */
int alfabeto_index[ULTIMO_CARACTERE] = { -1 };
char alfabeto[] = "abcdefghijklmnopqrstuvwxyz., ";
//char alfabeto[] = "ab";

/* Padrao global */
char *padrao;

/* Minimo entre A e B */
#define min(A, B)				(A < B ? A : B)

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
 * Checa o maior prefixo do sufixo.
 *
 * @param k Prefixo.
 * @param q Estado atual.
 * @param a Caractere Atual.
 * @return
 */
int checaSequencia(int k, int q, int a) {
	/* Variaveis auxiliares */
	int i, j;

	/* Se o caractere a não for sufixo do padrao na posição k retorna falso */
	if (padrao[k] != alfabeto[a]) {
		return 0;
	}

	/* Verifica se o prefixo é igual ao sufixo */
	for (i = k - 1, j = q;
			((i >= 0) && (j >= 0) && padrao[i] == padrao[j]);
			i--, j--)
		;

	/* Retorna se encontramos este sufixo ou não */
	return (i < 0);
}

/**
 * Cria a tabela delta que representa a execução do automato representado pelo padrão.
 *
 * @param texto_len Tamanho do texto.
 * @param texto Vetor com o texto.
 * @param padrao_len Tamanho do padrão.
 * @param delta_table Tabela delta com o automato gerado.
 */
void criaAutomato(int padrao_len, int delta_table[][TAMANHO_ALFABETO]) {
	/* Estado atual */
	int q;

	/* Caractere atual */
	int a;

	/* Valor minimo de m + 1 e q + 2 */
	int k;

	/* Tamanho do padrão */
	int m = padrao_len;

	/* Cria a tabela delta */
	for (q = 0; q <= m; q++) {
		/* Para cada caractere do alfabbeto */
		for (a = 0; a < TAMANHO_ALFABETO; a++) {
			/* Escolhe o menor indice */
			k = min(m + 1, q + 2) - 1;

			/* Repetir enquanto o maior prefixo do sufixo não for encontrado */
			do {
				k --;
			} while ((k >= 0) && (!checaSequencia(k, q - 1, a)));

			/* Armazena o prefixo na tabela delta */
			delta_table[q][a] = k + 1;
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
void imprimeTabela(int padrao_len, int delta_table[][TAMANHO_ALFABETO]) {
	/* Variaveis auxiliares */
	int i, j;

	/* Texto de entrada */
	printf("Tabela Delta:\n");

	/* Percorre a tabela e imprime os valores para cada item de delta */
	for (i = 0; i <= padrao_len; i++) {
		for (j = 0; j < TAMANHO_ALFABETO; j++) {
			if (alfabeto[j] == ' ') {
				/* Se o carecter for ' ' imprime com apostrofe */
				printf("[%d, ' ']: %d\n", i, delta_table[i][j]);
			} else {
				/* Caso contrário apenas imprime o caractere */
				printf("[%d, %c]: %d\n", i, alfabeto[j], delta_table[i][j]);
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
		int delta_table[][TAMANHO_ALFABETO]) {
	/* Variaveis auxiliares */
	int i;

	/* Estado atual */
	int q;

	/* Estado Final */
	int estado_final = padrao_len;

	/* Procura pela existência de padrões no texto */
	for (i = 0, q = 0; i < texto_len; i++) {
		/* Estado atual é igual ao estado do automato com a posição do texto verificado */
		q = delta_table[q][alfabeto_index[(int) texto[i]]];

		/* Se o estado atual for um estado final do automato então imprimimos a posição */
		if (isEstadoFinal(q, estado_final)) {
			printf("%d\n", posicaoDoTexto(i + 1, padrao_len));
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

	/* Tamanho do Texto */
	int texto_len;

	/* Lê o tamanho do texto */
	scanf(" %d", &texto_len);

	/* Vetor com Texto */
	char texto[texto_len + 1];

	/* Lê o texto */
	clear_newline();
	scanf("%[^\n]s", texto);
	clear_newline();

	/* Assume-se que o padrão não será maior que o tamanho da entrada */

	/* Vetor com o padrão */
	padrao = calloc(sizeof(char), texto_len + 1);

	/* Lê o padrão */
	scanf("%[^\n]s", padrao);
	clear_newline();

	/* Tamanho do Padrão */
	int padrao_len = strlen(padrao);

	/* Tabela delta */
	int delta_table[padrao_len + 1][TAMANHO_ALFABETO];

	/* Inicialização da tabela */
	for (i = 0; i <= padrao_len; i++) {
		for (j = 0; j < TAMANHO_ALFABETO; j++) {
			delta_table[i][j] = 0;
		}
	}

	/* Inicializa a tabela de indices */
	for (i = 0; i < TAMANHO_ALFABETO; i++) {
		alfabeto_index[(int) alfabeto[i]] = i;
	}

	/* Cria automato */
	criaAutomato(padrao_len, delta_table);

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
