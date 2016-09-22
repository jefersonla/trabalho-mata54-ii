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
#include <math.h>

/* Constantes do Trabalho */
#define NOME_ARQUIVO            "trabalho.bin"
#define TAMANHO_ARQUIVO         11
#define TAMANHO_MAX_STRING      20

/* Macros que retornam o ponteiro para o arquivo */
#define MODO_LER_ARQUIVO()      fopen(NOME_ARQUIVO, "rb")
#define MODO_GRAVAR_ARQUIVO()   fopen(NOME_ARQUIVO, "rb+")

/* Chave NULA */
#define CHAVE_NULA              -1
#define CHAVE_DELETADA          -2

/* Tamanho inválido */
#define TAMANHO_INVALIDO        -1

/* Arquivo inexistente */
#define ARQUIVO_INEXISTENTE     -2

/* Opções disponíveis no sistema */
#define INSERE_REGISTRO         'i'
#define CONSULTA_REGISTRO       'c'
#define REMOVE_REGISTRO         'r'
#define IMPRIME_REGISTROS       'p'
#define MEDIA_ACESSOS           'm'
#define SAIR_PROGRAMA           'e'

// Comente a linha abaixo para a entrega
//#define DEBUG

/* Retorna o máximo entre dois números */
#define max(A, B) (A > B? A : B)

/* Definições dos tipos TRUE e FALSE */
#define TRUE 1
#define FALSE 0

/* Definições do tipos chave não encontrada */
#define CHAVE_INEXISTENTE       -1
#define CHAVE_EXISTENTE         -2

/* Estrutura de Dados Registro */
typedef struct{
    int chave;
    int idade;
    char nome[TAMANHO_MAX_STRING];
} Registro;

/* Tamanho do registro */
#define TAMANHO_REGISTRO() (sizeof(Registro))

/**
 * Função de hash 1, recebe uma chave e retorna o mod dessa chave
 * pelo tamanho do arquivo.
 *
 * @param chave Chave a ser executado o hash.
 * @return Endereço desejado após a execução da função de hash;
 */
int h1(int chave){
    int hash_computed = (chave % TAMANHO_ARQUIVO);
#ifdef DEBUG
    printf(">> h1 %d\n",  hash_computed);
#endif
    return hash_computed;
}

/**
 * Função de hash 2, recebe uma chave e retorna o max entre o chao
 * da chave dividio pelo tamanho do arquivo e 1.
 *
 * @param chave Chave a ser executado o hash.
 * @return Endereço desejado após a execução da função de hash.
 */
int h2(int chave){
    double hash_computed = max(floor(chave / TAMANHO_ARQUIVO), 1);
#ifdef DEBUG
    printf(">> h2 %d / %.2f\n", (int)hash_computed, hash_computed);
#endif
    return (int) hash_computed;
}

/**
 * Função de Hash principal, recebe uma chave e um interador, e
 * retorna a posição aonde a chave está armazenada.
 *
 * @param k Chave a ser consultada.
 * @param i Iterador
 * @return Endereço do registro no arquivo de registros.
 */
int h(int i, int k){
    int hash_computed = ((h1(k) + (i * h2(k))) % TAMANHO_ARQUIVO);
#ifdef DEBUG
    printf(">> h %d\n", hash_computed);
#endif
    return hash_computed;
}

/**
 * Imprime um registro.
 *
 * @param registro Imprime os dados desse registro.
 */
void imprimeRegistro(Registro registro){
    /* Imprime o registro */
    printf("%d\n"
                   "%s\n"
                   "%d\n",
           registro.chave,
           registro.nome,
           registro.idade);
}

/**
 * Verifica o tamanho do arquivo binário, e retorna o mesmo.
 *
 * @return Retorna o tamanho do arquivo de registros, ou se ele existe
 */
