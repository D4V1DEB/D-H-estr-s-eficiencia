#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdlib> // Para usar la función rand()
#include <ctime> // Para usar la función time()

using namespace std;

// Potencia Modular
long long power(long long base, long long exponent, long long mod) {
	long long res = 1;
	while (exponent > 0) {
		if (exponent & 1)
			res = (res * base) % mod;
		base = (base * base) % mod;
		exponent >>= 1;
	}
	return res;
}

int main() {
	srand(time(0)); // Inicializar la semilla de la función rand()
	
	long long p = 104729; // número primo
	long long g = 3;  // número primitivo
	
	long long j = rand() % 1000000 + 1;  // clave privada de Jilmar
	long long d = rand() % 1000000 + 1; // clave privada de David
	
	// Jilmar y David calculan sus claves públicas
	long long A = power(g, j, p);
	long long B = power(g, d, p);
	
	// Inicio cronometro
	auto start = chrono::high_resolution_clock::now();
	
	// Repeticiones
	int num_reps = 30000000;
	
	for (int i = 0; i < num_reps; i++) {
		// Jilmar y David - clave compartida
		long long keyA = power(B, j, p);
		long long keyB = power(A, d, p);
	}
	
	// Fin cronómetro
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	
	cout<< "Tiempo de ejecución : " << duration.count() << " microsegundos" << endl;
	
	return 0;
}
