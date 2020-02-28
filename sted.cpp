#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include "sted.h"
#include "conster.h"
#include "funksjoner.h"
#include <cstring>
#include <fstream>
#include "stoler.h"
#include "vrimle.h"
#include "ListTool2B.h"
#include "sone.h"

// construtor 
Sted::Sted()
{
	antOppsett = 0;
}

// constructor med parameter
Sted::Sted(char* stedNavn) : TextElement(stedNavn)
{
    antOppsett = 0;

}

Sted::Sted(char* txt, std::ifstream & inn) : TextElement(txt)
{
	lesFraFil(inn);
}

// destructor
Sted::~Sted()
{
	for (int i = 0; i <= antOppsett; i++)
	{
		delete oppsett[i];
	}
}

// skriver til fil
void Sted::skrivTilFil(std::ofstream & ut)
{
	Sone* bufferSone;
	Stoler* bufferStol;
	Vrimle* bufferVrimle;

	ut << "-Sted: " << text << "\n"
		<< "Antall oppsett: " << antOppsett << "\n";

	// for-løkke som går igjennom alle oppsettene
	for (int i = 1; i <= antOppsett; i++)
	{
		ut << "Oppsettnr: " << i << "\n";
		// for å finne ut hvor mange som ligger i listen
		int antElem = oppsett[i]->noOfElements();
		// for-løkke som går gjennom alle sonene i listen
		for (int j = 1; j <= antElem; j++)
		{
			// tar ut en sone fra listen
			bufferSone = (Sone*)oppsett[i]->removeNo(j);
			// sjekker om det er et stol eller vrimle-objekt
			if (bufferSone->getTypeSone() == 'S')
			{
				ut << "S\n";
				// legger tilbake sonen
				oppsett[i]->add(bufferSone);
				// tar ut stolobjektet
				bufferStol = (Stoler*)oppsett[i]->removeNo(j);
				// skriver til fil
				bufferStol->skrivTilFil(ut);
				// legger stol tilbake i listen
				oppsett[i]->add(bufferStol);
			}
			else
			{
				ut << "V\n";
				// legger tilbake sonen
				oppsett[i]->add(bufferSone);
				// tar ut vrimleobjektet
				bufferVrimle = (Vrimle*)oppsett[i]->removeNo(j);
				// skriver til fil
				bufferVrimle->skrivTilFil(ut);
				// legger vrimle tilbake i listen
				oppsett[i]->add(bufferVrimle);
			}
		}
	}
}

// leser fra fil
void Sted::lesFraFil(std::ifstream & inn)
{
	Vrimle * bufferVrimle;
	Stoler * bufferStol;

	char typeSone;
	int pos;		//Int husker hvor i filen inn er:
	//Ignorerer tekst og henter adressen:
	inn.ignore(sizeof("Antall oppsett:")) >> antOppsett; inn.ignore();
	//Gaar gjennom antall oppsett lest inn:
	for (int i = 1; i <= antOppsett; i++)
	{
		char bufferNavn[NVNLEN];
		//Allokerer ny liste i oppsett[i]:
		oppsett[i] = new List(Sorted);

		//Ignore linjen oppsettnr (er max 5):
		inn.ignore(sizeof("Oppsettnr: 1"));
		//pos henter hvor i filen den er:
		pos = inn.tellg();
		//Leser inn en char:
		inn >> typeSone; 	
		//Hvis char er V eller S og det ikke er slutt paa filen:
		while ((typeSone == 'V' || typeSone == 'S') && !inn.eof())
		{
			inn.ignore();
			inn.ignore(sizeof("-Sonenavn:")); inn.getline(bufferNavn, NVNLEN);
			//Hvis char er en S er det en Stoler sone:
			if (typeSone == 'S')
			{
				bufferStol = new Stoler(bufferNavn, inn, false);
				oppsett[i]->add(bufferStol);
			}
			//Hvis ikke er det en Vrimle sone:
			else
			{
				bufferVrimle = new Vrimle(bufferNavn, inn, false);
				oppsett[i]->add(bufferVrimle);
			}
			//Leser inn hvor i filen inn er:
			pos = inn.tellg();
			//Leser inn en char:
			inn >> typeSone;
		}
		//Hvis den ikke er i slutten av filen er det et nytt oppsett 
		//eller et nytt sted da vil vi at posisjonen skal gaa tilbake 1
		//for da har vi lest inn noe uonsket:
        if (!inn.eof())
        {
            pos -= 1;
            inn.seekg(pos);
        }
	}
}

