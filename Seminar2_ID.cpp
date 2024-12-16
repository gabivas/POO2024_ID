#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<iterator>

//ca tema vector, set, map

using namespace std;

class Ochelari {
private:
	char* brand;
	float pret;
public:
	Ochelari() :pret(0), brand(nullptr) {}
	Ochelari(float pret, const char* brand) {
		this->pret = pret;
		this->brand = new char[strlen(brand) + 1];
		memcpy(this->brand, brand, strlen(brand) + 1);
	}

	Ochelari(const Ochelari& copie) {
		this->pret = copie.pret;
		if (copie.brand != nullptr) {
			this->brand = new char[strlen(copie.brand) + 1];
			memcpy(this->brand, copie.brand, strlen(copie.brand) + 1);
		}
		else {
			this->brand = nullptr;
		}
	}

	void operator=(const Ochelari& copie) {
		this->pret = copie.pret;

		if (this->brand != nullptr) {
			delete[] this->brand;
			this->brand = nullptr;
		}
		if (copie.brand != nullptr) {
			this->brand = new char[strlen(copie.brand) + 1];
			memcpy(this->brand, copie.brand, strlen(copie.brand) + 1);
		}
		else {
			this->brand = nullptr;
		}
	}

	//problema legata de destructor, rezolvata prin adaugarea constructorului de copiere si a operatorului =
	~Ochelari() {
		if (this->brand != nullptr) {
			delete[] this->brand;
		}
	}

	friend void operator<<(fstream& out, Ochelari ochelari) {
		out << ochelari.pret << endl;
		out << ochelari.brand << endl;
	}

	friend void operator>>(ifstream& in, Ochelari& ochelari) {
		in >> ochelari.pret;

		if (ochelari.brand != nullptr) {
			delete[] ochelari.brand;
			ochelari.brand = nullptr;
		}

		char buffer[50];
		in >> buffer;
		ochelari.brand = new char[strlen(buffer) + 1];
		strcpy(ochelari.brand, buffer);
	}

	friend void operator<<(ostream& out, Ochelari ochelari) {
		out << "Pret: " << ochelari.pret << endl;
		out << "Brand: " << ochelari.brand << endl;
	}

	float getPret() {
		return this->pret;
	}

	Ochelari operator+(const Ochelari ochelari) {
		Ochelari copie = *this;
		copie.pret = copie.pret + ochelari.pret;
		return copie;
	}

	friend float operator+(float suma, const Ochelari ochelari) {
		suma = suma + ochelari.pret;
		return suma;
	}

};

template<class T>
T suma(T a, T b) {
	return a + b;
}

template<class colectie>
class Mobilier {
private:
	colectie* vector;
	int dimensiune;
public:
	Mobilier() {
		this->dimensiune = 0;
		this->vector = NULL;
	}

	~Mobilier() {
		if (this->vector != NULL) {
			delete[] this->vector;
		}
	}
	Mobilier(colectie* vector, int dim) {
		this->dimensiune = dim;
		this->vector = new colectie[dim];
		for (int i = 0; i < dim; i++) {
			this->vector[i] = vector[i];
		}
	}

	float medie() {
		float suma = 0;
		for (int i = 0; i < dimensiune; i++) {
			suma = suma + vector[i];
		}
		return suma / dimensiune;
	}

};

void afisareLista(list<int> lista) {
	list<int>::iterator it;
	cout << endl;
	for (it = lista.begin(); it != lista.end(); it++) {
		cout << " " << *it;
	}
}

void main() {
	Ochelari ochelari(1000, "Rayban");
	fstream fileStream("Ochelari.txt", ios::out);
	fileStream << ochelari;
	fileStream.close();

	Ochelari ochelari2;
	ifstream iFileStream("Ochelari.txt", ios::in);
	iFileStream >> ochelari2;
	iFileStream.close();

	cout << ochelari2;

	cout << endl << suma(2.6, 3.7);

	Ochelari ochelari3 = suma(ochelari, ochelari2);
	cout << endl << ochelari3.getPret();

	Mobilier<int> m1;
	int dim = 4;
	float* vector = new float[dim] {2.5, 6.9, 1.75, 10};
	Mobilier<float> m2(vector, dim);
	cout << endl << "Medie: " << m2.medie();
	dim = 2;
	Ochelari* vectorOchelari = new Ochelari[dim]{ ochelari, ochelari2 };
	Mobilier<Ochelari> m3(vectorOchelari, dim);
	cout << endl << "Medie: " << m3.medie();

	delete[] vector;
	delete[] vectorOchelari;

	list<int> lista1, lista2;
	for (int i = 0; i < 4; i++) {
		lista1.push_back(i);
		lista2.push_front(i);
	}

	afisareLista(lista1);
	afisareLista(lista2);

	lista2.sort();
	lista1.reverse();

	afisareLista(lista1);
	afisareLista(lista2);

	lista1.pop_front();

	afisareLista(lista1);

}