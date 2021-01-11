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

Ninos *CrearNino(int ID, char *nombre, char *usuario, char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant){

    //Se crea un nuevo nodo apartando el espacio en memoria
    Ninos *NuevoNino = (Ninos *) malloc(sizeof(Ninos));
    NuevoNino->siguiente = NULL;

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

void Agregar_Nino(Registro_Ninos *Lista, int ID, char *nombre, char *usuario, char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant){

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

    //Se crea el nuevo niño
    Ninos *Nuevo = CrearNino(ID, nombre, usuario, correo, fecha_n, edad, necesidades, cant);

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
                    scanf("%i", seleccion2);

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
                        scanf("%s", &nombre);
                        strcpy(puntero->nombre, nombre);
                        printf("Se modifico el nombre del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el nombre de usuario
                    else if (seleccion2 == 3 && a == 0)
                    {
                        char usuario[40];
                        printf("Ingrese el nuevo nombre de usuario del nino(a): \n");
                        scanf("%s", &usuario);
                        strcpy(puntero->usuario, usuario);
                        printf("Se modifico el nombre de usuario del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el correo
                    else if (seleccion2 == 4 && a == 0)
                    {
                        char correo[40];
                        printf("Ingrese el nuevo correo del nino(a): \n");
                        scanf("%s", &correo);
                        strcpy(puntero->correo, correo);
                        printf("Se modifico el correo del nino exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar la fecha de nacimiento
                    else if (seleccion2 == 5 && a == 0)
                    {
                        char fecha_n[40];
                        printf("Ingrese la nueva fecha de nacimiento del nino(a): \n");
                        scanf("%s", &fecha_n);
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
                            scanf("%s", &necesidad);
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
                int a = 0;
                int seleccion2;

                // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
                while(a == 0){

                    // Se consulta al usuario el dato que desea modificar
                    printf("Ingrese 1 para eliminar el ID del nino \nIngrese 2 para eliminar el nombre del nino \nIngrese 3 para eliminar el usuario del nino \nIngrese 4 para eliminar el correo del nino \nIngrese 5 para eliminar la fecha de nacimiento del nino \nIngrese 6 para eliminar la edad del nino \nIngrese 7 para eliminar las necesidades especiales del nino \nIngrese 8 para cancelar \n");
                    scanf("%i", seleccion2);

                    //En caso de que se desee eliminar la identificación
                    if (seleccion2 == 1)
                    {
                        puntero->ID = 0;
                        printf("Se elimino la identificacion del nino exitosamente \n");
                        a++;
                    }

                    //En caso de que se desee eliminar el nombre
                    else if (seleccion2 == 2 && a == 0)
                    {
                        strcpy(puntero->nombre, "");
                        printf("Se elimino el nombre del nino exitosamente \n");
                        a++;
                    }

                    //En caso de que se desee eliminar el nombre de usuario
                    else if (seleccion2 == 3 && a == 0)
                    {
                        strcpy(puntero->usuario, "");
                        printf("Se elimino el nombre de usuario del nino exitosamente \n");
                        a++;
                    }

                    //En caso de que se desee eliminar el correo
                    else if (seleccion2 == 4 && a == 0)
                    {
                        strcpy(puntero->correo, "");
                        printf("Se elimino el correo del nino exitosamente \n");
                        a++;
                    }

                    //En caso de que se desee eliminar la fecha de nacimiento
                    else if (seleccion2 == 5 && a == 0)
                    {
                        strcpy(puntero->fecha_nacimiento, "");
                        printf("Se elimino la fecha de nacimiento del nino exitosamente \n");
                        a++;
                    }

                    //En caso de que se desee eliminar la edad
                    else if (seleccion2 == 6 && a == 0)
                    {
                        puntero->edad = 0;
                        printf("Se elimino la edad del nino exitosamente \n");
                        a++;
                    }

                    //En caso de que se desee eliminar las necesidades espaciales
                    else if (seleccion2 == 7 && a == 0)
                    {
                        int cant;
                        cant = puntero->cant;
                        int i;
                        for ( i = 0; i < cant; i++)
                        {
                            strcpy(puntero->necesidades_especiales[i], "");
                        }
                        printf("Se elimino las necesidades especiales del nino exitosamente \n");
                        puntero->cant = 0;
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
                    {
                        printf("El numero de opcion ingresada no es valida \n");
                    } 
                } 
            }
        }
        puntero = puntero->siguiente;
    }

    // En caso de que no se encuentre un niño que coincida con el ID ingresado se notifica el error
    if (validacion == 0)
        printf("No se pudo modificar o eliminar la informacion pues la identificacion ingresada no corresponde a la de ningun nino registrado \n");
}
typedef struct ayudantes Ayudante;
typedef struct Registros2 Registro_Ayudantes;

struct ayudantes
{
    Ayudante *siguiente;
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

Ayudante *CrearAyudante(int ID, char *nombre, char *puesto, char funciones[6][60], char *fecha, int cant){

    //Se crea un nuevo nodo apartando el espacio en memoria
    Ayudante *NuevoAyudante = (Ayudante *) malloc(sizeof(Ayudante));
    NuevoAyudante->siguiente = NULL;

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
                    scanf("%i", seleccion2);

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
                        scanf("%s", &nombre);
                        strcpy(puntero->nombre, nombre);
                        printf("Se modifico el nombre del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el puesto
                    else if (seleccion2 == 3)
                    {
                        char puesto[40];
                        printf("Ingrese el nuevo puesto del ayudante: \n");
                        scanf("%s", &puesto);
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
                            scanf("%s", &funcion);
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
                        scanf("%s", &fecha);
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
                int a = 0;
                int seleccion2;

                // Este ciclo se repetirá hasta que el usuario ingrese un número de opción válido
                while(a == 0){

                    // Se consulta al usuario el dato que desea eliminar
                    printf("Ingrese 1 para eliminar el ID del ayudante \nIngrese 2 para eliminar el nombre del ayudante \nIngrese 3 para eliminar el puesto del ayudante \nIngrese 4 para eliminar las funciones del ayudante \nIngrese 5 para eliminar la fecha en que empezo a trabajar el ayudante \nIngrese 6 para cancelar \n");
                    scanf("%i", seleccion2);

                    // En caso de que se desee eliminar la identificación
                    if (seleccion2 == 1)
                    {
                        puntero->ID = 0;
                        printf("Se elimino la identificacion del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee eliminar el nombre
                    else if (seleccion2 == 2)
                    {
                        strcpy(puntero->nombre, "");
                        printf("Se elimino el nombre del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee eliminar el puesto
                    else if (seleccion2 == 3)
                    {
                        strcpy(puntero->puesto, "");
                        printf("Se elimino el puesto del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee eliminar las funciones
                    else if (seleccion2 == 4)
                    {
                        int cant = puntero->cant;
                        int i;
                        for ( i = 0; i < cant; i++)
                        {
                            strcpy(puntero->funciones[i], "");
                        }
                        printf("Se eliminaron las funciones del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee eliminar la fecha en que inició a trabajar
                    else if (seleccion2 == 5)
                    {
                        strcpy(puntero->fecha, "");
                        printf("Se elimino la fecha del ayudante exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee cancelar
                    else if (seleccion2 == 6)
                    {
                        printf("No se ha eliminado ningun dato \n");
                        a++;
                    }
                    
                    // En caso de que la opción ingresada no sea válida
                    else
                        printf("El numero de opcion ingresada no es valida \n");
                } 
            }
        }
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

typedef struct juguetes Juguete;

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
                        scanf("%s", &codigo);
                        strcpy(recorrido->codigo, codigo);
                        printf("Se ha modificado exitosamente el codigo del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar el nombre
                    else if (seleccion2 == 2)
                    {
                        char nombre[30];
                        printf("Ingrese el nuevo nombre del juguete: \n");
                        scanf("%s", &nombre);
                        strcpy(recorrido->nombre, nombre);
                        printf("Se ha modificado exitosamente el nombre del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar la descripción
                    else if (seleccion2 == 3)
                    {
                        char descripcion[60];
                        printf("Ingrese la nueva descripcion del juguete: \n");
                        scanf("%s", &descripcion);
                        strcpy(recorrido->descripcion, descripcion);
                        printf("Se ha modificado exitosamente la descripcion del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar la categoría
                    else if (seleccion2 == 4)
                    {
                        char categoria[15];
                        printf("Ingrese la nueva categoria del juguete: \n");
                        scanf("%s", &categoria);
                        strcpy(recorrido->categoria, categoria);
                        printf("Se ha modificado exitosamente la categoria del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar el rango de edad
                    else if (seleccion2 == 5)
                    {
                        char rango[15];
                        printf("Ingrese el nuevo rango de edad del juguete: \n");
                        scanf("%s", &rango);
                        strcpy(recorrido->rango, rango);
                        printf("Se ha modificado exitosamente el rango de edad del juguete \n");
                        return;
                    }

                    // En caso de que se desee modificar el costo
                    else if (seleccion2 == 6)
                    {
                        int costo;
                        printf("Ingrese el nuevo costo del juguete: \n");
                        scanf("%s", &costo);
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
        printf("Codigo: %s \n", recorrido->codigo);
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

//Agrega en la main esto:
void main(){
    Registro_Lugares *Lista_Lugares = (Registro_Lugares *) malloc(sizeof(Registro_Lugares));
    Lista_Lugares->Inicio = NULL;
    Lista_Lugares->Final = NULL;
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
    Imprimir_Ayudantes(Lista_Ayudantes);
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
    imprimirJuguete(raiz);
}
