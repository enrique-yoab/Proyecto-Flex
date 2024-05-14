#ifndef TABLAS_H
#define TABLAS_H

#define MAX_TOKEN 200
#define PALABRAS_RESERVADAS \
  "case", "long", "if", "else", "double", "while", "do", "int", \
  "default", "float", "for", "switch", "short", "continue", "break", \
  "char", "return"

typedef struct{
    int linea;
    int clase;
    int valor;
    int posicion;
    char dato[30];
} TOKEN;
/// @brief 
typedef struct{
    int linea;
    char *dato;
    char *name;
    int valor; //valor de la clase específica (caso de tablas)
    int id; //clase
} ATOMOS; //Generamos una estructura para almacenar los átomos 
typedef struct{
    ATOMOS atomos[MAX_TOKEN];
}T_atomos;

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


void ADD_VALUE_TOKEN(TOKEN *llave, int class, char value, const char* cadena, int posicion, int linea);
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

//Nuevas funciones
void generate_atom(T_simbolos *sim, T_atomos *tabla_atomos, int i, ATOMOS *atm);
void ADD_ATOM(T_atomos *tabla_atomos, int clase, char *val_atom, char * dato, int contador, ATOMOS *atom);
void ATOM_VALUE(T_atomos *tabla_atomos, int clase, char *dato, int contador, ATOMOS *atom);
void printAtomos(T_atomos *atomos, int contador);
#endif