#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estrutura que guarda todas as Palavras (utilizada apenas para poder listar palavras com e sem "USG" se for necessário)
 */
typedef struct _palavra {
    int id;
    char *palavra, *def;
    struct _palavra *next;
} palavra;

/**
 * Estrutura que guarda todos os Tipos de Palavras
 */
typedef struct _tipoPalavra {
    int id;
    char *tipo;
    struct _tipoPalavra *next;
} tipoPalavra;

/**
 * Estrutura que guarda todas as Palavras relacionadas com um ou mais Tipos de Palavras
 * Inicialmente era para ser apenas uma estrutura de interligação/relação entre a Palavra e os seus Tipos de Palavra mas,
 * devido à lentidão de processamento na listagem final decidiu-se guardar também a Palavra e a sua Definição para mais
 * rápido acesso.
 */
typedef struct _palavraPorTipo {
    int idPalavra, idTipo;
    char *palavra, *def;
    struct _palavraPorTipo *next;
} palavraPorTipo;

/**
 * Função que insere Palavras (uma de cada vez)
 * @param listaPalavras -> Variável à qual a Palavra vai ser inserida
 * @param textoPalavra -> Palavra
 * @param def -> Definição da Palavra
 * @param id -> Id da Palavra
 * @return -> Lista de Palavras com a nova Palavra já adicionada
 */
palavra *InserirPalavra(palavra *listaPalavras, char *textoPalavra, char *def, int id) {
    palavra *node = (palavra *) malloc(sizeof(palavra));
    node->id = id;
    node->palavra = strdup(textoPalavra);
    node->def = strdup(def);
    node->next = listaPalavras;
    return node;
}

/**
 * Função que insere Tipos de Palavras (um de cada vez)
 * @param listaTiposPalavra -> Variável à qual o Tipo de Palavra vai ser inserido
 * @param tipo -> Tipo de Palavra
 * @param id -> Id do Tipo de Palavra
 * @return -> Lista de Tipos de Palavras com o novo Tipo de Palavra já adicionado
 */
tipoPalavra *InserirTipoPalavra(tipoPalavra *listaTiposPalavra, char *tipo, int id) {
    tipoPalavra *node = (tipoPalavra *) malloc(sizeof(tipoPalavra));
    node->id = id;
    node->tipo = strdup(tipo);
    node->next = listaTiposPalavra;
    return node;
}

/**
 * Função que insere Palavras por Tipo (interligação/relação) (um de cada vez)
 * @param listaPalavrasPorTipo -> Variável à qual a Palavra por Tipo vai ser inserida
 * @param idPalavra -> Id da Palavra a relacionar
 * @param palavra -> Palavra
 * @param def -> Definição da Palavra
 * @param idTipo -> Id do Tipo de Palavra a relacionar
 * @return -> Lista de Palavras por Tipo com a nova relação/interligação já adicionada
 */
palavraPorTipo *
InserirPalavraPorTipo(palavraPorTipo *listaPalavrasPorTipo, int idPalavra, char *palavra, char *def, int idTipo) {
    palavraPorTipo *node = (palavraPorTipo *) malloc(sizeof(palavraPorTipo));
    node->idPalavra = idPalavra;
    node->idTipo = idTipo;
    node->palavra = palavra;
    node->def = def;
    node->next = listaPalavrasPorTipo;
    return node;
}

/**
 * Função que pesquisa Tipos de Palavras
 * @param listaTiposPalavras -> Variável que vai ser pesquisada
 * @param tipo -> Tipo de Palavra a verificar se já existe
 * @return -> "0" se não existir o Tipo de Palavra procurado | "Id" do Tipo de Palavra procurado se existir
 */
int pesquisarTipoDePalavra(tipoPalavra *listaTiposPalavras, char *tipo) {
    if (listaTiposPalavras == NULL) return 0;
    if (strcmp(listaTiposPalavras->tipo, tipo) == 0) {
        return listaTiposPalavras->id;
    } else {
        return pesquisarTipoDePalavra(listaTiposPalavras->next, tipo);
    }
}

/**
 * Função que faz a listagem de todas as Palavras
 * @param listaPalavras -> Variável que vai ser listada
 */
void listarPalavras(palavra *listaPalavras) {
    if (listaPalavras == NULL) return;
    printf("----- Palavra! -----\n");
    printf("Id: %d", listaPalavras->id);
    printf("\nPalavra: %s", listaPalavras->palavra);
    printf("\nDefinição: %s\n\n", listaPalavras->def);
    listarPalavras(listaPalavras->next);
}

/**
 * Função que faz a listagem de todos os Tipos de Palavras
 * @param listaTiposPalavra -> Variável que vai ser listada
 * @param idTipoProcurar -> "Id" do Tipo de Palavra a listar
 *                          "0" - listagem completa
 *                          "Id" - listagem apenas do Tipo de Palavra com esse Id (utilizado na listagem ordenada final)
 */
void listarTiposPalavra(tipoPalavra *listaTiposPalavra, int idTipoProcurar) {
    if (listaTiposPalavra == NULL) return;
    if (idTipoProcurar == 0) {
        printf("----- Tipo Palavra! -----\n");
        printf("Id: %d", listaTiposPalavra->id);
        printf("\nTipo: %s\n\n", listaTiposPalavra->tipo);
    } else if (idTipoProcurar == listaTiposPalavra->id) {
        printf("\n%s:\n", listaTiposPalavra->tipo);
        return;
    }
    listarTiposPalavra(listaTiposPalavra->next, idTipoProcurar);
}

/**
 * Função que faz a listagem de todas as Palavras por Tipo (interligação/relação)
 * @param listaPalavrasPorTipo -> Variável que vai ser listada
 * @param idTipoVerificar -> "Id" do Tipo de Palavra a verificar
 *                           "0" - listagem completa
 *                           "Id" - listagem de todas as Palavras pertencentes a esse Tipo de Palavra (utilizado na listagem ordenada final)
 */
void listarPalavrasPorTipo(palavraPorTipo *listaPalavrasPorTipo, int idTipoVerificar) {
    if (listaPalavrasPorTipo == NULL) return;
    if (idTipoVerificar == 0) {
        printf("----- Palavra Por Tipo! -----\n");
        printf("Id Palavra: %d | %s", listaPalavrasPorTipo->idPalavra, listaPalavrasPorTipo->palavra);
        printf("\nId Tipo: %d\n\n", listaPalavrasPorTipo->idTipo);
    } else if (idTipoVerificar == listaPalavrasPorTipo->idTipo) {
        printf("- %s: %s\n", listaPalavrasPorTipo->palavra, listaPalavrasPorTipo->def);
    }
    listarPalavrasPorTipo(listaPalavrasPorTipo->next, idTipoVerificar);
}

/**
 * Função que faz a listagem final ordenada de todos os Tipos de Palavras e respetivas Palavras
 * @param listaTiposPalavra -> Variável que vai ser listada (apenas um Tipo de Palavra de cada vez)
 * @param qtdTiposPalavra -> Variável com a quantidade total de Tipos de Palavras
 * @param listaPalavrasPorTipo -> Variável que vai ser listada (apenas as Palavras pertencentes ao Tipo de Palavra a ser listado no momento)
 */
void listaOrdenada(tipoPalavra *listaTiposPalavra, int qtdTiposPalavra, palavraPorTipo *listaPalavrasPorTipo) {
    for (int i = 1; i <= qtdTiposPalavra; ++i) {
        listarTiposPalavra(listaTiposPalavra, i);
        listarPalavrasPorTipo(listaPalavrasPorTipo, i);
    }
}

/*int main() {
    return 0;
}*/