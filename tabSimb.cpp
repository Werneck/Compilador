#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
const int TAMTABELA = 47;
typedef struct entTabSimb {
    int str;
    void *info;
    entTabSimb *proximo;
};

static char *lexemas;
const int ACRESCIMO = 5;
static int final = -1;
static int tamLexemas = 0;

class tabSimb {
    protected:
       // struct entTabSimb* tabelaHash[TAMTABELA];
    public:

        struct entTabSimb* tabelaHash[TAMTABELA];

        tabSimb() {
            for (int i = 0; i < TAMTABELA; i++) {
                tabelaHash[i] = NULL;
            }
        }

        ~tabSimb() {
        }

        entTabSimb **pegaTabela() {
            return tabelaHash;
        }

        void insercao(entTabSimb entrada) {
            int indice = hash(obtemLexema(entrada.str));
            entTabSimb* novo = (entTabSimb*)malloc(sizeof(entTabSimb));
            novo->str = entrada.str;
            novo->info = entrada.info;
            novo->proximo = tabelaHash[indice];
            tabelaHash[indice] = novo;


//            if (tabelaHash[indice].str == -1) {
//                tabelaHash[indice] = entrada;
//            }
//            else {
//                entTabSimb entradaAux = tabelaHash[indice];
//                printf("%s\n", obtemLexema(entradaAux.str));
//                tabelaHash[indice] = entrada;
//                printf("%s\n", obtemLexema(tabelaHash[indice].str));
//                tabelaHash[indice].proximo = &entradaAux;
//                printf("%d\n", tabelaHash[indice].proximo->str);
//            }
        }

        int busca(char *lexema) {
            int h = hash(lexema);
            if (tabelaHash[h] == NULL) {
                return -1;
            }
            else {
                entTabSimb atual = *tabelaHash[h];
                 while (atual.proximo != NULL) {
                    if (strcmp(obtemLexema(atual.str), lexema) == 0) {
                        return h;
                    }
                    atual = *atual.proximo;
                }
                if (strcmp(obtemLexema(atual.str), lexema) == 0) {
                    return h;
                }
                return -1;
            }
        }

        int hash(char *lexema) {
            int h = 0, g = 0;
//            char *lexema = obtemLexema(str);
            for (int i = 0; i < strlen(lexema); i++) {
                h = ( h << 4 ) + lexema[i];
                g = h & 0xF0000000;
                if (g != 0) {
                    h = h ^ ( g >> 24 );
                    h = h ^ g;
                }
            }
            h = h % TAMTABELA;
            return h;
        }

        char *obtemLexema (int str) {
            int pos = str, tamLexema = 0;
            char *lexema;
            do {
                tamLexema++;
                pos++;
            } while (lexemas[pos] != '\0');
            lexema = (char*)malloc((tamLexema + 1) * sizeof(char));
            strncpy(lexema, lexemas+str, tamLexema);
            lexema[tamLexema] = '\0';
            return lexema;
        }

        int incluiLexema(char *lexema){
            int inicioProx = final + 1;
            if(inicioProx+strlen(lexema) > tamLexemas){
                lexemas = (char*)realloc(lexemas,(tamLexemas+strlen(lexema)+ ACRESCIMO)*sizeof(char));
                tamLexemas += ACRESCIMO + strlen(lexema);
            }
            for(int i = 0; i < strlen(lexema); i++){
                lexemas[inicioProx+i] = lexema[i];
            }
            final = strlen(lexema) + inicioProx;
            lexemas[final] = '\0';
            return inicioProx;
        }

        entTabSimb acessaTabela(char *lexema) {
            int indice = hash(lexema);
            entTabSimb atual = *tabelaHash[indice];
            while (atual.proximo != NULL) {
                if (strcmp(obtemLexema(atual.str), lexema) == 0) {
                    return atual;
                }
                atual = *atual.proximo;
            }
            return atual;
        }
};

class tabSimbPalavReserv : public tabSimb {
    public:

        tabSimbPalavReserv() {
           char aux[8];
           int *infoPalavReserv, tokenNum, str;
           FILE *arquivo;
           arquivo = fopen("palavrasReservadas", "r");
           for(int i = 1; i <= 22; i++) {
               aux[0] = '\0';
               entTabSimb entrada;
               fscanf(arquivo, "%s", aux);
               printf("%s\t", aux);
               str = incluiLexema(aux);
               aux[0] = '\0';
               fscanf(arquivo, "%s", aux);
               tokenNum = atoi(aux);
               infoPalavReserv = &tokenNum;
               entrada.info = malloc(sizeof(infoPalavReserv));
               memcpy(entrada.info, infoPalavReserv, sizeof(infoPalavReserv));
               entrada.str = str;
               entrada.proximo = NULL;
               insercao(entrada);
           }
           fclose(arquivo);
       }



//        tabSimbPalavReserv() {
//            int str;
//            char aux[7];
//            FILE *arquivo;
//            arquivo = fopen("palavrasReservadas.txt", "r");
//            for(int i = 1; i <= 4; i++) {
//                entTabSimb entrada;
//                fscanf(arquivo, "%s", aux);
//                printf("%s\t", aux);
//                str = incluiLexema(aux);
//                fscanf(arquivo, "%s", aux);
//                int *tokenNum;
//                int aux2 = 0;
//                entrada.info = &aux2;
//                tokenNum = (int*)entrada.info;
//                *tokenNum = atoi(aux);
//                entrada.str = str;
//                printf("%d\t", *(int*)entrada.info);
//                entrada.proximo = NULL;
//                insercao(entrada);
//            }
//            fclose(arquivo);
//        }

//        int busca(char *lexema) {
//            int h = hash(lexema);
//            if (tabelaHash[h].str == -1) {
//                return -1;
//            }
//            else {
//                entTabSimb atual = tabelaHash[h];
//                 while (atual.proximo != NULL) {
//                    if (strcmp(obtemLexema(atual.str), lexema) == 0) {
//                        return h;
//                    }
//                    atual = *atual.proximo;
//                }
//                if (strcmp(obtemLexema(atual.str), lexema) == 0) {
//                    return h;
//                }
//                return -1;
//            }
//        }
};

class tabSimbID : public tabSimb {
    public:

//        int busca(char *lexema) {
//            int h = hash(lexema);
//            if (tabelaHash[h].str == -1) {
//                return -1;
//                entTabSimb aux;
//                aux.str = str;
//                insercao(aux);
//                printf("\n%d\n", aux.str);
//                printf("%s\n", obtemLexema(tabelaHash[h].str));
//                return aux;
//            }
//            else {
//                entTabSimb atual = tabelaHash[h];
//                while (atual.proximo != NULL) {
//                    if (atual.str == str) {
//                        return atual;
//                    }
//                    atual = *atual.proximo;
//                }
//                entTabSimb aux;
//                aux.str = str;
//                insercao(aux);
//                return aux;
//            }
//        }
};

class tabSimbLiteral : public tabSimb {
    public:

//        entTabSimb busca(int str) {
//            int h = hash(str);
//            if (tabelaHash[h].str == -1) {
//                entTabSimb aux;
//                aux.str = str;
//                insercao(aux);
//                return aux;
//            }
//            else {
//                entTabSimb atual = tabelaHash[h];
//                while (atual.proximo != NULL) {
//                    if (atual.str == str) {
//                        return atual;
//                    }
//                    atual = *atual.proximo;
//                }
//                entTabSimb aux;
//                aux.str = str;
//                insercao(aux);
//                return aux;
//            }
//        }
};
