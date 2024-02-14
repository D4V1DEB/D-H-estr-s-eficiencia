#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdlib> 
#include <ctime> 
#include <vector>

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

// Funcion para verificar si un numero es primo
bool is_prime(long long n) {
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (long long i = 5; i * i <= n; i += 6) {
		if (n % i == 0 || n % (i + 2) == 0) return false;
	}
	return true;
}

// Funcion para generar un numero primo aleatorio
long long generate_prime() {
	while (true) {
		long long n = rand() % 10000000 + 1; 
		if (is_prime(n)) return n; 
	}
}

// Funcion para verificar si un numero es primitivo
bool is_primitive(long long r, long long p) {
	vector<bool> last(p - 1, false);
	long long power = r;
	for (long long i = 0; i < p - 1; i++) {
		last[power - 1] = true;
		power = (power * r) % p;
	}
	for (bool b : last) if (!b) return false;
	return true;
}

// Funcion para generar un número primitivo dado un numero primo
long long generate_primitive(long long p) {
	for (long long r = 2; r < p; r++) {
		if (is_primitive(r, p)) return r;
	}
	return -1; 
}

int main() {
	srand(time(0)); 
	
	long long p = generate_prime(); // numero primo
	long long g = generate_primitive(p);  // numero primitivo
	
	long long j = rand() % 10000000 + 1;  // clave privada de Jilmar
	long long d = rand() % 10000000 + 1; // clave privada de David
	
	// Claves publicas
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
	
	// Fin cronometro
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	
	cout<< "Tiempo de ejecucion : " << duration.count() << " microsegundos" << endl;
	
	return 0;
}