long tamanhoArquivoRegistros() {
    long size;

    /* Tenta abrir o arquivo de Registros */
    FILE* arquivo = MODO_LER_ARQUIVO();

    /* Se conseguimos abrir o arquivo com sucesso */
    if(arquivo != NULL){
        /* Caminha até o fim do arquivo */
        if( fseek(arquivo, 0, SEEK_END) ){
            /* Se não for possível retorna um tamanho de erro */
            fclose(arquivo);
            return TAMANHO_INVALIDO;
        }

        /* Se conseguimos alcançar o final do arquivo então o tamanho dele
         * será a posição atual do mesmo */
#ifdef DEBUG
        printf(">> Tamanho %ld\n", ftell(arquivo));
#endif
        size = ftell(arquivo);
        fclose(arquivo);
        return size;
    }

    return ARQUIVO_INEXISTENTE;
}

/**
 * Cria e inicializa o arquivo de registros.
 */
void criaArquivoRegistros(){
    /* Cria o arquivo ou trunca o mesmo para 0 bytes */
    FILE* arquivo = fopen(NOME_ARQUIVO, "wb");
    int i;

    /* Se não foi possível abrir o arquivo encerramos o programa */
    if(arquivo == NULL){
#ifdef DEBUG
       printf("CAN'T OPEN REGISTRY FILE. EXITING NOW!");
#endif
        exit(EXIT_FAILURE);
    }

    /* Com o arquivo criado inicializamos todas os registros com chaves
     * com o valor -1 que indicara que esse registro não existe */
    Registro registro_nulo;
    registro_nulo.chave = CHAVE_NULA;
    registro_nulo.nome[0] = '\0';
    registro_nulo.idade = 0;

    /* Iremos agora percorrer nosso novo arquivo e gravar todas as chaves
     * dele com esse registro */
    for ( i = 0; i < TAMANHO_ARQUIVO; i++){
        fwrite(&registro_nulo, TAMANHO_REGISTRO(), 1, arquivo);
    }

    /* Fecha o arquivo */
    fclose(arquivo);
}

/**
 * Verifica se dois registros são iguais
 *
 * @deprecated Não é necessário.
 * @param registro_a Um registro qualquer.
 * @param registro_b O registro a ser comparado.
 * @return Retorna TRUE caso eles sejam iguais e FALSE caso diferentes
 */
/*
int comparaRegistros(Registro registro_a, Registro registro_b){
    return ((registro_a.idade == registro_b.idade) &&
            (registro_a.chave == registro_b.chave) &&
            (strcmp(registro_a.nome, registro_b.nome) == 0));
}
*/

/**
 * Consulta um registro no arquivo de registros.
 *
 * @param chave Chave a ser consultada.
 * @param registro_retorno Registro encontrado por uma consulta, use NULO se não desejar.
 * @param endereco_inserir Informa o primeiro endereço para inserção, use NULO se não desejar.
 * @return posição a qual a chave foi encontrada
 */
