#include<iostream>
#include<string>

using namespace std;

class Masina {
private:
	const int id;
	static int nrMasini;
	string marca;
	int nrComponente;
	float* preturi;
public:
	Masina() :id(++nrMasini) {
		this->marca = "Necunoscuta";
		this->nrComponente = 0;
		this->preturi = nullptr;
	}

	Masina(string _marca, int nrComponente, float* preturi) :id(++nrMasini){
		marca = _marca;
		this->nrComponente = nrComponente;
		//shallow copy
		//this->preturi = preturi;

		//deep copy
		this->preturi = new float[nrComponente];
		for (int i = 0; i < nrComponente; i++) {
			this->preturi[i] = preturi[i];
		}
		delete[] preturi;
	}
	
	int getNrComponente() {
		return this->nrComponente;
	}

	void setNrComponente(int nrComponente){
		if (nrComponente > 0) {
			this->nrComponente = nrComponente;
		}
		else {
			throw "Valoare negativa!";
			//throw 400;
			//throw exception();
		}
	}

	//get si set pentru vectorul de preturi
	float* getPreturi() {
		//return this->preturi;
		float* vectorPreturi = new float[this->nrComponente];
		for (int i = 0; i < this->nrComponente; i++) {
			vectorPreturi[i] = this->preturi[i];
		}
		return vectorPreturi;
	}

	void setPreturi(float* noulVectorPreturi, int nouaDimensiune) {
		setNrComponente(nouaDimensiune);
		if (this->preturi != nullptr) {
			delete[] this->preturi;
		}
		this->preturi = new float[nouaDimensiune];
		for (int i = 0; i < nouaDimensiune; i++) {
			this->preturi[i] = noulVectorPreturi[i];
		}
		delete[] noulVectorPreturi;
	}

	const int getId() {
		return this->id;
	}

	~Masina() {
		cout << endl << "S-a apelat destructorul!";
		if(this->preturi != nullptr)
		delete[] this->preturi;
	}

	void afisareMasina() {
		cout << this->id << ". Masina cu marca " << this->marca;
		if (this->nrComponente >0) {
			cout << " are " << this->nrComponente << " componente cu urmatoarele preturi:";
			if (this->preturi != nullptr) {
				for (int i = 0; i < this->nrComponente; i++) {
					cout << " " << this->preturi[i];
				}
			}
		}
		cout << endl;
	}

	static int getNrMasini() {
		return nrMasini;
	}
	static void setNrMasini(int _nrMasini) {
		nrMasini = _nrMasini;
	}

};
int Masina::nrMasini = 0;

int main() {
	Masina masina1;
	try {
		masina1.setNrComponente(-1);
	}
	catch (const char* mesaj) {
		cout << endl << mesaj;
	}
	catch (int cod) {
		cout << endl << cod;
	}
	catch (...) {
		cout << endl << "Valoarea din set este <=0!";
	}
	cout <<endl<< "Noua valoare este: " << masina1.getNrComponente()<<endl;
	masina1.afisareMasina();
	Masina masina2("Renault", 4, new float[4] {23.5, 50.0, 60.7, 3.5});
	masina2.afisareMasina();
	masina2.setPreturi(new float[2]{10.5, 14.7}, 2);

	float* vectorPreturi = masina2.getPreturi();
	for (int i = 0; i < masina2.getNrComponente(); i++) {
		cout << " " << vectorPreturi[i];
	}
	delete[] vectorPreturi;
	
	//pointeri la obiecte
	cout << endl << "Pointeri la obiecte: " << endl;
	Masina* pMasina = new Masina();
	pMasina->afisareMasina();
	Masina* pMasina2 = new Masina("Ford", 3, new float[3] {50, 60, 70});
	pMasina2->afisareMasina();
	cout << endl << "Id: " << pMasina->getId();
	Masina::setNrMasini(5);
	cout << endl << "Nr masini: " << Masina::getNrMasini();

	delete pMasina;
	delete pMasina2;
}