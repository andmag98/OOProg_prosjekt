//Note fra eirik! hvis du vil at compileren ikke skal complaine legger man til denne

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

//Har ikke kommentert ut det under dette

#include <iostream>
#include "conster.h"
#include "arrangement.h"
#include "ListTool2B.h"
#include "funksjoner.h"
#include <fstream>
#include "arrangementer.h"
#include "steder.h"
#include "stoler.h"
#include "vrimle.h"
#include <string>
#include "sone.h"

extern Steder stedbase;
extern Arrangementer arrangementbase;

Arrangement::Arrangement(char* nvn, int nr, char* sted, int nummer) : TextElement(nvn)
{
    //spillestedet blir det stedet man velger hvor arrangementet sakl være
	spilleSted = new char[strlen(sted) + 1];
	strcpy(spilleSted, sted);
    //leser inn artist
	artist = lesChPointer("\tSkriv artist: ");
    //lerer dato, time, minutt og type arrangement
	dato = les("Skriv dato", 20190101, 20303112);
	time = les("Skriv time", 0, 23);
	minutt = les("Skriv minutt", 0, 59);
	int hjelpeType = les("Skriv type, 0-Musikk, 1-Sport, 2-Teater,\n\t3-Show,4-Kino, 5-Familie, 6-Festival", 0, 6);
	type = (arrType)hjelpeType;
	arrangementNr = nr;
    //kopierer listen fra det oppsettet man har valgt
	kopi = new List(Sorted);
	kopi = stedbase.kopier(sted, nummer, true);

    //skriver det kopierte oppsettet til fil
	skrivKopiTilFil(nr);
    //sletter koipen fra minnet
	delete kopi;
	kopi = nullptr;
}

void Arrangement::skrivKopiTilFil(int nr)
{
    //sørger for at riktig fil blir skrvet til
	std::string fil("ARR_");
	fil = fil + std::to_string(nr);
	fil += ".TXT";

	std::ofstream utKopi(fil);
	Vrimle* bufferVrimle;
	Stoler* bufferStol;
	Sone* bufferSone;
    //henter antall elementer i den kopierte listen
	int antElem = kopi->noOfElements();
	for (int j = 1; j <= antElem; j++)
	{
        //henter ut sone elementer fra listen
		bufferSone = (Sone*)kopi->removeNo(j);
        //hvis elementet er et stolobjekt
		if (bufferSone->getTypeSone() == 'S')
		{
			utKopi << "S\n";
            //legger tilbake sonen
			kopi->add(bufferSone);
            //henter ut stolobjektet
			bufferStol = (Stoler*)kopi->removeNo(j);
            //skriver stolen til fil
			bufferStol->skrivTilFil(utKopi);
            //legger tilbake stolen
			kopi->add(bufferStol);
		}
		else    //elementet er et vrimleobjekt
		{
			utKopi << "V\n";
            //legger tilbake sonen
			kopi->add(bufferSone);
            //henter ut vrimleobjektet
			bufferVrimle = (Vrimle*)kopi->removeNo(j);
            //skriver den til fil
			bufferVrimle->skrivTilFil(utKopi);
            //legger den tilbake i listen
			kopi->add(bufferVrimle);
		}
	}
}

Arrangement::Arrangement(char* txt, std::ifstream & inn) : TextElement(txt)
{
	lesFraFil(inn);     //leser inn fra fil
}

Arrangement::~Arrangement()
{
	delete[] spilleSted;    //sletter arrayen spillested
	delete[] artist;        //sletter arrayen artist
	delete kopi;            //sletter kopien av oppsettet
}


void Arrangement::display()
{
	std::cout << '\n';
	std::cout << "\tArrangements navn: " << text << '\n';
	std::cout << "\tspillested: " << spilleSted << '\n';
	std::cout << "\tArtist: " << artist << '\n';
	std::cout << "\tArrangementsnummer: " << arrangementNr << '\n';
	std::cout << "\tArrangementstype: ";
    //diaplayer forskjellige ting avhengig av emumverdi
	if (type == 0) std::cout << "Musikk" << '\n';
	else if (type == 1) std::cout << "Sport" << '\n';
	else if (type == 2) std::cout << "Teater" << '\n';
	else if (type == 3) std::cout << "Show" << '\n';
	else if (type == 4) std::cout << "Kino" << '\n';
	else if (type == 5) std::cout << "Familie" << '\n';
	else if (type == 6) std::cout << "Festival" << '\n';
    
	std::cout << "\tDato: " << dato << '\n';
	std::cout << "\tKlokkeslett: " << time << ":" << minutt << '\n';
}

void Arrangement::skrivTilFil(std::ofstream & ut)
{
	ut << "Arrangements navn: " << text << '\n'
		<< "Spillested: " << spilleSted << '\n'
		<< "Artist: " << artist << '\n'
		<< "Arrangementnummer: " << arrangementNr << '\n'
		<< "Arrangementstype: " << type << '\n'
		<< "Dato: " << dato << '\n'
		<< "Klokkeslett: " << time << ":" << minutt << '\n' << '\n';
}


