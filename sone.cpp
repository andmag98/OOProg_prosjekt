#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include "sone.h"
#include "conster.h"
#include "funksjoner.h"
#include <cstring>
#include <fstream>


// parameterløs-constructor
Sone::Sone()
{
	std::cout << "Denne skal aldri bli kjort";
}

//constructor med parameter
Sone::Sone(char* nvn) : TextElement(nvn)
{
	prisPrBillett = les("Billettpris", 0, MAXPRIS);
	antSolgt = 0;
	antBilletter = 0;
}

// 
Sone::Sone(Sone * soneFraSted) : TextElement(soneFraSted->text)
{
	antBilletter = soneFraSted->antBilletter;
	antSolgt = soneFraSted->antSolgt;
	prisPrBillett = soneFraSted->prisPrBillett;
}

Sone::Sone(char* txt, std::ifstream & inn) : TextElement(txt)
{
	lesFrafil(inn);
}

// destructor
Sone::~Sone()
{

}

// Skriver sone til fil
void Sone::skrivTilFil(std::ofstream & ut)
{
	ut << "-Sonenavn: " << text << "\n" << "Antall billetter: " 
		<< antBilletter << "\n" << "Antall solgt: " << antSolgt << "\n"
	 << "Pris pr. Billett: " << prisPrBillett << "\n"; 
}

// leser sone fra fil
void Sone::lesFrafil(std::ifstream & inn)
{
	inn.ignore(sizeof("Antall billetter:")) >> antBilletter; inn.ignore();
	inn.ignore(sizeof("Antall solgt:")) >> antSolgt; inn.ignore();
	inn.ignore(sizeof("Pris pr. Billett:")) >> prisPrBillett; inn.ignore();
}

// Blir aldri kalt på
char Sone::getTypeSone()
{
	std::cout << "getTypeSone skal aldri bli kalt på";
	return 'N';
}

// henter antall billetter kunden har kjopt
int Sone::henteAntallBiletterKundenHarKjopt(int kunNum)
{
	std::cout << "hentAntallBiletterKundenHarKjopt() sin funksjon har blitt brukt feil\n";
	return 0;
}
