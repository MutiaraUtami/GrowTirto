#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void tukarBaris(double** matriks, int N, int baris1, int baris2) {
    for (int i = 0; i < N + 1; i++) {
        swap(matriks[baris1][i], matriks[baris2][i]);
    }
}

void tampilkanMatriks(double** matriks, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            cout << setw(10) << matriks[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Metode eliminasi Gauss dengan partial pivoting yang lebih baik
void eliminasiGauss(double** matriks, int N) {
    for (int i = 0; i < N; i++) {
        // Cari elemen pivot terbesar di kolom i
        int maxBaris = i;
        for (int j = i + 1; j < N; j++) {
            if (fabs(matriks[j][i]) > fabs(matriks[maxBaris][i])) {
                maxBaris = j;
            }
        }

        // Tukar baris jika diperlukan
        if (maxBaris != i) {
            tukarBaris(matriks, N, i, maxBaris);
        }

        // Jika elemen diagonalnya 0 setelah pivoting, maka solusi tidak bisa ditemukan
        if (matriks[i][i] == 0) {
            cout << "Sistem tidak memiliki solusi unik (elemen diagonal nol setelah pivoting)." << endl;
            return;
        }

        // Lakukan eliminasi Gauss
        for (int j = i + 1; j < N; j++) {
            double ratio = matriks[j][i] / matriks[i][i];
            for (int k = 0; k < N + 1; k++) {
                matriks[j][k] -= ratio * matriks[i][k];
            }
        }
    }
}

// Substitusi balik setelah eliminasi Gauss
void substitusiBalik(double** matriks, int N) {
    double* hasil = new double[N];

    for (int i = N - 1; i >= 0; i--) {
        hasil[i] = matriks[i][N];
        for (int j = i + 1; j < N; j++) {
            hasil[i] -= matriks[i][j] * hasil[j];
        }
        hasil[i] /= matriks[i][i];
    }

    cout << "Solusi (dengan eliminasi Gauss dan substitusi balik):" << endl;
    for (int i = 0; i < N; i++) {
        cout << "x" << i + 1 << " = " << hasil[i] << endl;
    }

    delete[] hasil;
}

// Metode eliminasi Gauss-Jordan dengan partial pivoting yang lebih baik
void eliminasiGaussJordan(double** matriks, int N) {
    eliminasiGauss(matriks, N); // Lakukan eliminasi Gauss terlebih dahulu

    for (int i = N - 1; i >= 0; i--) {
        double divisor = matriks[i][i];
        for (int j = 0; j < N + 1; j++) {
            matriks[i][j] /= divisor;
        }

        for (int j = i - 1; j >= 0; j--) {
            double ratio = matriks[j][i];
            for (int k = 0; k < N + 1; k++) {
                matriks[j][k] -= ratio * matriks[i][k];
            }
        }
    }
}

// Menyelesaikan matriks setelah eliminasi Gauss-Jordan
void solusiGaussJordan(double** matriks, int N) {
    double* hasil = new double[N];
    for (int i = 0; i < N; i++) {
        hasil[i] = matriks[i][N];
    }

    cout << "Solusi (dengan eliminasi Gauss-Jordan):" << endl;
    for (int i = 0; i < N; i++) {
        cout << "x" << i + 1 << " = " << hasil[i] << endl;
    }

    delete[] hasil;
}

void masukkanEntriMatriks(double** matriks, int N) {
    cout << "Masukkan elemen matriks augmented. Format persamaan linear:\n";

    // Tampilkan format matriks secara simbolis
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "a" << i + 1 << j + 1 << " * x" << j + 1;
            if (j != N - 1) cout << " + ";
        }
        cout << " = b" << i + 1 << endl;
    }

    // Memasukkan nilai-nilai dari pengguna
    for (int i = 0; i < N; i++) {
        cout << "Baris " << i + 1 << ":" << endl;
        for (int j = 0; j < N; j++) {
            cout << "a" << i + 1 << j + 1 << ": ";
            cin >> matriks[i][j];
        }
        cout << "b" << i + 1 << ": ";
        cin >> matriks[i][N]; // Input elemen konstanta
    }
}

int main() {
    int N;

    cout << "Masukkan ukuran matriks (N): ";
    cin >> N;

    // Alokasi dinamis untuk matriks augmented
    double** matriks = new double*[N];
    for (int i = 0; i < N; i++) {
        matriks[i] = new double[N + 1];
    }

    // Masukkan entri matriks dari pengguna dengan ilustrasi
    masukkanEntriMatriks(matriks, N);

    cout << "\nMatriks awal:" << endl;
    tampilkanMatriks(matriks, N);

    int pilihan;
    cout << "Pilih metode eliminasi: " << endl;
    cout << "1. Eliminasi Gauss" << endl;
    cout << "2. Eliminasi Gauss-Jordan" << endl;
    cout << "Pilihan Anda: ";
    cin >> pilihan;

    if (pilihan == 1) {
        eliminasiGauss(matriks, N);
        cout << "\nMatriks setelah eliminasi Gauss:" << endl;
        tampilkanMatriks(matriks, N);
        substitusiBalik(matriks, N);
    } else if (pilihan == 2) {
        eliminasiGaussJordan(matriks, N);
        cout << "\nMatriks setelah eliminasi Gauss-Jordan:" << endl;
        tampilkanMatriks(matriks, N);
        solusiGaussJordan(matriks, N);
    } else {
        cout << "Pilihan tidak valid!" << endl;
        return 1;
    }

    // Dealokasi memori
    for (int i = 0; i < N; i++) {
        delete[] matriks[i];
    }
    delete[] matriks;

    return 0;
}
