#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "colors.h"

// CONFIGURACION (COLORES DE LAS LETRAS).
#define MAX 80
#define ARCHIVO_USUARIOS "usuarios.dat"
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 5
#define MAX_INTENTOS 3
#define RED "\x1b[31m"
#define BG_ROSE "\x1B[48;2;255;151;203m"
#define MAGENTA "\x1b[35m"
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"

// MENU SISTEMA (AGENDA).
#define titulo1 "Calculo 2"
#define titulo2 "Programacion"
#define titulo3 "Fisica 1"

//=========> FUNCIONES PRINCIPALES.<==========

/* Estructura de cuentas de usuario */
struct usuario
{
    char nombre[MAX];
    char password[MAX];
};
typedef struct usuario Usuario;

// INTERFAS DE MENU.
void gotoxy(int, int);
void dibujar_cuadrado(int, int, int, int);
void centrarTexto(char *, int);
void desactivarMaximizar();

// INTERFAS DE OPCIONES.
void menuInicial();
void menuRegistrarUsuario();
void menuOpciones();
void menuAyuda();
void menuIniciarSesion();

// AGENDA
void menuSistema();
void menuIniciarMateria();
void materialesAdicionales();
void libros();
void examenes();
void reproductorDeMusica();

/* Funciones que manipulan el archivo de usuarios */
char insertarUsuario(Usuario usuario);
char existeUsuario(char nombreUsuario[], Usuario *usuario);
Usuario *obtenerUsuarios(int *);
char logear(char nombreUsuario[], char password[]);

int leerLinea(char *cad, int n);

void leerClave(char *password);

char linea[MAX];

// ===================================
// COMENZAMOS CON LA ESTRUCTURA MY NOTE
// ===================================

int main()
{

    PlaySound("introS.wav", NULL, SND_ASYNC); // ESTE ES EL SONIDO INICIAL
    Sleep(3);
    system("mode con: cols=80 lines=25"); // DEFINE LAS DIMENSIONES DE LA VENTANA DEL PROGRAMA A 80 COLUMNAS Y 25 FILAS.
    system("COLOR F0");                   // COLOR DEL FONDO Y DE LA LETRA  F(COLOR DEL FONDO) (BLANCO) / 0(COLOR LETRA)(NEGRO).
    desactivarMaximizar();
    menuInicial();
    gotoxy(3, 18);
    system("pause");

    return 0;
}

// ===================================
//           INTERFAZ DE MENU.
// ===================================

void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void dibujar_cuadrado(int xa, int yb, int xc, int yd)

// ? LINEA HORIZONTAL SUPERIOR (x,y)= (a,b) / LINEA HORIZONTAL INFERIOR (x,y)= (c,d).
// ? LINEA VERTICAL   IZQUIERDA(x,y)= (a,b) / LINEA DERECHA    VERTICAL (x,y)= (c,d).

{
    int i;
    for (i = xa; i <= xc; i++) //? LINEAS HORIZONTALES.
    {
        gotoxy(i, yb);
        printf("%c", 205); // LINEA SUPERIOR.
        gotoxy(i, yd);
        printf("%c", 205); // LINEA INFERIOR.
    }
    for (i = yb; i <= yd; i++) //? LINEAS VERTICALES.
    {
        gotoxy(xa, i);
        printf("%c", 186); // LINEA IZQUIERDA.
        gotoxy(xc, i);
        printf("%c", 186); // LINEA DERECHA.
    }
    gotoxy(xa, yb);
    printf("%c", 201); //? DIBUJOS  DE LOS VERTICES.
    gotoxy(xc, yd);
    printf("%c", 188);
    gotoxy(xc, yb);
    printf("%c", 187);
    gotoxy(xa, yd);
    printf("%c", 200);
}

void centrarTexto(char *texto, int y) // (RECIBIMOS UN TEXTO, COLOCAMOS LA POSICION).

