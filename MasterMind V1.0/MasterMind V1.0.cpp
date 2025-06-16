

#include <iostream>
#include <cstdlib>
#include <ctime>

//Funciones
char generarLetraAleatoria() {
	return 'A' + rand() % 8; // Genera un número entre 0 y 7, luego se suma a 'A'
}
bool comprobarLetra(char codigoAdivinador[]) {
	char rangoLetras[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' }; //Rango de letras disponibles.
	bool todasEncontradas = true;

	for (int i = 0; i < 4; ++i) {
		bool encontrada = false;
		for (char l : rangoLetras) {
			if (toupper(codigoAdivinador[i]) == l) {
				encontrada = true;
				break;
			}
		}
		if (!encontrada) {
			todasEncontradas = false;
			break;
		}
	}
	return todasEncontradas;
}
char* ponerMayuscula(char codigoAdivinador[]) {
	for (int i = 0; i < 4; i++) {
		codigoAdivinador[i] = toupper(codigoAdivinador[i]);
	}
	return codigoAdivinador;
}
int Calcularesultados(char codigoAdivinador[], char codigoPensador[], int LARGO_CODIGO, int resultados[]) {
	resultados[0] = 0; // Coincidencias exactas
	resultados[1] = 0; // Coincidencias parciales

	for (int i = 0; i < LARGO_CODIGO; i++) {
		if (codigoAdivinador[i] == codigoPensador[i]) {
			resultados[0]++; // Coincidencia exacta
		}
		else {
			for (int j = 0; j < LARGO_CODIGO; j++) {
				if (i != j && codigoAdivinador[i] == codigoPensador[j]) {
					resultados[1]++; // Coincidencia parcial
					break;
				}
			}
		}
	}
	return resultados[0] + resultados[1]; // Retorna la suma de coincidencias
}

int main()
{
	std::cout << "MasterMind V1.0" << std::endl;
	std::cout << "" << std::endl;

	std::cout << "- Dispones de 10 intentos para adivinar el codigo." << std::endl;
	std::cout << "- El codigo generado es desde la A hasta la H, incluidas" << std::endl;
	std::cout << "" << std::endl;

	// Variables
	const int MAX_INTENTOS = 10; //Cantidad máxima de intentos.
	const int LARGO_CODIGO = 4; //El largo de los códigos.
	char codigoPensador[LARGO_CODIGO]; //El código secreto a adivinar.
	char codigoAdivinador[LARGO_CODIGO]; //El código ingresado por el jugador.
	int resultados[] = { 0,0 };

	// Inicialización del código secreto (ejemplo: "ABCD")
	srand(time(0));
	for (int i = 0; i < LARGO_CODIGO; i++)
	{
		codigoPensador[i] = generarLetraAleatoria();
	}

	// Bucle principal del juego
	for (int i = 0; i < MAX_INTENTOS; i++){
		std::string valor(codigoPensador, 4); // construye string con longitud explícita
		std::cout << "Valor: " << valor << std::endl;
		std::cout << "Codigo " << (i + 1) <<  " de 10 >> ";
		std::cin >> codigoAdivinador;

		if (!comprobarLetra(codigoAdivinador)) {
			std::cout << "La letra introducida no es valida, por favor introduce una letra entre A y H." << std::endl;
			i--; // No contar este intento
			continue;
		}

		ponerMayuscula(codigoAdivinador);

		 Calcularesultados(codigoAdivinador, codigoPensador, LARGO_CODIGO, resultados);

		//Mostrar resultados

		std::cout << "Coincidencias extactas: " << resultados[0] <<  " Coincidencias parciales:" << resultados[1] << std::endl;

		// Logica de ganador
		if (resultados[0] == 4) {
			std::cout << "" << std::endl;
			std::cout << "Felicidades, has adivinado el codigo!" << std::endl;
			exit(0);
		}
	}
}


