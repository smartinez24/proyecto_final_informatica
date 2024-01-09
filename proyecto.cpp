// Software de gestion para la biblioteca de la ETSE-UV
// Carlos Santiago Martinez Torres E Ivan Morcillo Ciscar
// Grupo G4 de laboratorio

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int maximo = 3000; // Declaro un maximo de 3000 libros para el vector

// Defino la estructura que contiene la informacion de un libro
struct Libro {
    string titulo;
    string autor;
    string isbn;
    string editorial;
    int anio_edicion;
    int num_paginas;
    string fecha_alta;
    int cantidad_ejemplares;
    int cantidad_prestados;
};

typedef Libro vector_libros[maximo]; // Defino un tipo de vector de tipo Libro

void LeerLibrosExistentes(ifstream&, vector_libros&, int&);
int Menu();
void AltaLibro(vector_libros&, int&, Libro);
void BajaLibro(vector_libros&, const int total_libros, Libro);
void MostrarInformacionLibro(const vector_libros info_libro, const int total_libros, Libro);
void PrestarLibro(vector_libros&, const int total_libros, Libro);
void EscribirFicheroLibros(ofstream&, const vector_libros info_libros, const int total_libros);

int main () 
{
    ifstream g_leer; // Variable para leer los libros del fichero
    ofstream g_escribir; // Variable para escribir los libros, una vez trabajado el programa
    Libro libro;
    vector_libros info_libros;
    int total_libros;
    int opcion;

    LeerLibrosExistentes(g_leer, info_libros, total_libros); // Funcion para leer los libros del ficheo existente

    do 
    {
        opcion = Menu(); // La funcion menu me retorna un entero, que es la opcion del usuario
        switch(opcion)
        {
            case 1:
                {
                    AltaLibro(info_libros, total_libros, libro);
                    break;
                }

            case 2:
                {
                    BajaLibro(info_libros, total_libros, libro);
                    break;
                }

            case 3: 
                {
                    MostrarInformacionLibro(info_libros, total_libros, libro);
                    break;
                }

            case 4:
                {
                    PrestarLibro(info_libros, total_libros, libro);
                    break;
                }

            case 5:
                {
                    EscribirFicheroLibros(g_escribir, info_libros, total_libros);
                    cout << "Has seleccionado salir del programa de gestion. ";
                    cout << "Revisa la carpeta y verifica el nuevo archivo .txt creado." << endl;
                    system("clear");
                    break;
                }

            default:
                {
                    cout << "Has seleccionado una opcion incorrecta." << endl;
                    break;
                }            
        }
    } 
    while (opcion != 5);

    return 0;
}

void LeerLibrosExistentes(ifstream& g, vector_libros& info_libros, int& total_libros)
{
    total_libros=0; // Para iniciar, declaro que tengo 0 libros

    g.open("libros_biblioteca.txt");

    if(!g)
        cout << "Error abriendo el fichero." << endl;
    
    else 
        {
            if (total_libros<maximo)
                {
                    while (getline(g, info_libros[total_libros].titulo, ';')) // Cada vez que se lea la informacion de un libro, se sumara una cantidad al total de libros
                        {
                            getline(g, info_libros[total_libros].autor, ';');
                            getline(g, info_libros[total_libros].isbn, ';');
                            getline(g, info_libros[total_libros].editorial, ';');
                            g >> info_libros[total_libros].anio_edicion;
                            g.ignore();
                            g >> info_libros[total_libros].num_paginas;
                            g.ignore();
                            getline(g, info_libros[total_libros].fecha_alta, ';');
                            g >> info_libros[total_libros].cantidad_ejemplares;
                            g.ignore();
                            g >> info_libros[total_libros].cantidad_prestados;
                            g.ignore();
                            total_libros++;
                        }
                    system("clear");
                }
            else 
                cout << "Tienes todos los espacios ocupados. No puedes dar de alta a más libros." << endl;
            
            g.close(); // Una vez leidos los libros y cargados al vector, cierro el fichero
        }

    if (total_libros<maximo) // Mensaje para comprobar la cantidad de espacios disponibles para libros, si se cumple la condicion
        cout << "Hay un total de " << total_libros << " libros. Quedan " << maximo-total_libros << " espacios para otros libros." << endl;
}