int consultaRegistro(int chave, Registro *registro_retorno, int *endereco_inserir) {
    int i;
    int endereco_hash;
    int hash_computado;
    Registro registro_encontrado;
    FILE* arquivo = MODO_LER_ARQUIVO();

#ifdef DEBUG
    printf(">> Searching key %d\n", chave);
#endif

    /* Procura o registro com a chave especificada */
    for ( i = 0; i < TAMANHO_ARQUIVO; i++){
        /* Põe o ponteiro do arquivo na posição da chave e lê o registro */
        hash_computado = h(i, chave);
        endereco_hash = (hash_computado * TAMANHO_REGISTRO());
        fseek(arquivo, endereco_hash, SEEK_SET);
        fread(&registro_encontrado, TAMANHO_REGISTRO(), 1, arquivo);

        /* Se o registro de retorno for esperado */
        if(registro_encontrado.chave == chave){

#ifdef DEBUG
            printf(">> Key found\n");
#endif
            /* Se o ponteiro do registro de retorno não for nulo modifica ele com as informações
             * econtradas */
            if(registro_retorno != NULL){
                registro_retorno->chave = registro_encontrado.chave;
                registro_retorno->idade = registro_encontrado.idade;
                strcpy(registro_retorno->nome, registro_encontrado.nome);
#ifdef DEBUG
                printf(">> Key Return : ");
                imprimeRegistro(*registro_retorno);
#endif
            }

            /* Se houver ponteiro de endereço de inserção de retorno */
            if(endereco_inserir != NULL &&
               *endereco_inserir == CHAVE_INEXISTENTE){
                *endereco_inserir = CHAVE_EXISTENTE;
            }

            /* Feche o arquivo e retorne a chave encontrada */
            fclose(arquivo);
            return hash_computado;
        }
        else if(registro_encontrado.chave == CHAVE_NULA){
            /* Se não existem mais chaves para consulta para a execução do for */
            /* Se não houve posições anteriores deletadas então a primeira chave NULA será o
             * endereço para a inserção */
            if(endereco_inserir != NULL &&
               *endereco_inserir == CHAVE_INEXISTENTE){
                *endereco_inserir = hash_computado;
#ifdef DEBUG
                printf(">> Null position %d\n", *endereco_inserir);
#endif
            }
            break;
        }
        else if(endereco_inserir != NULL &&
                *endereco_inserir == CHAVE_INEXISTENTE &&
                registro_encontrado.chave == CHAVE_DELETADA){
            /* Se encontramos uma posição deletada essa posição será o endereço de inserção */
            *endereco_inserir = hash_computado;
#ifdef DEBUG
            printf(">> Deleted position %d\n", *endereco_inserir);
#endif
        }
    }

#ifdef DEBUG
    printf(">> Key not found\n");
#endif

    /* Fecha o arquivo e retorna que não a chave não encontrada */
    fclose(arquivo);
    return CHAVE_INEXISTENTE;
}

/**
 * Insere o registro no arquivo de registros.
 *
 * @param registro Registro a ser inserido.
 * @return Retorna o status da inserção do registro.
 */
int insereRegistro(Registro registro){
    /* Consulta a posição da chave a ser removida */
    int posicao_inserir = CHAVE_INEXISTENTE;
    consultaRegistro(registro.chave, NULL, &posicao_inserir);

    /* Se não tivermos espaço para inserir retornarmos erro */
    if(posicao_inserir == CHAVE_INEXISTENTE){
        return FALSE;
    }
    else if(posicao_inserir == CHAVE_EXISTENTE){
        return CHAVE_EXISTENTE;
    }

#ifdef DEBUG
    printf(">> Inserting on ... %d\n", posicao_inserir);
#endif

    /* Como encontramos uma posição para inserir */
    /* Põe no modo gravar arquivo */
    FILE* arquivo = MODO_GRAVAR_ARQUIVO();

    /* Caminha até a posição que será inserida e escreve o registro novo */
    fseek(arquivo, (posicao_inserir * TAMANHO_REGISTRO()), SEEK_SET);
    fwrite(&registro, TAMANHO_REGISTRO(), 1, arquivo);

    /* Fecha o arquivo e retorna true */
    fclose(arquivo);
    return TRUE;
}

/**
 * Remove o registro no arquivo de registros.
 *
 * @param chave Chave a ser removida.
 * @return Retorna TRUE caso tenha sido removido e FALSE caso não.
 */
int removeRegistro(int chave){
    /* Consulta a posição da chave a ser removida */
    int posicao_remover = consultaRegistro(chave, NULL, NULL);

    /* Se a chave não for encontrada retorna erro */
    if(posicao_remover == CHAVE_INEXISTENTE){
        return FALSE;
    }

#ifdef DEBUG
    printf(">> Removing key ... %d\n", posicao_remover);
#endif

    /* Se a chave existe basta escrever na posição a ser removida o Registro deletado */
    Registro registro_deletado;
    registro_deletado.chave = CHAVE_DELETADA;
    registro_deletado.idade = 0;
    registro_deletado.nome[0] = '\0';

    /* Põe no modo gravar arquivo */
    FILE* arquivo = MODO_GRAVAR_ARQUIVO();

    /* Caminha até a posição que será removida e escreve o registro deletado */
    fseek(arquivo, (posicao_remover * TAMANHO_REGISTRO()), SEEK_SET);
    fwrite(&registro_deletado, TAMANHO_REGISTRO(), 1, arquivo);

    /* Fecha o arquivo e retorna true */
    fclose(arquivo);
    return TRUE;
}