// displayer info om sted
void Sted::display()
{
	std::cout << "\tSted: " << text << "\n"
		<< "\tAntall oppsett: " << antOppsett << "\n";
}

// displayer ett oppsett fra et sted
void Sted::displayOppsett()
{
	// hvis det finnes et oppsett på det aktuelle stedet
	if (antOppsett > 0)
	{
		// leser inn aktuelt oppsett som skal displayes
		int nr = les("Hvilket oppsett vil du se?", 1, antOppsett);
		oppsett[nr]->displayList();
	}
	else std::cout << "\tDette stedet har ikke noe oppsett enda.";
}

// for å lage et nytt oppsett
void Sted::oppsettNytt()
{   //hvis det er plass til flere oppsett
	if (antOppsett < 5)
	{
		char valg = ' ';
		do {
			std::cout << "\tLage nytt oppsett fra scratch? (L), eller kopiere et allerede eksisterende oppsett? (K): ";
			valg = les();
		} while (valg != 'L' && valg != 'K');

		// legger til nytt oppsett
		if (valg == 'L')
		{
			oppsett[++antOppsett] = new List(Sorted);
			// legger til nye vrimle/stol-oppsett
			oppsettValg(antOppsett);
		}
		else
		{
			// hvis det finnes et oppsett på det aktuelle stedet
			if (antOppsett > 0)
			{
				int nr = les("Hvilket oppsett vil du kopiere?", 1, antOppsett);
				std::cout << "\n";
				oppsett[++antOppsett] = new List(Sorted);
				// kopierer ett oppsett
				oppsett[antOppsett] = kopier(nr, false);
				// displayer oppsettet
				oppsett[antOppsett]->displayList();
				// mulighet til å redigere oppsettet 
				oppsettValg(antOppsett);
			}
			else std::cout << "\tDet finnes ingen oppsett aa kopiere";
		}
	}
	else std::cout << "\tIkke plass til flere oppsett.";
}

// endrer ett gitt oppsett
void Sted::oppsettEndre()
{
	// hvis stedet har noen oppsett
	if (antOppsett > 0)
	{
		// leser inn det aktuelle oppsettet som brukeren vil endre
		int nr = les("Hvilket oppsett vil du endre?", 1, antOppsett);
		// displayer aktuelt oppsett
		oppsett[nr]->displayList();
		// legge til/endre/slette soner
		oppsettValg(nr);
	}
	else std::cout << "\tDette stedet har ikke et oppsett enda";
}