{
    int tamanio = strlen(texto); // LONGITUD DEL TEXTO.
    gotoxy(40 - (tamanio / 2), y);
    printf(texto);
}

void desactivarMaximizar()
{
    HWND consoleWindow;
    consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

// ===================================
//           INTERFAZ DE OPCIONES.
// ===================================

void menuInicial()
{
	PlaySound("sonidos\\introS.wav", NULL, SND_ASYNC);
	Sleep(3);
    char repite = 1;
    int opcion[1];
    int num = 0;
    int i = 0;

    do
    {
        system("cls");

        dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
        dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
        centrarTexto("M Y   N O T E", 2);

        dibujar_cuadrado(1, 7, 77, 3);  // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 9, 77, 3);  // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 11, 77, 3); // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 13, 77, 3); // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 15, 77, 3); // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 17, 77, 3); // SE DIBUJA UN CUADRADO EN LAS OPCIONES

        centrarTexto("MENU PRINCIPAL", 4);
        centrarTexto("==============", 5);
        gotoxy(3, 8);
        printf("[1]  Registrar usuario nuevo");
        gotoxy(3, 10);
        printf("[2]  Ingresar al sistema");
        gotoxy(3, 12);
        printf("[3]  Ayuda");
        gotoxy(3, 14);
        printf("[4]  Configuraciones");
        gotoxy(3, 16);
        printf("[5]  Reproductor de musica\n");
        gotoxy(3, 18);
		printf("[6]  Salir\n");
        gotoxy(3, 20);
        printf(" \n   Ingrese su opcion:[ ]\b\b");
        leerLinea(linea, MAX);
        sscanf(linea, "%d", &opcion[i]);

        for (i = 0; i <= 5; i++)
        {

            if (opcion[i] == 1)
            {
                PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC); // CAMBIAR ESTE SONIDO POR UNO CORTO/amistoso al usuario
                Sleep(3);
                menuRegistrarUsuario();

                centrarTexto("CARGANDO (^_^.)", 21);
                PlaySound("sonidos\\op1.wav", NULL, SND_ASYNC);
                Sleep(3);
                for (num = 3; num <= 73; num++) // RECTANGULO ASCII 177
                {
                    gotoxy(num, 23);
                    printf("%c", 177);
                }
                for (num = 3; num <= 73; num++) // RECTANGULO ASCII 219
                {
                    gotoxy(num, 23);
                    printf("%c", 219);
                    Sleep(8); // MILESIMAS DE SEGUNDOS 1000 EQUIVALE 1 SEGUNDO. funcion hara pausa de 1 segundo, luego continuara la ejercucion.
                              // Nos servira para que vaya de apoco avanzando la barra ASCII 219.
                }
                gotoxy(3, 21);
                printf("                                                                           ");
                gotoxy(3, 23);
                printf("                                                                           ");
                break;
            }
            else if (opcion[i] == 2)
            {
                PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
                Sleep(1);
                menuIniciarSesion();

                centrarTexto("CARGANDO (^_^.)", 21);
                for (num = 3; num <= 73; num++) // RECTANGULO ASCII 177
                {
                    gotoxy(num, 23);
                    printf("%c", 177);
                }
                for (num = 3; num <= 73; num++) // RECTANGULO ASCII 219
                {
                    gotoxy(num, 23);
                    printf("%c", 219);
                    Sleep(35); // MILESIMAS DE SEGUNDOS 1000 EQUIVALE 1 SEGUNDO. funcion hara pausa de 1 segundo, luego continuara la ejercucion.
                               // Nos servira para que vaya de apoco avanzando la barra ASCII 219.
                }
                gotoxy(3, 21);
                printf("                                                                        ");
                gotoxy(3, 23);
                printf("                                                                        ");
                break;
            }
            else if (opcion[i] == 3)
            {
                PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
                Sleep(3);
                menuAyuda();
                break;
            }
			
            else if (opcion[i] == 4)
            {
                PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
                Sleep(3);
                menuOpciones();
                break;
            }
            
			else if (opcion[i] == 5)
			{
				PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
                Sleep(3);
				reproductorDeMusica();
				break;
			}
			
			else if (opcion[i] == 6)
            {
                repite = 0;

                centrarTexto("CARGANDO (^_^.)", 21);
                for (num = 3; num <= 73; num++) // RECTANGULO ASCII 177
                {
                    gotoxy(num, 23);
                    printf("%c", 177);
                }
                for (num = 3; num <= 73; num++) // RECTANGULO ASCII 219
                {
                    gotoxy(num, 23);
                    printf("%c", 219);
                    Sleep(15); // MILESIMAS DE SEGUNDOS 1000 EQUIVALE 1 SEGUNDO. funcion hara pausa de 1 segundo, luego continuara la ejercucion.
                               // Nos servira para que vaya de apoco avanzando la barra ASCII 219.
                }
                gotoxy(3, 21);
                printf("                                                                       ");
                gotoxy(3, 23);
                printf("                                                                       ");

                break;
            }
			else
            {
                break;
            }
        }
    } while (repite == 1);
}

