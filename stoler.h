#ifndef __STOLER_H                  //  Ensures that this file will be
#define __STOLER_H                  //    included only ONCE in each file.


#include "sone.h"
#include "sted.h"
#include "ListTool2B.h"


class Stoler: public Sone
{
private:
	//Hvordan skal vi ha en liste med rader som inneholder en liste med stoler pr. rad?
	int rader;
	int seterPrRad;
	int** kundeNumBestillt;

public:
	Stoler(char* nvn);
	Stoler(char* txt, std::ifstream & inn, bool brukesIArrangement);
	Stoler(Stoler & stolerFraSted, bool brukesIArrangement);
	~Stoler();
	void skrivTilFil(std::ofstream & ut);
	void lesFrafil(std::ifstream & inn, bool brukesIArrangement);
	void nullstilleStoler();
	virtual char getTypeSone() override;
	void display();
	void endreStoler();
	void kjop(int kunNum);
	void skrivBillett(int kunNum, char * arrNavn, char * sted, int dato, int time, int minutt, char* artist);
	int henteAntallBiletterKundenHarKjopt(int kunNum);

};


#endif