/**
 * Imprime todos os registros, presentes no arquivo de registros.
 */
void imprimeRegistros(){
    int i;
    FILE *arquivo = MODO_LER_ARQUIVO();
    Registro registro_atual;

    /* Percore o arquivo de registros e imprime registro por registro do mesmo */
    for(i = 0; i < TAMANHO_ARQUIVO; i++){
#ifdef DEBUG
        printf(">> File pos %ld\n", ftell(arquivo));
#endif
        /* Posiciona o ponteiro e lê o registro  */
        fseek(arquivo, (i * TAMANHO_REGISTRO()), SEEK_SET);
        fread(&registro_atual, TAMANHO_REGISTRO(), 1, arquivo);

#ifdef DEBUG
        printf(">> Registry Key %d\n", registro_atual.chave);
#endif

        /* Imprime o indice */
        printf("%d: ", i);

        /* Se não houver registro atual ou o mesmo tiver sido deletado imprime vazio */
        if(registro_atual.chave == CHAVE_INEXISTENTE || registro_atual.chave == CHAVE_DELETADA) {
            printf("vazio\n");
        }
        else {
            /* Imprime o registor corrente */
            printf("%d %s %d\n",
                   registro_atual.chave,
                   registro_atual.nome,
                   registro_atual.idade
            );
        }
    }

    /* Fecha o arquivo */
    fclose(arquivo);
}

/**
 * Retorna a média de acesso a todos os nós existentes no arquivo de registro.
 *
 * @return Media de acesso a todos os nós presentes no arquivo de registro.
 */
double mediaAcessoRegistros(){
    int i, j;
    int chave_encontrada;
    double quantidade_de_registros = 0;
    double somatorio_acessos = 0;
    FILE *arquivo = MODO_LER_ARQUIVO();
    Registro registro_atual;

#ifdef DEBUG
    printf(">> Calculating number of access\n");
#endif

    /* Percore o arquivo de registros e soma os acessos a cada registro */
    for(i = 0; i < TAMANHO_ARQUIVO; i++){
        /* Move o ponteiro de leitura para a posição atual */
        fseek(arquivo, (i * TAMANHO_REGISTRO()), SEEK_SET);

        /* Lê o registro  */
        fread(&registro_atual, TAMANHO_REGISTRO(), 1, arquivo);

        /* Armazena a chave encontrada */
        chave_encontrada = registro_atual.chave;

#ifdef DEBUG
        printf(">> Key calculating %d\n", chave_encontrada);
#endif

        /* Se o registro possuir chave */
        if(chave_encontrada != CHAVE_INEXISTENTE && chave_encontrada != CHAVE_DELETADA){
            /* Move para o começo do arquivo */
            rewind(arquivo);

            /* Incrementa o contador de registros encontrados */
            quantidade_de_registros += 1;

            /* Realiza uma consulta da chave e contabiliza a quantidade de acessos */
            for ( j = 0; j < TAMANHO_ARQUIVO; j++) {
                /* Põe o ponteiro do arquivo na chave  */
                fseek(arquivo, (h(j, chave_encontrada) * TAMANHO_REGISTRO()), SEEK_SET);
                fread(&registro_atual, TAMANHO_REGISTRO(), 1, arquivo);

                /* Incrementa a quantidade de acessos */
                somatorio_acessos += 1;

                if (registro_atual.chave == chave_encontrada) {
#ifdef DEBUG
                    printf(">> Got it!\n");
#endif
                    break;
                }

#ifdef DEBUG
                printf(">> Not this key.\n");
#endif
            }
        }

#ifdef DEBUG
        printf(">> Number of keys found %.2lf\n", quantidade_de_registros);
        printf(">> Number of access computed %.2lf\n", somatorio_acessos);
#endif
    }

    /* Retorna a media de acesso */
    fclose(arquivo);
    return (quantidade_de_registros > 0 ? (somatorio_acessos / quantidade_de_registros) : 0.0);
}

