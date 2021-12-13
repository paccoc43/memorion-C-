#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void tablero(char **a, int fil, int col, string cadena, int zoom)
{
    //Funcion que muestra el tablero en pantalla
    int poscadena=0;
    int vueltas=0;
    char oculto='?';

    for (int i=0; i<fil; i++)
    {
        while (poscadena!=fil)
        {
            //Imprime la fila de caracteres
            cout << "  " << cadena[poscadena] << " ";
            poscadena++;
            if (poscadena==fil)
            {
                cout << endl;
            }
        }
        //Imprime la columna de caracteres
        cout << cadena[i] << " ";

        while (vueltas!=zoom)
        {
            for (int j=0; j<col; j++)
            {   
                for (int marcador=0; marcador<zoom; marcador++)
                {
                    if ((a[i][j]>=97) && (a[i][j]<=122))
                    {
                        
                        /*for (int x=0; x<zoom; x++)
                        {
                            cout << a[i][j];  
                        }*/
                        
                        cout << a[i][j];
                        
                    }
                    else if ((a[i][j]>=65) && (a[i][j]<=90))
                    {
                        /*for (int x=0; x<zoom; x++)
                        {
                            cout << oculto;  
                        }*/
                        //Imprime el contenido de la matriz oculto
                        cout << oculto;
                        
                    }
                }
                cout << " ";
            }
            //cout << endl; //Utilizar con zoom
            vueltas++;
        }
        vueltas=0;
        cout << endl;
    }
    cout << endl;
}

void insertaElementos(char **a, int fil, int col, string cadena)
{
    //Crea un string aleatorio y lo inserta en la matriz
    string cadenautil=""; //Cadena que se utilizara para crear la cadena aleatoria
    string cadenaaleatoria;
    int caracter=0; //Posicion aleatoria de la cadena util
    int inserta=0;  //Contador de caracteres insertados en la matriz

    for (int h=0; h<(fil*col)/2; h++)
    {
        cadenautil=cadenautil+cadena[h]+cadena[h];  //Inserta los caracteres repetidos
    }

    for (int k=0; k<(fil*col); k++)
    {
        caracter = rand() % cadenautil.length();    //Escoge una posicion aleatoria del string cadenautil y la guarda
        cadenaaleatoria = cadenaaleatoria + cadenautil[caracter];   //Almacena el caracter en el string cadenaaleatoria
        cadenautil.erase(cadenautil.begin() + caracter);    //Elimina el caracter seleccionado anteriormente
    }

    //Recorre la matriz y inserta los caracteres de cadenaaleatoria
    for (int i=0; i<fil; i++)
    {
        for (int j=0; j<col; j++)
        {
            // Inserta los caracteres de cadenaaleatoria en la matriz de forma ordenada
            a[i][j]=cadenaaleatoria[inserta];
            inserta++;
        }
    }
}

void muestraTablero (char **a, int fil, int col)
{
    // Herramienta que muestra el tablero con los caracteres sin ocultar
    for (int i=0; i<fil; i++)
    {
        for (int j=0; j<col; j++)
        {
            cout << "[ " << a[i][j] << " ]";
        }
        cout << endl;
    }
    cout << endl;
}

void giracartas (char **a, char &fil1, char &col1, char &fil2, char &col2, int &acierto, int &fallo, char &pos1, char &pos2, string cadena, int tamfil, int tamcol, int zoom)
{
    if ((fil1>=65) && (fil1<=90) && (col1>=65) && (col1<=90))
    {
        fil1=fil1-65;
        col1=col1-65;
        pos1 = a[fil1][col1];
        if ((a[fil1][col1]>=65) && (a[fil1][col1]<=90))
        {
            a[fil1][col1]=pos1+32;
        }
        tablero(a, tamfil, tamcol, cadena, zoom);
        sleep(2);
    }
    if ((fil2>=65) && (fil2<=90) &&(col2>=65) && (col2<90))
    {
        fil2=fil2-65;
        col2=col2-65;
        pos2 = a[fil2][col2];
         if ((a[fil2][col2]>=65) && (a[fil2][col2]<=90))
        {
            a[fil2][col2]=pos2+32;
        }
        tablero(a, tamfil, tamcol, cadena, zoom);
        sleep(2);
    }
    // Gira las cartas, comprueba si son iguales y si se han descubierto anteriormente
    if ((pos1==pos2) && (pos1>=65) && (pos1<=90) && (pos2>=65) && (pos2<=90))
    {
        acierto++;
        pos1=100;
        pos2=100;
    }
    else if ((pos1!=pos2) && (pos1>=65) && (pos1<=90) && (pos2>=65) && (pos2<=90))
    {
        a[fil1][col1]=pos1;
        a[fil2][col2]=pos2;
        fallo--;
        pos1=100;
        pos2=100;
    }
}


