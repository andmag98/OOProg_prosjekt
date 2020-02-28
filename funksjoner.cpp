#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 


#include <iostream>
#include "funksjoner.h"
#include "conster.h"
#include <cctype>
#include <fstream>


void skrivMeny()          //  Presenterer lovlige menyvalg:
{
	std::cout << "\n\nFOLGENDE KOMMANDOER ER LOVLIG:\n\n";
	std::cout << "1.\tK D  = Kunde display\n";
	std::cout << "  \tK N  = Ny kunde\n";
	std::cout << "  \tK E  = Endre kunde\n\n";
	std::cout << "2.\tS D  = Display sted\n";
	std::cout << "  \tS N  = Nytt sted\n\n";
	std::cout << "3.\tO D  = Display oppsett\n";
	std::cout << "  \tO N  = Nytt oppsett\n";
	std::cout << "  \tO E  = Endre oppsett\n\n";
	std::cout << "4.\tA D  = Display arrangement\n";
	std::cout << "  \tA N  = Nytt arrangement\n";
	std::cout << "  \tA S  = Slett arrangement\n";
	std::cout << "  \tA K  = Kjop billetter til arrangement\n\n";
	std::cout << "  \tQ    = Quit/avslutt\n";
}

char les()                         //  Henter ett ikke-blankt upcaset tegn:
{
	char ch;
	std::cin >> ch;   std::cin.ignore();  //  Leser ETT tegn. Forkaster '\n'.
	return (toupper(ch));				  //  Upcaser og returnerer.
}

//  Leser et tall i et visst intervall:
int les(const char t[], const int min, const int max)
{
	int n;
	do                                  // Skriver ledetekst:
	{
		std::cout << '\t' << t << " (" << min << '-' << max << "): ";
		std::cin >> n;   std::cin.ignore();            // Leser inn ett tall.
	} while (n < min || n > max);         // Sjekker at i lovlig intervall.
	return n;                              // Returnerer innlest tall.
}

//  Leser en ikke-blank tekst:
void les(const char t[], char s[], const int LEN) 
{
	do 
	{
		std::cout << '\t' << t;	std::cin.getline(s, LEN); //  Ledetekst og leser.
	} while (strlen(s) == 0);             //  Sjekker at tekstlengden er ulik 0.
}


char* lesChPointer(const char t[])
{
	char * chPointer;
	std::cout << t;
	char bufferTekst[STRLEN];
	std::cin.getline(bufferTekst, STRLEN);
	chPointer = new char[strlen(bufferTekst) + 1];
	strcpy(chPointer, bufferTekst);
	return chPointer;
}

void understrek(std::ofstream & ut, const char v[], int n)				// for å gjøre fakturaen finere
{
	for (int i = 0; i < n; i++)		// printer bindestreker
	{
		ut << v;
	}
	ut << v;
}
