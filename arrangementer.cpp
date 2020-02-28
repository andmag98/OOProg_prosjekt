#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <fstream>
#include "arrangementer.h"
#include "arrangement.h"
#include "funksjoner.h"
#include "ListTool2B.h"
#include "conster.h"
#include "steder.h"
#include "string.h"
#include "kunder.h"
#include "kunde.h"
#include <stdio.h>
#include <string>
#include <cstring>
#include <cstdio>


extern Steder stedbase;
extern Kunder kundebase;


Arrangementer::Arrangementer()
{
    listeArrangement = new List(Sorted);    //lager sortert liste
    sisteArrangement = 0;                   //nulstiller sistearrangement
    lesFraFil();                            //leser fra fil
}

Arrangementer::~Arrangementer()
{
	delete listeArrangement;            //sletter arrangementer-objekt
}

void Arrangementer::skrivTilFil()
{
    //aapner filen ARRANGEMENTER.TXT
    std::ofstream utFil("ARRANGEMENTER.TXT");
    //lager en peker som peker på arrangementobjekter
    Arrangement* bufferArrangement;
    //skriver paa filen hvor mange arrangementer vi har
    utFil << "Antall arrangementer: " << sisteArrangement << '\n';
    
    //lokken gaar for alle arrangementene vaare
    for (int i = 1; i <= sisteArrangement; i++)
    {
        //arrangementpekeren peker paa objektet som blir tatt ut
        bufferArrangement = (Arrangement*)listeArrangement->removeNo(i);
        
        if (bufferArrangement)  //ikke er nullpointer
        {
            bufferArrangement->skrivTilFil(utFil);  //skriver til fil
            listeArrangement->add(bufferArrangement);   //legger tilbake i liste
        }
    }
}

void Arrangementer::lesFraFil()
{
    //filnavnet
    std::ifstream innFil("ARRANGEMENTER.TXT");
    if (innFil)
    {
        //ignorerer og leser inn
        innFil.ignore(sizeof("Antall arrangementer:")) >> sisteArrangement;
        innFil.ignore();
        char bufferTekst[STRLEN];
        Arrangement* bufferArrangement;
        //løkke som for for antall arrangementer
        for (int i = 1; i <= sisteArrangement; i++)
        {
            innFil.ignore(sizeof("Arrangements navn:"));
            innFil.getline(bufferTekst,STRLEN);
            //leger nytt arrangement
            bufferArrangement = new Arrangement(bufferTekst, innFil);
            //legger det til i listen
            listeArrangement->add(bufferArrangement);
        }
    }
}

void Arrangementer::handling()
{
    char kommando = les();
    switch (kommando)
    {
        case 'D':  arrangementDisplay();                       break;
        case 'N':  nyttArrangement();                           break;
        case 'S':  slettArrangement();                           break;
        case 'K':   kjopBillett();                             break;
        default:   std::cout <<
            "Andre kommando mÂ vÊre enten D, N, S eller K.";   break;
    }
}

void Arrangementer::arrangementDisplay()
{
    std::cout << "\n\nFOLGENDE KOMMANDOER ER LOVLIG:\n\n";
    std::cout << "\t1  = Alle arrangementer\n";
    std::cout << "\t2  = Arrangement navn\n";
    std::cout << "\t3  = Spillested\n";
    std::cout << "\t4  = Dato\n";
    std::cout << "\t5  = Type arrangement\n";
    std::cout << "\t6  = Artist\n";
    std::cout << "\t7  = Alle arrangementer med kopi\n";
    int kommando = les("Tall", 1,7);
    switch (kommando)
    {
        case 1:  alleA();                                       break;
        case 2:  navnA();                                       break;
        case 3:  diaplayArramnegentene(kommando);               break;
        case 4:  diaplayArramnegentene(kommando);               break;
        case 5:  diaplayArramnegentene(kommando);               break;
        case 6:  diaplayArramnegentene(kommando);               break;
        case 7:  alleAMedKopi();                                break;
        default:   std::cout <<
            "Feil kommando";   break;
    }
}

void Arrangementer::alleA()
{
    listeArrangement->displayList();    //diaplayer alt i listen
}

