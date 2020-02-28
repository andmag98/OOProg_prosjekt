#include <iostream>
#include "steder.h"
#include "sted.h"
#include "funksjoner.h"
#include "conster.h"
#include <fstream>
#include "ListTool2B.h"

// constructor uten parameter
Steder::Steder()
{
	//Allokerer minne til en ny tom liste:
	listeSted = new List(Sorted);
	lesFraFil();
}

// destructor
Steder::~Steder()
{
	delete listeSted;
}

// Sted og Oppsett-menyer
void Steder::handling(char k)
{
	if (k == 'S')
	{
		char kommando = les();
		switch (kommando)
		{
		case 'D':  stedDisplay();                        break;
		case 'N':  nyttSted();                           break;
		default:   std::cout <<
			"Andre kommando maa vere enten D eller N.";   break;
		}
	}
	else
	{
		char kommando = les();
		switch (kommando)
		{
		case 'D':  oppsettDisplay();                        break;
		case 'N':  nyttOppsett();                           break;
		case 'E':  endreOppsett();                          break;
		default:   std::cout <<
			"Andre kommando maa vere enten D, N eller E.";   break;
		}
	}

}

// skrive til fil
void Steder::skrivTilFil()
{
	//  èpner aktuell fil.
	std::ofstream utfil("STEDER.TXT");
	//Stedpointer peker til stedene i listeSted:
	Sted* bufferSted;
	//hjelpevariabel for while-loopen
	int hjelpeVariabel = 1;
	//Henter sted gitt stednavn/nummeret fra stedliste:
	bufferSted = (Sted*)listeSted->removeNo(hjelpeVariabel);
	//Kj¯rer sÂlenge den finner noe
	while (bufferSted)
	{
		//Hvis buffersted ikke peker paa nullpointer, kaller paa sted sin skrivtilffil:
		if (bufferSted) bufferSted->skrivTilFil(utfil);
		//Legger stedet tilbake i listen:
		listeSted->add(bufferSted);
		//gjentar prosessen, og oker hjelpevariablen med 1
		bufferSted = (Sted*)listeSted->removeNo(++hjelpeVariabel);
	}
}

// lese fra fil
void Steder::lesFraFil()
{

	//Aapner "STEDER.TXT"
    std::ifstream innfil("STEDER.TXT");
	//Hvis fant fil
	if (innfil)
	{
		//Buffersted lages for Â sÂ legges inn i liste
		Sted* bufferSted;
		char bufferNavn[STRLEN];
		//Ignorerer st¯rrelse string (med \0) og leser "Sted:",
		//  sÂ blir navnet getlinet
		innfil.ignore(sizeof("-Sted:")); innfil.getline(bufferNavn, STRLEN);
		//sÂlenge det ikke er slutt pÂ fila
		while (!innfil.eof())
		{
			//Allokerer minne til nytt sted og kj¯rer lesfrafil constructor
			bufferSted = new Sted(bufferNavn, innfil);
			//Legger sted til liste
			listeSted->add(bufferSted);
			//Leser inn neste sted
			innfil.ignore(sizeof("-Sted:")); innfil.getline(bufferNavn, STRLEN);
		}
	}
	else std::cout << "Fant ikke filen STEDER.TXT";
}

// Skriver alle stedenes navn og antall oppsett
void Steder::stedDisplay()
{
	listeSted->displayList(); 
}

// Nytt sted legges inn i datastrukturen
void Steder::nyttSted()
{
	//fÂr inn et navn som sted skal sorteres pÂ
	char bufferNavn[NVNLEN];
	les("Skriv inn stedsnavn: ", bufferNavn, NVNLEN);

	//hvis stedsnavnet ikke finnes i lista
	if (!listeSted->inList(bufferNavn))
	{
		//legger til nytt sted i listen og sender med navnet som parameter
		listeSted->add(new Sted(bufferNavn));
	}
	else std::cout << "\tDette stedet finnes allerede."; 
}

// Sp¯r om ett mulig oppsett, og displayer dette, inkludert alle sonene
void Steder::oppsettDisplay()
{
	// leser inn et navn fra brukeren
	char bufferNavn[NVNLEN];
	les("Skriv inn stedsnavn: ", bufferNavn, NVNLEN);

	Sted* bufferSted;

	// sjekker om dette stedsnavnet ligger i listen
	if (listeSted->inList(bufferNavn))
	{
		// remover den fra listen
		bufferSted = (Sted*)listeSted->remove(bufferNavn); 
		// displayer aktuelt sted sitt oppsett
		bufferSted->displayOppsett();
		// legger den tilbake i listen
		listeSted->add(bufferSted);
	}
	else std::cout << "\tStedet finnes ikke."; 
}

// nytt (stol)-oppsett opprettes, enten helt nytt eller kopiert
void Steder::nyttOppsett()
{
	// leser inn et stedsnavn fra brukeren
	char bufferNavn[NVNLEN];
	les("Skriv inn stedsnavn: ", bufferNavn, NVNLEN);

	Sted* bufferSted;

	// hvis stedet ligger i listen
	if (listeSted->inList(bufferNavn))
	{
		// remover den fra listen
		bufferSted = (Sted*)listeSted->remove(bufferNavn);
		// lager et nytt oppsett
		bufferSted->oppsettNytt();
		// legger den tilbake i listen
		listeSted->add(bufferSted);
	}
	else std::cout << "\tStedet finnes ikke.";
}

// kan endre på oppsett ved å slette/legge til soner
void Steder::endreOppsett()
{
	// leser inn stedsnavn fra brukeren
	char bufferNavn[NVNLEN];
	les("Skriv inn stedsnavn: ", bufferNavn, NVNLEN);

	Sted* bufferSted;

	// hvis den ligger i listen
	if (listeSted->inList(bufferNavn))
	{
		// remover den fra listen
		bufferSted = (Sted*)listeSted->remove(bufferNavn);
		// endrer oppsett
		bufferSted->oppsettEndre();
		// legger den tilbake i listen
		listeSted->add(bufferSted);
	}
	else std::cout << "\tStedet finnes ikke.";
}

// frodekode
List* Steder::kopier(char* nvn, int nr, bool brukesIArrangement)
{
  List* liste = NULL;
  Sted* sted;

  if ((sted = (Sted*) listeSted->remove(nvn)))
  {
	 liste = sted->kopier(nr, brukesIArrangement);
	 listeSted->add(sted);
  }
  return liste;
}

int Steder::hentOppsett(char* nvn)
{
    int returnerMeg = 0;
    
    Sted* bufferSted;
    
    if (listeSted->inList(nvn))
    {
        bufferSted = (Sted*)listeSted->remove(nvn);
        returnerMeg = bufferSted->hvorMangeOppsett();
        listeSted->add(bufferSted);
        return returnerMeg;
    }
    else
    {
        returnerMeg = -1;
        return returnerMeg;
    }
}
