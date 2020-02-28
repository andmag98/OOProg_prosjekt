#include <iostream>
#include "ListTool2B.h"
#include "funksjoner.h"
#include "kunder.h"
#include "arrangementer.h"
#include "steder.h"

Kunder kundebase;
Steder stedbase;
Arrangementer arrangementbase;



int main()
{
    char kommando;

    skrivMeny();
  
    std::cout << "\n\n\tSkriv inn kommando: ";
    kommando = les();

    while (kommando != 'Q')
    {
      switch (kommando)
      {	
          case 'K':  kundebase.handling();				break;
          case 'S':  case 'O':
				 stedbase.handling(kommando);		    break;
          case 'A':	 arrangementbase.handling();		break;
          default:	 skrivMeny();						break;
      }
        std::cout << "\n\n\tSkriv inn kommando: ";
        kommando = les();
        
        arrangementbase.skrivTilFil();
        kundebase.skrivTilFil();
        stedbase.skrivTilFil();
      }
	
    std::cout << "\n\n";
	
    return 0;
}
