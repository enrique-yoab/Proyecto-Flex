%{
    #include <stdio.h>
    #include "tablas.h"

    int clase, cont_par, contador_global, cont_const_num, cont_identidad, cont_cadena;
    T_simbolos *TABLA_SIMBOLOS;
    T_identity *TABLA_IDENTIDADES;
    T_const_num *TABLA_CONSTANTES;
    T_cadenas *TABLA_CADENAS;
    char *datos;
    int inicio, aux;
%}

/* Expresiones regulares */
/* Expresiones para letras */

MAY [A-Z]
MIN [a-z]
/* Expresiones para numeros */

DEC [0-9]
DECSC [1-9]
OCT [0-7]

/* Expresiones para los componentes léxicos */

/* Palabras reservadas */

Pal_reservada (case|long|if|else|double|while|do|int|default|float|for|switch|short|continue|break|char|return)

/* Identificadores */

Identificadores "$"({MIN}|{MAY}|{DEC}{0,5})+

/* Constantes enteras */

Entero (0|({DECSC}{DEC}*)|(o|O){OCT}+)


/* Constantes reales */

Real ({DEC}*\.{DEC}+)

/* Constantes cadena */

Cadena ({MAY}|{MIN})*|(["'].*["'])

/* Simbolos especiales */

Sim_especiales [\[\]\(\)\{\}\,\:\;]

/* Operadores aritméticos */

Op_aritmetico [\+|\-|\*|\/|\%|\\|\^]

/* Operadores relacionales */

Op_relacional (<|>|<=|>=|==|!=)

/* Operador de asignación */

Asignacion (\=)
%%
{Pal_reservada} {printf("Palabra reservada\n");                                             //se imprime que se encontro palabra reservada
                    clase=0;                                                                //definimos la clase en 0 ya que es el primero de la tabla
                    datos=yytext;                                                           //agregamos la produccion encontrada a otro puntero para compararla y agregarla a los tokens
                    TOKEN *llave=malloc(sizeof(TOKEN));                                     //creamos el token con memoria dinamica 
                    ADD_VALUE_TOKEN(llave, clase, cont_par, datos, contador_global);        //agregamos los valores que llevara el tokek, en esta caso su clase, el valor y la cadena reconocida, junto con su posicion
                    ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS, llave, contador_global);             //agregamos el token a la tabla de simbolos, con su correspondiente posicion\
                    cont_par++;                                                             //incrementamos la variable que es el indice del arreglo o las palabras reservadas que se van encontrando
                    contador_global++;                                                      //incrementamos el contador de las llaves global
                } //0
{Identificadores} {printf("es un identificador\n");                                         //se imrprime identificador si es que la produccion conincide con tal
                    clase=1;                                                                //asignamos a la clase el valor de 1
                    datos=yytext;                                                           //le agregamos al puntero cadena el texto que conincide con la regla de produccion
                    TOKEN *llave=malloc(sizeof(TOKEN));                                     //creamos el token con memoria dinamica
                    ADD_VALUE_TOKEN(llave, clase, contador_global, datos, contador_global); //se le agregan los valores al token
                    ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS, llave, contador_global);             //agregamos el token a la tabla de simbolos
                    ADD_VALUE_IDENTITY(TABLA_IDENTIDADES, llave, cont_identidad);           //agregamos ahora el token a la tabla de cont_identidad porque es un token identificador
                    cont_identidad++;                                                       //incrementamos el contador de Identificadores 
                    contador_global++;                                                      //incrementamos el contador global de las llaves
                  } //1

{Entero} {printf("Entero\n");                                                       //se imrprime Entero cuando encuentre la cadena que coincida con la regla de produccion
            clase=2;                                                                    //se define la clase en 2
            datos=yytext;                                                               //se almacena en el puntero de tipo caracter la concidencia que encontro la regla de produccion
            TOKEN *llave=malloc(sizeof(TOKEN));                                         //se crea el token con memoria dinamica
            ADD_VALUE_TOKEN(llave, clase, contador_global, datos, contador_global);     //se agrega los valores del token que en esta caso es la posicion en la tabla y la clase
            ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS, llave, contador_global);                 //se agrega el token a la tabla de simbolos
            contador_global++;                                                          //se incrementa el contador global de las llaves
          } //2

{Real} { printf("Es un real\n");                                                                    //se imprime real si encuentra una coincidencia en la regla de produccion
            clase = 3;                                                                              //se agrega el valor de 3 a la clase
            datos = yytext;                                                                         //se agrega al puntero caracter la coincidencia de la regla de produccion
            TOKEN *llave = malloc(sizeof(TOKEN));                                                   //se crea el token con memoria dinamica
            ADD_VALUE_TOKEN(llave, clase, cont_const_num, datos, contador_global);                  // se agregan los valores al token que es su posicion en la tabla constante y la posicion, junto con su clase
            ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS, llave, contador_global);                             //se agrega el token creado a la tabla de simbolos
            if (inicio == 0 || repetido(TABLA_CONSTANTES, datos, cont_const_num) == 0) {            //se agrega el primer valor a la tabla de constantes y si se repite no entra al if por lo que no se agrega a la tabla
                // Si es el primer valor o no está repetido, se agrega a la lista de constantes     //de constantes numericas
                ADD_VALUE_CONSTANTE_NUMERICA(TABLA_CONSTANTES, llave, cont_const_num);              //agrega el token a la tabla de constantes numericas si es que no se repite
                inicio++;                                                                           //se incrementa el inicio para que ya no sea de utilidad para el if
                cont_const_num++;                                                                   //se incrementa el contador de las constante numericas
            }
            contador_global++;                                                                      //se incrementa el valor de las llaves globales
        } //3