void menuRegistrarUsuario()
{

    Usuario usuario;
    char nombreUsuario[MAX];
    char respuesta[MAX];
    char repite = 1;
    do
    {
        system("cls");
        dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
        dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
        centrarTexto("M Y   N O T E", 2);

        dibujar_cuadrado(1, 4, 77, 15); // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        gotoxy(3, 5);
        printf("INICIAR SESI\340N", 2);
        gotoxy(3, 6);
        printf("=================");
        gotoxy(3, 8);
        printf("Ingrese nombre de usuario: ");
        leerLinea(linea, MAX);
        sscanf(linea, "%s", nombreUsuario);

        /* Se verifica que el nombre de usuario no exista */
        if (!existeUsuario(nombreUsuario, &usuario))
        {
            strcpy(usuario.nombre, nombreUsuario);
            gotoxy(3, 9);
            printf("Ingrese la clave: ");
            leerLinea(usuario.password, MAX);

            /* Se inserta el usuario en el archivo de usuarios */
            if (insertarUsuario(usuario))
            {
                gotoxy(3, 12);
                printf("El usuario fue registrado satisfactoriamente! (^_^)");
            }
            else
            {
                gotoxy(3, 12);
                printf("Ocurrio un error al registrar el usuario (;_:)");
                gotoxy(3, 13);
                printf("Inténtelo mas tarde");
            }
        }
        else
        {
            gotoxy(3, 12);
            printf("El usuario \"%s\" ya ha sido registrado previamente (*_*;", usuario.nombre);
            gotoxy(3, 13);
            printf("No puede registrar dos usuarios con el mismo nombre de usuario. (;_:)");
        }
        gotoxy(3, 14);
        printf("Desea seguir registrando usuarios? [S/N]: ");
        leerLinea(respuesta, MAX);

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            repite = 0;
        }

    } while (repite == 1);
}

