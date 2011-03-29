#include <iostream>
#include <malloc.h>
#include <string.h>
#include "tabSimb.cpp"
//const int P = 47;
//using namespace std;
//
//const int ACRESCIMO = 5;
//char *lexemas1;
//int final = -1;
//int tamLexemas = 0;

//void incluiLexema(char *lexema){
//    int inicioProx = final + 1;
//    if(inicioProx+strlen(lexema) > tamLexemas){
//        lexemas1 = (char*)realloc(lexemas1,(tamLexemas+strlen(lexema)+ ACRESCIMO)*sizeof(char));
//        tamLexemas += ACRESCIMO + strlen(lexema);
//    }
//    for(int i = 0; i < strlen(lexema); i++){
//        lexemas1[inicioProx+i] = lexema[i];
//    }
//    final = strlen(lexema) + inicioProx;
//    lexemas1[final] = '\0';
//}

//char *obtemLexema1 (int str) {
//    int pos = str, tamLexema = 0;
//    char *lexema;
//    do {
//        tamLexema++;
//        pos++;
//    } while (lexemas1[pos] != '\0');
//    lexema = (char*)malloc((tamLexema + 1) * sizeof(char));
//    strncpy(lexema, lexemas1+str, tamLexema);
//    lexema[tamLexema] = '\0';
//    return lexema;
//}
//int hashDesc(int str) {
//    int h = 0, g = 0;
//    char *lexema = obtemLexema(str);
//    for (int i = 0; i < strlen(lexema); i++) {
//        h = ( h << 4 ) + lexema[i];
//        g = h & 0xF0000000;
//        if (g != 0) {
//            h = h ^ ( g >> 24 );
//            h = h ^ g;
//        }
//    }
//    h = h % P;
//    return h;
//}
//int hashPrimUlt(int str) {
//    char *lexema = obtemLexema(str);
//    int h = (strlen(lexema) * (int)lexema[0]) + (int)lexema[strlen(lexema) - 1];
//    return h % P;
//}
//int hashSoma(int str) {
//    int h = 0;
//    char *lexema = obtemLexema(str);
//    for (int i = 0; i < strlen(lexema); i++) {
//        h += (int)lexema[i];
//    }
//    return h % P;
//}

int main()
{
//    char *string1, *string2;
//    string1 = (char*)malloc(20 * sizeof(char));
//    string2 = (char*)malloc(5 * sizeof(char));
//    string1 = "Rafael de Oliveira";
//    strncpy(string2, string1+10, 5);
//    printf("%s", string2);

//    lexemas = (char*)malloc(20 * sizeof(char));
//    lexemas[0] = 'x';
//    lexemas[1] = '1';
//    lexemas[2] = '2';
//    lexemas[3] = '3';
//    lexemas[4] = '\0';
//    lexemas[5] = 'x';
//    lexemas[6] = '2';
//    lexemas[7] = '\0';
//    lexemas[8] = 't';
//    lexemas[9] = 'e';
//    lexemas[10] = 'r';
//    lexemas[11] = '\0';
//    printf("%s\n", lexemas);
//    printf("%s\n", obtemLexema(5));
//    printf("%d\n", hashDesc(0));
//    printf("%d\n", hashDesc(5));
//    printf("%d\n", hashDesc(8));
//    printf("%d\n", hashPrimUlt(0));
//    printf("%d\n", hashPrimUlt(5));
//    printf("%d\n", hashPrimUlt(8));
//    printf("%d\n", hashSoma(0));
//    printf("%d\n", hashSoma(5));
//    printf("%d\n", hashSoma(8));

    tabSimbPalavReserv PR;
    for (int i = 0; i < TAMTABELA; i++) {
        if(PR.tabelaHash[i] != NULL){
            entTabSimb entrada = *PR.tabelaHash[i];
            while (entrada.proximo != NULL) {
                printf("%s\t%d -> ", PR.obtemLexema(entrada.str), *(int*)entrada.info);
                entrada = *entrada.proximo;
            }
            printf("%s\t%d", PR.obtemLexema(entrada.str), *(int*)entrada.info);
            printf("\n-----------\n");
        }
        else{
            printf("\n-----------\n");
        }
    }
//    entTabSimb e1;
//    e1.str = 0;
//    e1.proximo = NULL;
//    e1 = ID.busca(0);

//    incluiLexema("x1");
//    incluiLexema("if");
//    incluiLexema("Luiz Maurilio");
//    printf("%s\n",lexemas1);
//    printf("%s\n",obtemLexema1(3));
//    printf("%s\n",obtemLexema1(0));
//    printf("%s\n",obtemLexema1(6));


    return 0;
}