{Cadena} {printf("Es una cadena\n");                                                            //se imrprime cadena si es que la regla de produccion encuentra una coincidencia
            clase=4;                                                                            //se asgina el valor de 4 a la clase
            datos=yytext;                                                                       //se agrega al puntero caracter la cadena que coincidio con la regla de produccion
            TOKEN *llave=malloc(sizeof(TOKEN));                                                 //se crea el token con memoria dinamica
            ADD_VALUE_TOKEN(llave, clase, contador_global, datos, contador_global);             //se agrega los valores del token que es su clase, su valor el cual es la posicion en su tablas y la palabra
            ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS,llave,contador_global);                           //se agrega el token a la tabla de simbolos
            if(aux==0 || repetidoC(TABLA_CADENAS,datos,cont_cadena)==0){                        //se verifica agrega la llave a la tabla cadena si es el primero y si no esta repetido
                ADD_VALUE_CADENAS(TABLA_CADENAS, llave, cont_cadena);                           //se agrega el token a la tabla de cadena
                aux++;                                                                          //se incrementa el aux ya que no sera el primero, y solo se verifica si se repite
                cont_cadena++;                                                                  //se incrementa el contador de cadenas que es la posicion en su tabla.
            }   
            contador_global++;                                                                  //se incrementa el contador de llaves global
         } //4

{Sim_especiales} {printf("Simbolo especial\n");                                                 //se imprime el simbolo especial si se encuentra un coincidencia
                    clase=5;                                                                    //se agrega el valor de 5
                    datos=yytext;                                                               //se agrega al puntero caracter el la palabra que coincidio con la regla de produccion
                    TOKEN *llave=malloc(sizeof(TOKEN));                                         //se crea el token con memoria dinamica
                    int ASCII= (int)*datos;                                                     //se hace un cast al puntero caracter para que nos de el valor en ASCII
                    ADD_VALUE_TOKEN(llave, clase, ASCII, datos, contador_global);               //se agrega el token su clase y el valor de ASCII, junto con el simbolo y su posicion
                    ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS, llave, contador_global);                 //se agrega el token a la tabla de simbolos
                    contador_global++;                                                          //se incrementael contador de llaves global
                } //5

{Op_aritmetico} {printf("Op aritmetico\n");                                                     //se imprimer Op aritmetico cuando se encuentra una coincidencia con la regla de produccion
                    clase=6;                                                                    //se asigna el valor de 6 a la clase   
                    datos=yytext;                                                               //se asigna al puntero char, la coincidencia, en esta caso el operador encontrando
                    TOKEN *llave=malloc(sizeof(TOKEN));                                         //se crea el token con memoria dinamica
                    ADD_VALUE_TOKEN(llave, clase, contador_global, datos, contador_global);     //se agrega al token la clase y el valor en la posicion de la tabla
                    ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS, llave, contador_global);                 //se agrega a la tabla de simbolos
                    contador_global++;                                                          //se incrementa el valor de las llaves global
                } //6

{Op_relacional} {printf("Op relacional\n");                                                     //se imprimer Op relacional si se encuentra una coincidencia
                    clase=7;                                                                    //se agrega el valor de 7 a la clase
                    datos=yytext;                                                               //se agrega al puntero la coincidencia, en este caso el operador
                    TOKEN *llave=malloc(sizeof(TOKEN));                                         //se crea el token con memoria dinamica
                    ADD_VALUE_TOKEN(llave, clase, contador_global, datos, contador_global);     //se agrega los valores al token creado, que es su clase y la posicion del operador de su respectiva tabla
                    ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS, llave, contador_global);                 //se agrega el token a la tabla de simbolos con su posicion
                    contador_global++;                                                          //se incrementa el contador de llaves global
                } //7

{Asignacion} {printf("Asignacion\n");                                                           //se imprime asignacion si encuentra alguna coincidencia que es =
                    clase=8;                                                                    //se agrega el valor de 8 a la clase
                    datos=yytext;                                                               //se agrega al puntero caracter el caracter =
                    TOKEN *llave=malloc(sizeof(TOKEN));                                         //se crea el token con memoria dinamica
                    ADD_VALUE_TOKEN(llave, clase, contador_global, datos, contador_global);     //se asgina al token los valores de la clase y su posicion, junto con su dato
                    ADD_VALUE_SIMBOLOS(TABLA_SIMBOLOS, llave, contador_global);                 //se agrega a la tabla de simbolos
                    contador_global++;                                                          //se incrementa el valor de las llave global
             } //8

. {printf("Error\n");}
%%


int main(int argc, char *argv[]) {

    //se crean las tablas con memoria dinamica
    TABLA_SIMBOLOS=malloc(sizeof(T_simbolos));
    TABLA_IDENTIDADES=malloc(sizeof(T_identity));
    TABLA_CONSTANTES=malloc(sizeof(T_const_num));
    TABLA_CADENAS=malloc(sizeof(T_cadenas));

    if (argc < 2) {
        printf("Uso: %s archivo_de_entrada\n", argv[0]);
        return 1;
    }
    
    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
    
    yyin = archivo;  // Asignar el archivo como la entrada para yylex()
    
    yylex();
    printSimbolos(TABLA_SIMBOLOS, contador_global);
    printIdentity(TABLA_IDENTIDADES, cont_identidad);
    printConstante(TABLA_CONSTANTES, cont_const_num);
    printCadenas(TABLA_CADENAS, cont_cadena);
    free(TABLA_CADENAS);
    free(TABLA_CONSTANTES);
    free(TABLA_IDENTIDADES);
    free(TABLA_SIMBOLOS);
    
    fclose(archivo);
    yylex_destroy();
    return 0;
}