int Menu()
{
    int opcion;
    cout << "\n--- MENU ---" << endl;
    cout << "Este menu esta pensado para la biblioteca de la ETSE. Por favor introduce una de las siguientes opciones: \n" << endl;
    cout << "1. - Alta nuevo libro." << endl;
    cout << "2. - Baja libro existente." << endl;
    cout << "3. - Mostrar informacion de un ejemplar." << endl;
    cout << "4. - Prestar libro." << endl;
    cout << "5. - Salir del programa de gestión.\n" << endl;

    cout << "Escribe tu opcion: ";
    cin >> opcion;

    return opcion;
}

void AltaLibro(vector_libros& info_libro, int& total_libros, Libro l)
{
    bool existe=false; // Creo una variable booleana para saber si el ISBN existe o no

    cin.ignore(); // Evito la entrada del cin anterior del menu

    cout << "Por favor introduce el titulo del libro: ";
    getline(cin, l.titulo);

    cout << "Por favor introduce el autor del libro: ";
    getline(cin, l.autor);

    cout << "Por favor introduce el ISBN del libro: ";
    getline(cin, l.isbn);

    cout << "Por favor introduce el editorial del libro: ";
    getline(cin, l.editorial);

    cout << "Por favor introduce el anio de edicion del libro: ";
    cin >> l.anio_edicion;

    cout << "Por favor introduce el numero de paginas del libro: ";
    cin >> l.num_paginas;

    cin.ignore();

    cout << "Por favor introduce la fecha de alta del libro en el siguiente formato MM/DD/AAAA: ";
    getline(cin, l.fecha_alta);

    cout << "Por favor introduce la cantidad de ejemplares actuales del libro en la biblioteca: ";
    cin >> l.cantidad_ejemplares;

    cout << "Por favor introduce la cantidad de libros prestados. En caso de no haber libros prestados, escribe 0: ";
    cin >> l.cantidad_prestados;

    cin.ignore();

    for (int i=0; i<=total_libros; i++)
        {
            if(info_libro[i].isbn == l.isbn) // Si existe el ISBN, hace la operacion y termina la funcion
                {
                    existe = true;
                    info_libro[i].cantidad_ejemplares++;
                    cout << "Se ha sumado una cantidad a cantidad de ejemplares del libro: \'" << info_libro[i].titulo << "\'." << endl;
                    system("clear");
                }
        }

    if (existe==false) // Si no existe el ISBN, lo agrega al vector y suma una cantidad al total de libros
        {
            cout << "El libro \'" << l.titulo << "\' no existe en la biblioteca. Sera agregado al vector." << endl;
            info_libro[total_libros].titulo = l.titulo;
            info_libro[total_libros].autor = l.autor;
            info_libro[total_libros].isbn = l.isbn;
            info_libro[total_libros].editorial = l.editorial;
            info_libro[total_libros].anio_edicion = l.anio_edicion;
            info_libro[total_libros].num_paginas = l.num_paginas;
            info_libro[total_libros].fecha_alta = l.fecha_alta;
            info_libro[total_libros].cantidad_ejemplares = l.cantidad_ejemplares;
            info_libro[total_libros].cantidad_prestados = l.cantidad_prestados;
            total_libros++;
        }          
}

void BajaLibro(vector_libros& info_libro, const int total_libros, Libro l)
{
    bool existe=false; // Creo una variable booleana para saber si el ISBN existe o no

    cin.ignore(); // Evito la entrada del cin anterior del menu

    cout << "Por favor introduce el ISBN del libro que quieres dar de baja: ";
    getline(cin, l.isbn);

    for (int i=0; i<=total_libros; i++)
        if (info_libro[i].isbn == l.isbn) // Si existe el ISBN, hace la operacion y termina la funcion
            {
                existe = true;
                cout << "Si existe el libro." << endl;
                cout << "Calculando..." << endl;

                if(info_libro[i].cantidad_ejemplares==0) // En caso de que ya estuviera en la biblioteca, pero sin ejemplares disponibles
                    {
                        cout << "Ya no hay ejemplares de este libro." << endl;
                    }

                else if(info_libro[i].cantidad_ejemplares>=1) // Si hay ejemplares disponibles, resta una cantidad
                    {
                        info_libro[i].cantidad_ejemplares = info_libro[i].cantidad_ejemplares - 1;
                        cout << "Se ha restado una cantidad de cantidad de ejemplares del libro \'" << info_libro[i].titulo << "\'." << endl;
                        system("clear");
                    }         
            }

    if(existe==false) // Si no existe el ISBN, da un mensaje de alerta
        cout << "No se ha encontrado el libro con el ISBN indicado." << endl;        
}