// valgene man har når man lager nytt/endrer oppsett
void Sted::oppsettValg(int o)
{
	std::cout << "\n\tLegge til/slette soner/endre soner? (L/S/E) (avslutt = 0): ";
	char valg = les();

	// sålenge valg ikke er 0
	while (valg != '0')
	{
		// legger til soner
		if (valg == 'L')
		{
			std::cout << "\tVil legge til Vrimle (V) eller stol-oppsett (S)? Q for aa avslutte: ";
			valg = les();

			// legger til så mange soner som brukeren vil
			while (valg != 'Q')
			{
				char bufferNavn[STRLEN];
				switch (valg)
				{
					// legger til et stol-oppsett
				case 'S': std::cout << "\n\tStoler";
					do {
						les("\tHva heter sonen: ", bufferNavn, STRLEN);
						// looper til bruker taster gyldig sone
						if (oppsett[o]->inList(bufferNavn))
						{
							std::cout << "\tDette sonenummeret finnes allerede.\n";
						}
					} while (oppsett[o]->inList(bufferNavn));

					oppsett[o]->add(new Stoler(bufferNavn));
		
					break;
					// legger til vrimle
				case 'V': std::cout << "\n\tVrimle";
					do {
						les("\tHva heter sonen: ", bufferNavn, STRLEN);
						//looper til bruker taster lovlig sone
						if (oppsett[o]->inList(bufferNavn))
						{
							std::cout << "\tDette sonenummeret finnes allerede.\n";
						}
					} while (oppsett[o]->inList(bufferNavn));
			
					oppsett[o]->add(new Vrimle(bufferNavn));
					
					break;
				}
				std::cout << "\n\tVrimle(V), Stol-oppsett(S), Q for å avslutte: ";
				valg = les();
			}
		}
		else if (valg == 'S')
		{
			// hvis lista ikke er tom
			if (!oppsett[o]->isEmpty())
			{
				char bufferNavn[NVNLEN];
				les("Hvilken sone vil du slette?: ", bufferNavn, NVNLEN);
				// hvis sonen ligger i lista
				if (oppsett[o]->inList(bufferNavn))
				{
					// sletter sonen
					oppsett[o]->destroy(bufferNavn);
					std::cout << "\n\tSonen er nå slettet." << "\n\n";
				}
				else std::cout << "\tDenne sonen eksisterer ikke.";
			}
			else  std::cout << "\tGaar ikke an aa slette flere soner.\n";
		}
		else
		{
			Sone* bufferSone;
			// hvis lista ikke er tom
			if (!oppsett[o]->isEmpty())
			{
				char bufferNavn[NVNLEN];
				les("Hvilken sone vil du endre?: ", bufferNavn, NVNLEN);
				// hvis sonen ligger i lista
				if (oppsett[o]->inList(bufferNavn))
				{
					// displayer sonen
					oppsett[o]->displayElement(bufferNavn); 
					bufferSone = (Sone*)oppsett[o]->remove(bufferNavn);
					// Avhengig av typen, blir det laget et nytt stol/vrimle objekt med nye verdier
					if (bufferSone->getTypeSone() == 'S')
					{
						oppsett[o]->add(bufferSone);
						Stoler* bufferstol;
						bufferstol = (Stoler*)oppsett[o]->remove(bufferNavn);
						bufferstol->endreStoler();
						oppsett[o]->add(bufferstol);
					
						//oppsett[o]->add(new Vrimle(soneBuffer));
					}
					else
					{
						oppsett[o]->add(bufferSone);
						Vrimle* bufferVrimle;
						bufferVrimle = (Vrimle*)oppsett[o]->remove(bufferNavn);
						bufferVrimle->endreVrimle();
						oppsett[o]->add(bufferVrimle);
					}
				}
				else std::cout << "\tDenne sonen eksisterer ikke.";
			}
			else  std::cout << "\tDet finnes ingen oppsett.\n";
		}

		std::cout << "\tLegge til(L), slette(S), endre(E) eller avslutt(0): ";
		valg = les();
	}
}

// returnerer antall oppsett
int Sted::hvorMangeOppsett()
{
	return antOppsett;
}

// frodekode
List* Sted::kopier(int nr, bool brukesIArrangement) {
	List* liste = NULL;
	Sone *sone, *kopi;

	//Hvis vagt oppsett eksisterer:
	if (nr >= 1 && nr <= antOppsett)
	{

		//Finner anntall elementer i listen:
		int ant;
		ant = oppsett[nr]->noOfElements();

		//Allokerer minne til en ny sortert liste:
		liste = new List(Sorted);

		//Kjoerer mellom hvert element i listen:
		for (int i = 1; i <= ant; i++) {
			//Henter ut elementet 'i' fra listen
			sone = (Sone*)oppsett[nr]->removeNo(i);
			//Hvis elementet er "stoler" sone
			if ((sone->getTypeSone()) == 'S')
				//Kopierer elementet:
				kopi = new Stoler(*((Stoler*)sone), brukesIArrangement);
			//else er det vrimle:
			else
				//Kopierer elementet:
				kopi = new Vrimle(*((Vrimle*)sone), brukesIArrangement);
			//Legger sonen tilbake i listen:
			oppsett[nr]->add(sone);
			//Legger kopien inn i den nye listen:
			liste->add(kopi);
		}
	}
	return liste;
}