//=====================================WORKING============================================
void reproductorDeMusica()
{
    int opcion = 0;

    do
    {
        system("cls");
        dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
        dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
        centrarTexto("M Y   N O T E", 2);

        centrarTexto("BIENVENIDO A LA BIBLIOTECA DE MUSICA", 5);
        centrarTexto("[1] Musica Chill 1", 7);
        centrarTexto("[2] Musica Chill 2", 9);
        centrarTexto("[3] Musica Chill 3", 11);
        centrarTexto("[4] Musica Chill 4", 13);
        centrarTexto("[5] Reproducir todos los temas", 15);
        centrarTexto("[6] Salir al menu principal", 17);
        centrarTexto("Ingrese su opcion:[ ]\b\b", 19);

        leerLinea(linea, MAX);
        sscanf(linea, "%d", &opcion);
        system("cls");

        switch (opcion)
        {
        case 1:
            PlaySound("sonidos\\cute1.wav", NULL, SND_ASYNC);
            Sleep(3);
            break;
        case 2:
            PlaySound("sonidos\\cute2.wav", NULL, SND_ASYNC);
            Sleep(3);
            break;
        case 3:
            PlaySound("sonidos\\cute3.wav", NULL, SND_ASYNC);
			Sleep(3);
            break;
        case 4:
            PlaySound("sonidos\\cute4.wav", NULL, SND_ASYNC);
            Sleep(3);
            break;
        case 5:
            PlaySound("sonidos\\cute1.wav", NULL, SND_ASYNC);
			Sleep(3);
			PlaySound("sonidos\\cute2.wav", NULL, SND_ASYNC);
			Sleep(3);
			PlaySound("sonidos\\cute3.wav", NULL, SND_ASYNC);
			Sleep(3);
			PlaySound("sonidos\\cute4.wav", NULL, SND_ASYNC);
			Sleep(3);
            break;
        case 6:
            centrarTexto("|>| (.^_^.) *Esperamos que haya disfrutado de nuestra musica* (.^_^.) |<|", 15);
            PlaySound("sonidos\\sonido1.wav", NULL, SND_ASYNC);
            Sleep(1600);
            break;
        }

    } while (opcion != 6);
}
//=====================================WORKING============================================

void menuOpciones()
{
    int opcion = 0;

    do
    {
        system("cls");
        dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
        dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
        centrarTexto("M Y   N O T E", 2);

        centrarTexto("CONFIGURACION DE COLORES   ", 5);
        centrarTexto("[1] Rojo                   ", 7);
        centrarTexto("[2] Azul                   ", 9);
        centrarTexto("[3] Magenta                ", 11);
        centrarTexto("[4] Rosa                   ", 13);
        centrarTexto("[5] Negro                  ", 15);
        centrarTexto("[6] Salir al menu principal", 17);
        centrarTexto("Ingrese su opcion:[ ]\b\b", 19);

        leerLinea(linea, MAX);
        sscanf(linea, "%d", &opcion);
        system("cls");

        switch (opcion)
        {
        case 1:
            PlaySound("sonidos\\ROJO.wav", NULL, SND_ASYNC);
            centrarTexto(RED "", 13);
            break;
        case 2:
            PlaySound("sonidos\\AZUL.wav", NULL, SND_ASYNC);
            centrarTexto(BLUE "", 13);
            break;
        case 3:
            PlaySound("sonidos\\Magenta.wav", NULL, SND_ASYNC);
            centrarTexto(MAGENTA "", 13);
            break;
        case 4:
            PlaySound("sonidos\\ROSA.wav", NULL, SND_ASYNC);
            centrarTexto(ROSE "", 13);
            break;
        case 5:
            PlaySound("sonidos\\NEGRO.wav", NULL, SND_ASYNC);
            centrarTexto(BLACK "", 13);
            break;
        case 6:
            centrarTexto("|>| (.^_^.) *Disfrute de su color** (.^_^.) |<|", 15);
            PlaySound("sonidos\\SALIR.wav", NULL, SND_ASYNC);
            Sleep(1600);
            break;
        }

    } while (opcion != 6);
}

