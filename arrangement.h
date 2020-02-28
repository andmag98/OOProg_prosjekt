#ifndef __ARRANGEMENT_H                 //  Ensures that this file will be
#define __ARRANGEMENT_H                  //    included only ONCE in each file.
#include "ListTool2B.h"
#include <fstream>
#include "enum.h"



class Arrangement : public TextElement		// sortert på navn
{
  private:
    char* spilleSted;
    char* artist;
    int dato;
    int time;
    int minutt;
    int arrangementNr;
    enum arrType type;
    List * kopi;
  public:
    Arrangement(char* nvn, int nr, char* sted, int nummer);
    Arrangement(char* txt, std::ifstream & inn);
    ~Arrangement();
    void display();
    void skrivTilFil(std::ofstream & ut);
    void lesFraFil(std::ifstream & inn);
    bool likArrNavn(char* nvn);
    bool likSpillested(char* nvn);
    bool likDato(int n);
    bool likArtist(char* nvn);
    bool likType(int n);
    bool likNummer(int n);
    void lesInnKopiFraFil(int nr);
    void displayKopi();
    int returnerArrNummer();
    void slettKopi();
    void kjopBillett(int nr, int aNummer);
    void skrivKopiTilFil(int nr);
    void reduserANummer();
};



#endif
