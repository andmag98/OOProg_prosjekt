#ifndef __KUNDE_H                  //  Ensures that this file will be
#define __KUNDE_H                  //    included only ONCE in each file.
#include "ListTool2B.h"
#include <fstream>



class Kunde : public NumElement			// sortert paa nummer
{
private:
	char* navn;
	char* adresse;		
	char* postSted;
	char* mail;

	int postNummer;
	int telefonNummer;
	
public:
	Kunde();
	Kunde(int kundeNum);
	Kunde(int kundeNum, std::ifstream & inn);
	~Kunde();
	void display();
	void endreKunde();
	bool likNavn(char* nvn);
	void skrivTilFil(std::ofstream & ut);
	void lesFraFil(std::ifstream & inn);
};



#endif
