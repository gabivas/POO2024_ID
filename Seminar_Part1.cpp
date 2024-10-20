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

	~Masina() {
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

};
int Masina::nrMasini = 0;

int main() {
	Masina masina1;
	masina1.setNrComponente(1);
	cout << "Noua valoare este: " << masina1.getNrComponente()<<endl;
	masina1.afisareMasina();
	Masina masina2("Renault", 4, new float[4] {23.5, 50.0, 60.7, 3.5});
	masina2.afisareMasina();
	masina2.setPreturi(new float[2]{10.5, 14.7}, 2);

	float* vectorPreturi = masina2.getPreturi();
	for (int i = 0; i < masina2.getNrComponente(); i++) {
		cout << " " << vectorPreturi[i];
	}
	delete[] vectorPreturi;
}