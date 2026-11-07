#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct Producto {
    string nombre;
    int cantidad = 0;
};

constexpr int UMBRAL_ALERTA = 5;
constexpr int MAX_STOCK = 100;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    vector<Producto> inventario = {
        {"papaya"},
        {"limón"},
        {"cilantro"}
    };

    int productosPorReponer = 0;

    cout << "==================================\n";
    cout << "     CONTROL DE INVENTARIO\n";
    cout << "==================================\n";

    for (auto& item : inventario) {
        cout << "\nIngrese las unidades disponibles de " << item.nombre << ": ";

        while (true) {
            if (cin >> item.cantidad) {
                bool entradaLimpia = true;
                while (cin.peek() != '\n' && cin.peek() != EOF) {
                    if (!isspace(cin.peek())) {
                        entradaLimpia = false;
                    }
                    cin.get();
                }

                if (!entradaLimpia) {
                    cout << "Papito en este programa solo recibimos números enteros\n";
                } else if (item.cantidad < 0 || item.cantidad > MAX_STOCK) {
                    cout << "El programita solo recibe número entre 0 y " << MAX_STOCK << "\n";
                } else {
                    break;
                }
            } else {
                cout << "Entrada inválida, verifica que sea un numero compa\n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            }

            cout << "Ingrese un número entre 0 al " << MAX_STOCK << ": ";
        }

        // Evaluador con alertas dedicadas para 0 y 100
        if (item.cantidad == 0) {
            cout << "----- ALERTA CRÍTICA PAPU -----: ¡SE AGOTÓ POR COMPLETO! Stock en cero para: " << item.nombre << endl;
            productosPorReponer++;
        } else if (item.cantidad == MAX_STOCK) {
            cout << "----- ALERTA DE TOPE PAPU -----: ¡BODEGA AL LÍMITE MÁXIMO! Stock a reventar (100 unidades) en: " << item.nombre << endl;
        } else if (item.cantidad <= UMBRAL_ALERTA) {
            cout << "----- ALERTA PAPU -----: Es necesario reponer inventario en: " << item.nombre << endl;
            productosPorReponer++;
        } else {
            cout << "Inventario suficiente para: " << item.nombre << endl;
        }
    }

    cout << "\n==================================\n";
    cout << "         RESUMEN FINAL\n";
    cout << "==================================\n";

    for (const auto& item : inventario) {
        cout << item.nombre << ": " << item.cantidad << " unidades." << endl;
    } 
    cout << "\nProductos que necesitan reposición: " << productosPorReponer << endl;

    return 0;
} //(Este ahora si es el definitivo, lo prometo)