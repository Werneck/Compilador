#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 200

FILE *arquivo;
char *retentor;
char *lexema;
char *sentinela;
static int pos=0;
int estado;
char l;
int contLinhas=1;

char proximochar(){
    if(retentor[pos]==*sentinela){
        leituraRet();
        }
    if(lexema[pos]!='/0'){
        lexema[pos]=retentor[pos];
        retentor[pos]=' ';
        }
    else {
        lexema= realloc(lexema, 50*sizeof(char));
        lexema[pos]=retentor[pos];
        retentor[pos]=' ';}
    pos++;
    return lexema[pos];
}

void leituraRet(){
    int i=0;
    while(i<TAM){
        if(!feof(arquivo)){
        fscanf(arquivo,"%s",retentor[i]);
        i++;
        }
        else
        sentinela=&retentor[i];
        break;
    }
    pos=0;
}

void falha(int contL, int est){
    if(est==49) fprintf(stderr,"Erro 3: Fim inesperado de Arquivo. \n EOF \n linha: %d",contL);
    else if (est==50) fprintf(stderr,"Erro 1: Má formação de token.  \n linha: %d",contL);
    else if(estado==51) fprintf(stderr,"Erro 2: Má formação de número real. \n linha: %d",contL);
}

void construtor( ){

    retentor = (char *)malloc(TAM*sizeof(char));
    lexema = (char *)malloc(50*sizeof(char));
    sentinela= &lexema[strlen(lexema)];
    leituraRet();
    l = proximochar();
    estado=0;
}

void deconstrutor(){
    fclose(arquivo);
    free(retentor);
    free(sentinela);
    free(lexema);
}

char proximoToken(){
    //lexema=" ";
    char retorno;
    while(1){
        switch(estado){
            case 0:
            if(l==' '||l=='\t') estado=0;
            else if(lexema=='\n'){
                estado=0;
                contLinhas++;}
            else  if (isdigit(l)) estado=1;
            else  if(l=='[') estado=8;
            else if(l==']')estado=9;
            else if(l=='{')estado=10;
            else if(l=='}')estado=11;
            else if(l=='!')estado=12;
            else if(l=='<')estado=15;
            else if(l=='>')estado=18;
            else if(l=='&')estado=21;
            else if(l=='|')estado=24;
            else if(l=='+')estado=27;
            else if(l=='*')estado=28;
            else if(l=='/')estado=29;
            else if(l=='%')estado=30;
            else if(l=='-')estado=31;
            else if(l=='EOF')estado=32;
            else if(l=='.')estado=33;
            else if(l=='=')estado=36;
            else if(l==',')estado=39;
            else if(l==';')estado=40;
            else if(l=='(')estado=41;
            else if(l==')')estado=42;
            else if(l=='"') estado=43;
            else if(isalpha(l)) estado=45;
            else estado=50;
            break;

            case 1:
            l=proximochar();
            if(isdigit(l)) estado=1;
            else if(l=='.') estado=2;
            else if(l=='e'||l=='E') {estado=3;}
            else
            estado=5;
            break;

            case 2:
            l=proximochar();
            if(isdigit(l)) estado=2;
            else if(l=='e'||l=='E') {estado=3;}
            else
            estado=6;
            break;

            case 3:
            l=proximochar();
            if(l=='+'||(l=='-'))estado=7;
            else if(isdigit(l)){estado=4;}
            else
            estado=6;
            break;

            case 4:
            l=proximochar();
            if(isdigit(l)) {estado=4;}
            else
            estado=6;
            break;

            case 5:
            estado=0;
            sprintf(retorno,"NUMINT.%s",lexema);
            lexema=' ';
            return retorno;
            break;

            case 6:
            estado=0;
            sprintf(retorno,"NUMREAL.%s",lexema);
            lexema=' ';
            return retorno;
            break;

            case 7:
            l=proximochar();
            if(isdigit(l)){estado=4;}
            else
            estado=51;

            break;

            case 8:
            return "LEFTSQUARE";
            break;

            case 9:
            return "RIGHTSQUARE";
            break;

            case 10:
            return "LEFTCURLY";
            break;

            case 11:
            return "RIGHTCURLT";
            break;

            case 12:
            l=proximochar();
            if(l=='='){estado=13;}
            else estado=14;
            break;

            case 13:
            return "DIFFERENT";
            break;

            case 14:
            estado=0;
            lexema=' ';
            return "NOT";

            case 15:
            l=proximochar();
            if(l=='='){estado=16;}
            else estado=17;
            break;

            case 16:
            return "LESSEQ";
            break;

            case 17:
            estado=0;
            lexema=' ';
            return "LESS";
            break;

            case 18:
            l=proximochar();
            if(l=='='){estado=19;}
            else estado=20;
            break;

            case 19:
            return "MOREEQ";
            break;

            case 20:
            estado=0;
            lexema=' ';
            return "MORE";

            case 21:
            l=proximochar();
            if(l=='&'){estado=22;}
            else estado=23;
            break;

            case 22:
            return "AND";
            break;

            case 23:
            estado=0;
            lexema=' ';
            return "BITAND";

            case 24:
            l=proximochar();
            if(l=='|'){estado=25;}
            else estado=26;
            break;

            case 25:
            return "OR";
            break;

            case 26:
            estado=0;
            lexema=' ';
            return "BITOR";
            break;

            case 27:
            return "PLUS";
            break;

            case 28:
            return "PLUS";
            break;

            case 29:
            l=proximochar();
            if(l='*'){estado=47;}
            else estado= 35;
            break;

            case 30:
            return "MOD";
            break;

            case 31:
            return "MINUS";
            break;

            case 32:
            return "EOF";
            break;

            case 33:
            l=proximochar();
            if(isdigit(l)){estado=2;}
            else estado=34;
            break;

            case 34:
            estado=0;
            lexema=' ';
            return "DOT";
            break;

            case 35:
            estado=0;
            lexema=' ';
            return "DIV";
            break;

            case 36:
            l=proximochar();
            if(l=='='){estado=37;}
            else estado=38;
            break;

            case 37:
            return "EQUALS";
            break;

            case 38:
            estado=0;
            lexema=' ';
            return "ASSIGN";
            break;

            case 39:
            return "COMMA";
            break;

            case 40:
            return "SEMICOLON";
            break;

            case 41:
            return "LEFTROUND";
            break;

            case 42:
            return "RIGTHROUND";
            break;

            case 43:
            l=proximochar();
            if(l=='"'){estado=44;}
            else if(l=='EOF'){
                estado=49;
                }
            else estado=43;
            break;

            case 44:
            return "LITERAL";
            break;

            case 45:
            l=proximochar();
            if(isalpha(l)||isdigit(l)){estado=45;}
            else estado=46;
            break;

            case 46:
            estado=0;
            lexema=' ';
            return "ID ou PALARES";
            break;

            case 47:
            l=proximochar();
            if(l=='*')estado=48;
            else if(l=='EOF'){estado=49;}
            else estado=47;
            break;

            case 48:
            l=proximochar();
            if(l=='/') {estado=0;}
            else estado=47;
            break;

            case 49:
            falha(contLinhas,estado);
            break;

            case 50:
            estado=0;
            lexema=' ';
            falha(contLinhas, estado);
            break;

            case 51:
            estado=0;
            falha(contLinhas,estado);
            break;

        }
    }
}