void MostrarInformacionLibro(const vector_libros info_libro, const int total_libros, Libro l)
{
    bool existe=false; // Creo una variable booleana para saber si el ISBN existe o no

    cin.ignore(); // Evito la entrada del cin anterior del menu

    cout << "Por favor introduce el ISBN del libro que quieres ver: ";
    getline(cin, l.isbn);

    for (int i=0; i<=total_libros; i++)
        {
            if (info_libro[i].isbn == l.isbn) // Si existe el ISBN, muestra la informacion del libro
            {
                existe = true;
                cout << "Titulo: " << info_libro[i].titulo << endl;
                cout << "Autor: " << info_libro[i].autor << endl;
                cout << "ISBN: " << info_libro[i].isbn << endl;
                cout << "Editorial: " << info_libro[i].editorial << endl;
                cout << "Anio de edicion: " << info_libro[i].anio_edicion << endl;
                cout << "Numero de paginas: " << info_libro[i].num_paginas << endl;
                cout << "Fecha de alta: " << info_libro[i].fecha_alta << endl;
                cout << "Cantidad de ejemplares: " << info_libro[i].cantidad_ejemplares << endl;
                cout << "Cantidad de libros prestados: " << info_libro[i].cantidad_prestados << endl;
            }
        }

    if(existe==false) // Si no existe el ISBN, dará un mensaje de alerta
        cout << "No se ha encontrado el libro con el ISBN indicado." << endl;        
}

void PrestarLibro(vector_libros& info_libro, const int total_libros, Libro l)
{
    bool existe=false; // Creo una variable booleana para saber si el ISBN existe o no

    cin.ignore(); // Evito la entrada del cin anterior del menu

    cout << "Por favor introduce el ISBN del libro que quieres prestar: ";
    getline(cin, l.isbn);

    for (int i=0; i<=total_libros; i++)
        if (info_libro[i].isbn == l.isbn) // Si existe el ISBN, mostrara la posicion en el vector
            {
                existe = true;
                cout << "Si existe el libro. Esta en la posicion " << i << " del vector." << endl;
                cout << "Calculando..." << endl;

                if(info_libro[i].cantidad_ejemplares==0)
                    {
                        cout << "No hay ejemplares disponibles para prestar." << endl;
                    }

                else if(info_libro[i].cantidad_ejemplares>=1) // Si hay ejemplares para prestar, resta una cantidad y suma otra a prestados
                    {
                        info_libro[i].cantidad_ejemplares = info_libro[i].cantidad_ejemplares - 1;
                        cout << "Se ha restado una cantidad de cantidad de ejemplares del libro \'" << info_libro[i].titulo << "\'." << endl;
                        info_libro[i].cantidad_prestados++;
                        cout << "Se ha sumado una cantidad a cantidad de libros prestados." << endl;
                        system("clear");
                    }         
            }
    if(existe==false)
        cout << "No se ha encontrado el libro con el ISBN indicado." << endl;
}

void EscribirFicheroLibros(ofstream& g, const vector_libros info_libros, const int total_libros)
{
    g.open("libros_biblioteca.txt");

    if(!g)
        cout << "Error abriendo el fichero" << endl;
    
    else 
        {
            for (int i=0; i<total_libros; i++)
                {
                    g << info_libros[i].titulo << ";" << info_libros[i].autor << ";" << info_libros[i].isbn << ";" << info_libros[i].editorial << ";" << info_libros[i].anio_edicion << ";" << info_libros[i].num_paginas << ";" << info_libros[i].fecha_alta << ";" << info_libros[i].cantidad_ejemplares << ";" << info_libros[i].cantidad_prestados << endl;
                }
            cout << "Se ha creado el archivo nuevo exitosamente." << endl;
            g.close();  
        }
}