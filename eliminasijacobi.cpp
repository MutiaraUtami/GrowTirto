#include <iostream>
#include <cmath>

using namespace std;

#define EPSILON 0.00001 // toleransi kesalahan
#define MAX_ITER 1000  // maksimal iterasi

int main() {
    int n = 3; // jumlah variabel (x1, x2, x3)
    float a[3][3], b[3]; // matriks koefisien dan vektor konstanta
    float x[3] = {0, 0, 0}; // nilai awal x1, x2, x3
    float x_new[3]; // nilai baru setelah iterasi
    int iter = 0;

    // Input koefisien dan konstanta
    cout << "Masukkan koefisien dan konstanta untuk persamaan:\n";
    for (int i = 0; i < n; i++) {
        cout << "Persamaan " << i + 1 << " (format: a1 a2 a3 b): ";
        for (int j = 0; j < n; j++) {
            cin >> a[i][j]; // koefisien
        }
        cin >> b[i]; // konstanta
    }

    // Jacobi Iteration
    cout << "\nIterasi\t x1\t\t x2\t\t x3\n";
    do {
        x_new[0] = (b[0] - a[0][1] * x[1] - a[0][2] * x[2]) / a[0][0];
        x_new[1] = (b[1] - a[1][0] * x[0] - a[1][2] * x[2]) / a[1][1];
        x_new[2] = (b[2] - a[2][0] * x[0] - a[2][1] * x[1]) / a[2][2];

        cout << iter + 1 << "\t " << x_new[0] << "\t " << x_new[1] << "\t " << x_new[2] << "\n";

        // Cek apakah konvergensi tercapai
        if (fabs(x_new[0] - x[0]) < EPSILON && fabs(x_new[1] - x[1]) < EPSILON && 
        fabs(x_new[2] - x[2]) < EPSILON) {
            break;
        }

        // Update nilai untuk iterasi selanjutnya
        x[0] = x_new[0];
        x[1] = x_new[1];
        x[2] = x_new[2];

        iter++;
    } while (iter < MAX_ITER);

    if (iter == MAX_ITER) {
        cout << "Tidak konvergen setelah " << MAX_ITER << " iterasi." << endl;
    } else {
        cout << "\nKonvergensi tercapai setelah " << iter + 1 << " iterasi." << endl;
        cout << "Hasil akhirnya: x1 = " << x_new[0] << ", x2 = " << 
        x_new[1] << ", x3 = " << x_new[2] << endl;
    }

    return 0;
}
