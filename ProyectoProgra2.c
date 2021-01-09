#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ninos Ninos;
typedef struct Registros Registro_Ninos;

struct ninos{
    Ninos *siguiente;
    int ID;
    char nombre[60];
    char usuario[40];
    char correo[40];
    char fecha_nacimiento[40];
    int edad;
    char necesidades_especiales[10][60];
    int cant;
};

struct Registros
{
    Ninos *Inicio;
    Ninos *Final;
};
