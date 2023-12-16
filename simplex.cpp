#include <iostream>
#define MAX 10

using namespace std;

double funcion[MAX], restricciones[MAX + 1][MAX + MAX];
double independiente[MAX];

int ingresaDatos(int &nVar) {
    int nRest, a, i;
    cout << "*******  METODO SIMPLEX  *******\n\n";
    cout << " Numero de Variables: ";
    cin >> nVar;

    cout << "\nmax Z = (a1)X1+(a2)X2+ ...(an)Xn \n\n";

    for (a = 0; a < nVar; a++) {
        cout << " a" << a + 1 << " -> ";
        cin >> funcion[a];
    }

    cout << "\nNumero de restricciones: ";
    cin >> nRest;
    cout << "\n (a1)X1+(a2)X2+ ...(an)Xn <= b\n\n";

    for (i = 0; i < nRest; i++) {
        cout << "Restriccion " << i + 1 << "\n";
        for (a = 0; a < nVar; a++) {
            cout << " a" << a + 1 << " -> ";
            cin >> restricciones[i][a];
        }
        cout << " b" << i + 1 << " -> ";
        cin >> independiente[i];
    }
    return nRest;
}

double positiviza(double valor) {
    return (valor < 0) ? -valor : valor;
}

void lineas(string c, int n)
{

    for (int i = 0; i < 21 * n; i++) {
        cout << c;
    }
}

void tabla(int n, int nRest, int nVar) {
    cout << "\n\n"; lineas("-",nVar+nRest);
    cout << "\n\t\t  TABLA " << n;
    cout << "\n"; lineas("-",nVar+nRest); cout << endl;
    for (int i = 1; i <= nVar+nRest; i++) {
        cout << "X"<<i<<"\t\t";
    } cout << "b"<< endl;
    lineas("-",nVar+nRest);cout << "\n";
    for (int i = 0; i <= nRest; i++) {
        for (int j = 0; j <= nRest + nVar; j++) {
                cout << restricciones[i][j] << "\t\t";
        }
        cout << "\n";
    }
}

void simplex(int ni, int nRest, int nVar) {
    double maximo, temp, aux, menor;
    int columna, fila, cont, cuenta;

    maximo = positiviza(restricciones[nRest][0]);
    columna = 0;

    for (int j = 0; j <= nRest + nVar; j++) {
        if (restricciones[nRest][j] < 0) {
            temp = -1 * restricciones[nRest][j];
            if (maximo < temp) {
                maximo = temp;
                columna = j;
            }
        }
    }

    cont = 0;
    aux = 9999999999;
    menor = 9999999999;
    for (int i = 0; i < nRest; i++) {
        if (restricciones[i][columna] > 0)
            aux = restricciones[i][nRest + nVar] / restricciones[i][columna];
        else
            cont++;

        if (menor > aux) {
            menor = aux;
            fila = i;
        }
    }

    if (cont == nRest) {
        cout << "No hay solucion";
        exit(1);
    }

    cout << "\nElemento seleccionado: " << restricciones[fila][columna]
         << " , ubicado en: Fila " << fila + 1 << ", Columna " << columna + 1 << endl << endl;

    aux = restricciones[fila][columna];
    for (int j = 0; j <= (nRest + nVar); j++)
        restricciones[fila][j] = restricciones[fila][j] / aux;

    for (int i = 0; i <= nRest; i++) {
        if (i == fila)
            continue;
        else {
            aux = restricciones[i][columna] * -1;
            for (int k = 0; k <= nRest + nVar; k++) {
                restricciones[i][k] = (aux * restricciones[fila][k]) + restricciones[i][k];
            }
        }
    }

    tabla(ni, nRest, nVar);
    ni++;
    cuenta = 0;
    for (int j = 0; j < nRest + nVar; j++)
        if (restricciones[nRest][j] >= 0)
            cuenta++;

    if (cuenta == nRest + nVar)
        return;
    else
        simplex(ni, nRest, nVar);
}

int main() {
    int nRest, nVar, ni;
    ni = 1;

    nRest = ingresaDatos(nVar);

    for (int i = 0; i < nRest; i++)
        for (int j = 0; j < nRest; j++)
            if (i == j)
                restricciones[i][nVar + j] = 1;
            else
                restricciones[i][nVar + j] = 0;

    for (int i = 0; i < nRest; i++)
        restricciones[i][nVar + nRest] = independiente[i];

    for (int j = 0; j < nVar; j++)
        restricciones[nRest][j] = funcion[j] * -1;
    cout << endl;
    lineas("*",nVar);
    cout << "\n\tmax Z = ";

    for (int a = 0; a < nVar; a++) {
        if (a < nVar - 1) {
            cout << funcion[a] << "X" << a + 1 << " + ";
        } else
            cout << funcion[a] << "X" << a + 1 << "\t\t";
    }
    cout << "\n\tS.A.           \t\t\n";

    for (int i = 0; i < nRest; i++) {
        cout << "\t";
        for (int a = 0; a < nVar; a++) {
            if (a < nVar - 1) {
                cout << restricciones[i][a] << "X" << a + 1 << " + ";
            } else
                cout << restricciones[i][a] << "X" << a + 1;
        }
        cout << " <= " << independiente[i] << "\t\t";
        cout << endl;
    }
    lineas("*",nVar);

    tabla(ni, nRest, nVar);
    ni++;

    simplex(ni, nRest, nVar);

    cout << "\n\n Z = " << restricciones[nRest][nRest + nVar];

    return 0;
}