/*void memoriabot (char **a, int fil, int col, char fil1, char col1, char fil2, char col2)
{
    // Comprueba si has acertado 
    int pos1,pos2;
    int resul1, resul2;
    for(int i=0; i<fil; i++)
    {
        for (int j=0; j<col; j++)
        {
            if(a[fil1][col1]==a[i][j])
            {
                resul1=a[i][j];
                acierto[i][j]=false;
                // if(acierto==false) seguir por aqui
            }
            if (col1 == a[i][j])
            {
                resul2=a[i][j];
            }
            if ((fil1==resul1) && (col1==resul1) && (fil2==resul2) && (col2==resul2))
            {
                a[i][j]=0;
            }
        }
    }
}
*/
int main()
{
    srand(time(NULL));
    string cadena = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int num = rand() % 4;
    int tamfil = 3;
    int tamcol = 4;
    char fil1, col1, fil2, col2, pos1, pos2;
    char **array;
    
    int acierto = 0;
    int fallo = 10;
    int zoom=1;
    
    time_t tiempo;
    
    while(((tamfil*tamcol) % 2 != 0) || (tamfil!=tamcol) || (tamfil<0) || (tamcol<0))
    {
        // Pide el tamaño del tablero que tendra que ser par y igual
        cout << "Indica el tamaño del tablero" << endl;
        cout << "Inserta un numero de filas par" << endl;
        cin >> tamfil;
        cout << "Inserta un numero de columnas igual a filas" << endl;
        cin >> tamcol;
    }

    
    array = new char *[tamfil];
    //acierto = new bool *[tamfil];
    //Asignamos memoria a las filas del array
    for (int i = 0; i < tamfil; i++)
    {
        array[i] = new char[tamcol];
        //acierto[i] = new bool[tamcol];
        //Asignamos memoria a las columnas del array
    }

    insertaElementos(array, tamfil, tamcol, cadena);//Inserta parejas de caracteres en la matriz de forma aleatoria

    tiempo = time(nullptr);// iniciamos el contador

    while ((acierto!=(tamfil*tamcol)/2) && (fallo>0))
    {
        cout << endl;

        muestraTablero(array, tamfil, tamcol);//Muestra el tablero sin ocultar
        sleep(0);

        cout << "te quedan [" << fallo << "] intentos" << endl;        
        tablero(array, tamfil, tamcol, cadena, zoom);//Muestra el tablero oculto
        
        //Pedimos la primera posicion del tablero
        cout << "Introduce la primera posicion" << endl;
        cin >> fil1;
        cin >> col1;
        giracartas(array, fil1, col1, fil2, col2, acierto, fallo, pos1, pos2, cadena, tamfil, tamcol, zoom);//Comprueba si las cartas que elegimos son pareja

        // Pedimos la segunda posicion del tablero 
        cout << "Introduce la segunda posicion" << endl;
        cin >> fil2;
        cin >> col2;
        giracartas(array, fil1, col1, fil2, col2, acierto, fallo, pos1, pos2, cadena, tamfil, tamcol, zoom);
        //memoriabot(array, tamfil, tamcol, fil1, col1, fil2, col2, acierto);//Comprueba si es una pareja
    }

    //Calcula el tiempo que dura la partida
    int segundos = difftime(time(nullptr), tiempo);
    int minutos = segundos/60;
    int horas = minutos/60;

    cout << horas << " horas " << minutos%60 
     << " minutos " << segundos%60 << " segundos";
    // system("CLS");

    for (int i = 0; i < tamfil; i++)
    {
        delete (array[i]);
        //delete (acierto[i]);
    }
    delete array;
    //delete acierto;
    //Elimina la memoria reservada para el array
    return 0;
}