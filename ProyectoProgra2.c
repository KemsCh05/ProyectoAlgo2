#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ninos Ninos;
typedef struct Registros Registro_Ninos;
typedef struct juguete_carta Juguete_Carta;
typedef struct Lista_Deseos Deseos;
typedef struct carta Carta_Santa;
typedef struct Registros5 Registro_Carta;

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


Ninos *CrearNino(int ID, char *nombre, char *usuario, char *lugar_residencia ,char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant){

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

void Agregar_Nino(Registro_Ninos *Lista, Registro_Lugares *Lista2, int ID, char *nombre, char *usuario, char *lugar_residencia ,char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant){

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
    //Recorrido a los lugares registrados para validar que el lugar de residencia del niño se encuentre registrado
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

void Imprimir_Ninos(Registro_Ninos *Lista){
    printf("\n\nLista de Ninos: \n\n");
    int contador = 1;
    Ninos *puntero = Lista->Inicio;

    // Ciclo para recorrer la lista e imprimir los datos de cada niño
    while (puntero != NULL)
    {

        // Se imprimen los datos
        printf("\n\n%i. Identificacion: %i \nNombre: %s \nUsuario: %s \nCorreo: %s \nFecha de nacimiento: %s \nEdad: %i \n", contador, puntero->ID, puntero->nombre, puntero->usuario, puntero->correo, puntero->fecha_nacimiento, puntero->edad);
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

Ninos *CrearNino(int ID, char *nombre, char *usuario, char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant);
void Agregar_Nino(Registro_Ninos *Lista, int ID, char *nombre, char *usuario, char *correo, char *fecha_n, int edad, char necesidades[10][60], int cant);
void modificar_datos_nino(Registro_Ninos *Lista, int ID, int seleccion);
void Imprimir_Ninos(Registro_Ninos *Lista);

typedef struct lugar Lugar;
typedef struct Registros3 Registro_Lugares;

struct lugar
{
    Lugar *siguiente;
    Lugar *anterior;
    char codigo[10];
    char nombre[30];
    int codigo_postal;
};

struct Registros3
{
    Lugar *Inicio;
    Lugar *Final;
};

Lugar *Crear_Lugar(char *codigo, char *nombre, int codigo_postal){
    
    //Se crea un nuevo nodo apartando el espacio en memoria
    Lugar *NuevoLugar = (Lugar *) malloc(sizeof(Lugar));
    NuevoLugar->siguiente = NULL;
    NuevoLugar->anterior = NULL;

    //Agregamos los datos
    strcpy(NuevoLugar->codigo, codigo); 
    strcpy(NuevoLugar->nombre, nombre); 
    NuevoLugar->codigo_postal = codigo_postal;

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
                    scanf("%i", seleccion2);

                    // En caso de que se desee modificar el codigo
                    if (seleccion2 == 1)
                    {
                        char codigo[10];
                        printf("Ingrese el nuevo codigo del lugar: \n");
                        scanf("%s", &codigo);
                        strcpy(puntero->codigo, codigo);
                        printf("Se modifico el codigo del lugar exitosamente \n");
                        a++;
                    }

                    // En caso de que se desee modificar el nombre
                    else if (seleccion2 == 2)
                    {
                        char nombre[30];
                        printf("Ingrese el nuevo nombre del lugar: \n");
                        scanf("%s", &nombre);
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
                puntero->anterior->siguiente = puntero->siguiente;
                puntero->siguiente->anterior = puntero->anterior;
                free(puntero);
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

typedef struct comportamiento Comportamiento;
typedef struct Registros4 Registro_Comportamiento;

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

            // Si el juguete a eliminar es el único en la carta del niño
            if (puntero2 == puntero->Inicio_Juguetes && puntero2->siguiente == NULL)
            {
                puntero->Inicio_Juguetes = NULL;
                puntero->contador_juguetes = 0;
                free(puntero2);
            }

            // Si el juguete a eliminar es el inicio de la lista pero no el único en la carta del niño
            else if (puntero2 == puntero->Inicio_Juguetes && puntero2->siguiente != NULL)
            {
                puntero->Inicio_Juguetes = puntero2->siguiente;
                puntero2->siguiente->anterior = NULL;
                puntero->contador_juguetes -= 1;
                free(puntero2);
            }

            // En cualquier otro caso
            else
            {
                puntero2->anterior->siguiente = puntero2->siguiente;
                puntero2->siguiente->anterior = puntero2->anterior;
                puntero->contador_juguetes -= 1;
                free(puntero2);
            }
            printf("Se ha eliminado %s de la carta de %s exitosamente \n", juguete, nombre);
            return;
        }
        puntero2 = puntero2->siguiente;
    }

    // En caso de que no se encuentre el juguete en la carta del niño
    printf("No fue posible eliminar el juguete pues no se encontro %s dentro de la carta de %s \n", juguete, nombre);
}



void main(){
     Registro_Ninos *Lista_Ninos = (Registro_Ninos *) malloc(sizeof(Registro_Ninos));
     Lista_Ninos->Inicio = NULL;
     Lista_Ninos->Final = NULL;
     char necesidades1[10][60], necesidades2[10][60], necesidades3[10][60], necesidades4[10][60], necesidades5[10][60], necesidades6[10][60], necesidades7[10][60], necesidades8[10][60], necesidades9[10][60], necesidades10[10][60];
    strcpy(necesidades1[0], "Nada");strcpy(necesidades2[0], "Nada");strcpy(necesidades3[0], "Nada");strcpy(necesidades4[0], "Nada");strcpy(necesidades5[0], "Nada");strcpy(necesidades6[0], "Nada");strcpy(necesidades7[0], "Nada");strcpy(necesidades8[0], "Nada");strcpy(necesidades9[0], "Nada");strcpy(necesidades10[0], "Nada");   
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 1, "Zach Wilson", "Z-01", "ZachKapono@gmail.com", "03/08/1999", 21, necesidades1, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 11, "Brandon Aiyuk", "B-11", "Baiyuk@gmail.com", "17/03/1998", 22, necesidades2, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 85, "George Kittle", "K-85", "GKittle46@gmail.com", "09/10/1993", 27, necesidades3, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 19, "Deebo Samuel", "D-19", "19problemz@gmail.com", "15/01/1996", 24, necesidades4, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 31, "Raheem Mostert", "M-31", "Mosball@gmail.com", "09/04/1992", 28, necesidades5, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 97, "Nick Bosa", "B-97", "nbsmallerbear@gmail.com", "23/10/1997", 23, necesidades6, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 54, "Fred Warner", "F-54", "fredwarner@gmail.com", "19/11/1996", 24, necesidades7, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 99, "Javon Kinlaw", "K-99", "Mookdawg@gmail.com", "03/10/1997", 23, necesidades8, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 57, "Dre Greenlaw", "D-57", "Dre57@gmail.com", "25/05/1997", 23, necesidades9, 1);
    Agregar_Nino(Lista_Ninos, Lista_Lugares, 22, "Jason Verrett", "V-22", "JVerrett@gmail.com", "18/06/1991", 29, necesidades10, 1);
    Imprimir_Ninos(Lista_Ninos);
}


