%{
#include <stdio.h>

%}

/*Expresiones regulares*/
C \,({K})
N r|s|n
Q (\,({N}))|(\=({N}{C}))
K \i({Q})
TIPO b|g|"#"|y|x

DECLARACION {TIPO}{K};

%%
{DECLARACION} {printf("Correcta declaración del identificador\n")}

%%
