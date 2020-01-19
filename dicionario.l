	#include "main.c"
	char *orth = "" /* Palavra */, *usg = "" /* Tipo de Palavra */, *def = "" /* Definição */;
	int idPalavra = 0 /* Id das Palavras */, idTipoPalavra = 0 /* Id dos Tipos de Palavras */;
	int *idsTiposPalavraAssociar = NULL, idsTiposPalavraAssociarPointer = 0; /* Temporária que guarda os Id's dos Tipos de Palavra a associar à Palavra | Apontador para o primeiro elemento livre do array */
	palavra *listaPalavras = NULL; /* Lista de Palavras */
	tipoPalavra *listaTiposPalavra = NULL; /* Lista de Tipos de Palavras */
	palavraPorTipo *listaPalavrasPorTipo = NULL; /* Lista de Palavras Por Tipo */

%x ORTH
%x USG
%x DEF

%%

	/* ========== ORTH ========== */
\<orth\>				{
							BEGIN(ORTH); orth = "";
							free(idsTiposPalavraAssociar);
							idsTiposPalavraAssociar = (int *) malloc(sizeof(int));
							idsTiposPalavraAssociarPointer = 0;
						}
<ORTH>[^\<]*			{ orth = strdup(yytext); }
<ORTH>\<\/orth\>		{ BEGIN(INITIAL); }

	/* ========== USG ========== */
\<usg\ type\=\".*\"\>	{ BEGIN(USG); usg = ""; }
<USG>[^\<]*				{
							usg = strdup(yytext);
							int tipoPalavraPesquisada = pesquisarTipoDePalavra(listaTiposPalavra, usg);
							if (tipoPalavraPesquisada != 0){
								idsTiposPalavraAssociar[idsTiposPalavraAssociarPointer++] = tipoPalavraPesquisada;
							} else {
								listaTiposPalavra = InserirTipoPalavra(listaTiposPalavra, usg, ++idTipoPalavra);
								idsTiposPalavraAssociar[idsTiposPalavraAssociarPointer++] = idTipoPalavra;
							}
						}
<USG>\<\/usg\>			{ usg = ""; BEGIN(INITIAL); }

	/* ========== DEF ========== */
\<def\>\n?[ ]*			{ BEGIN(DEF); }
<DEF>[^\n]*				{
							char *resultado = malloc(strlen(def) + strlen(strdup(yytext)) + 1);
							strcat(resultado, def);
							if (def != ""){ strcat(resultado, " "); }
							strcat(resultado, strdup(yytext));
							def = resultado;
							resultado="";
						}
<DEF>\n					{}
<DEF>\n[ ]*\<\/def\>	{ BEGIN(INITIAL); }

\<\/entry\>				{
							listaPalavras = InserirPalavra(listaPalavras, orth, def, ++idPalavra);
							for (int i = 0; i < idsTiposPalavraAssociarPointer; ++i){
								listaPalavrasPorTipo = InserirPalavraPorTipo(listaPalavrasPorTipo, idPalavra, orth, def, idsTiposPalavraAssociar[i]);
							}
							orth = ""; def = "";
						}

\n						{}
.						{}
<<EOF>>					{
							listaOrdenada(listaTiposPalavra, idTipoPalavra, listaPalavrasPorTipo);
							//listarPalavras(listaPalavras);
							//listarPalavrasPorTipo(listaPalavrasPorTipo, 0);
							//listarTiposPalavra(listaTiposPalavra, 0);
							return 0;
						}

%%
