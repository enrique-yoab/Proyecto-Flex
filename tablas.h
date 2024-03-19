#ifndef TABLAS_H
#define TABLAS_H

#define MAX_TOKEN 200
typedef struct{
    int clase;
    int valor;
    int posicion;
    char dato[30];
} TOKEN;

typedef struct{
    TOKEN tokens[MAX_TOKEN];
} T_simbolos;

typedef struct{
    TOKEN tokens[MAX_TOKEN];
} T_identity;

typedef struct{
    TOKEN tokens[MAX_TOKEN];
} T_const_num;

typedef struct{
    TOKEN tokens[MAX_TOKEN];
} T_cadenas;


void ADD_VALUE_TOKEN(TOKEN *llave, int class, char value, const char* cadena, int posicion);
void ADD_VALUE_SIMBOLOS(T_simbolos *Tabla_simbolo, TOKEN *llave,int contador);
void ADD_VALUE_IDENTITY(T_identity *Tabla_identidad, TOKEN *llave,int contador);
void ADD_VALUE_CONSTANTE_NUMERICA(T_const_num *Tabla_constante,TOKEN *llave, int contador);
void ADD_VALUE_CADENAS(T_cadenas *Tabla_cadena, TOKEN *llave,int contador);
int repetido(T_const_num *Tabla_constante, const char* dato,int contador);
int repetidoC(T_cadenas *Tabla_cadena, const char* dato,int contador);
void printSimbolos(T_simbolos *Tabla_simbolos,int contador);
void printIdentity(T_identity *Tabla_identidad, int contador);
void printConstante(T_const_num *Tabla_constante, int contador);
void printCadenas(T_cadenas *Tabla_cadena, int contador);

#endif