void Arrangementer::navnA()
{
    char bufferNavn[NVNLEN];  //Buffernavn som skal sammenlignes med alle arrangementene.
	les("\tHva heter arrangementet: ", bufferNavn, NVNLEN);
    listeArrangement->displayElement(bufferNavn);
}

void Arrangementer:: alleAMedKopi()
{
    Arrangement* bufferArrangement;
    //lokke som gaar for alle arrangementene
    for (int i = 1; i <= sisteArrangement; i++)
    {
        //fjerner arrangement nr i
        bufferArrangement = (Arrangement*)listeArrangement->removeNo(i);
        //leser inn dens kopi
        bufferArrangement->lesInnKopiFraFil(i);
        //diaplayer arrangementet
        bufferArrangement->display();
        //displayer oppsettet til arrangementet
        bufferArrangement->displayKopi();
        //sletter kopien av oppsettet
        bufferArrangement->slettKopi();
        //legger tilbake arrangementet i listen
        listeArrangement->add(bufferArrangement);
    }
}


void Arrangementer::nyttArrangement()
 {
     char bufferTekstSted[STRLEN];
     char bufferTekstArr[STRLEN];

     //leser inn stedsnavnet hvor arrangementet skal lages
	 les("Skriv inn stedsnavn: ", bufferTekstSted, STRLEN);
    
     int  nr, ant;
     Arrangement* bufferArrangement;

     //henter en tallverdi på om stedet finnes eller hvor mange oppsett stedet har oppsett
     ant = stedbase.hentOppsett(bufferTekstSted);

     if (ant == -1)
         std::cout << "\n\n\tIngen arrangementsted med dette navnet!\n\n";
     else if (ant == 0)
         std::cout << "\n\n\tIngen (stol)oppsett registrert på dette stedet!\n\n";
     else
     {
         //hvis stedet har oppsett og finnes leses arrangementsnavnet som lages
         les("Nytt arrangements navn: ", bufferTekstArr, STRLEN);
         //velger hvilket oppsett man vil bruke
         nr = les("Oppsettnummer", 1, ant);
         //lager det nye arrangementet
         bufferArrangement = new Arrangement(bufferTekstArr, ++sisteArrangement, bufferTekstSted, nr);
         //legger den til i listen
         listeArrangement->add(bufferArrangement);
     }
}

void Arrangementer::diaplayArramnegentene(int t)
{
    char bufferNavn[NVNLEN]; //Buffernavn som skal sammenlignes med alle arrangementer.
    int hjelpDato;           //Hjelpeint som leser bade dato og arrangementstype.
    
    //switch som gaar på tidligere valg
    switch (t)
    {
        case 3: les("Skriv inn Spillested: ", bufferNavn, STRLEN);      break;
        case 4: std::cout << "Skriv inn Dato: ";
                hjelpDato = les("\tHvilken dato: ", 20190101, 20303112);    break;
        case 5: std::cout << "Typer arrangement: 0-Musikk, 1-Sport, 2-Teater,\n\t\t3-Show, 4-Kino, 5-Familie, 6-Festival" << '\n';
                hjelpDato = les("\tHvilken type arrangement vil du se: ", 0, 6); break;
        case 6: les("Skriv inn artist: ", bufferNavn, STRLEN);          break;
    }
    Arrangement* bufferArrangement; //Bufferarrangement som skal hente ut hvert arrangement fra listen.
    //For loop som gaar gjennom alle arrangementer i listen:
    for (int i = 1; i <= sisteArrangement; i++)
    {
        //Henter ut arrangement nummer 'i' i listen:
        bufferArrangement = (Arrangement*) listeArrangement->removeNo(i);
        
        //swith som gaar paa tidligere valg:
        switch (t)
        {
            case 3:
                if (bufferArrangement->likSpillested(bufferNavn))
            {
                //Display arrangementet med lik spillested:
                bufferArrangement->display();
            }          break;
            case 4:
                if (bufferArrangement->likDato(hjelpDato))
            {
                //Display arrangementet med lik dato:
                bufferArrangement->display();
            }  break;
            case 5:
                if (bufferArrangement->likType(hjelpDato))
            {
                //Display arrangementet med lik type:
                bufferArrangement->display();
            }          break;
            case 6:
                if(bufferArrangement->likArtist(bufferNavn))
            {
                //Display arrangementet med lik artist:
                bufferArrangement->display();
            }
        }
        //Legg arrangementet tilbake i listen:
        listeArrangement->add(bufferArrangement);
    }
}