void Arrangement::lesFraFil(std::ifstream & inn)
{

	char bufferTekst[STRLEN];  //Char array brukes for aa lese inn all tekst.

	//Ignoerer tekst og henter spillestedet:
	inn.ignore(sizeof("Spillested:"));
	inn.getline(bufferTekst, STRLEN);
	spilleSted = new char[strlen(bufferTekst) + 1];
	strcpy(spilleSted, bufferTekst);

	inn.ignore(sizeof("Artist:"));
	inn.getline(bufferTekst, STRLEN);
	artist = new char[strlen(bufferTekst) + 1];
	strcpy(artist, bufferTekst);

	//Ignorerer tekst og henter arrnummer, dato og klokkeslett:
	inn.ignore(sizeof("Arrangementnummer:")) >> arrangementNr; inn.ignore();
	int hjelpeType;
	inn.ignore(sizeof("Arrangementstype:")) >> hjelpeType; inn.ignore();
	type = (arrType)hjelpeType;
	inn.ignore(sizeof("Dato:")) >> dato; inn.ignore();
	inn.ignore(sizeof("Klokkeslett:")) >> time;
	inn.ignore(sizeof(':')) >> minutt; inn.ignore(2);


}

void Arrangement::lesInnKopiFraFil(int nr)
{
    //sørger for at riktig fil blir åpnet
	std::string fil("ARR_");
	fil = fil + std::to_string(nr);
	fil += ".TXT";
	std::ifstream innFil(fil);
	if (innFil)
	{
		kopi = new List(Sorted);
		Vrimle* bufferVrimle;
		Stoler* bufferStol;
		char typeSone;
		int pos;
		char bufferNavn[NVNLEN];
		//Ignorerer tekst og henter adressen:

		innFil >> typeSone;
		while ((typeSone == 'V' || typeSone == 'S') && !innFil.eof())
		{
			innFil.ignore();
			innFil.ignore(sizeof("-Sonenavn:")); innFil.getline(bufferNavn, NVNLEN);
			if (typeSone == 'S')
			{
				bufferStol = new Stoler(bufferNavn, innFil, true);
				kopi->add(bufferStol);
			}
			else
			{
				bufferVrimle = new Vrimle(bufferNavn, innFil, true);
				kopi->add(bufferVrimle);
			}
			pos = innFil.tellg();
			innFil >> typeSone;
		}
	}
	else std::cout << "finner ikke filen";
}

void Arrangement::displayKopi()
{
	kopi->displayList();
}

bool Arrangement::likArrNavn(char* nvn)
{
	if (strcmp(nvn, text) == 0) return true;
	else return false;
}

bool Arrangement::likSpillested(char* nvn)
{
	if (strcmp(nvn, spilleSted) == 0) return true;
	else return false;
}

bool Arrangement::likDato(int n)
{
	if (n == dato) return true;
	else return false;
}

bool Arrangement::likArtist(char* nvn)
{
	if (strcmp(nvn, artist) == 0) return true;
	else return false;
}

bool Arrangement::likType(int n)
{
	if (n == type) return true;
	else return false;
}

bool Arrangement::likNummer(int n)
{
	if (n == arrangementNr) return true;
	else return false;
}

int Arrangement::returnerArrNummer()
{
	return arrangementNr;
}

void Arrangement::slettKopi()
{
	delete kopi;
	kopi = nullptr;
}

void Arrangement::kjopBillett(int nr, int aNummer)
{
	Sone* bufferSone;
	char bufferNavn[NVNLEN];
	les("Hvilken sone vil du kjope billett i?: ", bufferNavn, NVNLEN);
	// hvis sonen ligger i lista
	if (kopi->inList(bufferNavn))
	{
		// displayer sonen
		kopi->displayElement(bufferNavn);
		bufferSone = (Sone*)kopi->remove(bufferNavn);
		// Avhengig av typen, blir det laget et nytt stol/vrimle objekt med nye verdier
		if (bufferSone->getTypeSone() == 'S')
		{
			kopi->add(bufferSone);
			Stoler* bufferStol;
			bufferStol = (Stoler*)kopi->remove(bufferNavn);
			bufferStol->kjop(nr);
			kopi->add(bufferStol);
			skrivKopiTilFil(aNummer);
			//Skriver bilett(er) til fil:
			bufferStol = (Stoler*)kopi->remove(bufferNavn);
			bufferStol->skrivBillett(nr, text, spilleSted, dato, time, minutt, artist);
			kopi->add(bufferStol);
		}
		else
		{
			kopi->add(bufferSone);
			Vrimle* bufferVrimle;
			bufferVrimle = (Vrimle*)kopi->remove(bufferNavn);
			bufferVrimle->kjop(nr);
			kopi->add(bufferVrimle);
			skrivKopiTilFil(aNummer);
			//Skriver bilett(er) til fil:
			bufferVrimle = (Vrimle*)kopi->remove(bufferNavn);
			bufferVrimle->skrivBillett(nr, text, spilleSted, dato, time, minutt, artist);
			kopi->add(bufferVrimle);
		}
	}
}

void Arrangement:: reduserANummer()
{
    arrangementNr--;
}



