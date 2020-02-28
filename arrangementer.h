#ifndef __ARRANGEMENTER_H                  //  Ensures that this file will be
#define __ARRANGEMENTER_H                  //    included only ONCE in each file.
#include "ListTool2B.h"
#include "arrangement.h"

class Arrangementer
{
private: 
	int sisteArrangement;				// siste brukt 
	List* listeArrangement;				// liste med arrangement-objekter
public:
	Arrangementer();
	~Arrangementer();
    void skrivTilFil();
    void lesFraFil();
    void handling();
    void nyttArrangement();
    void arrangementDisplay();
    void alleA();
    void navnA();
    void diaplayArramnegentene(int t);
    void slettArrangement();
    void alleAMedKopi();
    void kjopBillett();

};



#endif
