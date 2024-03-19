#include "tablas.h"
#include <string.h>
#include <stdio.h>

/* se crea la funcion que agregara los valores al token
*  recibira un token, la clase, el valor y la cadena que contendra, junto con su posicion en la tabla de simbolos
*/
void ADD_VALUE_TOKEN(TOKEN *llave, int class, char value, const char* cadena, int posicion) {
    int encontrado=0,i=0;                           //se crea una variable auxiliar que servira como bandera para el while
    char *valores[17]={"case","long","if","else","double","while","do","int","default","float","for","switch","short","continue","break","char","return"}; //el arreglo contendra las palabras reservadas
    char *relacional[6]={"<",">","<=",">=","==","!="};  //el arreglo contendra los operadores relacionales
    
    // el if es para saber de que clase es para reutilizar la funcion en varias producciones
    if(class==0){   //este es para la clase 0
    while(encontrado==0){       //si no es encontrado no es igual a 0 no se repite el while
        if(strcmp(valores[i],cadena)==0){   //se compara las palabras reservadas con la cadena que es la coincidencia
            encontrado=1;       //si lo encuentra se pone 1 para que termine el while
            i--;                //se decrementa para mantener la sitaxis porque cuando salga del if, se incrementara, y asi mantendra el numero en donde se encontro
        }
        i++;                //se incrementa para continuar con el siguiente dato del arreglo
    }   //fin del while
        llave->valor=i;     //se agrega el valor de i porque es la posicion de la palabra reservada
        llave->clase=class; //se agrega la clase que es 0
        strcpy(llave->dato, cadena); //se agrega la coincidencia al dato de la llave
    }else if(class==7){             //Este es para la clase 7 que son los operadores relacionales
            while(encontrado==0){   //mismo bucle que la clase 0
                if(strcmp(relacional[i],cadena)==0){
                encontrado=1;
                i--;
            }
            i++;
        }//fin del while
        llave->valor=i; //se asigna el valor i que es la posicion del signo
        llave->clase=class; //se le agrega a la llave la clase que es 7
        strcpy(llave->dato, cadena); //se cagrega al dato la coincidencia en este caso el operador relacional
    }else{ //si no es clase 0 y 7
        llave->clase=class; //se agrega la clase
        llave->valor=value; //y la posicion de la tabla
        strcpy(llave->dato, cadena); //se agrega la cadena que coincide al token
    }
    llave->posicion=posicion; //finalmente se le agrega al token la posicion en la que se encuentra
};

// Se le asignas los tokens a las tablas correspondientes
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
//fin de las tablas para los tokens correspondientes

//se imprime las tablas 
void printSimbolos(T_simbolos *Tabla_simbolos,int contador){
    printf("\n------------------TABLA DE SIMBOLOS------------------\n");
    for(int i=0; i<contador; i++){
        printf("clase %d, valor %d, Dato %s\t posicion %d\n",Tabla_simbolos->tokens[i].clase, Tabla_simbolos->tokens[i].valor, Tabla_simbolos->tokens[i].dato,Tabla_simbolos->tokens[i].posicion);
    }
};

//funcion que nos ayudara a verificar si un datos es repetido
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

//misma funcion para otra tabla que encontrara las coincidencias
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

//se immprimen las demas tablas
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
//fin de las funciones que imprimen las tablas