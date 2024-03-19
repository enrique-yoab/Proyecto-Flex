#include "tablas.h"
#include <string.h>
#include <stdio.h>

void ADD_VALUE_TOKEN(TOKEN *llave, int class, char value, const char* cadena, int posicion) {
    int encontrado=0,i=0;
    char *valores[17]={"case","long","if","else","double","while","do","int","default","float","for","switch","short","continue","break","char","return"};
    char *relacional[6]={"<",">","<=",">=","==","!="};
    if(class==0){
    while(encontrado==0){
        if(strcmp(valores[i],cadena)==0){
            encontrado=1;
            i--;
        }
        i++;
    }
        llave->valor=i;
        llave->clase=class;
        strcpy(llave->dato, cadena);
    }else if(class==7){
            while(encontrado==0){
                if(strcmp(relacional[i],cadena)==0){
                encontrado=1;
                i--;
            }
            i++;
        }
        llave->valor=i;
        llave->clase=class;
        strcpy(llave->dato, cadena);
    }else{
        llave->clase=class;
        llave->valor=value;
        strcpy(llave->dato, cadena);
    }
    llave->posicion=posicion;
};

void ADD_VALUE_IDENTITY(T_identity *Tabla_identidad, TOKEN *llave,int contador){
    Tabla_identidad->tokens[contador]=*llave;
};

void ADD_VALUE_CONSTANTE_NUMERICA(T_const_num *Tabla_constante,TOKEN *llave, int contador){
    Tabla_constante->tokens[contador]=*llave;
};

void ADD_VALUE_CADENAS(T_cadenas *Tabla_cadena, TOKEN *llave,int contador){
    Tabla_cadena->tokens[contador]=*llave;
};

void ADD_VALUE_SIMBOLOS(T_simbolos *Tabla_simbolo, TOKEN *llave,int contador){
    Tabla_simbolo->tokens[contador]=*llave;
};

void printSimbolos(T_simbolos *Tabla_simbolos,int contador){
    printf("\n------------------TABLA DE SIMBOLOS------------------\n");
    for(int i=0; i<contador; i++){
        printf("clase %d, valor %d, Dato %s\t posicion %d\n",Tabla_simbolos->tokens[i].clase, Tabla_simbolos->tokens[i].valor, Tabla_simbolos->tokens[i].dato,Tabla_simbolos->tokens[i].posicion);
    }
};

int repetido(T_const_num *Tabla_constante, const char* dato, int contador){
    int repetido=0;
    int i;
    for(i=0;i <= contador;i++){
        if(strcmp(Tabla_constante->tokens[i].dato,dato)==0){
            repetido=1;
        }
    }
    return repetido;
};

int repetidoC(T_cadenas *Tabla_cadena, const char* dato,int contador){
    int repetido=0;
    int i;
    for(i=0;i <= contador;i++){
        if(strcmp(Tabla_cadena->tokens[i].dato,dato)==0){
            repetido=1;
        }
    }
    return repetido;
};


void printIdentity(T_identity *Tabla_identidad,int contador){
    printf("\n------------------TABLA DE IDENTIDADES------------------\n");
    for(int i=0; i<contador; i++){
        printf("clase %d, valor %d, Dato %s\t posicion %d\n",Tabla_identidad->tokens[i].clase, Tabla_identidad->tokens[i].valor, Tabla_identidad->tokens[i].dato,Tabla_identidad->tokens[i].posicion);
    }
};
void printConstante(T_const_num *Tabla_constante, int contador){
    printf("\n------------------TABLA DE CONSTANTES------------------\n");
    for(int i=0; i<contador; i++){
        printf("clase %d, valor %d, Dato %s\t posicion %d\n",Tabla_constante->tokens[i].clase, Tabla_constante->tokens[i].valor, Tabla_constante->tokens[i].dato,Tabla_constante->tokens[i].posicion);
    }
};
void printCadenas(T_cadenas *Tabla_cadena, int contador){
    printf("\n------------------TABLA DE CADENAS------------------\n");
    for(int i=0; i<contador; i++){
        printf("clase %d, valor %d, Dato %s\t posicion %d\n",Tabla_cadena->tokens[i].clase, Tabla_cadena->tokens[i].valor, Tabla_cadena->tokens[i].dato,Tabla_cadena->tokens[i].posicion);
    }

};