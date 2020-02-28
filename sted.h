#ifndef __STED_H                  //  Ensures that this file will be
#define __STED_H                  //    included only ONCE in each file.
#include "ListTool2B.h"

class Sted : public TextElement
{
private:
	int antOppsett;
	List* oppsett[5+1];
public:
	Sted();
	Sted(char* stedNavn);
	Sted(char* txt, std::ifstream & inn);
	~Sted();
	void skrivTilFil(std::ofstream & ut);
	void lesFraFil(std::ifstream & inn);
	void display();
	void displayOppsett();
	void oppsettNytt();
	void oppsettEndre();
	void oppsettValg(int o);
	List* kopier(int nr, bool brukesIArrangement);
    int hvorMangeOppsett();

};

#endif
