#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include "ListTool2B.h"
#include "kunder.h"
#include "conster.h"
#include "funksjoner.h"
#include <cstring>
#include <cctype>
#include <fstream>

Kunde::Kunde()
{
	std::cout << "Dette \"Kunde\" objektet har blitt deklarert uten parameter\n";
}

Kunde::Kunde(int kundeNum) : NumElement(kundeNum)
{
	//Char array som tar i mot tekst og doer naar constructoren doer:

	//Faar navn til kunden fra bruker:
	navn = lesChPointer("\tNavnet til kunden: ");
	//Leser inn mail fra bruker:
	mail = lesChPointer("\tMailen til kunden: ");
	//Leser inn telefonnummer:
	telefonNummer = les("Telefonnummer", 11111111, 99999999);

	//Faar adressen til kunden fra bruker:
	adresse = lesChPointer("\tAdressen til kunden: ");

	//Leser inn poststed fra bruker:
	postSted = lesChPointer("\tPoststedet til kunden: ");
	//Leser inn postnummer:
	postNummer = les("Postnummer: ", 0001, 9999);
}
//Kjøres når programmet starter og skal lese fra fil:
Kunde::Kunde(int kundeNum, std::ifstream & inn) : NumElement(kundeNum)
{
	lesFraFil(inn);
}

Kunde::~Kunde()
{
	delete[] navn;
	delete[] adresse;
	delete[] postSted;
	delete[] mail;
}

bool Kunde::likNavn(char* nvn)
{
	if (strcmp(nvn, navn) == 0) return true;
	else return false;
}

void Kunde::display()
{
	std::cout << "\n\tKunde nr." << number << ":\n"
		<< '\t' << navn
		<< "\n\t" << mail << '\n'
		<< "\tKontaktnummer: " << telefonNummer << '\n'
		<< '\t' << adresse << '\n'
		<< '\t' << postSted << '\t' << postNummer << "\n";
}

void Kunde::endreKunde()
{
	char kommando;

	std::cout << "\n\tHva har du lyst aa endre:\n"
		<< "\tN\t-\tNavn\n"
		<< "\tT\t-\tTelefon\n"
		<< "\tM\t-\tMail\n"
		<< "\tA\t-\tAdresse\n"
		<< "\tS\t-\tPoststed\n"
		<< "\tP\t-\tPostnummer\n"
		<< "\tQ\t-\tQuit\n\n";

	std::cout << "\n\tkommando: ";
	kommando = les();

	while (kommando != 'Q')
	{
		switch (kommando)
		{
		case 'N':
			navn = lesChPointer("\tHva er det nye navnet: ");
			break;
		case 'T':
			telefonNummer = les("Hva er telefonnummeret: ", 11111111, 99999999);
			break;
		case 'M':
			mail = lesChPointer("\tHva er den nye mailen: ");
			break;
		case 'A':
			adresse = lesChPointer("\tHva er den nye adressen: ");
			break;
		case 'S':
			postSted = lesChPointer("\tHva er det nye poststedet ");
			break;
		case 'P':
			postNummer = les("Hva er det nye postnummeret: ", 1, 9999);
			break;
		}
		std::cout << "\tkommando: ";
		kommando = les();
	} 
}

void Kunde::skrivTilFil(std::ofstream & ut)
{
	ut << "Kundenummer: " << number << '\n'
		<< "Navn: " << navn << '\n'
		<< "Telefon: " << telefonNummer << '\n'
		<< "Mail: " << mail << '\n'
		<< "Adresse: " << adresse << '\n'
		<< postNummer << ' ' << postSted << '\n';
}
//Leser fra fil:
//NB!! Vi har valgt å ha dette i en egen funksjon i stedet for i en constructor.
void Kunde::lesFraFil(std::ifstream & inn)
{

	char bufferTekst[STRLEN];	//Char array brukes for å lese inn all tekst.

	//Ignoerer tekst og henter navnet:
	inn.ignore(sizeof("Navn:"));
	inn.getline(bufferTekst, STRLEN);
	navn = new char[strlen(bufferTekst) + 1];
	strcpy(navn, bufferTekst);

	//Ignorerer tekst og henter telefonnummer:
	inn.ignore(sizeof("Telefon:")) >> telefonNummer; inn.ignore();

	//Leser inn mail:
	inn.ignore(sizeof("Mail:"));
	inn.getline(bufferTekst, STRLEN);
	mail = new char[strlen(bufferTekst) + 1];
	strcpy(mail, bufferTekst);

	//Ignorerer tekst og henter adressen:
	inn.ignore(sizeof("Adresse:"));
	inn.getline(bufferTekst, STRLEN);
	adresse = new char[strlen(bufferTekst) + 1];
	strcpy(adresse, bufferTekst);

	//leser inn postnummer og poststed:
	inn >> postNummer; inn.ignore();
	inn.getline(bufferTekst, STRLEN);
	postSted = new char[strlen(bufferTekst) + 1];
	strcpy(postSted, bufferTekst);
}
