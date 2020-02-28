#ifndef __KUNDER_H                  //  Ensures that this file will be
#define __KUNDER_H                  //    included only ONCE in each file.
#include "kunde.h"
#include "ListTool2B.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 



class Kunder
{
private:
	int sisteKundeNummer;	//Liste over kunder.
	List* listeKunde;
public:
	Kunder();
	~Kunder();
	void handling();		//Kunde meny etter bruker har tastet "k"
	void registrerKunde();	//Registrerer kunder.
	void displayValg();		//Spoer om det skal displayes en enkel kunde eller alle.
	void displayEnkel();	//Displayer en enkel kunde etter kundenummer.
	void displyMedGittNavn();
	void redigerKunde();	//Endre kundestatus.
	void lesFraFil();
	void skrivTilFil();
    int returnerSiste();
};


#endif
