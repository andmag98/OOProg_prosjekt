#ifndef __VRIMLE_H                  //  Ensures that this file will be
#define __VRIMLE_H                  //    included only ONCE in each file.

#include "sone.h"
#include "sted.h"
#include "ListTool2B.h"


class Vrimle : public Sone
{
private:
	int* kundeNumBestillt;
public:
	Vrimle(char * nvn);
	//Vrimle(kundeBestilt); (?)
	Vrimle(char* txt, std::ifstream & inn, bool brukesIArrangement);
	Vrimle(Vrimle & vrimleFraSted, bool brukesIArrangement); //vi må få sone til å kjøre en spesifikk constructor.
	~Vrimle();
	void skrivTilFil(std::ofstream & ut);
	void lesFrafil(std::ifstream & inn, bool brukesIArrangement);
	void display();
	void nullstilleVrimle();
	virtual char getTypeSone() override;
	void endreVrimle();
    void kjop(int kunNum);
	void skrivBillett(int kunNum, char * arrNavn, char * sted, int dato, int time, int minutt, char* artist);
	int henteAntallBiletterKundenHarKjopt(int kunNum);

};

#endif
