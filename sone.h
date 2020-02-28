#ifndef __SONE_H                  //  Ensures that this file will be
#define __SONE_H                  //    included only ONCE in each file.
#include "ListTool2B.h"

class Sone : public TextElement
{
protected:
	//Disse er protected for å kunne brukes i Stoler og Vrimle:
	int antBilletter;
	int antSolgt;
	int prisPrBillett;
public: 
	Sone();
	Sone(Sone * soneFraSted);
	Sone(char* nvn);
	Sone(char* txt, std::ifstream & inn);
	~Sone();
	void skrivTilFil(std::ofstream & ut);
	void lesFrafil(std::ifstream & inn);
	virtual char getTypeSone();
	virtual int henteAntallBiletterKundenHarKjopt(int kunNum);

};


#endif