void menuAyuda()
{
    int opcion = 0;
    int cont = 0;

    do
    {
        system("cls");
        dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
        dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
        centrarTexto("M Y   N O T E", 2);
        dibujar_cuadrado(1, 4, 77, 14); // SE DIBUJA UN CUADRADO EN LAS OPCIONES

        centrarTexto(RED "[1] Qu3 es MyNote?          ", 5);
        centrarTexto(BLUE "[2] C0m0 cr3ar un4 cu3nta?  ", 7);
        centrarTexto(MAGENTA "[3] Ac3rca d3 n0sotr0s      ", 9);
        centrarTexto(YELLOW "[4] Volver al menu principal", 11);
        centrarTexto(BLACK "Ingrese su opcion:[ ]\b\b", 13);

        leerLinea(linea, MAX);
        sscanf(linea, "%d", &opcion);
        system("cls");
        int contador = 0;

        switch (opcion)
        {
        case 1:
            PlaySound("sonidos\\ingSonido.wav", NULL, SND_ASYNC);
            Sleep(3);
            break;

        case 2:
            PlaySound("sonidos\\AyudaSonido.wav", NULL, SND_ASYNC);
            Sleep(3);
            break;
        case 3:
            PlaySound("sonidos\\nosotros.wav", NULL, SND_ASYNC);

            while (contador < 10)
            {

                centrarTexto(ROSE "CREADO POR ESTUDIANTES DE LA:", 8);
                centrarTexto(RED "Universidad", 9);
                centrarTexto(GREEN "Nacional", 10);
                centrarTexto(YELLOW "General", 11);
                centrarTexto(BLUE "Sarmiento", 12);
                Sleep(120);
                system("cls");
                centrarTexto(ROSE "CREADO POR ESTUDIANTES DE LA:", 8);
                centrarTexto(GREEN "Universidad", 9);
                centrarTexto(YELLOW "Nacional", 10);
                centrarTexto(BLUE "General", 11);
                centrarTexto(RED "Sarmiento", 12);
                Sleep(120);
                system("cls");
                centrarTexto(ROSE "CREADO POR ESTUDIANTES DE LA:", 8);
                centrarTexto(YELLOW "Universidad", 9);
                centrarTexto(BLUE "Nacional", 10);
                centrarTexto(RED "General", 11);
                centrarTexto(GREEN "Sarmiento", 12);
                Sleep(120);
                system("cls");
                centrarTexto(ROSE "CREADO POR ESTUDIANTES DE LA:", 8);
                centrarTexto(BLUE "Universidad", 9);
                centrarTexto(RED "Nacional", 10);
                centrarTexto(GREEN "General", 11);
                centrarTexto(YELLOW "Sarmiento", 12);
                Sleep(120);
                system("cls");
                contador++;
            }
            centrarTexto(BLACK "", 13);
            break;
        case 4:
            centrarTexto(BLACK "|>| (.^_^.) **Gracias por conocernos** (.^_^.) |<|", 15);
            PlaySound("sonidos\\sonido1.wav", NULL, SND_ASYNC);
            Sleep(1600);
            break;
        }

    } while (opcion != 4);
}

void menuIniciarSesion()
{
    char nombreUsuario[MAX];
    char password[MAX];
    int intento = 0;
    int loginExitoso = 0;

    do
    {
        system("cls");
        dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
        dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
        centrarTexto("M Y   N O T E", 2);
        dibujar_cuadrado(1, 4, 77, 14); // SE DIBUJA UN CUADRADO EN LAS OPCIONES

        gotoxy(3, 5);
        printf("INGRESAR AL SISTEMA");
        gotoxy(3, 6);
        printf("===================");

        gotoxy(3, 7);
        printf("Ingrese el usuario : ");
        leerLinea(linea, MAX);
        sscanf(linea, "%s", nombreUsuario);

        gotoxy(3, 8);
        printf("Ingrese la clave: ");
        leerClave(password);

        if (logear(nombreUsuario, password))
        {
            loginExitoso = 1;
        }
        else
        {
            gotoxy(3, 12);
            printf(" Usuario y/o clave incorrectos   (=_=)  ");
            intento++;
            getchar();
        }
    } while (intento < MAX_INTENTOS && loginExitoso == 0);

    if (loginExitoso == 1)
    {
        menuSistema();
    }
    else
    {
        gotoxy(3, 13);
        printf("Ha sobrepasado el numero maximo de intentos permitidos (^_^.)");
        getchar();
    }
}

