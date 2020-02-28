#ifndef __FUNKSJONER_H              //  Ensures that this file will be
#define __FUNKSJONER_H              //    included only ONCE in each file.

void skrivMeny();							// meny for kommandoene
char les();												// bokstav
int les(const char t[], const int min, const int max);  // int
void les(const char t[], char s[], const int LEN);		// tekst
char* lesChPointer(const char t[]);			// lese char pointere
void understrek(std::ofstream & ut, const char v[], int n); // utseende billett

#endif

