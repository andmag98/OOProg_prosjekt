#include <iostream>
#include "ListTool2B.h"
#include "kunder.h"
#include "conster.h"
#include "funksjoner.h"
#include <cstring>
#include <cctype>
#include <fstream>


Kunder::Kunder()
{
	//Allokerer minne til en ny tom liste:
	listeKunde = new List(Sorted);
	//Nullstiller sisteKundeNummer:
	sisteKundeNummer = 0;
	lesFraFil();
}


Kunder::~Kunder()
{
	delete listeKunde;
}

//	Kunde-meny (Display, Ny kunde, Endre kunde)
void Kunder::handling()
{
	//Char leser inn kommando:
	char kommando = les();
	//switch viser alle valg:
	switch (kommando)
	{
	case 'D':  displayValg();							break;
	case 'N':  registrerKunde();						break;
	case 'E':  redigerKunde();							break;
	default:  std::cout <<
		"\tAndre kommando maa vaere enten D, N eller E.";   break;
	}
}


//legger ny kunde til "listeKunde":
void Kunder::registrerKunde()
{
	//Legger til en ny kunde i kundelisten:
	listeKunde->add(new Kunde(++sisteKundeNummer));
}


//displayValg spoer bruker om det skal displaye alle kunder eller bare en enkel kunde:
void Kunder::displayValg()
{
	//Spoer hvem bruker vil se:
	std::cout << "\tDisplaye alle kunder, en enkel kunde, med gitt navn (A / E / N): ";
	//Leser inn input fra bruker:
	char valg = les();
	//Utfoerer funksjon etter angitt input:
	if (valg == 'A') listeKunde->displayList();
	else if (valg == 'E') displayEnkel();
	else if (valg == 'N') displyMedGittNavn();

	//NB! Hvis ikke noen av disse blir valgt vil programmet hoppe ut av
	//funksjonen.
}

//displayEnkel displayer en enkel fkunde paa skjermen etter input om kundenummer
void Kunder::displayEnkel()
{
	//Hentes fra bruker for aa displaye en kunde.
	int kundeNum = les("Hvilket kundenummer vil du se: ", 1, sisteKundeNummer);				
	//Hvis kundenummeret er i listen:
	if (listeKunde->inList(kundeNum)) 
	{
		//henter ut kunden med gitt kundenummer:
		Kunde* bufferKunde = (Kunde*) listeKunde->remove(kundeNum);
		//displayer kunden:
		bufferKunde->display();
		//Legger kunden tilbake i listen:
		listeKunde->add(bufferKunde);
	}
	else
	{
		std::cout << "\tDette kundenummeret finnes ikke\n";
	}
}
//Displayer kunder med et gitt navn:
void Kunder::displyMedGittNavn()
{
	char bufferNavn[NVNLEN];	//Buffernavn som skal sammenlignes med alle kundene.
	std::cout << "\tHva slags navn ser du etter: ";
	//Henter navn fra bruker:
	std::cin.getline(bufferNavn, NVNLEN);

	Kunde* bufferKunde;			//Bufferkunde som skal hente ut hver kunde fra listen.
	//For loop som gaar gjennom alle kundene i kundelisten:
	for (int i = 1; i <= sisteKundeNummer; i++)
	{
		//Henter ut kunde nummer 'i' i kundelisten:
		bufferKunde = (Kunde*) listeKunde->removeNo(i);
		
		//Hvis kunden har lik navn som buffernavn:
		if (bufferKunde->likNavn(bufferNavn))
		{
			//Display kunden med lik navn:
			bufferKunde->display();
		}
		//Legg kunden tilbake i listen:
		listeKunde->add(bufferKunde);
	}
}

void Kunder::redigerKunde()
{
	//Hentes fra bruker for aa displaye en kunde.
	int kundeNum = les("Hvilket kundenummer vil du redigere", 1, sisteKundeNummer);
	//Hvis kundenummeret er i listen:
	if (listeKunde->inList(kundeNum))
	{
		//henter ut kunden med gitt kundenummer:
		Kunde* bufferKunde = (Kunde*)listeKunde->remove(kundeNum);
		//displayer kunden:
		std::cout << "\n\tDu er i ferd med aa redigere:\n";
		bufferKunde->display();
		bufferKunde->endreKunde();

		//Legger kunden tilbake i listen:
		listeKunde->add(bufferKunde);
	}
	else
	{
		std::cout << "\tDette kundenummeret finnes ikke\n";
	}
}

void Kunder::lesFraFil()
{
	//Aapner KUNDER.TXT:
	std::ifstream innfil("KUNDER.TXT");
	//Hvis fant fil:
	if (innfil) {
		//Ignorerer stoerelse string (med \0) og leser siste kunde:
		innfil.ignore(sizeof("Siste Kundenummer:")) >> sisteKundeNummer; innfil.ignore();
		int num;			//Bruker int for aa sjekke at fil ikke er ferdig.
		//Leser inn kundenummer:
		innfil.ignore(sizeof("Kundenummer:")) >> num; innfil.ignore();
		Kunde* bufferKunde;	//Bufferkunde lages for å så legges inn i liste:
		//Hvis num kunne leses inn/ fil ikke er ferdig:
		while (!innfil.eof())
		{
			//Allokerer minne til ny kunde og kjører les fra fil constructor:
			bufferKunde = new Kunde(num, innfil);
			//Legger kunde til liste:
			listeKunde->add(bufferKunde);
			//Leser inn neste kundenummer:
			innfil.ignore(sizeof("Kundenummer:")) >> num; innfil.ignore();
		}
	}
	else std::cout << "Finner ikke fil KUNDER.TXT\n";
}


//Skriver til fil:
void Kunder::skrivTilFil()
{
	std::ofstream utfil("KUNDER.TXT");
	//Kundepointer peker til kundene i listeKunder:
	Kunde* bufferKunde;
	//Skriver ut siste kundenummer:
	utfil << "Siste Kundenummer: " << sisteKundeNummer << '\n';
	//Gaar gjennom alle kundene sin skriv til fil:
	for (int i = 1; i <= sisteKundeNummer; i++)
	{
		bufferKunde = (Kunde*)listeKunde->remove(i);
		//Hvis buffer kunde ikke peker paa nullpointer:
		if (bufferKunde)
		{
			//kaller paa kunden sin skrivtilffil:
			bufferKunde->skrivTilFil(utfil);
			//Legger kunden tilbake i listen:
			listeKunde->add(bufferKunde);
		}
	}
}
//returnerer antall elementer i kunder sin liste:
int Kunder::returnerSiste()
{
    return listeKunde->noOfElements();
}