char insertarUsuario(Usuario usuario)
{
    FILE *archivo;
    char insercion = 0;

    /* Abre el archivo en modo de añadidura, para agregar datos al final. Si no existe es creado*/
    archivo = fopen(ARCHIVO_USUARIOS, "ab");

    if (archivo == NULL)
    {
        insercion = 0;
    }
    else
    {
        /* Registra el struct usuario en el archivo */
        fwrite(&usuario, sizeof(usuario), 1, archivo);
        insercion = 1;

        /* Cierra el archivo */
        fclose(archivo);
    }

    return insercion;
}

/* Retorna 1 si existe el nombre de usuario. Retorna el usuario buscado si existe */
char existeUsuario(char nombreUsuario[], Usuario *usuario)
{
    FILE *archivo;
    char existe;

    /* Abre el archivo en modo de lectura */
    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {
        existe = 0;
    }
    else
    {
        existe = 0;

        /* Lee secuencialmente del archivo de usuarios */
        fread(&(*usuario), sizeof(*usuario), 1, archivo);
        while (!feof(archivo))
        {
            if (strcmp((*usuario).nombre, nombreUsuario) == 0)
            {
                /* Encuentra un usuario del archivo con el nombre de usuario buscado */
                existe = 1;
                break;
            }

            fread(&(*usuario), sizeof(*usuario), 1, archivo);
        }

        /* Cierra el archivo*/
        fclose(archivo);
    }

    return existe;
}

Usuario *obtenerUsuarios(int *n)
{
    FILE *archivo;
    Usuario usuario;
    Usuario *usuarios; /* Vector dinámico de usuarios */
    int i;

    /* Abre el archivo en modo lectura */
    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {           /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        *n = 0; /* No se pudo abrir. Se considera n = 0 */
        usuarios = NULL;
    }
    else
    {

        fseek(archivo, 0, SEEK_END);                          /* Posiciona el cursor al final del archivo */
        *n = ftell(archivo) / sizeof(Usuario);                /* # de usuarios almacenados en el archivo. (# de registros) */
        usuarios = (Usuario *)malloc((*n) * sizeof(Usuario)); /* Se asigna memoria para todos los usuarios almacenados en el archivo */

        /* Se recorre el archivo secuencialmente */
        fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
        fread(&usuario, sizeof(usuario), 1, archivo);
        i = 0;
        while (!feof(archivo))
        {
            usuarios[i++] = usuario;
            fread(&usuario, sizeof(usuario), 1, archivo);
        }

        /* Cierra el archivo */
        fclose(archivo);
    }

    return usuarios;
}

/* Retorna 1 o 0 si el usuario y password son correctos para un usuario en particular */
char logear(char nombreUsuario[], char password[])
{
    FILE *archivo;
    char logeoExitoso;
    Usuario usuario;

    /* Abre el archivo en modo de lectura */
    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {
        logeoExitoso = 0;
    }
    else
    {
        logeoExitoso = 0;

        /* Lee secuencialmente del archivo de usuarios */
        fread(&usuario, sizeof(usuario), 1, archivo);
        while (!feof(archivo))
        {
            if (strcmp(usuario.nombre, nombreUsuario) == 0 && strcmp(usuario.password, password) == 0)
            {
                /* Encuentra un usuario del archivo con el nombre de usuario y password buscado */
                logeoExitoso = 1;
                break;
            }

            fread(&usuario, sizeof(usuario), 1, archivo);
        }

        /* Cierra el archivo*/
        fclose(archivo);
    }

    return logeoExitoso;
}

int leerLinea(char *cad, int n)
{
    int i, c;

    /* 1 COMPROBACIÓN DE DATOS INICIALES EN EL BUFFER */
    c = getchar();
    if (c == EOF)
    {
        cad[0] = '\0';
        return 0;
    }

    if (c == '\n')
    {
        i = 0;
    }
    else
    {
        cad[0] = c;
        i = 1;
    }

    /* 2. LECTURA DE LA CADENA */
    for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        cad[i] = c;
    }
    cad[i] = '\0';

    /*3. LIMPIEZA DEL BUFFER */
    if (c != '\n' && c != EOF) /* es un caracter */
        while ((c = getchar()) != '\n' && c != EOF)
            ;

    return 1;
}

