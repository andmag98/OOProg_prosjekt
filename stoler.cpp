
#include <iostream>
#include "stoler.h"
#include "ListTool2B.h"
#include "funksjoner.h"
#include "conster.h"
#include <fstream>


// Constructor uten parameter
Stoler::Stoler(char* nvn) : Sone(nvn)
{
	//Leser inn hvor mange rader det er :
	rader = les("Hvor mange rader har sonen", 1, MAXRADER);
	//Leser inn hvor mange seter per rad der er:
	seterPrRad = les("Hvor mange seter er det pr. rad", 1, MAXSETER);
	antBilletter = rader * seterPrRad;
	kundeNumBestillt = nullptr;
}

Stoler::Stoler(char* txt, std::ifstream & inn, bool brukesIArrangement) : Sone(txt, inn)
{
	kundeNumBestillt = nullptr;

	lesFrafil(inn, brukesIArrangement);
}

Stoler::Stoler(Stoler & stolerFraSted, bool brukesIArrangement) : Sone((Sone*)& stolerFraSted)
{
	//Kopierer rader:
	rader = stolerFraSted.rader;
	//Kopierer seterPrRad:
	seterPrRad = stolerFraSted.seterPrRad;
	//Peker kunNumBestillt til nullptr:
	kundeNumBestillt = nullptr;
	//Hvis denne blir brukt i arrangement:
	if (brukesIArrangement)
	{
		//Allokerer minne til en int-pointer-array:
		kundeNumBestillt = new int*[rader];
		for (int i = 0; i < rader; i++)
		{
			//Allokerer minne til en int array paa seterPrRad lang i hver
			//int peker:
			kundeNumBestillt[i] = new int[seterPrRad];
			//For loop som skal nullstille hvert sete:
			for (int j = 0; j < seterPrRad; j++)
			{
				//Nullstiller hver stol:
				kundeNumBestillt[i][j] = 0;
			}
		}
	}
}

// Destructor
Stoler::~Stoler()
{
	//Hvis kundeNumBestillt ikke er nullpointer:
	//Dette brukes når arrangement skriver kopi til fil:
	if (kundeNumBestillt)
	{
		//For loop frigjoer minne allokert til int arrayene i hver int-peker:
		for (int i = 0; i < rader; i++)
		{
			delete[] kundeNumBestillt[i];
		}
		//Frigjoer minne til allokert til int-peker-arrayen:
		delete[] kundeNumBestillt;
	}
}

// skriver til fil
void Stoler::skrivTilFil(std::ofstream & ut)
{
	//Kaller på sin sone sin skriv til fil:
	Sone::skrivTilFil(ut);
	ut << "Antall rader: " << rader << '\n'
		<< "Antalle seter per rad: " << seterPrRad << '\n';
	//Hvis kundeNumBestillt ikke peker på nullptr:
	if (kundeNumBestillt)
	{
		//For loop gaar gjennom hvert sete i int-pointer-arrayen (hver rad)
		//og saa gaar gjennom hver int i int-arrayen (hvert sete):
		for (int i = 0; i < rader; i++)
		{
			//Gaar gjennom hvert sete:
			for (int j = 0; j < seterPrRad; j++)
			{
				//Couter statusen til sete. Hvis 0 er den ledig
				//Hvis int er det kundenummeret til bestilleren:
				ut << kundeNumBestillt[i][j] << ' ';
			}
			ut << '\n';
		}
	}
}
// leser fra fil
void Stoler::lesFrafil(std::ifstream & inn, bool brukesIArrangement)
{
	//Leser inn rader og seter pr rad:
	inn.ignore(sizeof("Antall rader:")) >> rader; inn.ignore();
	inn.ignore(sizeof("Antalle seter per rad:")) >> seterPrRad; inn.ignore();
    //Hvis denne blir brukt av arrangement:
	if (brukesIArrangement)
	{
            //Allokerer minne til en int-pointer-array:
            kundeNumBestillt = new int*[rader];
            for (int i = 0; i < rader; i++)
            {
                //Allokerer minne til en int array paa seterPrRad lang i hver
                //int peker:
                kundeNumBestillt[i] = new int[seterPrRad];
                //For loop som skal nullstille hvert sete:
                for (int j = 0; j < seterPrRad; j++)
                {
                    //Nullstiller hver stol:
                    kundeNumBestillt[i][j] = 0;
                }
            }
		//For loop gaar gjennom hvert sete i int-pointer-arrayen (hver rad)
		//og saa gaar gjennom hver int i int-arrayen (hvert sete):
		for (int i = 0; i < rader; i++)
		{
			//Gaar gjennom hvert sete:
			for (int j = 0; j < seterPrRad; j++)
			{
				//Couter statusen til sete. Hvis 0 er den ledig
				//Hvis int er det kundenummeret til bestilleren:
				inn >> kundeNumBestillt[i][j];
			}
        }
		inn.ignore();
    }
}