int main(int argc, char *argv[]){
    /* Menu de opções da aplicação */
    char opcao;

    /* Retorna o tamanho do arquivo de registro caso ele já tenha  sido
     * criado */
    long tamanho_arquivo = tamanhoArquivoRegistros();

    /* Verifica se o arquivo de registros existe, se ele não existir cria
     * o mesmo */
    if(tamanho_arquivo == ARQUIVO_INEXISTENTE){
        criaArquivoRegistros();
#ifdef DEBUG
        printf("FILE DON'T EXIST OR INVALID SIZE\n");
#endif
    }
    /* Se o arquivo já existe verificamos se ele possuí a quantidade de entradas
     * que queremos, caso ele não possua reinicializa o arquivo */
    else if(tamanho_arquivo != (TAMANHO_REGISTRO() * TAMANHO_ARQUIVO)){
        criaArquivoRegistros();
#ifdef DEBUG
        printf(">> size %d | file %d\n", TAMANHO_ARQUIVO * TAMANHO_REGISTRO(), tamanho_arquivo);
        printf("FILE EXIST BUT HAS INVALID SIZE\n");
#endif
    }

    /* Executa a aplicação enquanto não for escolhida a opção para parar a execução */
    do{
        /* Registro Entrada */
        Registro registro;

        /* Registro retornado por uma consulta */
        Registro registro_retorno;

        /* Chave para consulta */
        int chave_consulta;

        /* Chave para remoção */
        int chave_remocao;

        /* Media de acessos */
        double media_acessos;

        /* Lê a opção desejada */
        scanf(" %c", &opcao);

        /* Executa a opção informada pelo usuario */
        switch(opcao){
            case INSERE_REGISTRO:
                /* Lê a chave */
                scanf(" %d", &registro.chave);
                /* Lê o nome */
                scanf(" %[^\n]s%*c", registro.nome);
                /* Lê a idade */
                scanf(" %d", &registro.idade);

                /* Insere o registro lido, e retorna caso tenha sido possível, caso não tenha sido imprime a chave */
                if(insereRegistro(registro) == CHAVE_EXISTENTE){
                    printf("chave ja existente: %d\n", registro.chave);
                }
                break;
            case CONSULTA_REGISTRO:
                /* Lê a chave a ser consultada */
                scanf(" %d", &chave_consulta);

                /* Consulta a chave informada pelo usuario */
                if(consultaRegistro(chave_consulta, &registro_retorno, NULL) == CHAVE_INEXISTENTE){
                    printf("chave nao encontrada: %d\n", chave_consulta);
                }
                else{
                    printf("chave: ");
                    imprimeRegistro(registro_retorno);
                }
                break;
            case REMOVE_REGISTRO:
                /* Lê a chave a ser removida */
                scanf(" %d", &chave_remocao);

                /* Remove a chave informada pelo usuario */
                if(!removeRegistro(chave_remocao)){
                    printf("chave nao encontrada: %d\n", chave_remocao);
                }
                break;
            case IMPRIME_REGISTROS:
                /* Imprime os registros armazenados no arquivo */
                imprimeRegistros();
                break;
            case MEDIA_ACESSOS:
                /* Retorna a média de acessos a todas as chaves do arquivo de registro */
                media_acessos = mediaAcessoRegistros();
                printf("%.1lf\n", media_acessos);
                break;
            case SAIR_PROGRAMA:
                break;
            default:
                /* Termina a aplicação forçadamente caso sejam lidas entradas não experadas */
#ifdef DEBUG
                printf("UNEXPECTED INPUT ERROR!!\n");
#endif
                break;
        }

    } while(opcao != SAIR_PROGRAMA);

#ifdef DEBUG
    printf("EXECUTION FINISHED WITH SUCCESS!\n");
#endif

    return EXIT_SUCCESS;
}
