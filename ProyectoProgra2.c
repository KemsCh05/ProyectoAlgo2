include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ninos Ninos;
typedef struct Registros Registro_Ninos;
typedef struct ayudantes Ayudante;
typedef struct Registros2 Registro_Ayudantes;
typedef struct juguetes Juguete;
typedef struct ruta Ruta;
typedef struct lugar Lugar;
typedef struct Registros3 Registro_Lugares;
typedef struct comportamiento Comportamiento;
typedef struct Registros4 Registro_Comportamiento;
typedef struct juguete_carta Juguete_Carta;
typedef struct Lista_Deseos Deseos;
typedef struct carta Carta_Santa;
typedef struct Registros5 Registro_Carta;
typedef struct anno Anno;
typedef struct Registros6 Registro_Annos;
typedef struct juguetes_lugar Juguete_Lugar;
typedef struct Registros7 Registro_Lugares_Juguetes;
typedef struct juguetes_top Juguete_Top;
typedef struct Registros8 Registro_Top_Juguetes;

struct ninos{
    Ninos *siguiente;
    Ninos *anterior;
    int ID;
    char nombre[60];
    char usuario[40];
    char residencia[30];
    char correo[40];
    char fecha_nacimiento[40];
    int edad;
    char necesidades_especiales[10][60];
    int cant;
    int comportamientos_malos;
};

struct Registros
{
    Ninos *Inicio;
    Ninos *Final;
};

struct ayudantes
{
    Ayudante *siguiente;
    Ayudante *anterior;
    int ID;
    char nombre[60];
    char puesto[25];
    char funciones[6][60];
    char fecha[11];
    int cant;
    int cantidad_procesadas;
};

struct Registros2
{
    Ayudante *Inicio;
    Ayudante *Final;
};

struct juguetes
{
    Juguete *izq;
    Juguete *der;
    Juguete *anterior;
    char codigo[10];
    char nombre[30];
    char descripcion[60];
    char categoria[15];
    char rango[15];
    int costo;
};

Juguete *raiz = NULL;

struct ruta
{
    Lugar *origen;
    Lugar *destino;
    int minutos;
    int distancia;
    char tipo[10];
    Ruta *siguiente;
    Ruta *anterior;
};

struct lugar
{
    Ruta *Inicio;
    Ruta *Final;
    Lugar *siguiente;
    Lugar *anterior;
    Lugar *antecesor;
    char codigo[10];
    char nombre[30];
    int codigo_postal;
    int distancia_acumulada;
    int visitado_o_permanente;
    int ninos;
    int cantidad_juguetes;
};

struct Registros3
{
    Lugar *Inicio;
    Lugar *Final;
};

struct comportamiento
{
    Comportamiento *siguiente;
    char nombre_padre[30];
    int ID_Nino;
    char fecha[11];
    char descripcion[130];
    char indicacion[6];
};

struct Registros4
{
    Comportamiento *Inicio;
    Comportamiento *Final;
};

struct juguete_carta
{
    Juguete_Carta *siguiente;
    Juguete_Carta *anterior;
    char estado[25];
    char juguete[30];
    int ayudante;
    int anno;
    int nino;
};

struct Lista_Deseos
{
    Deseos *siguiente;
    Deseos *anterior;
    char juguete[30];
};

struct carta
{
    Juguete_Carta *Inicio_Juguetes;
    Juguete_Carta *Final_Juguetes;
    Deseos *Inicio_Deseos;
    Deseos *Final_Deseos;
    Carta_Santa *siguiente;
    Carta_Santa *anterior;
    int ID_Nino;
    char nombre_nino[60];
    char estado[15];
    int contador_juguetes;
    int contador_juguetes_a_entregar;
    int anno;
};

struct Registros5
{
    Carta_Santa *Inicio;
    Carta_Santa *Final;
};

struct anno
{
    Anno *siguiente;
    int anno;
    int cantidad_juguetes;
    int cantidad_cartas_aprobadas;
    int cantidad_cartas_rechazadas;
};

struct Registros6
{
    Anno *Inicio;
    Anno *Final;
};

struct juguetes_lugar
{
    Juguete_Lugar *siguiente;
    char nombre[30];
    int cantidad_juguetes;
};

struct Registros7
{
    Juguete_Lugar *Inicio;
    Juguete_Lugar *Final;
};

struct juguetes_top
{
    Juguete_Top *siguiente;
    Juguete_Top *anterior;
    char nombre[30];
    int contador;
};

struct Registros8
{
    Juguete_Top *Inicio;
    Juguete_Top *Final;
};

Ninos *CrearNino(int ID, char *nombre, char *usuario, char *lugar_residencia, char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant){

    //Se crea un nuevo nodo apartando el espacio en memoria
    Ninos *NuevoNino = (Ninos *) malloc(sizeof(Ninos));
    NuevoNino->siguiente = NULL;
    NuevoNino->anterior = NULL;

    //Agregamos los datos
    NuevoNino->ID = ID;
    strcpy(NuevoNino->nombre, nombre); 
    strcpy(NuevoNino->usuario, usuario);
    strcpy(NuevoNino->residencia, lugar_residencia);
    strcpy(NuevoNino->correo, correo); 
    strcpy(NuevoNino->fecha_nacimiento, fecha_n);
    NuevoNino->edad = edad;
    NuevoNino->cant = cant;
    NuevoNino->comportamientos_malos = 0;
    int i;
    for (i = 0; i < cant; i++)
    {
        strcpy(NuevoNino->necesidades_especiales[i], necesidades[i]);
    }

    //Devolvemos el nodo creado
    return NuevoNino; 
}

void Agregar_Nino(Registro_Ninos *Lista, Registro_Lugares *Lista2, int ID, char *nombre, char *usuario, char *lugar_residencia, char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant){

    //Se realiza un recorrido a la lista de niños para validar que no se repitan identificaciones
    Ninos *puntero = Lista->Inicio;
    printf("\n\n");
    while (puntero != NULL)
    {
        if (puntero->ID == ID)
        {
            printf("Error, Ya existe un nino con esa identificacion. Ingrese otra identificacion y vuelva a intentarlo.\n");
            return;
        }
        puntero = puntero->siguiente;
    }

    // Recorrido a los lugares registrados para validar que el lugar de residencia del niño se encuentre registrado
    Lugar *puntero2 = Lista2->Inicio;
    int validacion = 0;
    while (puntero2 != NULL)
    {
        if (strcmp(puntero2->nombre, lugar_residencia) == 0)
        {
            validacion++;
        }
        puntero2 = puntero2->siguiente;
    }
    
    if (validacion == 0)
    {
        printf("Lo sentimos: el lugar de residencia del nino no se encuentra dentro del catalogo de lugares. \n");
        return;
    }

    //Se crea el nuevo niño
    Ninos *Nuevo = CrearNino(ID, nombre, usuario, lugar_residencia, correo, fecha_n, edad, necesidades, cant);

    //En caso de que la lista este vacia 
    if (Lista->Inicio == NULL)
    {
        Lista->Inicio = Nuevo;
        Lista->Final = Nuevo;
    }

    //En caso de que la lista no este vacia
    else
    {
        Lista->Final->siguiente = Nuevo;
        Nuevo->anterior = Lista->Final;
        Lista->Final = Nuevo;
    }    
    printf("Se registro el nino exitosamente \n");
}