// display stol-oppsett
void Stoler::display()
{
	std::cout << "\tSTOLER" << "\tSone: " << text << "\n"
		<< "\tPris: " << prisPrBillett << "\tTil slags: " << antBilletter
		<< "\tSolgt: " << antSolgt << "\n\n";

	std::cout << "\t" << "  ";
	for (int k = 1; k <= seterPrRad; k++)
	{
		std::cout << k % 10;
	}
	std::cout << "\n";
	for (int i = 0; i < rader; i++)
	{
		std::cout << "\t" << (i + 1) % 10 << " ";
		for (int j = 0; j < seterPrRad; j++)
		{
			if (kundeNumBestillt) {
				(kundeNumBestillt[i][j] == 0)
					? std::cout << '-' : std::cout << 'x';
			}
			else	std::cout << '-';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

//Kalles paa naar arragnement kopierer oppsettlisten:
void Stoler::nullstilleStoler()
{
	//Gaar gjennom hver int peker for aa allokere minne til int arrayer :
	for (int i = 0; i < rader; i++)
	{
		//For loop som skal nullstille hvert sete:
		for (int j = 0; j < seterPrRad; j++)
		{
			//Nullstiller hver stol:
			kundeNumBestillt[i][j] = 0;
		}
	}
}

char Stoler::getTypeSone()
{
	return 'S';
}

// endre på stoler
void Stoler::endreStoler()
{
	char kommando = ' ';
	// meny om hva man vil endre på
	std::cout << "\tHva har du lyst aa endre:\n"
		<< "\tP\t-\tPris pr billett\n"
		<< "\tR\t-\tAntall rader\n"
		<< "\tS\t-\tAntall seter\n"
		<< "\tQ\t-\tAvslutte\n";

	std::cout << "\n\tkommando: ";
	kommando = les();

	// kan endre på så mange ting til man skriver 'Q'
	while (kommando != 'Q')
	{
		switch (kommando)
		{
		case 'P':
			prisPrBillett = les("Pris pr billett", 0, MAXPRIS);
			break;
		case 'R':
			rader = les("Hvor mange rader?: ", 1, MAXRADER);
			break;
		case 'S':
			seterPrRad = les("Hvor mange seter er det pr. rad", 1, MAXSETER);
			break;
		}
		std::cout << "\tkommando: ";
		kommando = les();
	}
}

// salg av stol-sone-billetter
void Stoler::kjop(int kunNum)
{
	//Hvis det er mulig aa kjope flere biletter:
	if (antSolgt < antBilletter)
	{
		//Inter brukt for onsket antall biletter og plass fra bruker:
		int antOnsketBiletter, radOnsket, seteOnsket;
		bool ok = true; //Bool blir false hvis bruker taster noe som
						//gjor at det ikke er mulig aa sette av biletter:
		//Loop gaar til alt er ok eller hvis brukeren velger aa ikke kjope bilett:
		do
		{
			ok = true;
			antOnsketBiletter = les("Hvor mange billetter vil du kjope?: ", 0, 10);
			radOnsket = les("Hilken rad vil du ha", 1, rader);
			radOnsket--;	//trekker fra 1 fordi luke 0 brukes
			seteOnsket = les("Hvilket sete vil du ha", 1, seterPrRad);
			seteOnsket--;	//trekker fra 1 fordi luke 0 brukes
			int i = 0;	//Loopevariabel.
			//Gaar gjennom alle kundeNumBestillt inntil ok = false: 
			while (i < antOnsketBiletter && ok == true)
			{
				//Hvis luken i kundeNumBestillt ikke er ledig blir ok = false:
				if (kundeNumBestillt[radOnsket][i + seteOnsket] != 0) ok = false;
				//oker loopvariabelen:
				i++;
			}
		} while (ok == false);
		//Hvis kundenumBestillt finnes (som den skal når denne kjorer), og antall
		//onsket biletter er storre enn 0:
		if (kundeNumBestillt && antOnsketBiletter > 0)
		{
			//setter av plassene til sett kundenummer:
			for (int i = seteOnsket; i < (seteOnsket + antOnsketBiletter); i++)
			{
				kundeNumBestillt[radOnsket][i] = kunNum;
			}
			//Oker antall solgt:
			antSolgt += antOnsketBiletter;
		}
	}
}

void Stoler::skrivBillett(int kunNum, char * arrNavn, char * sted,
	int dato, int time, int minutt, char* artist)
{
	std::ofstream ut("BILLETTER.txt", std::ios::app);
	//utfil.seekp(0,std::ios::end);
	//Henter hvor mange biletter gitt kundenummer har kjopt
	//Fordi det skal skrives en bilett for hvert sete:
	int antallKjopt = henteAntallBiletterKundenHarKjopt(kunNum);
	//Looper for hver gang kundenummer har kjopt:
	for (int i = 1; i <= antallKjopt; i++)
	{
		ut << "\t"; understrek(ut, "_", 55);
		ut << "\n\t|\t\t\t\t\t\t\t|\n";

		ut << "\t|" << "\tSone: " << text << "\tSonetype: " << "Sitteplass" << "\t\t|\n";
		ut << "\t|\t\t\t\t\t\t\t|\n";

		//antall treff:
		int ticks = 0;
		//NBNB!!! (eirik) bruker while og ikke for slik at hvis programmet
		//finner neste gyldige sete gaar ikke programmet gjennom resten:
		//loopvariabler:
		int j = 0;
		//gaar gjennom alle rader og hvis ticks ikke er ettersokt mengde:
		while (j < rader && ticks <= i)
		{
			int k = 0;

			//gaar gjennom alle seter pr rad og
			//hvis ikke ettersokt mengde er oppnaadd:
			while (k < seterPrRad && ticks <= i)
			{
				//Hvis sete er bestillt av kunNum:
				if (kundeNumBestillt[j][k] == kunNum)
				{
					//Oker ticks med 1:
					ticks++;
					//Hvis ticks er lik i:
					if (ticks == i) 
					ut << "\t|" << "\tRad: " << j + 1 << "\t\tSete: " << k + 1 << "\t\tPris: " << prisPrBillett << "\t|\n";
				}
				k++;
			}
			j++;
		}

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

//Returnerer antall biletter Kunden har kjopt:
int Stoler::henteAntallBiletterKundenHarKjopt(int kunNum)
{
	int sum = 0; //Nullstiller total:
	//Hvis kundenNumBestillt finnes:
	if (kundeNumBestillt)
	{
		//Gaar gjennom alle seter i sone:
		for (int i = 0; i < rader; i++)
		{
			for (int j = 0; j < seterPrRad; j++)
			{
				//Hvis sete er bestillt av kundenummer okes sum:
				if (kundeNumBestillt[i][j] == kunNum) sum++;
			}
		}
	}
	else
	{
		std::cout << "finner ikke seter. hentAntallBiletterKundenHarKjopt(int kunNum) missbrukt\n";
	}
	return sum;
}
