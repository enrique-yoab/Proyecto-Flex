#include "tablas.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* se crea la funcion que agregara los valores al token
*  recibira un token, la clase, el valor y la cadena que contendra, junto con su posicion en la tabla de simbolos
*/
void ADD_VALUE_TOKEN(TOKEN *llave, int class, char value, const char* cadena, int posicion) {
    int encontrado=0,i=0;                           //se crea una variable iiliar que servira como bandera para el while
    char *valores[17]={"alternative","big","evaluate","instead","large","loop","make","number","other","real","repeat","select","small","step","stop","symbol","throw"}; //el arreglo contendra las palabras reservadas
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
void ATOM_VALUE(T_atomos *tabla_atomos, int clase, char *dato, int contador, ATOMOS *atom){
    char *pal_reservadas [17] = {"alternative", "big", "evaluate", "instead", "large", "loop", "make", "number", "other", "real", "repeat", "select", "small", "step", "stop", "symbol", "throw"};
    char *atom_pr [17] = {"a", "b", "f", "t", "g", "w", "m", "#", "o", "x", "j", "h", "p", "c", "q", "y", "z"};
    char *op_rel [6] = {"<", ">", "<=", ">=", "==", "!="};
    char *atom_op_r [6] = {"<", ">", "i", "u", "e", "d"};
    
    //Palabras reservadas
    if (clase == 0){
        for (int i = 0; i <= 16; i++){
            if (strcmp(dato, pal_reservadas[i]) == 0){
                atom->id = clase;
                atom->valor = i;
                atom->name = atom_pr[i];
                atom->dato = dato;
            }
        }
    }else if(clase == 5){ 
        //Simbolos especiales
        atom->id = clase;
        atom->valor = clase;
        atom->name = dato;
        atom->dato = dato;
    }else if(clase == 6){
        //Operadores aritmeticos
        atom->id = clase;
        atom->valor = clase;
        atom->name = dato;
        atom->dato = dato;
    }else if (clase == 7){//Opreadores relacionales
        for (int i = 0; i <= 5; i++){
            if(strcmp(dato, op_rel[i]) == 0){
                atom->id = clase;
                atom->valor = i;
                atom->name = atom_op_r[i];
                atom->dato = dato;
            }
        }
    }
    tabla_atomos->atomos[contador] = *atom;

}

//Funcion para agregar atomos a la tabla de atomos

void ADD_ATOM(T_atomos *tabla_atomos, int clase, char *val_atom, char * dato, int i, ATOMOS *atom){
    printf("Pas 0\n");
    //ATOMOS *atom=malloc(sizeof(ATOMOS));
    printf("Pas 1\n");
    atom->id = clase;
    printf("Pas 2\n");
    atom->valor = clase;
    printf("Pas 3\n");
    atom->name = val_atom;
    printf("Pas 4\n");
    atom->dato = dato;
    printf("Pas 5\n");
    tabla_atomos->atomos[i] = *atom;
    printf("Pas 6\n");

}


//Función para los átomos
void generate_atom(T_simbolos *sim ,T_atomos *tabla_atomos, int  i, ATOMOS *atom){
    
    printf("Entre a generar atomos\n");
    printf("%d\n", sim->tokens[i].clase);
    switch (sim->tokens[i].clase)
    {
        //caso para palabras reservadas
        case 0:
            printf("Caso 0");
            ATOM_VALUE(tabla_atomos, sim->tokens[i].clase, sim->tokens[i].dato, i, atom);
            printf("0\n");
        break;
        //Caso para identificadores
        case 1:
            printf("Caso 1");
            ADD_ATOM(tabla_atomos, sim->tokens[i].clase, "i", sim->tokens[i].dato, i, atom);
            printf("1\n");
        break;
        //Caso para enteros
        case 2:
            printf("Caso 2");
            ADD_ATOM(tabla_atomos, sim->tokens[i].clase, "n", sim->tokens[i].dato, i, atom);
            printf("2\n");
        break;
        //Caso para las reales
        case 3:
            printf("Caso 3");
            ADD_ATOM(tabla_atomos, sim->tokens[i].clase, "r", sim->tokens[i].dato, i, atom);
            printf("3\n");
        break;
        //Caso para cadenas
        case 4:
            printf("Caso 4");
            ADD_ATOM(tabla_atomos, sim->tokens[i].clase, "s", sim->tokens[i].dato, i, atom);
            printf("4\n");
        break;
        //Caso para sim especiales
        case 5:
            printf("Caso 5");
            ATOM_VALUE(tabla_atomos, sim->tokens[i].clase, sim->tokens[i].dato, i, atom);
            printf("5\n");
        break;
        //Caso para 
        case 6:
            printf("Caso 6");
            ATOM_VALUE(tabla_atomos, sim->tokens[i].clase, sim->tokens[i].dato, i, atom);
            printf("6\n");
        break;
        case 7:
            printf("Caso 7");
            ATOM_VALUE(tabla_atomos, sim->tokens[i].clase, sim->tokens[i].dato, i, atom);
            printf("7\n");
        break;
        case 8:
            printf("Caso 8");
            ADD_ATOM(tabla_atomos, sim->tokens[i].clase, "=", sim->tokens[i].dato, i, atom);
            printf("8\n");
        break;
        default:
            printf("Error\n");
        break;

    }
}

void printAtomos(T_atomos *atomos, int contador){
    printf("\n------------------TABLA DE ATOMOS------------------\n");
    for (int i = 0; i <= contador; i++){
        printf("Clase: %d, Valor: %d, Atomo: %s, Token asociado: %s\n", atomos->atomos[i].id, atomos->atomos[i].valor, atomos->atomos[i].name, atomos->atomos[i].dato);
    }
}