
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include "vrimle.h"
#include "conster.h"
#include "funksjoner.h"
#include <fstream>

Vrimle::Vrimle(char * nvn) : Sone(nvn)
{
	antBilletter = les("Skriv inn antall billetter", 0, MAXBILLETTER);
	kundeNumBestillt = nullptr;
}

Vrimle::Vrimle(char* txt, std::ifstream & inn, bool brukesIArrangement) : Sone(txt, inn)
{
	kundeNumBestillt = nullptr;
	lesFrafil(inn, brukesIArrangement);
}

Vrimle::Vrimle(Vrimle & vrimleFraSted, bool brukesIArrangement) : Sone((Sone*)& vrimleFraSted)
{
	kundeNumBestillt = nullptr;
	//Hvis denne brukes i arrangement:
	if (brukesIArrangement)
	{
		//Allokerer minne til en int array:
		kundeNumBestillt = new int[antBilletter];
		//Nullstiller intarrayen:
		nullstilleVrimle();
	}
}


Vrimle::~Vrimle()
{
	delete[] kundeNumBestillt;
}


void Vrimle::skrivTilFil(std::ofstream & ut)
{
	Sone::skrivTilFil(ut);
	//Gaar gjennom alle bilettene til vrimlesonen
	//og skriver kundenummeret hvis noen har kjoet billetten:
	if (kundeNumBestillt)
	{
		//Skriver alle kundenummer eller 0 til fil:
		for (int i = 0; i < antBilletter; i++)
		{
			ut << kundeNumBestillt[i] << ' ';
		}
		ut << '\n';
	}
}

void Vrimle::lesFrafil(std::ifstream & inn, bool brukesIArrangement)
{
	//Hvis brukes i arrangement:
	if (brukesIArrangement)
	{
		//Allokerer minne til en int array:
		kundeNumBestillt = new int[antBilletter];
		//Gaar gjennom alle biletter:
		for (int i = 0; i < antBilletter; i++)
		{
			inn >> kundeNumBestillt[i];
		}
		inn.ignore();
	}
}

void Vrimle::display()
{
	std::cout << "\tVRIMLE" << "\tSone: " << text << "\n"
		<< "\tPris: " << prisPrBillett
		<< "\tTil slags: " << antBilletter - antSolgt
		<< "\tSolgt: " << antSolgt << "\n\n";
}

//Kalles på når arrangement kopierer en liste:
void Vrimle::nullstilleVrimle()
{
	for (int i = 0; i < antBilletter; i++)
	{
		kundeNumBestillt[i] = 0;
	}
}

char Vrimle::getTypeSone()
{
	return 'V';
}

// endre verdier på vrimle-sone-objekt
void Vrimle::endreVrimle()
{
	char kommando = ' ';

	// meny om valg av endringer
	std::cout << "\tHva har du lyst aa endre:\n"
		<< "\tP\t-\tPris pr billett\n"
		<< "\tB\t-\tAntall billetter\n"
		<< "\tQ\t-\tAvslutte\n";

	std::cout << "\n\tkommando: ";
	kommando = les();

	// kan endre verdier til man trykker 'Q'
	while (kommando != 'Q')
	{
		switch (kommando)
		{
		case 'P':
			prisPrBillett = les("Pris pr billett", 0, MAXPRIS);
			break;
		case 'B':
			antBilletter = les("Skriv inn antall billetter", 0, MAXBILLETTER);
			break;
		}
		std::cout << "\tkommando: ";
		kommando = les();
	}
}

// for kjop av vrimle-sone-billetter
void Vrimle::kjop(int kunNum)
{
	//Hvis det er plass til flere biletter:
	if (antSolgt < antBilletter)
	{
		int antOnsketBilletter;
		do
		{
			antOnsketBilletter = les("Hvor mange billetter vil du kjope?: ", 0, 10);
		} while (antOnsketBilletter > (antBilletter - antSolgt));

		if (kundeNumBestillt && antOnsketBilletter > 0)
		{
			for (int i = antSolgt; i < antSolgt + antOnsketBilletter; i++)
			{
				kundeNumBestillt[i] = kunNum;
			}
			antSolgt += antOnsketBilletter;
		}
	}
}


void Vrimle::skrivBillett(int kunNum, char * arrNavn, char * sted,
	int dato, int time, int minutt, char* artist)
{

	std::ofstream ut("BILLETTER.txt", std::ios::app);
	//utfil.seekp(0,std::ios::end);
	//Henter inn antall kjopt fordi det skal skriv en bilett for hver
	//Vrimleplass kunden har kjopt:
	int antKjopt = henteAntallBiletterKundenHarKjopt(kunNum);
	//Gaar gjennom alle biletter kjopt av kunde:
	for (int i = 1; i <= antKjopt; i++)
	{
		ut << "\t"; understrek(ut, "_", 55);
		ut << "\n\t|\t\t\t\t\t\t\t|\n";
		ut << "\t|" << "\tSone: " << text << "\tSonetype: " << "Vrimle" << "\t\t|\n";
		ut << "\t|\t\t\t\t\t\t\t|\n";
		ut << "\t|" << "\tStaaplass" << "\t\t\tPris: " << prisPrBillett << "\t|\n";

		ut << "\t|\t\t\t\t\t\t\t|\n";
		ut << "\t|\t";  understrek(ut, "_", 40); ut << "\t|\n";
		ut << "\t|\t|" << "\t\t\t\t\t|\t|\n";
		ut << "\t|\t|" << "\tArrangementnavn: " << arrNavn << "\t\t|\t|\n";
		ut << "\t|\t|" << "\tArtist: " << artist << "\t\t\t|\t|\n";
		ut << "\t|\t|" << "\tSted: " << sted << "\t\t\t|\t|\n";
		ut << "\t|\t|" << "\tDato: " << dato << "\t" << time << ":" << minutt << "\t\t|\t|\n";
		ut << "\t|\t|" << "\tKjopt billett refunderes ikke.\t|\t|\n";
		ut << "\t|\t|"; understrek(ut, "_", 38); ut << "|\t|\n";
		ut << "\t|"; understrek(ut, "_", 54); ut << "|";
		ut << "\n\n";
	}

}

//Returnerer antall biletter kjopt av kunde:
int Vrimle::henteAntallBiletterKundenHarKjopt(int kunNum)
{
	int sum = 0;
	if (kundeNumBestillt)
	{
		//Sumerer antall ganger gitt kundenummer oppstaar i vrimlesonen:
		for (int i = 0; i < antSolgt; i++)
		{
			if (kundeNumBestillt[i] == kunNum) sum++;
		}
	}
	return sum;

}