void leerClave(char *password)
{
    char caracter;
    int i = 0;

    while (caracter = getch())
    {
        if (caracter == TECLA_ENTER)
        {
            password[i] = '\0';
            break;
        }
        else if (caracter == TECLA_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            if (i < MAX)
            {
                printf("*");
                password[i] = caracter;
                i++;
            }
        }
    }
}

// ===================================
//           AGENDA
// ===================================

void menuSistema()
{
    char repite = 1;
    int opcion = -1;
    int num = 0;

    do
    {
        system("cls");
        dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
        dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
        centrarTexto("M Y   N O T E", 2);

        dibujar_cuadrado(1, 7, 77, 3);  // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 9, 77, 3);  // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 11, 77, 3); // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        gotoxy(3, 8);
        printf("[1]  Catalogo de materia.");
        gotoxy(3, 10);
        printf("[2]  Material adicional.");
        gotoxy(3, 12);
        printf("[0]  ATRAS <===.");

        leerLinea(linea, MAX);
        sscanf(linea, "%d", &opcion);
        switch (opcion)
        {
        case 1:
            PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
            Sleep(3);

            // menuIniciarMateria();

            centrarTexto("CARGANDO (^_^.)", 21);
            // PlaySound("sonidos\\op1.wav", NULL, SND_ASYNC);
            Sleep(3);
            for (num = 3; num <= 73; num++) // RECTANGULO ASCII 177
            {
                gotoxy(num, 23);
                printf("%c", 177);
            }
            for (num = 3; num <= 73; num++) // RECTANGULO ASCII 219
            {
                gotoxy(num, 23);
                printf("%c", 219);
                Sleep(8); // MILESIMAS DE SEGUNDOS 1000 EQUIVALE 1 SEGUNDO. funcion hara pausa de 1 segundo, luego continuara la ejercucion.
                          // Nos servira para que vaya de apoco avanzando la barra ASCII 219.
            }
            gotoxy(3, 21);
            printf("                                                                           ");
            gotoxy(3, 23);
            printf("                                                                           ");

            break;
        case 2:
            PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
            Sleep(3);
            materialesAdicionales();

            centrarTexto("CARGANDO (^_^.)", 21);
            // PlaySound("sonidos\\op1.wav", NULL, SND_ASYNC);
            Sleep(3);
            for (num = 3; num <= 73; num++) // RECTANGULO ASCII 177
            {
                gotoxy(num, 23);
                printf("%c", 177);
            }
            for (num = 3; num <= 73; num++) // RECTANGULO ASCII 219
            {
                gotoxy(num, 23);
                printf("%c", 219);
                Sleep(8); // MILESIMAS DE SEGUNDOS 1000 EQUIVALE 1 SEGUNDO. funcion hara pausa de 1 segundo, luego continuara la ejercucion.
                          // Nos servira para que vaya de apoco avanzando la barra ASCII 219.
            }
            gotoxy(3, 21);
            printf("                                                                           ");
            gotoxy(3, 23);
            printf("                                                                           ");
            break;
        case 0:
            PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
            Sleep(3);
            repite = 0;
            break;
        }
    } while (repite == 1);
}

// void menuIniciarMateria();

