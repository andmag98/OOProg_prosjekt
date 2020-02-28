#ifndef __STEDER_H                  //  Ensures that this file will be
#define __STEDER_H                  //    included only ONCE in each file.
#include "ListTool2B.h"


class Steder
{
private: 
	List* listeSted;
public: 
	Steder();
	~Steder();
	void handling(char k);
	void skrivTilFil();
	void lesFraFil();
	void stedDisplay();
	void nyttSted();
	void oppsettDisplay();
	void nyttOppsett();
	void endreOppsett();
    List* kopier(char* nvn, int nr, bool brukesIArrangement);
    int hentOppsett(char* nvn);
};


#endif