void Arrangementer:: kjopBillett()
{
    //henter kundenummeret som skal kjope billett
    int nr = kundebase.returnerSiste();
    int kNummer = les("Skriv inn kundenummer", 1, nr);
    
    int hjelpeVariabel = 0;   //hjelpevariabel som sier hvor mange arrangementer som heter det samme
    
    Arrangement* bufferArrangement;
    char bufferTekstArr[STRLEN];
    
    //ber om arrangementsnavn
    les("Skriv inn arrangementsnavn: ", bufferTekstArr, STRLEN);
    
    //hvis arranegemntet finnes loopes alle arrangementene for aa finne ut hvor mange der er av samme navn
    if (listeArrangement->inList(bufferTekstArr))
    {
        for (int i = 1; i<=sisteArrangement; i++)
        {
            //henter ut arrangement nr i
            bufferArrangement = (Arrangement*)listeArrangement->removeNo(i);
            //hvis arrangementet har samme navn som det brukeren skrev inn
            if (bufferArrangement->likArrNavn(bufferTekstArr))
            {
                bufferArrangement->display();   //diaplayer alle med dette navnet
                hjelpeVariabel++;               //antall arrangementer med samme navn plusses på
            }
            listeArrangement->add(bufferArrangement);   //legger dem tilbake i listen
        }
    }
    else        //hvis ikke arrangementsnavnet finnes i listen
    {
        std::cout << "\tAtrrangementet finnes ikke";
    }
    
    if (hjelpeVariabel == 1) //hvis det kun er et arrangement som heter det bruker skrev
    {
        //henter vi ut dette arangementet fra listen
        bufferArrangement = (Arrangement*)listeArrangement->remove(bufferTekstArr);
        //finner arrangementsnummeret fil arrangementet
        int valg = bufferArrangement->returnerArrNummer();
        bufferArrangement->lesInnKopiFraFil(valg);
        bufferArrangement->displayKopi();
        //kunden kjoper billett på dette arrangementet med kundenummeret
        bufferArrangement->kjopBillett(kNummer, valg);
        //sletter kopien fra minnet
        bufferArrangement->slettKopi();
        //legger arrangementet tilbake i listen
        listeArrangement->add(bufferArrangement);
        
        
    }
    else if(hjelpeVariabel > 1)      //hvis det er flere arrangementer med samme navn
    {
        std::cout << "\tDu må velge et av arrangementnummerene ovenfor: ";
        int valgtNummer;
        std::cin >> valgtNummer;
        for (int j = 1; j<=sisteArrangement; j++)
        {
            bufferArrangement = (Arrangement*)listeArrangement->removeNo(j);
            if (bufferArrangement->likNummer(valgtNummer))
            {
                std::cout << "\tDette arrangementet har du valgt\n";
                bufferArrangement->lesInnKopiFraFil(valgtNummer);
                bufferArrangement->displayKopi();
                bufferArrangement->kjopBillett(kNummer, valgtNummer);
                bufferArrangement->slettKopi();
                listeArrangement->add(bufferArrangement);
            }
            listeArrangement->add(bufferArrangement);
        }
    }
}