void materialesAdicionales()
{
    char repite = 1;
    int opcion = -1;
    int num = 0;
    do
    {
        system("cls");
        dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
        dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
        centrarTexto("M Y   N O T E", 2);

        dibujar_cuadrado(1, 7, 77, 3);  // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 9, 77, 3);  // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        dibujar_cuadrado(1, 11, 77, 3); // SE DIBUJA UN CUADRADO EN LAS OPCIONES
        gotoxy(3, 8);
        printf("[1]  Examenes.");
        gotoxy(3, 10);
        printf("[2]  Material extra.");
        gotoxy(3, 12);
        printf("[0]  Salir.");

        leerLinea(linea, MAX);
        sscanf(linea, "%d", &opcion);
        switch (opcion)
        {
        case 1:
            PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
            Sleep(3);
            examenes();

            centrarTexto("CARGANDO (^_^.)", 21);
            PlaySound("sonidos\\op1.wav", NULL, SND_ASYNC);
            Sleep(3);
            for (num = 3; num <= 73; num++) // RECTANGULO ASCII 177
            {
                gotoxy(num, 23);
                printf("%c", 177);
            }
            for (num = 3; num <= 73; num++) // RECTANGULO ASCII 219
            {
                gotoxy(num, 23);
                printf("%c", 219);
                Sleep(8); // MILESIMAS DE SEGUNDOS 1000 EQUIVALE 1 SEGUNDO. funcion hara pausa de 1 segundo, luego continuara la ejercucion.
                          // Nos servira para que vaya de apoco avanzando la barra ASCII 219.
            }
            gotoxy(3, 21);
            printf("                                                                           ");
            gotoxy(3, 23);
            printf("                                                                           ");
            break;

        case 2:
            PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
            Sleep(3);
            libros();

            centrarTexto("CARGANDO (^_^.)", 21);
            PlaySound("sonidos\\op1.wav", NULL, SND_ASYNC);
            Sleep(3);
            for (num = 3; num <= 73; num++) // RECTANGULO ASCII 177
            {
                gotoxy(num, 23);
                printf("%c", 177);
            }
            for (num = 3; num <= 73; num++) // RECTANGULO ASCII 219
            {
                gotoxy(num, 23);
                printf("%c", 219);
                Sleep(8); // MILESIMAS DE SEGUNDOS 1000 EQUIVALE 1 SEGUNDO. funcion hara pausa de 1 segundo, luego continuara la ejercucion.
                          // Nos servira para que vaya de apoco avanzando la barra ASCII 219.
            }
            gotoxy(3, 21);
            printf("                                                                           ");
            gotoxy(3, 23);
            printf("                                                                           ");
            break;
        case 0:
            PlaySound("sonidos\\sonido2.wav", NULL, SND_ASYNC);
            Sleep(3);
            repite = 0;
            break;
        }
    } while (repite == 1);
}

void libros()
{
    char modificar;
    char caracter;

    system("cls");
    dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
    centrarTexto("M Y   N O T E", 2);

    FILE *archivoLB; // archivo de  LIBROS
    archivoLB = fopen("archivos\\LIBROS.dat", "r");
    if (archivoLB == NULL)
    {
        gotoxy(3, 4);
        printf("\n\nNo se puede abrir la Materia");
        getch();
        exit(0);
    }
    else
    {
        gotoxy(3, 4);
        printf("ABRIENDO  MATERIA");
        gotoxy(3, 5);
        printf("===============");
    }
    while (feof(archivoLB) == 0)
    {
        caracter = fgetc(archivoLB);

        printf("%c", caracter);
    }

    fclose(archivoLB);
    getch();
}

void examenes()
{
    char modificar;
    char caracter;

    system("cls");
    dibujar_cuadrado(0, 0, 78, 24); // SE DIBUJA EL CUADRO PRINCIPAL
    dibujar_cuadrado(1, 1, 77, 3);  // SE DIBUJA EL CUADRO DEL TITULO
    centrarTexto("M Y   N O T E", 2);

    FILE *archivoEX; // archivo de EXAMENES
    archivoEX = fopen("archivos\\EXAMENES.dat", "r");
    if (archivoEX == NULL)
    {
        gotoxy(3, 4);
        printf("\n\nNo se puede el archivo");
        getch();
        exit(0);
    }
    else
    {
        gotoxy(3, 4);
        printf("EXAMENES FINALES");
        gotoxy(3, 5);
        printf("===============");
    }
    while (feof(archivoEX) == 0)
    {
        caracter = fgetc(archivoEX);

        printf("%c", caracter);
    }

    fclose(archivoEX);
    getch();
}