%{
#include <stdio.h>

%}

/*Expresiones regulares*/
/*Para el identificador*/
C \,({K})
N r|s|n
Q (\,({N}))|(\=({N}{C}))
K \i({Q})
TIPO b|g|"#"|y|x

DECLARACION {TIPO}{K};

/*Expresion regular para la asignacion*/
A \i={B};
B s|E

/*Expresion aritmetica*/
E {T}{F}
G \+{T}{G}|\-{T}{G}
T {F}{L}
L \*{F}{L}|\/{F}[L]|\\{F}{L}|\%{F}{L}|\^{F}{L}
F \({E}\)|i|n|r|{llama}

/*Expresion regular para el relacional*/
R i{R1}{V}|n{R1}{V1}|r{R1}{V2}|s{R1}{V3}
R1 \>|\<|l|e|d|u
V i|n|r|s
V1 b|i|r
V2 r|i
V3 s|i

/*Expresion regular para las preposiciones*/
P {A}|{I}|{H}|{W}|{J}|{llama}|{Devuelve}|c\;

/*Epresion regular para mas proposiciones*/
ListaP {P}{ListaP}

/*Expresion regular para la sentencia lop*/
W w\({R}\)m{ListaP}

/*Sentencia Evaluate*/

I f\({R}\){ListaP}{I1}\:
I1 t{ListaP}

/*sentencia repeat*/
J j\({Y}{X}{Z}\{{ListaP}\}
Y i={E}|\;
X {R}\;|\;
Z i={E}\)|\)

/*sentencia select*/
H h\(i\){C}
C an\:{ListaP}{U}{C}
O o\:{ListaP}
U q

/*SEntencia Trowh*/
Devuelve z\({valor}\)
valor {V}

/*Llamada a una funcion*/
llama \[i\({arg}\)\]
arg {V}{otroarg}
otroarg \,{V}{otroarg}

/*funciones*/
Func {TIPO}i\({param}\)\{{cuerpo}\}
param {TIPO}i{otroparam}
cuerpo {decl}{ListaP}
decl {DECLARACION}{decl}

/*Estructura del programa*/
Program {Func}{otraFunc}
otraFunc {Func}{otraFunc}
%%
{DECLARACION} {printf("Correcta declaración del identificador\n")}

{A} {printf("Correcta declaracion de la asignacion\n");}

{E} {printf("Correcta declaracion de la expresion aritmetica\n");}

{R} {printf("Correcta declaracion de la expresion relacional\n");}

{P} {printf("Correcta declaracion de las proposiciones\n");}

{ListaP} {printf("Correcta declaracion de otras proposicioens\n");}

{W} {printf("Correcta declaracion de la sentencia Loop\n");}

{I} {printf("Correcta declaracion de la sentencia evaluate\n");}

{J} {printf("Correcta declaracion de la sentencia repeat\n");}

{H} {printf("Correcta declaracion de la sentencia select\n");}

{Devuelve} {printf("Correcta declaracion de la sentencia Throw");}

{llama} {printf("Correcta declaracion de la llamada a funcion\n");}

{Func} {printf("Correcta declaracion de la funcion\n");}

{Program} {printf("Correcta declaracion de estructura del programa\n");}

. {printf("Error encontrado\n");}
%%