void modificar_datos_nino(Registro_Ninos *Lista, int ID, int seleccion){
    Ninos *puntero = Lista->Inicio;
    int validacion = 0;

    // Ciclo para buscar en la lista de niños un niño que coincida con el ID ingresado que se modificará/eliminará
    while (puntero != NULL)
    {

        // En caso de que se encuentre el niño que coincide con el ID ingresado
        if (puntero->ID == ID){
            validacion++;

            // En caso de que se desee modificar los datos
            if (seleccion == 1){
                int seleccion2;
                int a = 0;

                // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
                while(a == 0){

                    // Se consulta al usuario el dato que desea modificar
                    printf("Ingrese 1 para modificar el ID del nino \nIngrese 2 para modificar el nombre del nino \nIngrese 3 para modificar el usuario del nino \nIngrese 4 para modificar el correo del nino \nIngrese 5 para modificar la fecha de nacimiento del nino \nIngrese 6 para modificar la edad del nino \nIngrese 7 para modificar las necesidades especiales del nino \nIngrese 8 para cancelar \n");
                    scanf("%i", &seleccion2);

                    // En caso de que se desee modificar la identificación
                    if (seleccion2 == 1)
                    {
                        int ID2;
                        printf("Ingrese la nueva identificacion del nino(a): \n");
                        scanf("%i", &ID2);
                        puntero->ID = ID2;
                        printf("Se modifico la identificacion del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el nombre
                    else if (seleccion2 == 2 && a == 0)
                    {
                        char nombre[60];
                        printf("Ingrese el nuevo nombre del nino(a): \n");
                        scanf(" %[^\t\n]s", &nombre);
                        strcpy(puntero->nombre, nombre);
                        printf("Se modifico el nombre del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el nombre de usuario
                    else if (seleccion2 == 3 && a == 0)
                    {
                        char usuario[40];
                        printf("Ingrese el nuevo nombre de usuario del nino(a): \n");
                        scanf(" %[^\t\n]s", &usuario);
                        strcpy(puntero->usuario, usuario);
                        printf("Se modifico el nombre de usuario del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el correo
                    else if (seleccion2 == 4 && a == 0)
                    {
                        char correo[40];
                        printf("Ingrese el nuevo correo del nino(a): \n");
                        scanf(" %[^\t\n]s", &correo);
                        strcpy(puntero->correo, correo);
                        printf("Se modifico el correo del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar la fecha de nacimiento
                    else if (seleccion2 == 5 && a == 0)
                    {
                        char fecha_n[40];
                        printf("Ingrese la nueva fecha de nacimiento del nino(a): \n");
                        scanf(" %[^\t\n]s", &fecha_n);
                        strcpy(puntero->fecha_nacimiento, fecha_n);
                        printf("Se modifico la fecha de nacimiento del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar la edad
                    else if (seleccion2 == 6 && a == 0)
                    {
                        int edad;
                        printf("Ingrese la nueva edad del nino(a): \n");
                        scanf("%i", &edad);
                        puntero->edad = edad;
                        printf("Se modifico la edad del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar las necesidades especiales
                    else if (seleccion2 == 7 && a == 0)
                    {
                        int cant;
                        printf("Ingrese la cantidad de necesidades especiales que desea agregar: \n");
                        scanf("%i", &cant);
                        int i;
                        for ( i = 0; i < cant; i++)
                        {
                            char necesidad[60]; 
                            printf("Ingrese la necesidad %i: \n", i+1);
                            scanf(" %[^\t\n]s", &necesidad);
                            strcpy(puntero->necesidades_especiales[i], necesidad);
                        }
                        printf("Se modifico las necesidades especiales del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee cancelar
                    else if (seleccion2 == 8 && a == 0)
                    {
                        printf("No se ha modificado ningun dato \n");
                        a++;
                    }

                    // En caso de que se ingrese un dato inválido
                    else
                        printf("El numero de opcion ingresada no es valida \n");
                } 
            }

            // En caso de que se desee eliminar un dato
            if (seleccion == 2){

                // En caso de que el niño sea el único en la lista
                if (puntero == Lista->Inicio && puntero->siguiente == NULL)
                {
                    Lista->Inicio = NULL;
                    free(puntero);
                    return;
                }

                // En caso de que el niño sea el primero en la lista pero no el único
                else if (puntero == Lista->Inicio && puntero->siguiente != NULL)
                {
                    Lista->Inicio = puntero->siguiente;
                    puntero->siguiente->anterior = NULL;
                    free(puntero);
                    printf("Se ha eliminado el niño\n\n");
                    return;
                }

                else if(puntero == Lista->Final)
                {
                    Lista->Final = puntero->anterior;
                    puntero->anterior->siguiente = NULL;
                    free(puntero);
                    printf("Se ha eliminado el niño\n\n");
                    return;
                }
                
                else
                {
                    puntero->anterior->siguiente = puntero->siguiente;
                    puntero->siguiente->anterior = puntero->anterior;
                    free(puntero);
                    printf("Se ha eliminado el niño\n\n");
                    return;
                }
            }
        }
        puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre un niño que coincida con el ID ingresado se notifica el error
    if (validacion == 0)
        printf("No se pudo modificar o eliminar la informacion pues la identificacion ingresada no corresponde a la de ningun nino registrado \n");
}

void Imprimir_Ninos(Registro_Ninos *Lista){
    printf("\n\nLista de Ninos: \n\n");
    int contador = 1;
    Ninos *puntero = Lista->Inicio;

    // Ciclo para recorrer la lista e imprimir los datos de cada niño
    while (puntero != NULL)
    {

        // Se imprimen los datos
        printf("\n\n%i. Identificacion: %i \nNombre: %s \nUsuario: %s \nLugar de residencia: %s \nCorreo: %s \nFecha de nacimiento: %s \nEdad: %i \n", contador, puntero->ID, puntero->nombre, puntero->usuario, puntero->residencia, puntero->correo, puntero->fecha_nacimiento, puntero->edad);
        int cant = puntero->cant;
        int i;
        printf("Necesidades especiales: \n");

        // Para imprimir las necesidades especiales es necesario un ciclo
        for ( i = 0; i < cant; i++)
            printf("%i. %s \n", i+1, puntero->necesidades_especiales[i]);
        contador++;
        puntero = puntero->siguiente;
    }
}

Ninos *CrearNino(int ID, char *nombre, char *usuario, char *lugar_residencia, char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant);
void Agregar_Nino(Registro_Ninos *Lista, Registro_Lugares *Lista2, int ID, char *nombre, char *usuario, char *lugar_residencia, char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant);
void modificar_datos_nino(Registro_Ninos *Lista, int ID, int seleccion);
void Imprimir_Ninos(Registro_Ninos *Lista);

Ayudante *CrearAyudante(int ID, char *nombre, char *puesto, char funciones[6][60], char *fecha, int cant){

    //Se crea un nuevo nodo apartando el espacio en memoria
    Ayudante *NuevoAyudante = (Ayudante *) malloc(sizeof(Ayudante));
    NuevoAyudante->siguiente = NULL;
    NuevoAyudante->anterior = NULL;

    //Agregamos los datos
    NuevoAyudante->ID = ID;
    strcpy(NuevoAyudante->nombre, nombre); 
    strcpy(NuevoAyudante->puesto, puesto); 
    strcpy(NuevoAyudante->fecha, fecha);
    NuevoAyudante->cant = cant;
    NuevoAyudante->cantidad_procesadas = 0;
    int i;
    for (i = 0; i < cant; i++)
    {
        strcpy(NuevoAyudante->funciones[i], funciones[i]);
    }

    //Devolvemos el nodo creado
    return NuevoAyudante; 
}

void Agregar_Ayudante(Registro_Ayudantes *Lista, int ID, char *nombre, char *puesto, char funciones[6][60], char *fecha, int cant){

    //Se realiza un recorrido a la lista de ayudantes para validar que no se repitan identificaciones
    Ayudante *puntero = Lista->Inicio;
    printf("\n\n");
    while (puntero != NULL)
    {
        if (puntero->ID == ID)
        {
            printf("Error, Ya existe un ayudante de santa con esa identificacion. Ingrese otra identificacion y vuelva a intentarlo.\n");
            return;
        }
        puntero = puntero->siguiente;
    }

    //Se crea el nuevo ayudante
    Ayudante *Nuevo = CrearAyudante(ID, nombre, puesto, funciones, fecha, cant);

    //En caso de que la lista este vacia 
    if (Lista->Inicio == NULL)
    {
        Lista->Inicio = Nuevo;
        Lista->Final = Nuevo;
    }

    //En caso de que la lista no este vacia
    else
    {
        Lista->Final->siguiente = Nuevo;
        Nuevo->anterior = Lista->Final;
        Lista->Final = Nuevo;
    }    
    printf("Se registro el ayudante exitosamente \n");
}

void modificar_datos_ayudante(Registro_Ayudantes *Lista, int ID, int seleccion){
    Ayudante *puntero = Lista->Inicio;
    int validacion = 0;

    // Ciclo para buscar en la lista de ayudantes un ayudante que coincida con el ID ingresado que se modificará/eliminará
    while (puntero != NULL)
    {

        // En caso de que se encuentre el ayudante que coincide con el ID ingresado
        if (puntero->ID == ID){
            validacion++;

            // En caso de que se desee modificar los datos
            if (seleccion == 1){
                int a = 0;
                int seleccion2;

                // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
                while(a == 0){

                    // Se consulta al usuario el dato que desea modificar
                    printf("Ingrese 1 para modificar el ID del ayudante \nIngrese 2 para modificar el nombre del ayudante \nIngrese 3 para modificar el puesto del ayudante \nIngrese 4 para modificar las funciones del ayudante \nIngrese 5 para modificar la fecha en que empezo a trabajar el ayudante \nIngrese 6 para cancelar \n");
                    scanf("%i", &seleccion2);

                    // En caso de que se desee modificar la identificación
                    if (seleccion2 == 1)
                    {
                        int ID2;
                        printf("Ingrese la nueva identificacion del ayudante: \n");
                        scanf("%i", &ID2);
                        puntero->ID = ID2;
                        printf("Se modifico la identificacion del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el nombre
                    else if (seleccion2 == 2)
                    {
                        char nombre[60];
                        printf("Ingrese el nuevo nombre del ayudante: \n");
                        scanf(" %[^\t\n]s", &nombre);
                        strcpy(puntero->nombre, nombre);
                        printf("Se modifico el nombre del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el puesto
                    else if (seleccion2 == 3)
                    {
                        char puesto[40];
                        printf("Ingrese el nuevo puesto del ayudante: \n");
                        scanf(" %[^\t\n]s", &puesto);
                        strcpy(puntero->puesto, puesto);
                        printf("Se modifico el puesto del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar las funciones del puesto
                    else if (seleccion2 == 4)
                    {
                        int cant;
                        printf("Ingrese la cantidad de funciones que desea agregar: \n");
                        scanf("%i", &cant);
                        int i;
                        for ( i = 0; i < cant; i++)
                        {
                            char funcion[60]; 
                            printf("Ingrese la funcion %i: \n", i+1);
                            scanf(" %[^\t\n]s", &funcion);
                            strcpy(puntero->funciones[i], funcion);
                        }
                        printf("Se modifico las funciones del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar la fecha en que inició a trabajar
                    else if (seleccion2 == 5)
                    {
                        char fecha[40];
                        printf("Ingrese la nueva fecha en que empezo a trabajar el ayudante: \n");
                        scanf(" %[^\t\n]s", &fecha);
                        strcpy(puntero->fecha, fecha);
                        printf("Se modifico la fecha del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee cancelar
                    else if (seleccion2 == 6)
                    {
                        printf("No se ha modificado ningun dato \n");
                        a++;
                    }
                    
                    // En caso de que se ingrese un dato inválido
                    else
                    {
                        printf("El numero de opcion ingresada no es valida \n");
                    } 
                } 
            }

            // En caso de que se desee eliminar un dato
            if (seleccion == 2){

                // En caso de que el ayudante sea el único en la lista
                if (puntero == Lista->Inicio && puntero->siguiente == NULL)
                {
                    Lista->Inicio = NULL;
                    Lista->Final = NULL;
                    free(puntero);
                    printf("Se ha eliminado el ayudante\n\n");
                }

                // En caso de que el ayudante sea el primero en la lista pero no el único
                else if (puntero == Lista->Inicio && puntero->siguiente != NULL)
                {
                    Lista->Inicio = puntero->siguiente;
                    puntero->siguiente->anterior = NULL;
                    free(puntero);
                    printf("Se ha eliminado el ayudante\n\n");
                }

                // En caso de que sea el último en la lista
                else if(puntero == Lista->Final)
                {
                    Lista->Final = puntero->anterior;
                    puntero->anterior->siguiente = NULL;
                    free(puntero);
                    printf("Se ha eliminado el ayudante\n\n");
                }

                // En cualquier otro caso
                else
                {
                    puntero->anterior->siguiente = puntero->siguiente;
                    puntero->siguiente->anterior = puntero->anterior;
                    free(puntero);
                    printf("Se ha eliminado el ayudante\n\n");
                }
            }
        }
        if(validacion == 0)
            puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre un ayudante que coincida con el ID ingresado se notifica el error
    if (validacion == 0)
    {
        printf("No se pudo modificar o eliminar la informacion pues la identificacion ingresada no corresponde a la de ningun ayudante registrado \n");
    }
}

void Imprimir_Ayudantes(Registro_Ayudantes *Lista){
    printf("\n\nLista de ayudantes: \n\n");
    int contador = 1;
    Ayudante *puntero = Lista->Inicio;

    // Ciclo para recorrer la lista e imprimir los datos de cada niño
    while (puntero != NULL){

        // Se imprimen los datos
        printf("\n%i. Identificacion: %i \nNombre: %s \nPuesto: %s \nFecha en que empezo a trabajar con Santa: %s \n", contador, puntero->ID, puntero->nombre, puntero->puesto, puntero->fecha);
        int cant = puntero->cant;
        int i;
        printf("Funciones que realiza en su puesto: \n");

        // Para imprimir las funciones es necesario un ciclo
        for ( i = 0; i < cant; i++)
            printf("%i. %s \n", i+1, puntero->funciones[i]);
        contador++;
        puntero = puntero->siguiente;
    }
}

Ayudante *CrearAyudante(int ID, char *nombre, char *puesto, char funciones[6][60], char *fecha, int cant);
void Agregar_Ayudante(Registro_Ayudantes *Lista, int ID, char *nombre, char *puesto, char funciones[6][60], char *fecha, int cant);
void modificar_datos_ayudante(Registro_Ayudantes *Lista, int ID, int seleccion);
void Imprimir_Ayudantes(Registro_Ayudantes *Lista);

Juguete *Crear_Juguete(char *codigo, char *nombre, char *descripcion, char *categoria, char *rango, int costo){

    // Se crea un nuevo nodo apartando el espacio en memoria
    Juguete *nuevo;
    nuevo = malloc(sizeof(Juguete));

    // Agregamos los datos
    strcpy(nuevo->codigo, codigo);
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->descripcion, descripcion);
    strcpy(nuevo->categoria, categoria);
    strcpy(nuevo->rango, rango);
    nuevo->costo = costo;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->anterior = NULL;

    // Devolvemos el nodo creado
    return nuevo;
}

void Agregar_Juguete(char *codigo, char *nombre, char *descripcion, char *categoria, char *rango, int costo){

    // Se crea el nuevo juguete
    Juguete *nuevo = Crear_Juguete(codigo, nombre, descripcion, categoria, rango, costo);

    // En caso de que no haya ningún juguete en el árbol, el nuevo juguete se convierte en la raíz
    if (raiz == NULL)
        raiz = nuevo;

    // En caso de que ya se haya agregado al menos un juguete
    else
    {
        Juguete *anterior, *recorrido;
        anterior = NULL;
        recorrido = raiz;

        // Mientras queden elementos en el árbol se repite el ciclo
        while (recorrido != NULL)
        {
            anterior = recorrido;

            // En caso de que el costo del nuevo juguete sea menor al de el elemento en cuestión se continúa por la izquierda
            if (nuevo->costo < recorrido->costo)
                recorrido = recorrido->izq;

            // En caso de que el costo del nuevo juguete sea mayor al de el elemento en cuestión se continúa por la derecha
            else
                recorrido = recorrido->der;
        }

        // En caso de que el costo del nuevo juguete sea menor al de el último elemento recorrido se inserta a la izquierda de este
        if (nuevo->costo < anterior->costo){
            anterior->izq = nuevo;
            nuevo->anterior = anterior;
        }

        // En caso de que el costo del nuevo juguete sea mayor al de el último elemento recorrido se inserta a la derecha de este
        else{
            anterior->der = nuevo;
            nuevo->anterior = anterior;
        }
    }
    printf("Se agrego el juguete existosamente\n\n");
}

void Modificar_Juguetes(Juguete *recorrido, char *nombre, int costo, int seleccion){

    // Ciclo para buscar en la lista de juguetes un juguete que coincida con el nombre ingresado que se modificará/eliminará
    while (recorrido != NULL)
    {

        // En caso de que se encuentre el juguete a modificar/eliminar
        if (strcmp(recorrido->nombre, nombre)== 0 )
        {

            // En caso de que se desee modificar
            if (seleccion == 1)
            {
                int a = 0;

                // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
                while (a == 0)
                {
                    int seleccion2 = 0;

                    // Se consulta al usuario el dato que desea modificar
                    printf("Ingrese 1 para modificar el codigo del juguete \nIngrese 2 para modificar el nombre del juguete \nIngrese 3 para modificar la descripcion del juguete \nIngrese 4 para modificar la categoria del juguete \nIngrese 5 para modificar el rango de edad del juguete \nIngrese 6 para modificar el costo del juguete \nIngrese 7 para cancelar \n");
                    scanf("%i", &seleccion2);

                    // En caso de que se desee modificar el código
                    if (seleccion2 == 1)
                    {
                        char codigo[10];
                        printf("Ingrese el nuevo codigo del juguete: \n");
                        scanf(" %[^\t\n]s", &codigo);
                        strcpy(recorrido->codigo, codigo);
                        printf("Se ha modificado exitosamente el codigo del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar el nombre
                    else if (seleccion2 == 2)
                    {
                        char nombre[30];
                        printf("Ingrese el nuevo nombre del juguete: \n");
                        scanf(" %[^\t\n]s", &nombre);
                        strcpy(recorrido->nombre, nombre);
                        printf("Se ha modificado exitosamente el nombre del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar la descripción
                    else if (seleccion2 == 3)
                    {
                        char descripcion[60];
                        printf("Ingrese la nueva descripcion del juguete: \n");
                        scanf(" %[^\t\n]s", &descripcion);
                        strcpy(recorrido->descripcion, descripcion);
                        printf("Se ha modificado exitosamente la descripcion del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar la categoría
                    else if (seleccion2 == 4)
                    {
                        char categoria[15];
                        printf("Ingrese la nueva categoria del juguete: \n");
                        scanf(" %[^\t\n]s", &categoria);
                        strcpy(recorrido->categoria, categoria);
                        printf("Se ha modificado exitosamente la categoria del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar el rango de edad
                    else if (seleccion2 == 5)
                    {
                        char rango[15];
                        printf("Ingrese el nuevo rango de edad del juguete: \n");
                        scanf(" %[^\t\n]s", &rango);
                        strcpy(recorrido->rango, rango);
                        printf("Se ha modificado exitosamente el rango de edad del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar el costo
                    else if (seleccion2 == 6)
                    {
                        int costo;
                        printf("Ingrese el nuevo costo del juguete: \n");
                        scanf("%i", &costo);
                        recorrido->costo = costo;
                        printf("Se ha modificado exitosamente el costo del juguete \n");
                        return;
                    }

                    // En caso de que se desee cancelar
                    else if (seleccion2 == 7)
                    {
                        printf("No se ha modificado ningun dato \n");
                        return;
                    }
                    
                    // En caso de que se ingrese un dato inválido
                    else
                        printf("El numero ingresado no corresponde a ninguna de las opciones disponibles. Vuelva a intentarlo \n");
                }   
            }

            // En caso de que se desee eliminar un dato
            if (seleccion == 2)
            {

                // En caso de que el dato a eliminar sea la raíz
                if (recorrido == raiz)
                {

                    // En caso de que la raíz no tenga hijos
                    if (recorrido->izq == NULL && recorrido->der == NULL)
                    {
                        raiz = NULL;
                        free(recorrido);
                        return;
                    }

                    // En caso de que la raíz tenga solo hijo izquierdo
                    else if (recorrido->izq != NULL && recorrido->der == NULL)
                    {
                        raiz = recorrido->izq;
                        recorrido->izq->anterior = NULL;
                        recorrido->izq = NULL;
                        free(recorrido);
                        return;
                    }

                    // En caso de que la raíz tenga solo hijo derecho
                    else if (recorrido->izq == NULL && recorrido->der != NULL)
                    {
                        raiz = recorrido->der;
                        recorrido->der->anterior = NULL;
                        recorrido->der = NULL;
                        free(recorrido);
                        return;
                    }

                    // En caso de que tenga dos hijos
                    else
                    {
                        recorrido->izq->der->anterior = NULL;
                        recorrido->izq->der->izq = recorrido->izq;
                        recorrido->izq->der->der = recorrido->der;
                        raiz = recorrido->izq->der;
                        recorrido->izq->der = NULL;
                        free(recorrido);
                        return;
                    }
                }
                
                // En caso de que no se vaya a eliminar la raíz sino otro elemento

                // En caso de que el elemento no tenga hijos y esté a la izquierda de su elemento anterior
                if (recorrido->izq == NULL && recorrido->der == NULL && recorrido->anterior->izq == recorrido)
                {
                    recorrido->anterior->izq = NULL;
                    free(recorrido);
                    return;
                }

                // En caso de que el elemento no tenga hijos y esté a la derecha de su elemento anterior
                else if (recorrido->izq == NULL && recorrido->der == NULL && recorrido->anterior->der == recorrido)
                {
                    recorrido->anterior->der = NULL;
                    free(recorrido);
                    return;
                }

                // En caso de que el elemento solo tenga hijo izquierdo y esté a la izquierda de su elemento anterior
                else if (recorrido->izq != NULL && recorrido->der == NULL && recorrido->anterior->izq == recorrido)
                {
                    recorrido->izq->anterior = recorrido->anterior;
                    recorrido->anterior->izq = recorrido->izq;
                    recorrido->izq = NULL;
                    free(recorrido);
                    return;
                }

                // En caso de que el elemento solo tenga hijo izquierdo y esté a la derecha de su elemento anterior
                else if (recorrido->izq != NULL && recorrido->der == NULL && recorrido->anterior->der == recorrido)
                {
                    recorrido->izq->anterior = recorrido->anterior;
                    recorrido->anterior->der = recorrido->izq;
                    recorrido->izq = NULL;
                    free(recorrido);
                    return;
                }

                // En caso de que el elemento solo tenga hijo derecho y esté a la derecha de su elemento anterior
                else if (recorrido->der != NULL && recorrido->izq == NULL && recorrido->anterior->der == recorrido)
                {
                    recorrido->der->anterior = recorrido->anterior;
                    recorrido->anterior->der = recorrido->der;
                    recorrido->der = NULL;
                    free(recorrido);
                    return;
                }

                // En caso de que el elemento solo tenga hijo derecho y esté a la izquierda de su elemento anterior
                else if (recorrido->der != NULL && recorrido->izq == NULL && recorrido->anterior->izq == recorrido)
                {
                    recorrido->der->anterior = recorrido->anterior;
                    recorrido->anterior->izq = recorrido->der;
                    recorrido->der = NULL;
                    free(recorrido);
                    return;
                }

                // En caso de que el elemento solo tenga dos hijos y esté a la izquierda de su elemento anterior
                else if (recorrido->der != NULL && recorrido->izq != NULL && recorrido->anterior->izq == recorrido)
                {
                    recorrido->izq->der->anterior = recorrido->anterior;
                    recorrido->anterior->izq = recorrido->izq->der;
                    recorrido->izq->der = NULL;
                    free(recorrido);
                    return;
                }

                // En caso de que el elemento solo tenga dos hijos y esté a la derecha de su elemento anterior
                else if (recorrido->der != NULL && recorrido->izq != NULL && recorrido->anterior->der == recorrido)
                {
                    recorrido->izq->der->anterior = recorrido->anterior;
                    recorrido->anterior->der = recorrido->izq->der;
                    recorrido->izq->der = NULL;
                    free(recorrido);
                    return;
                }
            }
        }

        // En caso de que no se haya concluido la búsqueda y que el costo ingresado sea mayor al costo del elemento en cuestión
        else if (costo > recorrido->costo) 
            recorrido = recorrido->der; 

        // En caso de que no se haya concluido la búsqueda y que el costo ingresado sea menor al costo del elemento en cuestión
        else if (costo < recorrido->costo) 
            recorrido = recorrido->izq;

        // En caso de que no se haya concluido la búsqueda y que el costo ingresado sea igual al costo del elemento en cuestión
        else
            recorrido = recorrido->der; 
    }
}

void imprimirJuguete(Juguete *recorrido)
{

    // Se repite la recursividad mientras hayan juguetes para imprimir
    if (recorrido != NULL)
    {

        // Se imprimen los datos
        printf("\n\nCodigo: %s \n", recorrido->codigo);
        printf("Nombre: %s \n", recorrido->nombre);
        printf("Descripcion: %s \n", recorrido->descripcion);
        printf("Categoria: %s \n", recorrido->categoria);
        printf("Rango de edad: %s \n", recorrido->rango);
        printf("Costo: %i \n", recorrido->costo);
        imprimirJuguete(recorrido->izq);
        imprimirJuguete(recorrido->der);
    }
}

Juguete *Crear_Juguete(char *codigo, char *nombre, char *descripcion, char *categoria, char *rango, int costo);
void Agregar_Juguete(char *codigo, char *nombre, char *descripcion, char *categoria, char *rango, int costo);
void Modificar_Juguetes(Juguete *recorrido, char *nombre, int costo, int seleccion);
void imprimirJuguete(Juguete *recorrido);

Lugar *Crear_Lugar(char *codigo, char *nombre, int codigo_postal){
    
    //Se crea un nuevo nodo apartando el espacio en memoria
    Lugar *NuevoLugar = (Lugar *) malloc(sizeof(Lugar));
    NuevoLugar->siguiente = NULL;
    NuevoLugar->anterior = NULL;
    NuevoLugar->Inicio = NULL;
    NuevoLugar->antecesor = NULL;

    //Agregamos los datos
    strcpy(NuevoLugar->codigo, codigo); 
    strcpy(NuevoLugar->nombre, nombre); 
    NuevoLugar->codigo_postal = codigo_postal;
    NuevoLugar->distancia_acumulada = 0;
    NuevoLugar->visitado_o_permanente = 0;
    NuevoLugar->ninos = 0;
    NuevoLugar->cantidad_juguetes = 0;

    //Devolvemos el nodo creado
    return NuevoLugar; 
}

void Agregar_Lugar(Registro_Lugares *Lista, char *codigo, char *nombre, int codigo_postal){
    //Se realiza un recorrido a la lista de lugares para validar que no se repitan códigos
    Lugar *puntero = Lista->Inicio;
    printf("\n\n");
    while (puntero != NULL)
    {
        if (puntero->codigo == codigo)
        {
            printf("Error, Ya existe un lugar con ese codigo. Ingrese otro codigo y vuelva a intentarlo.\n");
            return;
        }
        puntero = puntero->siguiente;
    }

    //Se crea el nuevo lugar
    Lugar *Nuevo = Crear_Lugar(codigo, nombre, codigo_postal);

    //En caso de que la lista este vacia 
    if (Lista->Inicio == NULL)
    {
        Lista->Inicio = Nuevo;
        Lista->Final = Nuevo;
    }

    //En caso de que la lista no este vacia
    else
    {
        Lista->Final->siguiente = Nuevo;
        Nuevo->anterior = Lista->Final;
        Lista->Final = Nuevo;
    }    
    printf("Se registro el lugar exitosamente \n");
}

void modificar_datos_lugar(Registro_Lugares *Lista, char *nombre, int seleccion){
    Lugar *puntero = Lista->Inicio;
    int validacion = 0;

    // Ciclo para buscar en la lista de lugares un lugar que coincida con el nombre ingresado que se modificará/eliminará
    while (puntero != NULL)
    {

        // En caso de que se encuentre el lugar que coincide con el nombre ingresado
        if (strcmp(puntero->nombre, nombre)== 0){
            validacion++;

            // En caso de que se vaya a modificar un dato
            if (seleccion == 1){
                int a = 0;
                int seleccion2;

                // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
                while(a == 0){

                    // Se consulta al usuario el dato que desea modificar
                    printf("Ingrese 1 para modificar el codigo del lugar \nIngrese 2 para modificar el nombre del lugar \nIngrese 3 para modificar el codigo postal del lugar \nIngrese 4 para cancelar \n");
                    scanf("%i", &seleccion2);

                    // En caso de que se desee modificar el codigo
                    if (seleccion2 == 1)
                    {
                        char codigo[10];
                        printf("Ingrese el nuevo codigo del lugar: \n");
                        scanf(" %[^\t\n]s", &codigo);
                        strcpy(puntero->codigo, codigo);
                        printf("Se modifico el codigo del lugar exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el nombre
                    else if (seleccion2 == 2)
                    {
                        char nombre[30];
                        printf("Ingrese el nuevo nombre del lugar: \n");
                        scanf(" %[^\t\n]s", &nombre);
                        strcpy(puntero->nombre, nombre);
                        printf("Se modifico el nombre del lugar exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el codigo postal
                    else if (seleccion2 == 3)
                    {
                        int codigo_postal;
                        printf("Ingrese el nuevo codigo postal del lugar: \n");
                        scanf("%i", &codigo_postal);
                        puntero->codigo_postal = codigo_postal;
                        printf("Se modifico el codigo postal del lugar exitosamente \n");
                        a++;
                    }

                    //En caso de que se desee cancelar
                    else if (seleccion2 == 4)
                    {
                        printf("No se modifico ningun dato \n");
                        return;
                    }
                    
                    else
                    {
                        printf("El numero de opcion ingresada no es valida \n");
                    } 
                } 
            }

            // En caso de que se desee eliminar un lugar
            if (seleccion == 2){

                // En caso de que el lugar sea el único en la lista
                if (puntero == Lista->Inicio && puntero->siguiente == NULL)
                {
                    Lista->Inicio = NULL;
                    free(puntero);
                    printf("Se ha eliminado el lugar\n\n");
                    return;
                }

                // En caso de que el lugar sea el primero en la lista pero no el único
                else if (puntero == Lista->Inicio && puntero->siguiente != NULL)
                {
                    Lista->Inicio = puntero->siguiente;
                    puntero->siguiente->anterior = NULL;
                    free(puntero);
                    printf("Se ha eliminado el lugar\n\n");
                    return;
                }
                
                else if(puntero == Lista->Final)
                {
                    Lista->Final = puntero->anterior;
                    puntero->anterior->siguiente = NULL;
                    free(puntero);
                    printf("Se ha eliminado el lugar\n\n");
                    return;
                }

                // En cualquier otro caso
                else
                {
                    puntero->anterior->siguiente = puntero->siguiente;
                    puntero->siguiente->anterior = puntero->anterior;
                    free(puntero);
                    return;
                }
            }
        }
        puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre un lugar que coincida con el nombre ingresado se notifica el error
    if (validacion == 0)
    {
        printf("No se pudo modificar o eliminar la informacion pues el nombre ingresado no corresponde al de ningun lugar registrado \n");
    }
}

Ruta *CrearRuta(Lugar *origen, Lugar *destino, int minutos, int distancia, char *tipo){
    //Se crea un nuevo nodo apartando el espacio en memoria
    Ruta *NuevaRuta = (Ruta *) malloc(sizeof(Ruta));
    NuevaRuta->siguiente = NULL;
    NuevaRuta->anterior = NULL;

    //Agregamos los datos
    NuevaRuta->origen = origen; 
    NuevaRuta->destino = destino;
    NuevaRuta->minutos = minutos;
    NuevaRuta->distancia = distancia; 
    strcpy(NuevaRuta->tipo, tipo);

    //Devolvemos el nodo creado
    return NuevaRuta; 
}

void Agregar_Ruta(Registro_Lugares *Lista, char *origen, char *destino, int minutos, int distancia, char *tipo){
    Lugar *puntero = Lista->Inicio;
    int validacion = 0;

    // Ciclo para validar que el lugar de origen de la ruta esté registrado dentro de la lista de lugares
    while (puntero != NULL && validacion == 0)
    {
        if (strcmp(puntero->nombre, origen) == 0)
            validacion++;
        if (validacion == 0)
            puntero = puntero->siguiente;
    }

    // En caso de que el lugar de origen no esté registrado dentro de la lista de lugares
    if (validacion == 0)
    {
        printf("El lugar de origen ingresado no se encuentra en el catalogo de lugares. Ingrese otro origen o registre un lugar con ese nombre y vuelva a intentarlo. \n");
        return;
    }
    Lugar *puntero2 = Lista->Inicio;
    int validacion2 = 0;

    // Ciclo para validar que el lugar de destino de la ruta esté registrado dentro de la lista de lugares
    while (puntero2 != NULL && validacion2 == 0)
    {
        if (strcmp(puntero2->nombre, destino) == 0)
            validacion2++;
        if (validacion2 == 0)
            puntero2 = puntero2->siguiente;
    }

    // En caso de que el lugar de destino no esté registrado dentro de la lista de lugares
    if (validacion2 == 0)
    {
        printf("El lugar de destino ingresado no se encuentra en el catalogo de lugares. Ingrese otro destino o registre un lugar con ese nombre y vuelva a intentarlo. \n");
        return;
    }
    Lugar *puntero3 = Lista->Inicio;

    // Ciclo para encontrar el lugar de origen para asginarle el nuevo nodo adyacente (la ruta que contiene el lugar de destino)
    while (strcmp(puntero3->nombre, origen) != 0)
    {
        puntero3 = puntero3->siguiente;
    }

    // Creamos la nueva ruta
    Ruta *nueva = CrearRuta(puntero, puntero2, minutos, distancia, tipo);

    // En caso de que no se haya agregado ningún nodo adyacente, se inserta el nuevo nodo en el inicio y final de los nodos adyacentes
    if (puntero3->Inicio == NULL)
    {
        puntero3->Inicio = nueva;
        puntero3->Final = nueva;
    }

    // En caso de que ya se haya agregado algún nodo adyacente, se inserta el nuevo nodo en el final de los nodos adyacentes
    else
    {
        puntero3->Final->siguiente = nueva;
        nueva->anterior = puntero3->Final;
        puntero3->Final = nueva;
    }    
    printf("Se registro la ruta exitosamente \n");
}

void modificar_datos_ruta(Registro_Lugares *Lista, int seleccion, char *origen, char *destino, char *tipo){
    Lugar *puntero = Lista->Inicio;
    int validacion = 0;

    // Ciclo para buscar la ruta que coincida con los datos ingresados
    while (puntero != NULL)
    {

        // En caso de que se encuentre el lugar que coincide con el nombre de origen ingresado
        if (strcmp(puntero->nombre, origen)== 0){
            validacion++;
            int validacion2 = 0;
            Ruta *puntero2 = puntero->Inicio;

            // Ciclo para recorrer cada uno de los lugares adyacentes al origen (con los datos de cada ruta)
            while (puntero2 != NULL && validacion2 == 0)
            {

                // En el caso de que se encuentre una ruta que coincida con el origen, destino y tipo ingresados
                if (strcmp(puntero2->origen->nombre, origen) == 0 && strcmp(puntero2->destino->nombre, destino) == 0 && strcmp(puntero2->tipo, tipo) == 0)
                {
                    validacion2++;
                }
                if(validacion2 == 0)
                    puntero2 = puntero2->siguiente;
            }

            // En caso de no encontrar ninguna ruta que cumpla con los criterios de búsqueda
            if (validacion2 == 0)
            {
                printf("No se pudo modificar o eliminar la informacion pues la ruta ingresada no corresponde a la de ninguna ruta registrada \n");
                return;
            }

            // En caso de que se desee modificar la ruta
            if (seleccion == 1){
                int a = 0;
                int seleccion2;

                // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
                while(a == 0){

                    // Se consulta al usuario el dato que desea modificar
                    printf("Ingrese 1 para modificar el tiempo que tarda la ruta \nIngrese 2 para modificar la distancia de la ruta \nIngrese 3 para modificar el tipo de ruta \nIngrese 4 para cancelar \n");
                    scanf("%i", &seleccion2);

                    // En caso de que se desee modificar la duración de la ruta
                    if (seleccion2 == 1)
                    {
                        int minutos;
                        printf("Ingrese el nuevo tiempo que tarda la ruta: \n");
                        scanf("%i", &minutos);
                        puntero2->minutos = minutos;
                        printf("Se modifico el tiempo de la ruta exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar la distancia de la ruta
                    else if (seleccion2 == 2)
                    {
                        int distancia;
                        printf("Ingrese la nueva distancia de la ruta: \n");
                        scanf("%i", &distancia);
                        puntero2->distancia = distancia;
                        printf("Se modifico la distancia de la ruta exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el tipo de ruta
                    else if (seleccion2 == 3)
                    {
                        char tipo[10];
                        printf("Ingrese el nuevo tipo de ruta: \n");
                        scanf(" %[^\t\n]s", &tipo);
                        strcpy(puntero2->tipo, tipo);
                        printf("Se modifico el nuevo tipo exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee cancelar
                    else if (seleccion2 == 4)
                    {
                        printf("No se ha modificado ningun dato. \n");
                        a++;
                    }
                    
                    // En caso de que se ingrese una opción inválida
                    else
                    {
                        printf("El numero de opcion ingresada no es valida \n");
                    } 
                } 
            }

            // En caso de que se desee eliminar una ruta
            if (seleccion == 2){

                // En caso de que la ruta sea la único en la lista
                if (puntero2 == puntero->Inicio && puntero2->siguiente == NULL)
                {
                    puntero->Inicio = NULL;
                    free(puntero2);
                    printf("Se ha eliminado el la ruta\n\n");
                    return;
                }

                // En caso de que el lugar sea el primero en la lista pero no el único
                else if (puntero2 == puntero->Inicio && puntero2->siguiente != NULL)
                {
                    puntero->Inicio = puntero2->siguiente;
                    puntero2->siguiente->anterior = NULL;
                    free(puntero2);
                    printf("Se ha eliminado el lugar\n\n");
                    return;
                }
                
                else if(puntero2 == puntero->Final)
                {
                    puntero->Final = puntero2->anterior;
                    puntero2->anterior->siguiente = NULL;
                    free(puntero2);
                    printf("Se ha eliminado el lugar\n\n");
                    return;
                }

                // En cualquier otro caso
                else
                {
                    puntero2->anterior->siguiente = puntero2->siguiente;
                    puntero2->siguiente->anterior = puntero2->anterior;
                    free(puntero2);
                    return;
                }
            }
        }
        puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre ninguna ruta que cumpla con los criterios de búsqueda
    if (validacion == 0)
    {
        printf("No se pudo modificar o eliminar la informacion pues la ruta ingresada no corresponde a la de ninguna ruta registrada \n");
    }
}

void Imprimir_Lugares_Y_Rutas(Registro_Lugares *Lista){
    printf("\n\nLista de lugares y rutas: \n\n");
    int contador = 1;
    Lugar *puntero = Lista->Inicio;

    // Ciclo para recorrer cada lugar
    while (puntero != NULL)
    {

        // Impresión de la información del lugar
        printf("\n\nLugar %i. Codigo: %s \nNombre: %s \nCodigo postal: %i \n", contador, puntero->codigo, puntero->nombre, puntero->codigo_postal);
        Ruta *puntero2 = puntero->Inicio;
        printf("Rutas que que salen desde %s: \n", puntero->nombre);
        int contador2 = 1;

        // Ciclo para recorrer cada nodo adyacente al lugar (y los datos de la ruta)
        while (puntero2 != NULL)
        {

            // Impresión de los datos de la ruta
            printf("\nRuta %i. %s - %s \nDuracion en minutos: %i \nDistancia a recorrer en km: %i \nTipo de ruta: %s \n", contador2, puntero2->origen->nombre, puntero2->destino->nombre, puntero2->minutos, puntero2->distancia, puntero2->tipo);
            contador2++;
            puntero2 = puntero2->siguiente;
        }
        contador++;
        puntero = puntero->siguiente;
    }
}

Lugar *Crear_Lugar(char *codigo, char *nombre, int codigo_postal);
void Agregar_Lugar(Registro_Lugares *Lista, char *codigo, char *nombre, int codigo_postal);
void modificar_datos_lugar(Registro_Lugares *Lista, char *nombre, int seleccion);
Ruta *CrearRuta(Lugar *origen, Lugar *destino, int minutos, int distancia, char *tipo);
void Agregar_Ruta(Registro_Lugares *Lista, char *origen, char *destino, int minutos, int distancia, char *tipo);
void modificar_datos_ruta(Registro_Lugares *Lista, int seleccion, char *origen, char *destino, char *tipo);
void Imprimir_Lugares_Y_Rutas(Registro_Lugares *Lista);

Comportamiento *Crear_Comportamiento(char *nombre_padre, int ID_Nino, char *fecha, char *descripcion, char *indicacion){
    
    //Se crea un nuevo nodo apartando el espacio en memoria
    Comportamiento *NuevoComportamiento = (Comportamiento *) malloc(sizeof(Comportamiento));
    NuevoComportamiento->siguiente = NULL;

    //Agregamos los datos
    strcpy(NuevoComportamiento->nombre_padre, nombre_padre); 
    NuevoComportamiento->ID_Nino = ID_Nino;
    strcpy(NuevoComportamiento->fecha, fecha);
    strcpy(NuevoComportamiento->descripcion, descripcion);
    strcpy(NuevoComportamiento->indicacion, indicacion);

    //Devolvemos el nodo creado
    return NuevoComportamiento; 
}

void Agregar_Comportamiento(Registro_Comportamiento *Lista, Registro_Ninos *Lista2, char *nombre_padre, int ID_Nino, char *fecha, char *descripcion, char *indicacion){
    
    //Se realiza un recorrido a la lista de niños para validar que esté registrado
    Ninos *puntero = Lista2->Inicio;
    int validacion = 0;
    printf("\n\n");
    while (puntero != NULL)
    {
        if (puntero->ID == ID_Nino)
        {
            validacion++;
            if (strcmp(indicacion, "Malo") == 0 || strcmp(indicacion, "malo") == 0)
            {
                puntero->comportamientos_malos += 1;
            }
            
        }
        puntero = puntero->siguiente;
    }

    if (validacion == 0)
    {
        printf("No existe ningun nino registrado con esa identificacion. Ingrese otra identificacion y vuelva a intentarlo. \n");
        return;
    }

    //Se crea el nuevo ayudante
    Comportamiento *Nuevo = Crear_Comportamiento(nombre_padre, ID_Nino, fecha, descripcion, indicacion);

    //En caso de que la lista este vacia 
    if (Lista->Inicio == NULL)
    {
        Lista->Inicio = Nuevo;
        Lista->Final = Nuevo;
    }

    //En caso de que la lista no este vacia
    else
    {
        Lista->Final->siguiente = Nuevo;
        Lista->Final = Nuevo;
    }    
    printf("Se registro el comportamiento exitosamente \n");
}

Comportamiento *Crear_Comportamiento(char *nombre_padre, int ID_Nino, char *fecha, char *descripcion, char *indicacion);
void Agregar_Comportamiento(Registro_Comportamiento *Lista, Registro_Ninos *Lista2, char *nombre_padre, int ID_Nino, char *fecha, char *descripcion, char *indicacion);

Carta_Santa *Crear_Carta(int identificacion, char *nombre, int anno){
    //Se crea un nuevo nodo apartando el espacio en memoria
    Carta_Santa *Nueva_Carta = (Carta_Santa *) malloc(sizeof(Carta_Santa));
    Nueva_Carta->siguiente = NULL;
    Nueva_Carta->anterior = NULL;
    Nueva_Carta->Inicio_Juguetes = NULL;
    Nueva_Carta->Inicio_Deseos = NULL;
    Nueva_Carta->contador_juguetes = 0;
    Nueva_Carta->contador_juguetes_a_entregar = 0;

    //Agregamos los datos
    Nueva_Carta->ID_Nino = identificacion;
    strcpy(Nueva_Carta->nombre_nino, nombre);
    Nueva_Carta->anno = anno;

    //Devolvemos el nodo creado
    return Nueva_Carta;
}

void Completar_Registro_Carta(Juguete *recorrido, Carta_Santa *puntero, Registro_Ninos *Lista, Registro_Lugares *Lista2, char *juguete, int precio){
    int validacion = 0;

    // Ciclo para recorrer el árbol de juguetes
    while (recorrido != NULL && validacion == 0)
    {

        // En caso de encontrar un juguete un juguete que coincida con el nombre ingresado
        if (strcmp(recorrido->nombre, juguete) == 0)
        {
            validacion++;

            // Impresión de los datos del juguete
            printf("\n\nINFORMACION DEL JUGUETE: \n");
            printf("Nombre: %s \n", recorrido->nombre);
            printf("Codigo: %s \n", recorrido->codigo);
            printf("Descripcion: %s \n", recorrido->descripcion);
            printf("Categoria: %s \n", recorrido->categoria);
            printf("Rango de edad recomendado para utilizar el juguete: %s \n", recorrido->rango);
        }

        // En caso de que no se haya encontrado el juguete y el costo ingresado sea mayor al costo del juguete actual
        else if (precio > recorrido->costo) 
            recorrido = recorrido->der; 

        // En caso de que no se haya encontrado el juguete y el costo ingresado sea menor al costo del juguete actual
        else if (precio < recorrido->costo) 
            recorrido = recorrido->izq;

        // En caso de que no se haya encontrado el juguete y el costo ingresado sea igual al costo del juguete actual
        else
            recorrido = recorrido->der; 
    }

    // En caso de que no se haya encontrado ningún juguete que coincida con el nombre ingresado
    if (recorrido == NULL)
    {
        printf("No existe ningun juguete con ese nombre y precio en el catalogo de juguetes. \n");
        return;
    }
    int decision_usuario;
    int a = 0;

    // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
    while(a == 0){

        // Se consulta al usuario la acción que desea agregar con el nuevo juguete
        printf("DIGITE 1 para agregar el juguete a su carta \nDIGITE 2 para agregar el juguete a su lista de deseos \nDIGITE 3 para cancelar \n");
        scanf("%i", &decision_usuario);

        // En caso de que desee agregarlo a su carta
        if (decision_usuario == 1)
        {

            // Creación de un nuevo nodo de los juguetes de la carta del niño
            Juguete_Carta *Nuevo = (Juguete_Carta *) malloc(sizeof(Juguete_Carta));
            Nuevo->anterior = NULL;
            Nuevo->siguiente = NULL;
            strcpy(Nuevo->estado, "Solicitado");
            strcpy(Nuevo->juguete, juguete);

            // Se agrega el nuevo juguete al inicio de la carta
            puntero->Inicio_Juguetes = Nuevo;
            puntero->Final_Juguetes = Nuevo;
            puntero->contador_juguetes += 1;
            Ninos *puntero2 = Lista->Inicio;

            // Este procedimiento agrega un nuevo juguete solicitado al lugar en que reside el niño

            //Búsqueda del niño al que se le acaba de crear la carta en la lista de niños
            while (puntero2->ID != puntero->ID_Nino)
                puntero2 = puntero2->siguiente;
            Lugar *puntero3 = Lista2->Inicio;

            // Búsqueda del lugar de residencia del niño al que se le acaba de crear la carta en la lista de lugares
            while (strcmp(puntero2->residencia, puntero3->nombre) != 0)
                puntero3 = puntero3->siguiente;

            // Se suma 1 a la cantidad de juguetes solicitados en el lugar en cuestión
            puntero3->cantidad_juguetes += 1;
            printf("Se agrego exitosamente el juguete a la carta \n");
            a++;
        }

        // En caso de que se desee agregarlo a la carta de deseos
        else if (decision_usuario == 2)
        {

            // Creación de un nuevo nodo de los juguetes de la lista de deseos del niño
            Deseos *Nuevo = (Deseos *) malloc(sizeof(Deseos));
            Nuevo->anterior = NULL;
            Nuevo->siguiente = NULL;
            strcpy(Nuevo->juguete, juguete);

            // Se agrega el nuevo juguete al inicio de la lista de deseos
            puntero->Inicio_Deseos = Nuevo;
            puntero->Final_Deseos = Nuevo;
            printf("Se agrego exitosamente el juguete a la lista de deseos. \n");
            a++;
        }

        // En caso de que se desee cancelar
        else if (decision_usuario == 3)
        {
            printf("NO se agrego el juguete ni a la carta ni a la lista de deseos. \n");
            a++;
        }

        // En caso de que se ingrese una opción inválida
        else
        {
            printf("El numero de opcion ingresada no es valida. Vuelva a intentarlo. \n");
        }  
    }
}

void Completar_Registro_Carta2(Juguete *recorrido, Carta_Santa *puntero, Registro_Ninos *Lista, Registro_Lugares *Lista2, char *juguete, int precio){
    int validacion = 0;

    // Ciclo para recorrer el árbol de juguetes
    while (recorrido != NULL && validacion == 0)
    {

        // En caso de encontrar un juguete un juguete que coincida con el nombre ingresado
        if (strcmp(recorrido->nombre, juguete) == 0)
            validacion++;

        // En caso de que no se haya encontrado el juguete y el costo ingresado sea mayor al costo del juguete actual
        else if (precio > recorrido->costo) 
            recorrido = recorrido->der; 

        // En caso de que no se haya encontrado el juguete y el costo ingresado sea menor al costo del juguete actual
        else if (precio < recorrido->costo) 
            recorrido = recorrido->izq;

        // En caso de que no se haya encontrado el juguete y el costo ingresado sea igual al costo del juguete actual
        else
            recorrido = recorrido->der; 
    }

    // En caso de que no se haya encontrado ningún juguete que coincida con el nombre ingresado
    if (recorrido == NULL)
    {
        printf("No existe ningun juguete con ese nombre y precio en el catalogo de juguetes. \n");
        return;
    }
    int decision_usuario = 1;
    int a = 0;

    // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
    while(a == 0){

        // En caso de que desee agregarlo a su carta
        if (decision_usuario == 1)
        {

            // Creación de un nuevo nodo de los juguetes de la carta del niño
            Juguete_Carta *Nuevo = (Juguete_Carta *) malloc(sizeof(Juguete_Carta));
            Nuevo->anterior = NULL;
            Nuevo->siguiente = NULL;
            strcpy(Nuevo->estado, "Solicitado");
            strcpy(Nuevo->juguete, juguete);

            // Se agrega el nuevo juguete al inicio de la carta
            puntero->Inicio_Juguetes = Nuevo;
            puntero->Final_Juguetes = Nuevo;
            puntero->contador_juguetes += 1;
            Ninos *puntero2 = Lista->Inicio;

            // Este procedimiento agrega un nuevo juguete solicitado al lugar en que reside el niño

            //Búsqueda del niño al que se le acaba de crear la carta en la lista de niños
            while (puntero2->ID != puntero->ID_Nino)
                puntero2 = puntero2->siguiente;
            Lugar *puntero3 = Lista2->Inicio;

            // Búsqueda del lugar de residencia del niño al que se le acaba de crear la carta en la lista de lugares
            while (strcmp(puntero2->residencia, puntero3->nombre) != 0)
                puntero3 = puntero3->siguiente;

            // Se suma 1 a la cantidad de juguetes solicitados en el lugar en cuestión
            puntero3->cantidad_juguetes += 1;
            printf("Se agrego exitosamente el juguete a la carta \n");
            a++;
        }

        // En caso de que se desee agregarlo a la carta de deseos
        else if (decision_usuario == 2)
        {

            // Creación de un nuevo nodo de los juguetes de la lista de deseos del niño
            Deseos *Nuevo = (Deseos *) malloc(sizeof(Deseos));
            Nuevo->anterior = NULL;
            Nuevo->siguiente = NULL;
            strcpy(Nuevo->juguete, juguete);

            // Se agrega el nuevo juguete al inicio de la lista de deseos
            puntero->Inicio_Deseos = Nuevo;
            puntero->Final_Deseos = Nuevo;
            printf("Se agrego exitosamente el juguete a la lista de deseos. \n");
            a++;
        }

        // En caso de que se desee cancelar
        else if (decision_usuario == 3)
        {
            printf("NO se agrego el juguete ni a la carta ni a la lista de deseos. \n");
            a++;
        }

        // En caso de que se ingrese una opción inválida
        else
        {
            printf("El numero de opcion ingresada no es valida. Vuelva a intentarlo. \n");
        }  
    }
}

void Agregar_Carta(Registro_Carta *Lista, Juguete *recorrido, Registro_Ninos *Lista2, Registro_Lugares *Lista3,  int identificacion, char *nombre, int anno, char *juguete, int precio){

    //Se realiza un recorrido a la lista de cartas para validar que ese niño no tenga su carta creada
    Carta_Santa *puntero = Lista->Inicio;
    printf("\n\n");
    while (puntero != NULL)
    {
        if (puntero->ID_Nino == identificacion && puntero->anno == anno)
        {
            printf("Ya este nino tiene una carta registrada para ese anno. Si desea puede editar su carta en el menu de opciones. \n");
            return;
        }
        puntero = puntero->siguiente;
    }

    //Se crea el nuevo ayudante
    Carta_Santa *Nuevo = Crear_Carta(identificacion, nombre, anno);

    //En caso de que la lista este vacia 
    if (Lista->Inicio == NULL)
    {
        Lista->Inicio = Nuevo;
        Lista->Final = Nuevo;
    }

    //En caso de que la lista no este vacia
    else
    {
        Lista->Final->siguiente = Nuevo;
        Nuevo->anterior = Lista->Final;
        Lista->Final = Nuevo;
    }    
    printf("Se registro la carta exitosamente \n");
    Completar_Registro_Carta(recorrido, Nuevo, Lista2, Lista3, juguete, precio);
}

void Agregar_Carta2(Registro_Carta *Lista, Juguete *recorrido, Registro_Ninos *Lista2, Registro_Lugares *Lista3,  int identificacion, char *nombre, int anno, char *juguete, int precio){

    //Se realiza un recorrido a la lista de cartas para validar que ese niño no tenga su carta creada
    Carta_Santa *puntero = Lista->Inicio;
    printf("\n\n");
    while (puntero != NULL)
    {
        if (puntero->ID_Nino == identificacion && puntero->anno == anno)
        {
            printf("Ya este nino tiene una carta registrada para ese anno. Si desea puede editar su carta en el menu de opciones. \n");
            return;
        }
        puntero = puntero->siguiente;
    }

    //Se crea el nuevo ayudante
    Carta_Santa *Nuevo = Crear_Carta(identificacion, nombre, anno);

    //En caso de que la lista este vacia 
    if (Lista->Inicio == NULL)
    {
        Lista->Inicio = Nuevo;
        Lista->Final = Nuevo;
    }

    //En caso de que la lista no este vacia
    else
    {
        Lista->Final->siguiente = Nuevo;
        Nuevo->anterior = Lista->Final;
        Lista->Final = Nuevo;
    }    
    printf("Se registro la carta exitosamente \n");
    Completar_Registro_Carta2(recorrido, Nuevo, Lista2, Lista3, juguete, precio);
}

void Agregar_Juguete_Carta(Registro_Carta *Lista, Juguete *recorrido, Registro_Ninos *Lista2, Registro_Lugares *Lista3, char *juguete, int ID_Nino, char *nombre, int anno, int precio){
    int validacion = 0;

    // Ciclo para recorrer el árbol de juguetes
    while (recorrido != NULL && validacion == 0)
    {

        // En caso de que se encuentre el juguete que coincide con el nombre ingresado
        if (strcmp(recorrido->nombre, juguete) == 0)
            validacion++;
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea mayor al costo del juguete actual
        else if (precio > recorrido->costo) 
            recorrido = recorrido->der; 
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea menor al costo del juguete actual
        else if (precio < recorrido->costo) 
            recorrido = recorrido->izq;
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea igual al costo del juguete actual
        else
            recorrido = recorrido->der; 
    }

    // En caso de que no se haya encontrado ningún juguete que coincida con el nombre ingresado
    if (recorrido == NULL)
    {
        printf("No existe ningun juguete con ese nombre y precio en el catalogo de juguetes. \n");
        return;
    }
    Carta_Santa *puntero = Lista->Inicio;
    int validacion2 = 0;

    // Ciclo para validar que exista una carta registrada para un niño con la identificación ingresada en ese año
    while (puntero != NULL && validacion2 == 0)
    {

        // En caso de que la carta actual esté registrada para el niño en cuestión en ese año
        if (puntero->ID_Nino == ID_Nino && puntero->anno == anno)
            validacion2++;

        // En caso de que la carta actual no esté registrada para el niño en cuestión en ese año
        if (validacion2 == 0)
            puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre ninguna carta registrada para el niño en ese año
    if (validacion2 == 0)
    {
        printf("No fue posible agregar el juguete pues no existe ninguna carta registrada para %s en %i \n", nombre, anno);
        return;
    }

    // En caso de que el niño ya haya agregado al menos 10 juguetes a su carta
    if (puntero->contador_juguetes == 10)
    {
        printf("No fue posible agregar el juguete pues ya la carta de %s ha alcanzado el numero maximo de juguetes permitidos. \n", nombre);
        return;
    }

    // Creación de un nuevo nodo de los juguetes de la carta del niño
    Juguete_Carta *Nuevo = (Juguete_Carta *) malloc(sizeof(Juguete_Carta));
    Nuevo->anterior = NULL;
    Nuevo->siguiente = NULL;
    strcpy(Nuevo->estado, "Solicitado");
    strcpy(Nuevo->juguete, juguete);
    Ninos *puntero2 = Lista2->Inicio;

    // Este procedimiento agrega un nuevo juguete solicitado al lugar en que reside el niño

    //Búsqueda del niño al que se le acaba de crear la carta en la lista de niños
    while (puntero2->ID != puntero->ID_Nino)
        puntero2 = puntero2->siguiente;
    Lugar *puntero3 = Lista3->Inicio;

    // Búsqueda del lugar de residencia del niño al que se le acaba de crear la carta en la lista de lugares
    while (strcmp(puntero2->residencia, puntero3->nombre) != 0)
        puntero3 = puntero3->siguiente;

    // Se suma 1 a la cantidad de juguetes solicitados en el lugar en cuestión
    puntero3->cantidad_juguetes += 1;

    // Si la lista de juguetes de la carta está vacía el nuevo juguete es el primero y último en la lista
    if (puntero->Inicio_Juguetes == NULL)
    {
        puntero->Inicio_Juguetes = Nuevo;
        puntero->Final_Juguetes = Nuevo;
    }

    // Si la lista de juguetes de la carta no está vacía el nuevo juguete es el último en la lista
    else
    {
        puntero->Final_Juguetes->siguiente = Nuevo;
        Nuevo->anterior = puntero->Final_Juguetes;
        puntero->Final_Juguetes = Nuevo;
    }

    // Se suma 1 a la cantidad de juguetes en la carta del niño
    puntero->contador_juguetes += 1;
    printf("Se agrego exitosamente %s a la carta de %s \n", juguete, nombre);
}

void Eliminar_Juguete_Carta(Registro_Carta *Lista, Juguete *recorrido, char *juguete, int ID_Nino, char *nombre, int anno, int precio){
    int validacion = 0;

    // Ciclo para recorrer el árbol de juguetes
    while (recorrido != NULL && validacion == 0)
    {

        // En caso de que se encuentre el juguete que coincide con el nombre ingresado
        if (strcmp(recorrido->nombre, juguete) == 0)
            validacion++;
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea mayor al costo del juguete actual
        else if (precio > recorrido->costo) 
            recorrido = recorrido->der; 
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea menor al costo del juguete actual
        else if (precio < recorrido->costo) 
            recorrido = recorrido->izq;
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea igual al costo del juguete actual
        else
            recorrido = recorrido->der; 
    }

    // En caso de que no se haya encontrado ningún juguete que coincida con el nombre ingresado
    if (recorrido == NULL)
    {
        printf("No existe ningun juguete con ese nombre y precio en el catalogo de juguetes. \n");
        return;
    }
    Carta_Santa *puntero = Lista->Inicio;
    int validacion2 = 0;

    // Ciclo para validar que exista una carta registrada para un niño con la identificación ingresada en ese año
    while (puntero != NULL && validacion2 == 0)
    {

        // En caso de que la carta actual esté registrada para el niño en cuestión en ese año
        if (puntero->ID_Nino == ID_Nino && puntero->anno == anno)
            validacion2++;
        
        // En caso de que la carta actual no esté registrada para el niño en cuestión en ese año
        if (validacion2 == 0)
            puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre ninguna carta registrada para el niño en ese año
    if (validacion2 == 0)
    {
        printf("No fue posible eliminar el juguete pues no existe ninguna carta registrada para %s en %i \n", nombre, anno);
        return;
    }
    Juguete_Carta *puntero2 = puntero->Inicio_Juguetes;

    // Ciclo para encontrar el juguete ingresado en la carta del niño
    while (puntero2 != NULL)
    {

        // En caso de que se encuentre en la carta el juguete (nombre) ingresado
        if (strcmp(puntero2->juguete, juguete) == 0)
        {

                // En caso de que la ruta sea la único en la lista
                if (puntero2 == puntero->Inicio_Juguetes && puntero2->siguiente == NULL)
                {
                    puntero->Inicio_Juguetes = NULL;
                    free(puntero2);
                    return;
                }

                // En caso de que el lugar sea el primero en la lista pero no el único
                else if (puntero2 == puntero->Inicio_Juguetes && puntero2->siguiente != NULL)
                {
                    puntero->Inicio_Juguetes = puntero2->siguiente;
                    puntero2->siguiente->anterior = NULL;
                    free(puntero2);
                    return;
                }
                
                else if(puntero2 == puntero->Final_Juguetes)
                {
                    puntero->Final_Juguetes = puntero2->anterior;
                    puntero2->anterior->siguiente = NULL;
                    free(puntero2);
                    return;
                }

                // En cualquier otro caso
                else
                {
                    puntero2->anterior->siguiente = puntero2->siguiente;
                    puntero2->siguiente->anterior = puntero2->anterior;
                    free(puntero2);
                    return;
                }
            printf("Se ha eliminado %s de la carta de %s exitosamente \n", juguete, nombre);
            return;
        }
        puntero2 = puntero2->siguiente;
    }

    // En caso de que no se encuentre el juguete en la carta del niño
    printf("No fue posible eliminar el juguete pues no se encontro %s dentro de la carta de %s \n", juguete, nombre);
}

void Agregar_a_Deseos(Registro_Carta *Lista, Juguete *recorrido, char *juguete, int ID_Nino, char *nombre, int anno, int precio){
    int validacion = 0;

    // Ciclo para recorrer el árbol de juguetes
    while (recorrido != NULL && validacion == 0)
    {

        // En caso de que se encuentre el juguete que coincide con el nombre ingresado
        if (strcmp(recorrido->nombre, juguete) == 0)
            validacion++;
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea mayor al costo del juguete actual
        else if (precio > recorrido->costo) 
            recorrido = recorrido->der; 
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea menor al costo del juguete actual
        else if (precio < recorrido->costo) 
            recorrido = recorrido->izq;
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea igual al costo del juguete actual
        else
            recorrido = recorrido->der; 
    }

        
    // En caso de que no se haya encontrado ningún juguete que coincida con el nombre ingresado
    if (recorrido == NULL)
    {
        printf("No existe ningun juguete con ese nombre y precio en el catalogo de juguetes. \n");
        return;
    }
    Carta_Santa *puntero = Lista->Inicio;
    int validacion2 = 0;

    // Ciclo para validar que exista una carta registrada para un niño con la identificación ingresada en ese año
    while (puntero != NULL && validacion2 == 0)
    {

        // En caso de que la carta actual esté registrada para el niño en cuestión en ese año
        if (puntero->ID_Nino == ID_Nino && puntero->anno == anno)
            validacion2++;
        
        // En caso de que la carta actual no esté registrada para el niño en cuestión en ese año
        if (validacion2 == 0)
            puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre ninguna carta registrada para el niño en ese año
    if (validacion2 == 0)
    {
        printf("No fue posible agregar el juguete a la lista de deseos pues no existe ninguna carta registrada para %s en %i \n", nombre, anno);
        return;
    }

    // Se crea un nuevo nodo de la lista de deseos del niño
    Deseos *Nuevo = (Deseos *) malloc(sizeof(Deseos));
    Nuevo->anterior = NULL;
    Nuevo->siguiente = NULL;
    strcpy(Nuevo->juguete, juguete);

    // Si la lista de deseos está vacía
    if (puntero->Inicio_Deseos == NULL)
    {
        puntero->Inicio_Deseos = Nuevo;
        puntero->Final_Deseos = Nuevo;
    }

    // Si la lista de deseos no está vacía
    else
    {
        puntero->Final_Deseos->siguiente = Nuevo;
        Nuevo->anterior = puntero->Final_Deseos;
        puntero->Final_Deseos = Nuevo;
    }
    printf("Se agrego exitosamente %s a la lista de deseos de %s \n", juguete, nombre);
}

void Eliminar_De_Deseos(Registro_Carta *Lista, Juguete *recorrido, char *juguete, int ID_Nino, char *nombre, int anno, int precio){
    int validacion = 0;

    // Ciclo para recorrer el árbol de juguetes
    while (recorrido != NULL && validacion == 0)
    {

        // En caso de que se encuentre el juguete que coincide con el nombre ingresado
        if (strcmp(recorrido->nombre, juguete) == 0)
            validacion++;
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea mayor al costo del juguete actual
        else if (precio > recorrido->costo) 
            recorrido = recorrido->der; 
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea menor al costo del juguete actual
        else if (precio < recorrido->costo) 
            recorrido = recorrido->izq;
        
        // En caso de que no se haya encontrado el juguete y el costo ingresado sea igual al costo del juguete actual
        else
            recorrido = recorrido->der; 
    }

    // En caso de que no se haya encontrado ningún juguete que coincida con el nombre ingresado
    if (recorrido == NULL)
    {
        printf("No existe ningun juguete con ese nombre y precio en el catalogo de juguetes. \n");
        return;
    }
    Carta_Santa *puntero = Lista->Inicio;
    int validacion2 = 0;
    // Ciclo para validar que exista una carta registrada para un niño con la identificación ingresada en ese año
    while (puntero != NULL && validacion2 == 0)
    {

        // En caso de que la carta actual esté registrada para el niño en cuestión en ese año
        if (puntero->ID_Nino == ID_Nino && puntero->anno == anno)
            validacion2++;
        
        // En caso de que la carta actual no esté registrada para el niño en cuestión en ese año
        if (validacion2 == 0)
            puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre ninguna carta registrada para el niño en ese año
    if (validacion2 == 0)
    {
        printf("No fue posible agregar el juguete a la lista de deseos pues no existe ninguna carta registrada para %s en %i \n", nombre, anno);
        return;
    }
    Deseos *puntero2 = puntero->Inicio_Deseos;

    // Ciclo para recorrer la lista de deseos buscando un juguete que coincida con el nombre de juguete ingresado
    while (puntero2 != NULL)
    {

        // En caso de que se encuentre en la carta el juguete (nombre) ingresado
        if (strcmp(puntero2->juguete, juguete) == 0)
        {

            // En caso de que la ruta sea la único en la lista
                if (puntero2 == puntero->Inicio_Deseos && puntero2->siguiente == NULL)
                {
                    puntero->Inicio_Deseos = NULL;
                    free(puntero2);
                    return;
                }

                // En caso de que el lugar sea el primero en la lista pero no el único
                else if (puntero2 == puntero->Inicio_Deseos && puntero2->siguiente != NULL)
                {
                    puntero->Inicio_Deseos = puntero2->siguiente;
                    puntero2->siguiente->anterior = NULL;
                    free(puntero2);
                    return;
                }
                
                else if(puntero2 == puntero->Final_Deseos)
                {
                    puntero->Final_Deseos = puntero2->anterior;
                    puntero2->anterior->siguiente = NULL;
                    free(puntero2);
                    return;
                }

                // En cualquier otro caso
                else
                {
                    puntero2->anterior->siguiente = puntero2->siguiente;
                    puntero2->siguiente->anterior = puntero2->anterior;
                    free(puntero2);
                    return;
                }
            printf("Se ha eliminado %s de la lista de deseos de %s exitosamente \n", juguete, nombre);
            return;
        }
        puntero2 = puntero2->siguiente;
    }

    // En caso de que no se encuentre el juguete en la carta del niño
    printf("No fue posible eliminar el juguete pues no se encontro %s dentro de la lista de deseos de %s \n", juguete, nombre);
}

void Consultar_Carta(Registro_Carta *Lista, int ID_Nino, int anno){
    Carta_Santa *puntero = Lista->Inicio;

    // Ciclo para recorrer la lista de cartas 
    while (puntero != NULL)
    {

        // En caso de que la carta actual coincida con la identificación y el año ingresados
        if (puntero->ID_Nino == ID_Nino && puntero->anno == anno)
        {

            //Impresión de la información de la carta
            printf("\n\nCarta a Santa: %s || %i \n\n", puntero->nombre_nino, puntero->anno);
            int i = 1;
            Juguete_Carta *puntero2 = puntero->Inicio_Juguetes;
            printf("Lista de juguetes de la carta: \n");

            // Recorrido por la lista de juguetes de la carta
            while (puntero2 != NULL)
            {

                // Impresión de cada juguete de la carta
                printf("%i. %s \n", i, puntero2->juguete);
                puntero2 = puntero2->siguiente;
                i++;
            }
            int b = 1;
            Deseos *puntero3 = puntero->Inicio_Deseos;
            printf("\nLista de deseos: \n");

            // Recorrido por la lista de deseos
            while (puntero3 != NULL)
            {

                // Impresión de cada juguete de la lista de deseos
                printf("%i. %s \n", b, puntero3->juguete);
                puntero3 = puntero3->siguiente;
                b++;
            }
            return;
        }
        puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre una carta que coincida con la identificación y el año ingresados
    printf("No se encontro ninguna carta del nino en ese anno \n");
}

void De_Deseo_A_Carta(Registro_Carta *Lista, char *juguete, int ID_Nino, int anno){
    Carta_Santa *puntero = Lista->Inicio;

    // Ciclo para recorrer la lista de cartas
    while (puntero != NULL)
    {

        // En caso de que la carta actual coincida con la identificación y el año ingresados
        if (puntero->ID_Nino == ID_Nino && puntero->anno == anno)
        {
            int validacion = 0;
            Deseos *puntero2 = puntero->Inicio_Deseos;

            // Lista para recorrer cada juguete de la lista de deseos
            while (puntero2 != NULL && validacion == 0)
            {
                if (strcmp(puntero2->juguete, juguete) == 0)
                    validacion++;
                if(validacion == 0)
                    puntero2 = puntero2->siguiente;
            }

            // En caso de que no se encuentre el juguete dentro de la lista de deseos
            if (validacion == 0)
            {
                printf("No fue posible pasar el juguete a la carta pues no se encuentra dentro de la lista de deseos \n");
                return;
            }

            // En caso de que el niño ya tenga 10 juguetes en su carta
            if (puntero->contador_juguetes == 10)
            {
                printf("No fue posible pasar el juguete a la carta pues ya el nino ha alcanzado el numero maximo de juguetes en su carta \n");
                return;
            }
            char copia[30];
            strcpy(copia, puntero2->juguete);

            // En caso de que el juguete sea el único en la lista de deseos
            if (puntero2 == puntero->Inicio_Deseos && puntero2->siguiente == NULL)
            {
                puntero->Inicio_Deseos = NULL;
                free(puntero2);
            }

            // En caso de que el juguete sea el primero en la lista de deseos pero no el único
            else if (puntero2 == puntero->Inicio_Deseos && puntero2->siguiente != NULL)
            {
                puntero->Inicio_Deseos = puntero2->siguiente;
                puntero2->siguiente->anterior = NULL;
                free(puntero2);
            }

            // En cualquier otro caso
            else
            {
                puntero2->anterior->siguiente = puntero2->siguiente;
                puntero2->siguiente->anterior = puntero2->anterior;
                free(puntero2);
            }

            // Creación de un nuevo juguete de la carta
            Juguete_Carta *Nuevo = (Juguete_Carta *) malloc(sizeof(Juguete_Carta));
            Nuevo->anterior = NULL;
            Nuevo->siguiente = NULL;
            strcpy(Nuevo->estado, "Solicitado");
            strcpy(Nuevo->juguete, copia);

            // En caso de que la carta no tenga juguetes agregados
            if (puntero->Inicio_Juguetes == NULL)
            {
                puntero->Inicio_Juguetes = Nuevo;
                puntero->Final_Juguetes = Nuevo;
            }

            // En caso de que ya hayan juguetes en la carta
            else
            {
                puntero->Final_Juguetes->siguiente = Nuevo;
                Nuevo->anterior = puntero->Final_Juguetes;
                puntero->Final_Juguetes = Nuevo;
            }
            puntero->contador_juguetes += 1;
            printf("Se elimino %s de la lista de deseos y se agrego a la carta de %s \n", copia, puntero->nombre_nino);
            return;
        }
        puntero = puntero->siguiente;
    }
    printf("No fue posible pasar el juguete a la carta pues no hay ninguna carta registrada para ese nino en ese anno \n");
}

void Procesar_Carta(Registro_Carta *Lista, Registro_Ninos *Lista2, Registro_Ayudantes *Lista3, int anno){
    Carta_Santa *puntero = Lista->Inicio;
    int validacion = 0;
    int contador = 1;

    // Ciclo para recorrer la lista de cartas
    while (puntero != NULL)
    {

        // En caso de que la carta sea del año indicado por el usuario se imprimen los datos del niño
        if (puntero->anno == anno)
        {
            validacion++;
            printf("%i. Nombre: %s || Identificacion: %i \n", contador, puntero->nombre_nino, puntero->ID_Nino);
            contador++;
        }
        puntero = puntero->siguiente; 
    }

    // En caso de que no se haya registrado ninguna carta en el año indicado por el usuario
    if (validacion == 0)
    {
        printf("Lo sentimos: ningun nino registro una carta para ese anno \n");
        return;
    }

    // Se solicita la identificación del niño al que se procesará la carta
    int decision_usuario;
    printf("Ingrese la identificacion del nino al que desea procesarle la carta: \n");
    scanf("%i", &decision_usuario);

    // Se solicita la identificación del ayudante que procesará la carta
    int ayudante;
    printf("Ingrese la identificacion del ayudante que procesa la carta: \n");
    scanf("%i", &ayudante);
    Ayudante *buscar = Lista3->Inicio;
    int comprobar = 0;

    // Ciclo para validar que exista un ayudante con la identificación ingresada
    while (buscar != NULL)
    {
        if (buscar->ID == ayudante)
        {
            buscar->cantidad_procesadas += 1;
            comprobar++;
        }
        buscar = buscar->siguiente;
    }

    // En caso de que no exista un ayudante con la identificación ingresada
    if (comprobar == 0)
    {
        printf("Lo sentimos: No hay ningun ayudante registrado con esa identificacion, por lo tanto no se pudo procesar la carta. \n");
        return;
    }
    int validacion2 = 0;
    Carta_Santa *puntero2 = Lista->Inicio;

    // Ciclo para encontrar la carta del niño
    while (puntero2 != NULL && validacion2 == 0)
    {

        // En caso de que se encuentre la carta del niño
        if (puntero2->ID_Nino == decision_usuario)
        {
            Ninos *puntero3 = Lista2->Inicio;
            int validacion3 = 0;

            // Ciclo para recorrer la lista de niños y validar que el niño no tenga más de seis comportamientos malos
            while (puntero3 != NULL == validacion3 == 0)
            {

                // Cuando se encuentre al niño
                if (puntero3->ID == decision_usuario)
                {

                    // En caso de que el niño no tenga más de seis comportamientos malos
                    if (puntero3->comportamientos_malos > 6)
                    {

                        // Se rechaza la carta
                        strcpy(puntero2->estado, "Rechazada");
                        Juguete_Carta *puntero4 = puntero2->Inicio_Juguetes;

                        // Ciclo para dejar cada juguete del niño rechazado
                        while (puntero4 != NULL)
                        {
                            puntero4->ayudante = ayudante;
                            puntero4->anno = anno;
                            puntero4->nino = decision_usuario;
                            strcpy(puntero4->estado, "Rechazado");
                            puntero4 = puntero4->siguiente;
                        }
                        printf("Se ha procesado la carta y se ha encontrado que el nino cuenta con mas de 6 comportamientos malos. Por lo tanto el nino no recibira regalos y se enviara un correo a los padre indicando la situacion \n");
                        validacion2++;
                    }
                    validacion3++;
                }

                // En caso de que no se haya encontrado aún al niño
                if (validacion3 == 0)
                    puntero3 = puntero3->siguiente;
            }

            // En caso de que el niño NO tenga más de seis malos comportamientos
            if (validacion2 == 0)
            {

                // Se aprueba la carta
                strcpy(puntero2->estado, "Aprobada");
                Juguete_Carta *puntero5 = puntero2->Inicio_Juguetes;

                // Ciclo para aprobar cada juguete de la carta del niño
                while (puntero5 != NULL)
                {
                    puntero5->ayudante = ayudante;
                    puntero5->anno = anno;
                    puntero5->nino = decision_usuario;
                    strcpy(puntero5->estado, "Listo para entregar");
                    puntero2->contador_juguetes_a_entregar += 1;
                    puntero5 = puntero5->siguiente;
                }
                validacion2++;
                printf("Se ha procesado la carta de %s exitosamente \n", puntero2->nombre_nino);
            }  
        }
        puntero2 = puntero2->siguiente;
    }
    if (validacion2 == 0)
        printf("Lo sentimos: el numero ingresado no corresponde a la identificacion de ningun nino registrado \n");
}

void Procesar_Carta2(Registro_Carta *Lista, Registro_Ninos *Lista2, Registro_Ayudantes *Lista3, int anno, int ID_Nino, int ayudante){
    Carta_Santa *puntero = Lista->Inicio;
    int validacion = 0;

    // Ciclo para recorrer la lista de cartas
    while (puntero != NULL)
    {

        // En caso de que la carta sea del año indicado por el usuario se imprimen los datos del niño
        if (puntero->anno == anno)
            validacion++;
        puntero = puntero->siguiente; 
    }

    // En caso de que no se haya registrado ninguna carta en el año indicado por el usuario
    if (validacion == 0)
    {
        printf("Lo sentimos: ningun nino registro una carta para ese anno \n");
        return;
    }

    Ayudante *buscar = Lista3->Inicio;
    int comprobar = 0;

    // Ciclo para validar que exista un ayudante con la identificación ingresada
    while (buscar != NULL)
    {
        if (buscar->ID == ayudante)
        {
            buscar->cantidad_procesadas += 1;
            comprobar++;
        }
        buscar = buscar->siguiente;
    }

    // En caso de que no exista un ayudante con la identificación ingresada
    if (comprobar == 0)
    {
        printf("Lo sentimos: No hay ningun ayudante registrado con esa identificacion, por lo tanto no se pudo procesar la carta. \n");
        return;
    }
    int validacion2 = 0;
    Carta_Santa *puntero2 = Lista->Inicio;

    // Ciclo para encontrar la carta del niño
    while (puntero2 != NULL && validacion2 == 0)
    {

        // En caso de que se encuentre la carta del niño
        if (puntero2->ID_Nino == ID_Nino)
        {
            Ninos *puntero3 = Lista2->Inicio;
            int validacion3 = 0;

            // Ciclo para recorrer la lista de niños y validar que el niño no tenga más de seis comportamientos malos
            while (puntero3 != NULL == validacion3 == 0)
            {

                // Cuando se encuentre al niño
                if (puntero3->ID == ID_Nino)
                {

                    // En caso de que el niño no tenga más de seis comportamientos malos
                    if (puntero3->comportamientos_malos > 6)
                    {

                        // Se rechaza la carta
                        strcpy(puntero2->estado, "Rechazada");
                        Juguete_Carta *puntero4 = puntero2->Inicio_Juguetes;

                        // Ciclo para dejar cada juguete del niño rechazado
                        while (puntero4 != NULL)
                        {
                            puntero4->ayudante = ayudante;
                            puntero4->anno = anno;
                            puntero4->nino = ID_Nino;
                            strcpy(puntero4->estado, "Rechazado");
                            puntero4 = puntero4->siguiente;
                        }
                        printf("Se ha procesado la carta y se ha encontrado que el nino cuenta con mas de 6 comportamientos malos. Por lo tanto el nino no recibira regalos y se enviara un correo a los padre indicando la situacion \n");
                        validacion2++;
                    }
                    validacion3++;
                }

                // En caso de que no se haya encontrado aún al niño
                if (validacion3 == 0)
                    puntero3 = puntero3->siguiente;
            }

            // En caso de que el niño NO tenga más de seis malos comportamientos
            if (validacion2 == 0)
            {

                // Se aprueba la carta
                strcpy(puntero2->estado, "Aprobada");
                Juguete_Carta *puntero5 = puntero2->Inicio_Juguetes;

                // Ciclo para aprobar cada juguete de la carta del niño
                while (puntero5 != NULL)
                {
                    puntero5->ayudante = ayudante;
                    puntero5->anno = anno;
                    puntero5->nino = ID_Nino;
                    strcpy(puntero5->estado, "Listo para entregar");
                    puntero2->contador_juguetes_a_entregar += 1;
                    puntero5 = puntero5->siguiente;
                }
                validacion2++;
                printf("Se ha procesado la carta de %s exitosamente \n", puntero2->nombre_nino);
            }  
        }
        puntero2 = puntero2->siguiente;
    }
    if (validacion2 == 0)
        printf("Lo sentimos: el numero ingresado no corresponde a la identificacion de ningun nino registrado \n");
}

void Entregar_Juguetes(Registro_Lugares *Lista, Registro_Ninos *Lista2, Registro_Carta *Lista3, int decision){

    // En caso de que la entrega se haga para todo tipo de rutas
    if (decision == 1){
        Lugar *puntero = Lista->Inicio->siguiente;
        int contador_lugares = 0;

        // Ciclo para recorrer todos los lugares y validar en cuantos lugares vive al menos un niño con carta aprobada
        // Se llamará lugar en cuestión a cada uno de los lugares de la lista 
        while (puntero != NULL)
        {
            Carta_Santa *puntero2 = Lista3->Inicio;

            // Ciclo para recorrer cada carta para encontrar un niño con carta aprobada que viva en el lugar en cuestión
            while (puntero2 != NULL && puntero->ninos == 0)
            {

                // En caso de que la carta tenga al menos un juguete por entregar
                if (puntero2->contador_juguetes_a_entregar > 0)
                {
                    Ninos *puntero3 = Lista2->Inicio;

                    // Ciclo para recorrer la lista de niños y validar si el niño de la carta vive en lugar en cuestión
                    while (puntero3 != NULL && puntero->ninos == 0)
                    {

                        // En caso de que se encuentre el niño de la carta y viva en el lugar en cuestión
                        if (puntero3->ID == puntero2->ID_Nino && strcmp(puntero3->residencia, puntero->nombre) == 0)
                        {
                            puntero->ninos += 1;
                            contador_lugares++;
                        }
                        puntero3 = puntero3->siguiente;
                    }
                }
                puntero2 = puntero2->siguiente;
            }
            puntero = puntero->siguiente;
        }
        int contador = 0;
        Lugar *puntero4;

        // Este ciclo se repetirá mientras aún hayan lugares con juguetes por entregar
        while (contador < contador_lugares)
        {

            // En caso de que se trate de el primer lugar (lugar de salida) se marca como permanente
            if (contador == 0){
                puntero4 = Lista->Inicio;
                puntero4->visitado_o_permanente += 2;
            }
            Ruta *puntero5 = puntero4->Inicio;

            //  Ciclo para visitar cada nodo adyacente y ver si se puede acortar el camino
            while (puntero5 != NULL)
            {
                Lugar *buscar = Lista->Inicio;

                // Buscar en la lista de lugares el destino
                while (strcmp(buscar->nombre, puntero5->destino->nombre) != 0)
                    buscar = buscar->siguiente;

                Lugar *buscar2 = Lista->Inicio;

                // Buscar en la lista de lugares el origen
                while (strcmp(buscar2->nombre, puntero5->origen->nombre) != 0)
                    buscar2 = buscar2->siguiente;

                // En caso de que el nodo adyacente no haya sido visitado o el camino sea más corto, y el nodo adyacente no tenga etiqueta permanente y tenga al menos un niño con carta aprobada
                if ((buscar->visitado_o_permanente == 0 || buscar->distancia_acumulada > buscar2->distancia_acumulada + puntero5->minutos) && buscar->ninos > 0 && buscar->visitado_o_permanente != 2)
                {

                    // El origen se convierte en el nuevo antecesor del nodo adyacente
                    buscar->antecesor = buscar2;

                    // La nueva distancia acumulada es la distancia acumulada del antecesor más la duración de la ruta 
                    // Se marca el nodo como visitado en caso de que no se haya visitado antes
                    buscar->distancia_acumulada = buscar2->distancia_acumulada + puntero5->minutos;
                    if (buscar->visitado_o_permanente == 0)
                        buscar->visitado_o_permanente += 1;
                }
                puntero5 = puntero5->siguiente;                
            }
            Lugar *puntero6 = Lista->Inicio->siguiente;
            Lugar *menor;
            int validacion = 0;

            // Ciclo para recorrer la lista de lugares y buscar el nodo visitado de menor distancia acumulada
            while (puntero6 != NULL)
            {

                // En caso de que se trate del primer lugar evaluado y sea un nodo visitado se convierte en el menor
                if (validacion == 0 && puntero6->visitado_o_permanente == 1)
                {
                    menor = puntero6;
                    validacion++;
                }

                // En caso de que ya se haya evaluado al menos un lugar
                else
                {

                    // En caso de que la distancia acumulada sea menor a la del menor y que se tarte de un nodo visitado
                    if (puntero6->distancia_acumulada < menor->distancia_acumulada && puntero6->visitado_o_permanente == 1)
                        menor = puntero6;
                }
                puntero6 = puntero6->siguiente;
            }
            Lugar *buscar3 = Lista->Inicio;

            // Ciclo para buscar el nodo menor en la lista de lugares
            while (strcmp(buscar3->nombre, menor->nombre) != 0)
                buscar3 = buscar3->siguiente;

            // Se marca al nodo menor como permanente y se asigna puntero4 para visitar sus adyacentes
            puntero4 = buscar3;
            buscar3->visitado_o_permanente++;

            int contador2 = 1;
            printf("\n\nViaje desde %s hasta %s \nEntregando regalos a los siguientes ninos: \n", buscar3->antecesor->nombre, buscar3->nombre);
            Ninos *puntero7 = Lista2->Inicio;

            // Ciclo para imprimir los nombres de los niños a los que se les entregará regalos en dicho lugar
            while (puntero7 != NULL)
            {

                // En caso de que se encuentre un niño que viva en dicho lugar se imprimen sus datos
                if (strcmp(puntero7->residencia, buscar3->nombre) == 0)
                {
                    printf("%i. %s \n", contador2, puntero7->nombre);
                    contador2++;
                }
                puntero7 = puntero7->siguiente;
            }
            contador++;
        }
    }

    // En caso de que la entrega se haga para solo un tipo de rutas
    if (decision == 2)
    {

        // Se solicita el tipo de ruta al que se entregarán regalos
        char tipo_ruta[10];
        printf("Ingrese el tipo de ruta a la que desea entregar los juguetes: \n");
        scanf("%s", &tipo_ruta);

        // En caso de que no se trate de una ruta aérea, marítima o terrestre
        if (strcmp(tipo_ruta, "Maritima") != 0 && strcmp(tipo_ruta, "maritima") != 0 && strcmp(tipo_ruta, "Marítima") != 0 && strcmp(tipo_ruta, "marítima") != 0 && strcmp(tipo_ruta, "Aerea") != 0 && strcmp(tipo_ruta, "aerea") != 0 && strcmp(tipo_ruta, "Aérea") != 0 && strcmp(tipo_ruta, "aérea") != 0 && strcmp(tipo_ruta, "Terrestre") != 0 && strcmp(tipo_ruta, "terrestre") != 0){
            printf("Solo se puede hacer entregas para las siguientes rutas: aerea, terrestre o maritima \n\n");
            return;
        }

        Lugar *puntero = Lista->Inicio->siguiente;
        int contador_lugares = 0;

        // Ciclo para recorrer todos los lugares y validar en cuantos lugares vive al menos un niño con carta aprobada
        // Se llamará lugar en cuestión a cada uno de los lugares de la lista
        while (puntero != NULL)
        {
            Carta_Santa *puntero2 = Lista3->Inicio;

            // Ciclo para recorrer cada carta para encontrar un niño con carta aprobada que viva en el lugar en cuestión
            while (puntero2 != NULL && puntero->ninos == 0)
            {

                // En caso de que la carta tenga al menos un juguete por entregar
                if (puntero2->contador_juguetes_a_entregar != 0)
                {
                    Ninos *puntero3 = Lista2->Inicio;

                    // Ciclo para recorrer la lista de niños y validar si el niño de la carta vive en lugar en cuestión
                    while (puntero3 != NULL && puntero->ninos == 0)
                    {

                        // En caso de que se encuentre el niño de la carta y viva en el lugar en cuestión
                        if (puntero3->ID == puntero2->ID_Nino && strcmp(puntero3->residencia, puntero->nombre) == 0)
                        {
                            Lugar *validar = Lista->Inicio;
                            int val = 0;

                            // Ciclo para validar que el lugar sea de la ruta especificada
                            while (validar != NULL && val == 0)
                            {
                                Ruta *validar2 = validar->Inicio;

                                // Ciclo para recorrer las rutas para validar que el lugar sea de la ruta especificada
                                while (validar2 != NULL && val == 0)
                                {

                                    // En los casos de que el lugar esté conectado por la ruta especificada
                                    if (strcmp(puntero->nombre, validar2->destino->nombre) == 0 && strcmp(validar2->tipo, tipo_ruta) == 0)
                                    {
                                        val++;
                                        puntero->ninos += 1;
                                        contador_lugares++;
                                    }
                                    validar2 = validar2->siguiente;
                                }
                                validar = validar->siguiente;
                            }
                        }
                        puntero3 = puntero3->siguiente;
                    }
                }
                puntero2 = puntero2->siguiente;
            }
            puntero = puntero->siguiente;
        }
        int contador = 0;
        Lugar *puntero4;

        // Este ciclo se repetirá mientras aún hayan lugares con juguetes por entregar
        while (contador < contador_lugares)
        {

            // En caso de que se trate de el primer lugar (lugar de salida) se marca como permanente
            if (contador == 0){
                puntero4 = Lista->Inicio;
                puntero4->visitado_o_permanente += 2;
            }
            Ruta *puntero5 = puntero4->Inicio;

            //  Ciclo para visitar cada nodo adyacente y ver si se puede acortar el camino
            while (puntero5 != NULL)
            {
                Lugar *buscar = Lista->Inicio;

                // Buscar en la lista de lugares el destino
                while (strcmp(buscar->nombre, puntero5->destino->nombre) != 0)
                    buscar = buscar->siguiente;

                Lugar *buscar2 = Lista->Inicio;

                // Buscar en la lista de lugares el origen
                while (strcmp(buscar2->nombre, puntero5->origen->nombre) != 0)
                    buscar2 = buscar2->siguiente;

                // En caso de que el nodo adyacente no haya sido visitado o el camino sea más corto, y el nodo adyacente no tenga etiqueta permanente y tenga al menos un niño con carta aprobada
                if ((buscar->visitado_o_permanente == 0 || buscar->distancia_acumulada > buscar2->distancia_acumulada + puntero5->distancia) && buscar->ninos > 0 && buscar->visitado_o_permanente != 2 && strcmp(puntero5->tipo, tipo_ruta) == 0)
                {

                    // El origen se convierte en el nuevo antecesor del nodo adyacente
                    buscar->antecesor = buscar2;

                    // La nueva distancia acumulada es la distancia acumulada del antecesor más la duración de la ruta 
                    // Se marca el nodo como visitado en caso de que no se haya visitado antes
                    buscar->distancia_acumulada = buscar2->distancia_acumulada + puntero5->distancia;
                    if (buscar->visitado_o_permanente == 0)
                        buscar->visitado_o_permanente += 1;
                }
                puntero5 = puntero5->siguiente;                
            }
            Lugar *puntero6 = Lista->Inicio->siguiente;
            Lugar *menor;
            int validacion = 0;

            // Ciclo para recorrer la lista de lugares y buscar el nodo visitado de menor distancia acumulada
            while (puntero6 != NULL)
            {

                // En caso de que se trate del primer lugar evaluado y sea un nodo visitado se convierte en el menor
                if (validacion == 0 && puntero6->visitado_o_permanente == 1)
                {
                    menor = puntero6;
                    validacion++;
                }

                // En caso de que ya se haya evaluado al menos un lugar
                else
                {

                    // En caso de que la distancia acumulada sea menor a la del menor y que se tarte de un nodo visitado
                    if (puntero6->distancia_acumulada < menor->distancia_acumulada && puntero6->visitado_o_permanente == 1)
                        menor = puntero6;
                }
                puntero6 = puntero6->siguiente;
            }
            Lugar *buscar3 = Lista->Inicio;

            // Ciclo para buscar el nodo menor en la lista de lugares
            while (strcmp(buscar3->nombre, menor->nombre) != 0)
                buscar3 = buscar3->siguiente;

            // Se marca al nodo menor como permanente y se asigna puntero4 para visitar sus adyacentes
            puntero4 = buscar3;
            buscar3->visitado_o_permanente++;

            int contador2 = 1;
            printf("\n\nViaje desde %s hasta %s \nEntregando regalos a los siguientes ninos: \n", buscar3->antecesor->nombre, buscar3->nombre);
            Ninos *puntero7 = Lista2->Inicio;

            // Ciclo para imprimir los nombres de los niños a los que se les entregará regalos en dicho lugar
            while (puntero7 != NULL)
            {

                // En caso de que se encuentre un niño que viva en dicho lugar se imprimen sus datos
                if (strcmp(puntero7->residencia, buscar3->nombre) == 0)
                {
                    printf("%i. %s \n", contador2, puntero7->nombre);
                    contador2++;
                }
                puntero7 = puntero7->siguiente;
            }
            contador++;
        }
    }
}

Carta_Santa *Crear_Carta(int identificacion, char *nombre, int anno);
void Completar_Registro_Carta(Juguete *recorrido, Carta_Santa *puntero, Registro_Ninos *Lista, Registro_Lugares *Lista2,  char *juguete, int precio);
void Completar_Registro_Carta2(Juguete *recorrido, Carta_Santa *puntero, Registro_Ninos *Lista, Registro_Lugares *Lista2,  char *juguete, int precio);
void Agregar_Carta(Registro_Carta *Lista, Juguete *recorrido, Registro_Ninos *Lista2, Registro_Lugares *Lista3,  int identificacion, char *nombre, int anno, char *juguete, int precio);
void Agregar_Carta2(Registro_Carta *Lista, Juguete *recorrido, Registro_Ninos *Lista2, Registro_Lugares *Lista3,  int identificacion, char *nombre, int anno, char *juguete, int precio);
void Agregar_Juguete_Carta(Registro_Carta *Lista, Juguete *recorrido, Registro_Ninos *Lista2, Registro_Lugares *Lista3, char *juguete, int ID_Nino, char *nombre, int anno, int precio);
void Eliminar_Juguete_Carta(Registro_Carta *Lista, Juguete *recorrido, char *juguete, int ID_Nino, char *nombre, int anno, int precio);
void Agregar_a_Deseos(Registro_Carta *Lista, Juguete *recorrido, char *juguete, int ID_Nino, char *nombre, int anno, int precio);
void Eliminar_De_Deseos(Registro_Carta *Lista, Juguete *recorrido, char *juguete, int ID_Nino, char *nombre, int anno, int precio);
void Consultar_Carta(Registro_Carta *Lista, int ID_Nino, int anno);
void De_Deseo_A_Carta(Registro_Carta *Lista, char *juguete, int ID_Nino, int anno);
void Procesar_Carta(Registro_Carta *Lista, Registro_Ninos *Lista2, Registro_Ayudantes *Lista3, int anno);
void Entregar_Juguetes(Registro_Lugares *Lista, Registro_Ninos *Lista2, Registro_Carta *Lista3, int decision);

void Cantidad_Juguetes_Anno(Registro_Annos *Lista, Registro_Carta *Lista2){
    Carta_Santa *puntero = Lista2->Inicio;

    // Recorrido de todas las cartas 
    while (puntero != NULL)
    {
        int validacion2 = 0;
        Anno *puntero2;

        // Recorrido por la lista de años para validar si ya el año se encuentra en la lista o no
        for (puntero2 = Lista->Inicio; puntero2 != NULL; puntero2 = puntero2->siguiente)
        {

            // En caso de que el año ya esté en la lista, se suma la cantidad de juguetes de la carta a la cantidad de juguetes solicitados ese año
            if (puntero->anno == puntero2->anno)
            {
                puntero2->cantidad_juguetes += puntero->contador_juguetes;
                validacion2++;
            }
        }

        // En caso de que el año no se encuentre en la lista de años
        if (validacion2 == 0)
        {

            // Se crea el nuevo año
            Anno *NuevoAnno = (Anno *) malloc(sizeof(Anno));
            NuevoAnno->siguiente = NULL;
            NuevoAnno->anno = puntero->anno;
            NuevoAnno->cantidad_juguetes = puntero->contador_juguetes;
            NuevoAnno->cantidad_cartas_aprobadas = 0;
            NuevoAnno->cantidad_cartas_rechazadas = 0;
            
            // En caso de que la lista esté vacía
            if (Lista->Inicio == NULL)
            {
                Lista->Inicio = NuevoAnno;
                Lista->Final = Lista->Inicio;
            }

            // En caso de que la lista no esté vacía
            else
            {
                Anno *puntero3 = Lista->Inicio;
                Anno *anterior = NULL;
                int validacion = 0;

                // Se recorre la lista de años para insertar los años en orden
                while (puntero3 != NULL && validacion == 0)
                {

                    // En caso de que sea menor al año del puntero actual
                    if (NuevoAnno->anno < puntero3->anno)
                    {
                        NuevoAnno->siguiente = puntero3;

                        // En caso de se inserte al inicio de la lista
                        if (anterior == NULL)
                        {
                            Lista->Inicio = NuevoAnno;
                        }

                        // En caso de NO se inserte al inicio de la lista
                        if(anterior != NULL)
                            anterior->siguiente = NuevoAnno;
                        validacion++;
                    }

                    // En caso de que ya se trate del último puntero de la lista (el año es mayor a todos los de la lista)
                    else if (puntero3->siguiente == NULL && validacion != 1)
                    {
                        puntero3->siguiente = NuevoAnno;
                        Lista->Final = NuevoAnno;
                        validacion = 1;
                    }
                    anterior = puntero3;
                    puntero3 = puntero3->siguiente;
                }
            }
        }
        puntero = puntero->siguiente;
    }
    Anno *puntero4 = Lista->Inicio;
    printf("\n\nCantidad de juguetes solicitados por anno: \n\n");
    int contador = 1;

    // Ciclo para imprimir cada año y la cantidad de juguetes solicitados ese año
    while (puntero4 != NULL)
    {
        printf("%i. Anno: %i \nCantidad de juguetes solicitados: %i \n", contador, puntero4->anno, puntero4->cantidad_juguetes);
        contador++;
        puntero4 = puntero4->siguiente;
    }
}

void ordenar_lugares(Juguete_Lugar *inicio) 
{ 
    int cambio, i; 
    Juguete_Lugar *ptr1; 
    Juguete_Lugar *lptr = NULL; 
  
    // En caso de que no hayan elementos en la lista
    if (inicio == NULL) 
        return; 
  
    // En caso de que hayan elementos en la lista
    do
    { 
        cambio = 0; 
        ptr1 = inicio; 

        // Recorrido de la la lista
        while (ptr1->siguiente != lptr) 
        { 
            // En caso de que un contador sea mayor a otro se intercambian datos
            if (ptr1->cantidad_juguetes > ptr1->siguiente->cantidad_juguetes) 
            {  
                int temp = ptr1->cantidad_juguetes;
                ptr1->cantidad_juguetes = ptr1->siguiente->cantidad_juguetes;
                ptr1->siguiente->cantidad_juguetes = temp;
                char nombre[20];
                strcpy(nombre, ptr1->nombre);
                strcpy(ptr1->nombre, ptr1->siguiente->nombre);
                strcpy(ptr1->siguiente->nombre, nombre);
                cambio = 1; 
            } 
            ptr1 = ptr1->siguiente; 
        } 
        lptr = ptr1; 
    } 
    while (cambio); 
} 

void Cantidad_Juguetes_Lugar(Registro_Lugares *Lista){

    // Se crea la lista donde se guardarán los lugares según su cantidad de juguetes
    Registro_Lugares_Juguetes *Lista_Lugares_Juguetes = (Registro_Lugares_Juguetes *)malloc(sizeof(Registro_Lugares_Juguetes));
    Lista_Lugares_Juguetes->Inicio = NULL;
    Lista_Lugares_Juguetes->Final = NULL;
    Lugar *puntero = Lista->Inicio;

    // Recorrido a cada lugar para insertarlo en la nueva cita
    while (puntero != NULL)
    {

        // Se realiza una copia con los datos del lugar
        Juguete_Lugar *copia = (Juguete_Lugar *) malloc(sizeof(Juguete_Lugar));
        copia->siguiente = NULL;
        copia->cantidad_juguetes = puntero->cantidad_juguetes;
        strcpy(copia->nombre, puntero->nombre);

        // En caso de que la lista esté vacía
        if (Lista_Lugares_Juguetes->Inicio == NULL)
        {
        Lista_Lugares_Juguetes->Inicio = copia;
        Lista_Lugares_Juguetes->Final = copia;
        }

        // En caso de que la lista NO esté vacía
        else
        {
            Lista_Lugares_Juguetes->Final->siguiente = copia;
            Lista_Lugares_Juguetes->Final = copia;
        }
        puntero = puntero->siguiente;
    }
    
    // Se ordena la lista
    ordenar_lugares(Lista_Lugares_Juguetes->Inicio);
    int contador = 0;

    //Impresión del lugar con más juguetes solicitados y lugar con menos juguetes solicitados
    printf("\n\nLugar con mas juguetes solicitados: %s con %i \n", Lista_Lugares_Juguetes->Final->nombre, Lista_Lugares_Juguetes->Final->cantidad_juguetes);
    printf("Lugar con menos juguetes solicitados: %s con %i \n", Lista_Lugares_Juguetes->Inicio->nombre, Lista_Lugares_Juguetes->Inicio->cantidad_juguetes);
}

void Cantidad_Cartas_Aprobadas(Registro_Annos *Lista, Registro_Carta *Lista2){
    Carta_Santa *puntero = Lista2->Inicio;

    // Recorrido de todas las cartas 
    while (puntero != NULL)
    {
        int validacion2 = 0;
        Anno *puntero2;

        // Recorrido por la lista de años para validar si ya el año se encuentra en la lista o no
        for (puntero2 = Lista->Inicio; puntero2 != NULL; puntero2 = puntero2->siguiente)
        {

            // En caso de que el año ya esté en la lista
            if (puntero->anno == puntero2->anno)
            {

                // En caso de que la carta esté aprobada
                if (strcmp(puntero->estado, "Aprobada") == 0)
                    puntero2->cantidad_cartas_aprobadas += 1;
                validacion2++;
            }
        }

        // En caso de que el año no se encuentre en la lista de años
        if (validacion2 == 0)
        {

            // Se crea el nuevo año
            Anno *NuevoAnno = (Anno *) malloc(sizeof(Anno));
            NuevoAnno->siguiente = NULL;
            NuevoAnno->anno = puntero->anno;
            NuevoAnno->cantidad_cartas_rechazadas = 0;
            NuevoAnno->cantidad_juguetes = 0;

            // En caso de que la carta esté aprobada
            if (strcmp(puntero->estado, "Aprobada") == 0)
                NuevoAnno->cantidad_cartas_aprobadas = 1;

            //  En caso de que la carta NO esté aprobada 
            else
                NuevoAnno->cantidad_cartas_aprobadas = 0;

            // En caso de que la lista esté vacía
            if (Lista->Inicio == NULL)
            {
                Lista->Inicio = NuevoAnno;
                Lista->Final = Lista->Inicio;
            }

            // En caso de que la lista NO esté vacía
            else
            {
                Anno *puntero3 = Lista->Inicio;
                Anno *anterior = NULL;
                int validacion = 0;

                // Se recorre la lista de años para insertar los años en orden
                while (puntero3 != NULL && validacion == 0)
                {

                    // En caso de que sea menor al año del puntero actual
                    if (NuevoAnno->anno < puntero3->anno)
                    {
                        NuevoAnno->siguiente = puntero3;

                        // En caso de se inserte al inicio de la lista
                        if (anterior == NULL)
                        {
                            Lista->Inicio = NuevoAnno;
                        }

                        // En caso de NO se inserte al inicio de la lista
                        if(anterior != NULL)
                            anterior->siguiente = NuevoAnno;
                        validacion++;
                    }

                    // En caso de que ya se trate del último puntero de la lista (el año es mayor a todos los de la lista)
                    else if (puntero3->siguiente == NULL && validacion != 1)
                    {
                        puntero3->siguiente = NuevoAnno;
                        Lista->Final = NuevoAnno;
                        validacion = 1;
                    }
                    anterior = puntero3;
                    puntero3 = puntero3->siguiente;
                }
            }
        }
        puntero = puntero->siguiente;
    }
    Anno *puntero4 = Lista->Inicio;
    printf("\n\nCantidad de cartas aprobadas por anno: \n\n");
    int contador = 1;

    // Impresion de la cantidad de cartas aprobadas por año
    while (puntero4 != NULL)
    {
        printf("%i. Anno: %i \nCantidad de cartas aprobadas: %i \n", contador, puntero4->anno, puntero4->cantidad_cartas_aprobadas);
        contador++;
        puntero4 = puntero4->siguiente;
    }
}

void Cantidad_Cartas_Rechazadas(Registro_Annos *Lista, Registro_Carta *Lista2){
    Carta_Santa *puntero = Lista2->Inicio;

    // Recorrido de todas las cartas 
    while (puntero != NULL)
    {
        int validacion2 = 0;
        Anno *puntero2;

        // Recorrido por la lista de años para validar si ya el año se encuentra en la lista o no
        for (puntero2 = Lista->Inicio; puntero2 != NULL; puntero2 = puntero2->siguiente)
        {

            // En caso de que el año ya esté en la lista
            if (puntero->anno == puntero2->anno)
            {

                // En caso de que la carta esté rechazada
                if (strcmp(puntero->estado, "Rechazada") == 0)
                    puntero2->cantidad_cartas_rechazadas += 1;    
                validacion2++;
            }
        }

        // En caso de que el año no se encuentre en la lista de años
        if (validacion2 == 0)
        {

            // Se crea el nuevo año
            Anno *NuevoAnno = (Anno *) malloc(sizeof(Anno));
            NuevoAnno->siguiente = NULL;
            NuevoAnno->anno = puntero->anno;
            NuevoAnno->cantidad_cartas_aprobadas = 0;
            NuevoAnno->cantidad_juguetes = 0;

            // En caso de que la carta esté rechazada
            if (strcmp(puntero->estado, "Rechazada") == 0)
                NuevoAnno->cantidad_cartas_rechazadas = 1;

            // En caso de que la carta NO esté rechazada
            else
                NuevoAnno->cantidad_cartas_rechazadas = 0;

            // En caso de que la lista esté vacía
            if (Lista->Inicio == NULL)
            {
                Lista->Inicio = NuevoAnno;
                Lista->Final = Lista->Inicio;
            }

            // En caso de que la lista NO esté vacía
            else
            {
                Anno *puntero3 = Lista->Inicio;
                Anno *anterior = NULL;
                int validacion = 0;

                // Se recorre la lista de años para insertar los años en orden
                while (puntero3 != NULL && validacion == 0)
                {

                    // En caso de que sea menor al año del puntero actual
                    if (NuevoAnno->anno < puntero3->anno)
                    {
                        NuevoAnno->siguiente = puntero3;

                        // En caso de se inserte al inicio de la lista
                        if (anterior == NULL)
                        {
                            Lista->Inicio = NuevoAnno;
                        }

                        // En caso de NO se inserte al inicio de la lista
                        if(anterior != NULL)
                            anterior->siguiente = NuevoAnno;
                        validacion++;
                    }

                    // En caso de que ya se trate del último puntero de la lista (el año es mayor a todos los de la lista)
                    else if (puntero3->siguiente == NULL && validacion != 1)
                    {
                        puntero3->siguiente = NuevoAnno;
                        Lista->Final = NuevoAnno;
                        validacion = 1;
                    }
                    anterior = puntero3;
                    puntero3 = puntero3->siguiente;
                }
            }
        }
        puntero = puntero->siguiente;
    }
    Anno *puntero4 = Lista->Inicio;
    printf("\n\nCantidad de cartas rechazadas por anno: \n\n");
    int contador = 1;

    // Impresion de la cantidad de cartas rechazadas por año
    while (puntero4 != NULL)
    {
        printf("%i. Anno: %i \nCantidad de cartas rechazadas: %i \n", contador, puntero4->anno, puntero4->cantidad_cartas_rechazadas);
        contador++;
        puntero4 = puntero4->siguiente;
    }
}

void Cantidad_Comportamientos(Registro_Comportamiento *Lista){
    int buenos = 0, malos = 0;

    // Recorrido a la lista de comportamientos
    Comportamiento *puntero = Lista->Inicio;
    while (puntero != NULL)
    {

        // En caso de que se trate de un comportamiento bueno
        if (strcmp(puntero->indicacion, "Bueno") == 0 || strcmp(puntero->indicacion, "bueno") == 0)
            buenos++;
        
        // En caso de que se trate de un comportamiento malo
        if (strcmp(puntero->indicacion, "Malo") == 0 || strcmp(puntero->indicacion, "malo") == 0)
            malos++;
        puntero = puntero->siguiente;
    }

    // Impresión de la cantidad de comportamientos buenos y malos
    printf("\nCantidad de comportamientos buenos: %i \n", buenos);
    printf("\nCantidad de comportamientos malos: %i \n", malos);
}

void Cantidad_Cartas_Procesadas(Registro_Ayudantes *Lista){
    Ayudante *puntero = Lista->Inicio;
    printf("\n\nCantidad de cartas procesadas por ayudante \n\n");
    int contador = 1;

    // Recorrido de la lista de ayudantes
    while (puntero != NULL)
    {

        // Se imprime los datos del ayudante y la cantidad de cartas procesadas
        printf("%i. Nombre: %s | Identificacion: %i | Cantidad cartas procesadas: %i \n", contador, puntero->nombre, puntero->ID, puntero->cantidad_procesadas);
        contador++;
        puntero = puntero->siguiente;
    }
}

void ordenar_juguetes(Juguete_Top *inicio) 
{ 
    int cambio, i; 
    Juguete_Top *ptr1; 
    Juguete_Top *lptr = NULL; 
  
    // En caso de que la lista esté vacía
    if (inicio == NULL) 
        return; 
    
    // En caso de que la lista NO esté vacía
    do
    { 
        cambio = 0; 
        ptr1 = inicio; 

        // Recorrido de la la lista
        while (ptr1->siguiente != lptr) 
        { 
            // En caso de que un contador sea mayor a otro se intercambian datos
            if (ptr1->contador > ptr1->siguiente->contador) 
            {  
                int temp = ptr1->contador;
                ptr1->contador = ptr1->siguiente->contador;
                ptr1->siguiente->contador = temp;
                char nombre[20];
                strcpy(nombre, ptr1->nombre);
                strcpy(ptr1->nombre, ptr1->siguiente->nombre);
                strcpy(ptr1->siguiente->nombre, nombre);
                cambio = 1; 
            } 
            ptr1 = ptr1->siguiente; 
        } 
        lptr = ptr1; 
    } 
    while (cambio); 
} 

void Top_Juguetes(Registro_Carta *Lista){

    // Creación de la lista donde se guardarán los juguetes según la cantidad de veces que han sido solicitados
    Registro_Top_Juguetes *Lista_Top_Juguetes = (Registro_Top_Juguetes *)malloc(sizeof(Registro_Top_Juguetes));
    Lista_Top_Juguetes->Inicio = NULL;
    Lista_Top_Juguetes->Final = NULL;

    // Se recorre cada carta
    Carta_Santa *puntero = Lista->Inicio;
    while (puntero != NULL)
    {
        Juguete_Carta *puntero2 = puntero->Inicio_Juguetes;

        // Se recorre cada juguete de la carta
        while (puntero2 != NULL)
        {
            int validacion = 0;
            Juguete_Top *puntero3 = Lista_Top_Juguetes->Inicio;

            // Se recorre cada elemento de la nueva lista
            while (puntero3 != NULL && validacion == 0)
            {

                // En caso de que el juguete ya haya sido agregado a la nueva lista se le suma uno a su contador
               if (strcmp(puntero3->nombre, puntero2->juguete) == 0)
               {
                   puntero3->contador += 1;
                   validacion++;
               }
               puntero3 = puntero3->siguiente; 
            }

            // En caso de que el juguete NO haya sido agregado a la nueva lista
            if (validacion == 0)
            {

                // Se crea un nuevo elemento de la nueva lista
                Juguete_Top *copia = (Juguete_Top *) malloc(sizeof(Juguete_Top));
                copia->siguiente = NULL;
                copia->anterior = NULL;
                copia->contador = 1;
                strcpy(copia->nombre, puntero2->juguete);

                // En caso de que la nueva lista esté vacía
                if (Lista_Top_Juguetes->Inicio == NULL)
                {
                    Lista_Top_Juguetes->Inicio = copia;
                    Lista_Top_Juguetes->Final = copia;
                }

                // En caso de que la nueva lista NO esté vacía
                else
                {
                    Lista_Top_Juguetes->Final->siguiente = copia;
                    copia->anterior = Lista_Top_Juguetes->Final;
                    Lista_Top_Juguetes->Final = copia;
                }
            }
            puntero2 = puntero2->siguiente;
        }
        puntero = puntero->siguiente;
    }

    // Se ordena la lista
    ordenar_juguetes(Lista_Top_Juguetes->Inicio);
    int contador = 0;
    Juguete_Top *imprimir = Lista_Top_Juguetes->Final;
    printf("\n\nTOP 10 juguetes mas solicitados: \n\n");

    // Impresion de juguetes en orden de más a menos solicitado
    // Mientras no se haya completado el top 10
    while (contador < 10 && imprimir != NULL)
    {
        printf("%i. Nombre juguete: %s | Cantidad de solicitudes: %i \n", contador+1, imprimir->nombre, imprimir->contador);
        contador++;
        imprimir = imprimir->anterior;
    }

    // En caso de que se hayan registrado menos de 10 juguetes
    if (contador < 10)
        printf("Solo se han solicitado %i juguetes. Por lo tanto no es posible completar un top 10 \n", contador);
}

void Precargar(Registro_Ninos *Lista_Ninos, Registro_Lugares *Lista_Lugares, Registro_Ayudantes *Lista_Ayudantes, Registro_Comportamiento *Lista_Comportamientos, Registro_Carta *Lista_Cartas, Registro_Annos *Lista_Annos){
    Agregar_Lugar(Lista_Lugares, "Polo-01", "Polo Norte", 1);
    Agregar_Lugar(Lista_Lugares, "Lug-01", "Perez Zeledon", 11901);
    Agregar_Lugar(Lista_Lugares, "Lug-02", "San Jose", 10102);
    Agregar_Lugar(Lista_Lugares, "Lug-03", "Heredia", 40104);
    Agregar_Lugar(Lista_Lugares, "Lug-04", "Alajuela", 20101);
    Agregar_Lugar(Lista_Lugares, "Lug-05", "Cartago", 30101);
    Agregar_Lugar(Lista_Lugares, "Lug-06", "Limon", 70101);
    Agregar_Lugar(Lista_Lugares, "Lug-07", "Nicoya", 50201);
    Agregar_Lugar(Lista_Lugares, "Lug-08", "Puntarenas", 60107);

    Agregar_Ruta(Lista_Lugares, "Polo Norte", "Perez Zeledon", 500, 150, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Polo Norte", "Heredia", 360, 140, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Polo Norte", "Alajuela", 90, 145, "Aerea");
    Agregar_Ruta(Lista_Lugares, "Polo Norte", "Limon", 600, 160, "Maritima");
    Agregar_Ruta(Lista_Lugares, "Polo Norte", "Puntarenas", 550, 157, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Perez Zeledon", "San Jose", 180, 25, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Perez Zeledon", "Heredia", 210, 35, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Perez Zeledon", "Limon", 250, 45, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "San Jose", "Limon", 15, 30, "Aerea");
    Agregar_Ruta(Lista_Lugares, "San Jose", "Alajuela", 60, 15, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "San Jose", "Cartago", 45, 10, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Heredia", "Perez Zeledon", 210, 35, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Heredia", "Nicoya", 110, 45, "Maritima");
    Agregar_Ruta(Lista_Lugares, "Alajuela", "San Jose", 60, 15, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Alajuela", "Perez Zeledon", 28, 39, "Aerea");
    Agregar_Ruta(Lista_Lugares, "Alajuela", "Limon", 120, 37, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Cartago", "Heredia", 70, 18, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Cartago", "Nicoya", 140, 28, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Limon", "Nicoya", 40, 16, "Maritima");
    Agregar_Ruta(Lista_Lugares, "Limon", "Puntarenas", 70, 26, "Maritima");
    Agregar_Ruta(Lista_Lugares, "Limon", "Cartago", 120, 26, "Terrestre");
    Agregar_Ruta(Lista_Lugares, "Nicoya", "Cartago", 35, 28, "Aerea");
    Agregar_Ruta(Lista_Lugares, "Nicoya", "Puntarenas", 80, 30, "Maritima");
    Agregar_Ruta(Lista_Lugares, "Puntarenas", "San Jose", 230, 34, "Terrestre");
                                                                                        
    char necesidades1[10][60], necesidades2[10][60], necesidades3[10][60], necesidades4[10][60], necesidades5[10][60], necesidades6[10][60], necesidades7[10][60], necesidades8[10][60], necesidades9[10][60], necesidades10[10][60], necesidades11[10][60];
    strcpy(necesidades1[0], "Nada");strcpy(necesidades2[0], "Nada");strcpy(necesidades3[0], "Nada");strcpy(necesidades4[0], "Nada");strcpy(necesidades5[0], "Nada");strcpy(necesidades6[0], "Nada");strcpy(necesidades7[0], "Nada");strcpy(necesidades8[0], "Nada");strcpy(necesidades9[0], "Nada");strcpy(necesidades10[0], "Nada");   
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 1, "Zach Wilson", "Z-01", "Perez Zeledon", "ZachKapono@gmail.com", "03/08/1999", 21, necesidades1, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 11, "Brandon Aiyuk", "B-11", "San Jose", "Baiyuk@gmail.com", "17/03/1998", 22, necesidades2, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 85, "George Kittle", "K-85", "Heredia", "GKittle46@gmail.com", "09/10/1993", 27, necesidades3, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 19, "Deebo Samuel", "D-19", "Cartago", "19problemz@gmail.com", "15/01/1996", 24, necesidades4, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 31, "Raheem Mostert", "M-31", "Alajuela", "Mosball@gmail.com", "09/04/1992", 28, necesidades5, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 97, "Nick Bosa", "B-97", "Limon", "nbsmallerbear@gmail.com", "23/10/1997", 23, necesidades6, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 54, "Fred Warner", "F-54", "Nicoya", "fredwarner@gmail.com", "19/11/1996", 24, necesidades7, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 99, "Javon Kinlaw", "K-99", "Puntarenas", "Mookdawg@gmail.com", "03/10/1997", 23, necesidades8, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 57, "Dre Greenlaw", "D-57", "Perez Zeledon", "Dre57@gmail.com", "25/05/1997", 23, necesidades9, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 22, "Jason Verrett", "V-22", "San Jose", "JVerrett@gmail.com", "18/06/1991", 29, necesidades10, 1);
    //Agregar_Nino(Lista_Ninos, Lista_Lugares, 118220472, "Jairo Calderon", "Jairocs", "Heredia", "calderonjairo88@gmail.com", "10/09/2001", 19, necesidades11, 0);

    char funciones1[10][60], funciones2[10][60], funciones3[10][60], funciones4[10][60], funciones5[10][60], funciones6[10][60], funciones7[10][60], funciones8[10][60], funciones9[10][60], funciones10[10][60];
    strcpy(funciones1[0], "Nada");strcpy(funciones2[0], "Nada");strcpy(funciones3[0], "Nada");strcpy(funciones4[0], "Nada");strcpy(funciones5[0], "Nada");strcpy(funciones6[0], "Nada");strcpy(funciones7[0], "Nada");strcpy(funciones8[0], "Nada");strcpy(funciones9[0], "Nada");strcpy(funciones10[0], "Nada");
    Agregar_Ayudante(Lista_Ayudantes, 100, "Duende 1", "Director de duendes", funciones1, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 101, "Duende 2", "Asistente de duendes", funciones2, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 102, "Duende 3", "Miembro de equipo de duendes", funciones3, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 103, "Duende 4", "Miembro de equipo de duendes", funciones4, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 105, "Duende 5", "Miembro de equipo de duendes", funciones5, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 106, "Duende 6", "Miembro de equipo de duendes", funciones6, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 107, "Duende 7", "Miembro de equipo de duendes", funciones7, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 108, "Duende 8", "Miembro de equipo de duendes", funciones8, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 109, "Duende 9", "Miembro de equipo de duendes", funciones9, "01/01/2021", 1);
    Agregar_Ayudante(Lista_Ayudantes, 110, "Duende 10", "Miembro de equipo de duendes", funciones10, "01/01/2021", 1);

    Agregar_Juguete("J01", "Buzz Lightyear", "Nada", "Juguete", "0-12 annos", 2300);
    Agregar_Juguete("J02", "Buzz Lightyear2", "Nada", "Juguete", "0-12 annos", 2500);
    Agregar_Juguete("J03", "Buzz Lightyear3", "Nada", "Juguete", "0-12 annos", 2800);
    Agregar_Juguete("J04", "Buzz Lightyear4", "Nada", "Juguete", "0-12 annos", 2100);
    Agregar_Juguete("J05", "Buzz Lightyear5", "Nada", "Juguete", "0-12 annos", 2200);
    Agregar_Juguete("J06", "Buzz Lightyear6", "Nada", "Juguete", "0-12 annos", 2900);
    Agregar_Juguete("J07", "Buzz Lightyear7", "Nada", "Juguete", "0-12 annos", 3000);
    Agregar_Juguete("J08", "Buzz Lightyear8", "Nada", "Juguete", "0-12 annos", 2300);
    Agregar_Juguete("J09", "Buzz Lightyear9", "Nada", "Juguete", "0-12 annos", 2500);
    Agregar_Juguete("J10", "Buzz Lightyear10", "Nada", "Juguete", "0-12 annos", 2800);
    Agregar_Juguete("J11", "Buzz Lightyear11", "Nada", "Juguete", "0-12 annos", 2100);
    Agregar_Juguete("J12", "Buzz Lightyear12", "Nada", "Juguete", "0-12 annos", 2200);
    Agregar_Juguete("J13", "Buzz Lightyear13", "Nada", "Juguete", "0-12 annos", 2900);
    Agregar_Juguete("J14", "Buzz Lightyear14", "Nada", "Juguete", "0-12 annos", 3000);
    Agregar_Juguete("J15", "Buzz Lightyear15", "Nada", "Juguete", "0-12 annos", 2500);
    Agregar_Juguete("J16", "Buzz Lightyear16", "Nada", "Juguete", "0-12 annos", 2800);
    Agregar_Juguete("J17", "Buzz Lightyear17", "Nada", "Juguete", "0-12 annos", 2100);
    Agregar_Juguete("J18", "Buzz Lightyear18", "Nada", "Juguete", "0-12 annos", 2200);
    Agregar_Juguete("J19", "Buzz Lightyear19", "Nada", "Juguete", "0-12 annos", 2900);
    Agregar_Juguete("J20", "Buzz Lightyear20", "Nada", "Juguete", "0-12 annos", 3000);

    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 1, "Zach Wilson", 2021, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 11, "Brandon Aiyuk", 2021, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 85, "George Kittle", 2021, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 19, "Deebo Samuel", 2020, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 31, "Raheem Mostert", 2020, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 97, "Nick Bosa", 2021, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 54, "Fred Warner", 2021, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 99, "Javon Kinlaw", 2020, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 57, "Dre Greenlaw", 2019, "Buzz Lightyear16", 2800);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 22, "Jason Verrett", 2019, "Buzz Lightyear16", 2800);

    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 1, "Zach Wilson", 2021, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear8", 1, "Zach Wilson", 2021, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear10", 1, "Zach Wilson", 2021, 2800);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 11, "Brandon Aiyuk", 2021, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear3", 11, "Brandon Aiyuk", 2021, 2800);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear11", 11, "Brandon Aiyuk", 2021, 2100);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 85, "George Kittle", 2021, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear8", 85, "George Kittle", 2021, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear5", 85, "George Kittle", 2021, 2200);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 19, "Deebo Samuel", 2020, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear9", 19, "Deebo Samuel", 2020, 2500);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear19", 19, "Deebo Samuel", 2020, 2900);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 31, "Raheem Mostert", 2020, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear3", 31, "Raheem Mostert", 2020, 2800);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear13", 31, "Raheem Mostert", 2020, 2900);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 97, "Nick Bosa", 2021, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear7", 97, "Nick Bosa", 2021, 3000);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear9", 97, "Nick Bosa", 2021, 2500);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 54, "Fred Warner", 2021, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear5", 54, "Fred Warner", 2021, 2200);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear4", 54, "Fred Warner", 2021, 2100);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 99, "Javon Kinlaw", 2020, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear9", 99, "Javon Kinlaw", 2020, 2500);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear17", 99, "Javon Kinlaw", 2020, 2100);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 57, "Dre Greenlaw", 2019, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear5", 57, "Dre Greenlaw", 2019, 2200);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear7", 57, "Dre Greenlaw", 2019, 3000);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear", 22, "Jason Verrett", 2019, 2300);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear2", 22, "Jason Verrett", 2019, 2500);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Buzz Lightyear18", 22, "Jason Verrett", 2019, 2200);

    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 1, "Zach Wilson", 2021, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 11, "Brandon Aiyuk", 2021, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 85, "George Kittle", 2021, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 19, "Deebo Samuel", 2020, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 31, "Raheem Mostert", 2020, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 97, "Nick Bosa", 2021, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 54, "Fred Warner", 2021, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 99, "Javon Kinlaw", 2020, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 57, "Dre Greenlaw", 2019, 3000);
    Agregar_a_Deseos(Lista_Cartas, raiz, "Buzz Lightyear20", 22, "Jason Verrett", 2019, 3000);

    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 11, "04/01/2021", "Solto pases", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 11, "04/01/2021", "Solto pases", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 11, "04/01/2021", "Solto pases", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 11, "04/01/2021", "Solto pases", "Malo");
    //Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 11, "04/01/2021", "Solto pases", "Malo");
    //Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 11, "04/01/2021", "Solto pases", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 11, "04/01/2021", "Solto pases", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 57, "04/01/2021", "Fallo cobertutras", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 57, "04/01/2021", "Fallo cobertutras", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 57, "04/01/2021", "Fallo cobertutras", "Malo");
    //Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 57, "04/01/2021", "Fallo cobertutras", "Malo");
    //Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 57, "04/01/2021", "Fallo cobertutras", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 57, "04/01/2021", "Fallo cobertutras", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 57, "04/01/2021", "Fallo cobertutras", "Malo");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 1, "04/01/2021", "Buena temporada bro", "Bueno");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 85, "04/01/2021", "Buena temporada bro", "Bueno");
    Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, "Kyle Shanahan", 97, "04/01/2021", "Buena temporada bro", "Bueno");
  
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2021, 1, 100);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2021, 11, 101);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2021, 85, 100);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2020, 19, 103);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2020, 31, 103);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2021, 97, 100);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2021, 54, 108);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2020, 99, 105);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2019, 57, 107);
    Procesar_Carta2(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, 2019, 22, 106);

    //Entregar_Juguetes(Lista_Lugares, Lista_Ninos, Lista_Cartas, 1);
    /*
    char funciones1[10][60];
    strcpy(funciones1[0], "nadaa");
    Agregar_Ayudante(Lista_Ayudantes, 101, "duendee", "secretario", funciones1, "02/01/2021", 1);
    Agregar_Lugar(Lista_Lugares, "L-001", "Herediaa", 40100);
    Agregar_Lugar(Lista_Lugares, "L-002", "San Jose", 28239);
    Agregar_Ruta(Lista_Lugares, "Herediaa", "San Jose", 80, 14, "aerea");
    char necesidades1[10][60];
    strcpy(necesidades1[0], "Ya no es grinch");
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 118220472, "Jairoo Calderon", "jairocs97", "Herediaa", "calderonjairo80@gmail.com", "10/09/2021", 90, necesidades1, 1);
    Agregar_Juguete("J-001", "El Woody", "Solo el Woody", "vaqueritos", "0-8 annos", 10000);
    Agregar_Juguete("J-002", "Oso", "Un oso de peluche", "ninguna", "0-6 annos", 6000);
    Agregar_Juguete("J-003", "Oso 2", "Otro oso de peluche", "ninguna", "0-6 annos", 6000);
    Agregar_Carta2(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, 118220472, "Jairoo Calderon", 2021, "El Woody", 10000);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Oso", 118220472, "Jairoo Calderon", 2021, 6000);
    Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, "Oso 2", 118220472, "Jairoo Calderon", 2021, 6000);
    */
}

void main(){
    Registro_Ninos *Lista_Ninos = (Registro_Ninos *) malloc(sizeof(Registro_Ninos));
    Lista_Ninos->Inicio = NULL;
    Lista_Ninos->Final = NULL;
    Registro_Lugares *Lista_Lugares = (Registro_Lugares *) malloc(sizeof(Registro_Lugares));
    Lista_Lugares->Inicio = NULL;
    Lista_Lugares->Final = NULL;
    Registro_Ayudantes *Lista_Ayudantes = (Registro_Ayudantes *) malloc(sizeof(Registro_Ayudantes));
    Lista_Ayudantes->Inicio = NULL;
    Lista_Ayudantes->Final = NULL;
    Registro_Comportamiento *Lista_Comportamientos = (Registro_Comportamiento *) malloc(sizeof(Registro_Comportamiento));
    Lista_Comportamientos->Inicio = NULL;
    Lista_Comportamientos->Final = NULL;
    Registro_Carta *Lista_Cartas = (Registro_Carta *) malloc(sizeof(Registro_Carta));
    Lista_Cartas->Inicio = NULL;
    Lista_Cartas->Final = NULL;
    Registro_Annos *Lista_Annos = (Registro_Annos *) malloc(sizeof(Registro_Annos));
    Lista_Annos->Inicio = NULL;
    Lista_Annos->Final = NULL;

    Precargar(Lista_Ninos, Lista_Lugares, Lista_Ayudantes, Lista_Comportamientos, Lista_Cartas, Lista_Annos);

    int a = 0;
    while (a == 0)
    {
        int decision_usuario;
        printf("\n\nBIENVENIDO! \n\nDIGITE 1 para registrar un nino o nina \nDIGITE 2 para modificar informacion o eliminar un nino \nDIGITE 3 para ver la lista de ninos \nDIGITE 4 para para registrar un ayudante \nDIGITE 5 para modificar informacion o eliminar un ayudante \nDIGITE 6 para ver la lista de ayudantes \nDIGITE 7 para para registrar un juguete \nDIGITE 8 para modificar/eliminar un juguete \nDIGITE 9 para ver la lista de juguetes \nDIGITE 10 para agregar un lugar \nDIGITE 11 para modificar o eliminar un lugar \nDIGITE 12 para ver la lista de lugares y rutas registradas \nDIGITE 13 para agregar una ruta \nDIGITE 14 para modificar o eliminar una ruta \nDIGITE 15 para registrar el comportamiento de un nino \nDIGITE 16 para registrar una carta \nDIGITE 17 para agregar un juguete a su carta \nDIGITE 18 para agregar un juguete a su lista de deseos \nDIGITE 19 para pasar un juguete de su lista de deseos a su carta \nDIGITE 20 para eliminar un juguete de su carta \nDIGITE 21 para eliminar un juguete de su lista de deseos \nDIGITE 22 para consultar la informacion de su carta \nDIGITE 23 para procesar una carta \nDIGITE 24 para hacer la simulacion de entrega de juguetes \nDIGITE 25 para hacer analisis de datos \nDIGITE 26 para salir \n\n");
        scanf("%i", &decision_usuario);
        if (decision_usuario == 1)
        {
            int ID_NINO, edad, cant, i;
            char nombre[60], usuario[40], residencia[30], correo[40], fecha_nacimiento[40];
            char necesidades_especiales[10][60];
            printf("Ingrese la identificacion del nino \n");
            scanf("%i", &ID_NINO);
            printf("Ingrese el nombre del nino \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese el nombre de usuario del nino \n");
            scanf(" %[^\t\n]s", &usuario);
            printf("Ingrese el lugar de residencia del nino \n");
            scanf(" %[^\t\n]s", &residencia);
            printf("Ingrese el correo del nino \n");
            scanf(" %[^\t\n]s", &correo);
            printf("Ingrese la fecha de nacimiento del nino \n");
            scanf(" %[^\t\n]s", &fecha_nacimiento);
            printf("Ingrese la edad del nino \n");
            scanf("%i", &edad);
            printf("Cuantas necesidades especiales desea anadir para el nino? \n");
            scanf("%i", &cant);
            for ( i = 0; i < cant; i++)
            {
                char necesidad[60];
                printf("Ingrese la necesidad especial: \n");
                scanf(" %[^\t\n]s", &necesidad);
                strcpy(necesidades_especiales[i], necesidad);
            }
            Agregar_Nino(Lista_Ninos, Lista_Lugares, ID_NINO, nombre, usuario, residencia, correo, fecha_nacimiento, edad, necesidades_especiales, cant);
        }
        else if (decision_usuario == 2)
        {
            int validacion_modificar_nino = 0;
            while (validacion_modificar_nino == 0)
            {
                int decision2;
                printf("Ingrese 1 para modificar informacion \nIngrese 2 para eliminar un nino \nIngrese 3 para cancelar \n");
                scanf("%i", &decision2);
                if (decision2 == 1 || decision2 == 2 || decision2 == 3){
                    if (decision2 == 1 || decision2 == 2){
                        int ID_Nino;
                        printf("Ingrese la identificacion del nino al que desee modificar/eliminar \n");
                        scanf("%i", &ID_Nino);
                        modificar_datos_nino(Lista_Ninos, ID_Nino, decision2);
                    } 
                    validacion_modificar_nino++;
                }
                else
                    printf("La opcion ingresada no es valida. Vuelva a intentarlo \n");
            }
        }
        else if (decision_usuario == 3)
            Imprimir_Ninos(Lista_Ninos);
        else if (decision_usuario == 4)
        {
            int ID_Ayudante, cant, i;
            char nombre[60], puesto[25], funciones[6][60], fecha[11];
            printf("Ingrese la identificacion del ayudante \n");
            scanf("%i", &ID_Ayudante);
            printf("Ingrese el nombre del ayudante \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese el puesto del ayudante \n");
            scanf(" %[^\t\n]s", &puesto);
            printf("Ingrese la fecha en que inicio a trabajar con santa \n");
            scanf(" %[^\t\n]s", &fecha);
            printf("Cuantas funciones tiene en su puesto? \n");
            scanf("%i", &cant);
            for ( i = 0; i < cant; i++)
            {
                char funcion[60];
                printf("Ingrese la necesidad especial: \n");
                scanf(" %[^\t\n]s", &funcion);
                strcpy(funciones[i], funcion);
            }
            Agregar_Ayudante(Lista_Ayudantes, ID_Ayudante, nombre, puesto, funciones, fecha, cant);
        }
        else if (decision_usuario == 5)
        {
            int validacion_modificar_ayudante = 0;
            while (validacion_modificar_ayudante == 0)
            {
                int decision2;
                printf("Ingrese 1 para modificar informacion \nIngrese 2 para eliminar un ayudante \nIngrese 3 para cancelar \n");
                scanf("%i", &decision2);
                if (decision2 == 1 || decision2 == 2 || decision2 == 3){
                    validacion_modificar_ayudante++;
                    if (decision2 == 1 || decision2 == 2){
                        int ID_Ayudante;
                        printf("Ingrese la identificacion del ayudante al que desee modificar/eliminar \n");
                        scanf("%i", &ID_Ayudante);
                        modificar_datos_ayudante(Lista_Ayudantes, ID_Ayudante, decision2);
                    } 
                }
                else
                    printf("La opcion ingresada no es valida. Vuelva a intentarlo \n");
            }
        }
        else if (decision_usuario == 6)
            Imprimir_Ayudantes(Lista_Ayudantes);
        else if (decision_usuario == 7)
        {
            char codigo[10], nombre[30], descripcion[60], categoria[15], rango[15];
            int costo;
            printf("Ingrese el codigo del juguete: \n");
            scanf(" %[^\t\n]s", &codigo);
            printf("Ingrese el nombre del juguete: \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese la descripcion del juguete: \n");
            scanf(" %[^\t\n]s", &descripcion);
            printf("Ingrese la categoria del juguete: \n");
            scanf(" %[^\t\n]s", &categoria);
            printf("Ingrese el rango de edad en que se recomienda utilizar el juguete: \n");
            scanf(" %[^\t\n]s", &rango);
            printf("Ingrese el precio del juguete: \n");
            scanf("%i", &costo);
            Agregar_Juguete(codigo, nombre, descripcion, categoria, rango, costo);
        }
        else if (decision_usuario == 8)
        {
            int validacion_modificar_juguete = 0;
            while (validacion_modificar_juguete == 0)
            {
                int decision2;
                printf("Ingrese 1 para modificar informacion \nIngrese 2 para eliminar un juguete \nIngrese 3 para cancelar \n");
                scanf("%i", &decision2);
                if (decision2 == 1 || decision2 == 2 || decision2 == 3){
                    validacion_modificar_juguete++;
                    if (decision2 == 1 || decision2 == 2){
                        char nombre_juguete[30];
                        printf("Ingrese el nombre del juguete que desee modificar/eliminar \n");
                        scanf(" %[^\t\n]s", &nombre_juguete);
                        int costo_juguete;
                        printf("Ingrese el costo del juguete que desee modificar/eliminar \n");
                        scanf("%i", &costo_juguete);
                        Modificar_Juguetes(raiz, nombre_juguete, costo_juguete, decision2);
                    } 
                }
                else
                    printf("La opcion ingresada no es valida. Vuelva a intentarlo \n");
            }
        }
        else if (decision_usuario == 9)
            imprimirJuguete(raiz);
        else if (decision_usuario == 10)
        {
            char codigo[10], nombre[30];
            int codigo_postal;
            printf("Ingrese el codigo del lugar: \n");
            scanf(" %[^\t\n]s", &codigo);
            printf("Ingrese el nombre del lugar: \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese el codigo postal del lugar: \n");
            scanf("%i", &codigo_postal);
            Agregar_Lugar(Lista_Lugares, codigo, nombre, codigo_postal);
        }
        else if (decision_usuario == 11)
        {
            int validacion_modificar_lugar = 0;
            while (validacion_modificar_lugar == 0)
            {
                int decision2;
                printf("Ingrese 1 para modificar informacion \nIngrese 2 para eliminar un lugar \nIngrese 3 para cancelar \n");
                scanf("%i", &decision2);
                if (decision2 == 1 || decision2 == 2 || decision2 == 3){
                    validacion_modificar_lugar++;
                    if (decision2 == 1 || decision2 == 2){
                        char nombre_lugar[30];
                        printf("Ingrese el nombre del lugar que desee modificar/eliminar \n");
                        scanf(" %[^\t\n]s", &nombre_lugar);
                        modificar_datos_lugar(Lista_Lugares, nombre_lugar, decision2);
                    } 
                }
                else
                    printf("La opcion ingresada no es valida. Vuelva a intentarlo \n");
            }
        }
        else if (decision_usuario == 12)
            Imprimir_Lugares_Y_Rutas(Lista_Lugares);
        else if (decision_usuario == 13)
        {
            char origen[30], destino[30], tipo[10];
            int minutos, distancia;
            printf("Ingrese el nombre del lugar de origen de la ruta: \n");
            scanf(" %[^\t\n]s", &origen);
            printf("Ingrese el nombre del lugar de destino de la ruta: \n");
            scanf(" %[^\t\n]s", &destino);
            int validacion = 0;
            while (validacion == 0)
            {
                printf("Ingrese el tipo de ruta: \n");
                scanf(" %[^\t\n]s", &tipo);
                if (strcmp(tipo, "Maritima") == 0 || strcmp(tipo, "Marítima") == 0 || strcmp(tipo, "maritima") == 0 || strcmp(tipo, "marítima") == 0 || strcmp(tipo, "Aérea") == 0 || strcmp(tipo, "aérea") == 0 || strcmp(tipo, "Aerea") == 0 || strcmp(tipo, "aerea") == 0 || strcmp(tipo, "Terrestre") == 0 || strcmp(tipo, "terrestre") == 0)
                    validacion++;
                else
                    printf("Las unicos tipos de ruta validos son: aerea, terrestre y maritima. Vuelva a intentarlo \n");
            }
            printf("Ingrese la duracion (en minutos) de la ruta: \n");
            scanf("%i", &minutos);
            printf("Ingrese la distancia (en kilometros) de la ruta: \n");
            scanf("%i", &distancia);
            Agregar_Ruta(Lista_Lugares, origen, destino, minutos, distancia, tipo);
        }
        else if (decision_usuario == 14)
        {
            int validacion_modificar_ruta = 0;
            while (validacion_modificar_ruta == 0)
            {
                int decision2;
                char origen[30], destino[30], tipo[10];
                printf("Ingrese 1 para modificar informacion \nIngrese 2 para eliminar una ruta \nIngrese 3 para cancelar \n");
                scanf("%i", &decision2);
                if (decision2 == 1 || decision2 == 2 || decision2 == 3){
                    validacion_modificar_ruta++;
                    if (decision2 == 1 || decision2 == 2){
                        printf("Ingrese el nombre del lugar de origen de la ruta: \n");
                        scanf(" %[^\t\n]s", &origen);
                        printf("Ingrese el nombre del lugar de destino de la ruta: \n");
                        scanf(" %[^\t\n]s", &destino);
                        int validacion = 0;
                        while (validacion == 0)
                        {
                            printf("Ingrese el tipo de ruta: \n");
                            scanf(" %[^\t\n]s", &tipo);
                            if (strcmp(tipo, "Maritima") == 0 || strcmp(tipo, "Marítima") == 0 || strcmp(tipo, "maritima") == 0 || strcmp(tipo, "marítima") == 0 || strcmp(tipo, "Aérea") == 0 || strcmp(tipo, "aérea") == 0 || strcmp(tipo, "Aerea") == 0 || strcmp(tipo, "aerea") == 0 || strcmp(tipo, "Terrestre") == 0 || strcmp(tipo, "terrestre") == 0)
                                validacion++;
                            else
                                printf("Las unicos tipos de ruta validos son: aerea, terrestre y maritima. Vuelva a intentarlo \n");
                        }
                    } 
                    modificar_datos_ruta(Lista_Lugares, decision2, origen, destino, tipo);
                }
                else
                    printf("La opcion ingresada no es valida. Vuelva a intentarlo \n");
            }
        }
        else if (decision_usuario == 15)
        {
            char nombre_padre[30], fecha[11], descripcion[130], indicacion[6];
            int ID_Nino;
            printf("Ingrese el nombre del padre del nino: \n");
            scanf(" %[^\t\n]s", &nombre_padre);
            printf("Ingrese la identificacion del nino: \n");
            scanf("%i", &ID_Nino);
            printf("Ingrese la fecha del reporte: \n");
            scanf(" %[^\t\n]s", &fecha);
            printf("Ingrese la descripcion del comportamiento: \n");
            scanf(" %[^\t\n]s", &descripcion);
            int validacion = 0;
            while (validacion == 0)
            {
                printf("Indique si se trata de un comportamiento bueno o malo: \n");
                scanf("%s", &indicacion);
                if (strcmp(indicacion, "Bueno") == 0 || strcmp(indicacion, "bueno") == 0 || strcmp(indicacion, "Malo") == 0 || strcmp(indicacion, "malo") == 0)
                    validacion++;
                else
                    printf("Entrada invalida. Debe indicar unicamente bueno o malo \n");
            }
            Agregar_Comportamiento(Lista_Comportamientos, Lista_Ninos, nombre_padre, ID_Nino, fecha, descripcion, indicacion);
        }
        else if (decision_usuario == 16)
        {
            char nombre[30], nombre_juguete[30];
            int ID_Nino, anno, costo;
            printf("Ingrese la identificacion del nino al que desea crearle la carta \n");
            scanf("%i", &ID_Nino);
            printf("Ingrese el nombre del nino al que desea crearle la carta \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese el anno para el que se registrara la carta \n");
            scanf("%i", &anno);
            printf("Ingrese el nombre de uno de los juguetes disponibles \n");
            scanf(" %[^\t\n]s", &nombre_juguete);
            printf("Ingrese el costo de ese juguete: \n");
            scanf("%i", &costo);
            Agregar_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, ID_Nino, nombre, anno, nombre_juguete, costo);
        }
        else if (decision_usuario == 17)
        {
            char nombre[30], nombre_juguete[30];
            int ID_Nino, anno, costo;
            printf("Ingrese la identificacion del nino al que pertenece la carta \n");
            scanf("%i", &ID_Nino);
            printf("Ingrese el nombre del nino al que pertenece la carta \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese el anno de la carta \n");
            scanf("%i", &anno);
            printf("Ingrese el nombre de uno de los juguetes disponibles \n");
            scanf(" %[^\t\n]s", &nombre_juguete);
            printf("Ingrese el costo de ese juguete: \n");
            scanf("%i", &costo);
            Agregar_Juguete_Carta(Lista_Cartas, raiz, Lista_Ninos, Lista_Lugares, nombre_juguete, ID_Nino, nombre, anno, costo);
        }
        else if (decision_usuario == 18)
        {
            char nombre[30], nombre_juguete[30];
            int ID_Nino, anno, costo;
            printf("Ingrese la identificacion del nino al que pertenece la carta \n");
            scanf("%i", &ID_Nino);
            printf("Ingrese el nombre del nino al que pertenece la carta \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese el anno de la carta \n");
            scanf("%i", &anno);
            printf("Ingrese el nombre de uno de los juguetes disponibles \n");
            scanf(" %[^\t\n]s", &nombre_juguete);
            printf("Ingrese el costo de ese juguete: \n");
            scanf("%i", &costo);
            Agregar_a_Deseos(Lista_Cartas, raiz, nombre_juguete, ID_Nino, nombre, anno, costo);
        }
        else if (decision_usuario == 19)
        {
            char nombre_juguete[30];
            int ID_Nino, anno, costo;
            printf("Ingrese la identificacion del nino al que pertenece la carta \n");
            scanf("%i", &ID_Nino);
            printf("Ingrese el anno de la carta \n");
            scanf("%i", &anno);
            printf("Ingrese el nombre de uno de los juguetes disponibles \n");
            scanf(" %[^\t\n]s", &nombre_juguete);
            De_Deseo_A_Carta(Lista_Cartas, nombre_juguete, ID_Nino, anno);
        }
        else if (decision_usuario == 20)
        {
            char nombre[30], nombre_juguete[30];
            int ID_Nino, anno, costo;
            printf("Ingrese la identificacion del nino al que pertenece la carta \n");
            scanf("%i", &ID_Nino);
            printf("Ingrese el nombre del nino al que pertenece la carta \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese el anno de la carta \n");
            scanf("%i", &anno);
            printf("Ingrese el nombre del juguete a eliminar \n");
            scanf(" %[^\t\n]s", &nombre_juguete);
            printf("Ingrese el costo de ese juguete: \n");
            scanf("%i", &costo);
            Eliminar_Juguete_Carta(Lista_Cartas, raiz, nombre_juguete, ID_Nino, nombre, anno, costo);
        }
        else if (decision_usuario == 21)
        {
            char nombre[30], nombre_juguete[30];
            int ID_Nino, anno, costo;
            printf("Ingrese la identificacion del nino al que pertenece la carta \n");
            scanf("%i", &ID_Nino);
            printf("Ingrese el nombre del nino al que pertenece la carta \n");
            scanf(" %[^\t\n]s", &nombre);
            printf("Ingrese el anno de la carta \n");
            scanf("%i", &anno);
            printf("Ingrese el nombre del juguete a eliminar \n");
            scanf(" %[^\t\n]s", &nombre_juguete);
            printf("Ingrese el costo de ese juguete: \n");
            scanf("%i", &costo);
            Eliminar_De_Deseos(Lista_Cartas, raiz, nombre_juguete, ID_Nino, nombre, anno, costo);
        }
        else if (decision_usuario == 22)
        {
            int ID_Nino, anno;
            printf("Ingrese la identificacion del nino al que pertenece la carta \n");
            scanf("%i", &ID_Nino);
            printf("Ingrese el anno de la carta \n");
            scanf("%i", &anno);
            Consultar_Carta(Lista_Cartas, ID_Nino, anno);
        }
        else if (decision_usuario == 23)
        {
            int anno;
            printf("Ingrese el anno de la carta \n");
            scanf("%i", &anno);
            Procesar_Carta(Lista_Cartas, Lista_Ninos, Lista_Ayudantes, anno);
        }
        else if (decision_usuario == 24)
        {
            int validacion = 0;
            while (validacion == 0)
            {
                int decision2;
                printf("Ingrese 1 para hacer la simulacion de todas las rutas \nIngrese 2 para hacer simulacion solo de una ruta especifica \nIngrese 3 para cancelar \n");
                scanf("%i", &decision2);
                if (decision2 == 1 || decision2 == 2 || decision2 == 3)
                {
                    validacion++;
                    Entregar_Juguetes(Lista_Lugares, Lista_Ninos, Lista_Cartas, decision2);
                }
                else
                    printf("La opcion ingresada no es valida. Vuelva a intentarlo \n");
            }
        }
        else if (decision_usuario == 25)
        {
            int decision_analisis;
            printf("Ingrese 1 para ver la cantidad de juguetes solicitados por anno \nIngrese 2 para consultar el lugar donde se solicitaron mas juguetes y el lugar donde se solicitaron menos juguetes \nIngrese 3 para conocer la cantidad de ninos a los que se les aprobo su carta por anno \nIngrese 4 para conocer la cantidad de ninos a los que se les rechazo su carta por anno \nIngrese 5 para conocer la cantidad de comportamientos buenos y malos registrados \nIngrese 6 para conocer la cantidad de cartas procesadas segun ayudante\nIngrese 7 para ver el Top 10 de los juguetes mas pedidos \n");
            scanf("%i", &decision_analisis);
            if (decision_analisis == 1)
                Cantidad_Juguetes_Anno(Lista_Annos, Lista_Cartas);
            else if(decision_analisis == 2)
                Cantidad_Juguetes_Lugar(Lista_Lugares);
            else if(decision_analisis == 3)
                Cantidad_Cartas_Aprobadas(Lista_Annos, Lista_Cartas);
            else if(decision_analisis == 4)
                Cantidad_Cartas_Rechazadas(Lista_Annos, Lista_Cartas);
            else if(decision_analisis == 5)
                Cantidad_Comportamientos(Lista_Comportamientos);
            else if(decision_analisis == 6)
                Cantidad_Cartas_Procesadas(Lista_Ayudantes);
            else if(decision_analisis == 7)
                Top_Juguetes(Lista_Cartas);
            else
                printf("La opcion ingresada no es valida \n");
        }
        else if (decision_usuario == 26)
        {
            printf("\n\nGRACIAS POR UTILIZAR EL SISTEMA! \n\n");
            a++;
        }
        else
            printf("La opcion ingresada no es valida. Vuelcva a intentarlo \n");
    }  
}


