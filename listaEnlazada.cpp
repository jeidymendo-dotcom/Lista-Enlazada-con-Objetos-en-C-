#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Alumno {
public:
    string nombres;
    string apellidos;
    string carnet;
    string email;
    string telefono;
    float notas[5];

    float promedio() {
        float suma = 0;
        for (int i = 0; i < 5; i++) {
            suma += notas[i];
        }
        return suma / 5.0;
    }

    void mostrar() {
        cout << "\n========================" << endl;
        cout << "Nombres: " << nombres << endl;
        cout << "Apellidos: " << apellidos << endl;
        cout << "Carnet: " << carnet << endl;
        cout << "Email: " << email << endl;
        cout << "Telefono: " << telefono << endl;

        cout << "Notas: ";
        for (int i = 0; i < 5; i++) {
            cout << notas[i] << " ";
        }

        cout << endl;
        cout << "Promedio: " << promedio() << endl;
    }
};

class Nodo {
public:
    Alumno alumno;
    Nodo* siguiendo;

    Nodo(Alumno a) {
        alumno = a;
        siguiendo = NULL;
    }
};

class ListaEnlazada {
private:
    Nodo* inicio;

public:
    ListaEnlazada() {
        inicio = NULL;
    }

    void agregar(Alumno a) {
        Nodo* nuevo = new Nodo(a);

        if (inicio == NULL) {
            inicio = nuevo;
        } else {
            Nodo* aux = inicio;
            while (aux->siguiendo != NULL) {
                aux = aux->siguiendo;
            }
            aux->siguiendo = nuevo;
        }
    }

    void mostrarLista() {
        Nodo* aux = inicio;
        while (aux != NULL) {
            aux->alumno.mostrar();
            aux = aux->siguiendo;
        }
    }

    ~ListaEnlazada() {
        Nodo* aux;
        while (inicio != NULL) {
            aux = inicio;
            inicio = inicio->siguiendo;
            delete aux;
        }
    }
};

int main() {
    ListaEnlazada lista;
    char opcion;
    bool primerIngreso = true;

    do {
        Alumno alumno;

        if (!primerIngreso) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        primerIngreso = false;

        cout << "\n===== INGRESAR ALUMNO =====" << endl;

        cout << "Nombres: ";
        getline(cin, alumno.nombres);

        cout << "Apellidos: ";
        getline(cin, alumno.apellidos);

        cout << "Carnet: ";
        getline(cin, alumno.carnet);

        cout << "Email: ";
        getline(cin, alumno.email);

        cout << "Telefono: ";
        getline(cin, alumno.telefono);

        for (int i = 0; i < 5; i++) {
            do {
                cout << "Ingrese nota " << i + 1 << " (0 - 10): ";
                cin >> alumno.notas[i];

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[Error] Entrada invalida. Por favor, ingrese un numero entero o decimal." << endl;
                    continue;
                }

                if (alumno.notas[i] < 0 || alumno.notas[i] > 10) {
                    cout << "Nota invalida. Debe estar entre 0 y 10. Intente nuevamente." << endl;
                }

            } while (alumno.notas[i] < 0 || alumno.notas[i] > 10);
        }

        lista.agregar(alumno);

        cout << "\nDesea agregar otro alumno? (s/n): ";
        cin >> opcion;

    } while (opcion == 's' || opcion == 'S');

    cout << "\n===== LISTA DE ALUMNOS =====" << endl;
    lista.mostrarLista();

    return 0;
}