void Arrangementer::slettArrangement()
{
    int hjelpeVariabel = 0;   //hjelpevariabel som sier hvor mange arrangementer som heter det samme
    
    Arrangement* bufferArrangement;
    char bufferTekstArr[STRLEN];
    
    //ber om arrangementsnavn
    les("\tHva heter arrangementet du vil slette?: ", bufferTekstArr, STRLEN);
    
    //hvis arranegemntet finnes loopes alle arrangementene for aa finne ut hvor mange der er av samme navn
    if (listeArrangement->inList(bufferTekstArr))
    {
        for (int i = 1; i<=sisteArrangement; i++)
        {
            bufferArrangement = (Arrangement*)listeArrangement->removeNo(i);
            if (bufferArrangement->likArrNavn(bufferTekstArr))
            {
                bufferArrangement->display();   //diaplayer alle med dette navnet
                hjelpeVariabel++;
            }
            listeArrangement->add(bufferArrangement);   //legegr dem tilbake i listen
            
        }
    }
    else        //hvis ikke arrangementsnavnet finnes i listen
    {
        std::cout << "\tAtrrangementet finnes ikke";
    }
    
    if (hjelpeVariabel == 1) //hvis det kun er et arrangement som heter det bruker skrev
    {
        //fjerner arrangementet fra listen
        bufferArrangement = (Arrangement*)listeArrangement->remove(bufferTekstArr);
        //henter arrangementsnummeret
        int aNummer = bufferArrangement->returnerArrNummer();
        //sletter arrangementet
		delete bufferArrangement;
        //teller ned antall arrangementer
        sisteArrangement--;
        //finner filnavnet til det gitte arrangementet
        std::string fil("ARR_");
        fil = fil + std::to_string(aNummer);
        fil += ".TXT";
        char filnavn[STRLEN];
        strcpy(filnavn,fil.c_str());
        //sletter filen
        remove(filnavn);
        //løkke som kjorer gjennom alle arrangementer
        for (int i = 1; i<=sisteArrangement; i++)
        {
            bufferArrangement = (Arrangement*)listeArrangement->removeNo(i);
            int nr = bufferArrangement->returnerArrNummer();
            //hvis arrangementsnummeret er storre enn det som ble sletter
            if (nr > aNummer)
            {
                //reduserer vi nummeret
                bufferArrangement->reduserANummer();
                //finner navnet fil filen
                std::string fil("ARR_");
                fil = fil + std::to_string(i+1);
                fil += ".TXT";
                
                std::string fil2("ARR_");
                fil2 = fil2 + std::to_string(i);
                fil2 += ".TXT";
                
                char filnavn2[STRLEN];
                char filnavn[STRLEN];
                
                strcpy(filnavn,fil.c_str());
                strcpy(filnavn2,fil2.c_str());
                //døper om filen til et nummer lavere
                rename(filnavn, filnavn2);
            }
            listeArrangement->add(bufferArrangement);
        }
    
    }
    else if(hjelpeVariabel > 1)      //hvis det er flere arrangementer med samme navn
    {
        std::cout << "\tDu må velge et arrangementnummer ovenfor: ";
        int valgtNummer;
        std::cin >> valgtNummer;
        for (int j = 1; j<=sisteArrangement; j++)
        {
            bufferArrangement = (Arrangement*)listeArrangement->removeNo(j);
            if (bufferArrangement->likNummer(valgtNummer))
            {
                std::cout << "\tDette arrangementet har du valgt\n";
                bufferArrangement->display();
				delete bufferArrangement;
                sisteArrangement--;
                std::string fil("ARR_");
                fil = fil + std::to_string(valgtNummer);
                fil += ".TXT";
                char filnavn[STRLEN];
                strcpy(filnavn,fil.c_str());
                remove(filnavn);
                for (int i = 1; i<=sisteArrangement; i++)
                {
                    bufferArrangement = (Arrangement*)listeArrangement->removeNo(i);
                    int arrNummerer = bufferArrangement->returnerArrNummer();
                    if (arrNummerer>valgtNummer)
                    {
                        bufferArrangement->reduserANummer();
                        std::string fil("ARR_");
                        fil = fil + std::to_string(i+1);
                        fil += ".TXT";
                        
                        std::string fil2("ARR_");
                        fil2 = fil2 + std::to_string(i);
                        fil2 += ".TXT";
                        
                        char filnavn2[STRLEN];
                        char filnavn[STRLEN];
                        
                        strcpy(filnavn,fil.c_str());
                        strcpy(filnavn2,fil2.c_str());
                        rename(filnavn, filnavn2);
                    }
                    listeArrangement->add(bufferArrangement);
                    
                }
            }
            listeArrangement->add(bufferArrangement);
        }
    }
}



