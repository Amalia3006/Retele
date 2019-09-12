#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string.h>

#define NEGRU 12
#define ALB 11

#define REGE 1
#define REGINA 2
#define TURA 3
#define NEBUN 4
#define CAL 5
#define PION 6

using namespace std;

class PIESE
{
  private:
	int culoare; //11 reprezinta alb, 12 reprezinta negru also sunt definite
	int tip;	 // aici am asa: 1=REGE; 2=REGINA; 3=TURA; 4=NEBUN; 5=CAL; 6=PION also sunt definite;
  public:
	PIESE(int culoare, int tip);
	~PIESE();

	void SHOWtip(); //AFISEAZA tipul pionului
	int GETtip();   //RETURNEAZA codul tipului pionului ales de mine

	void SHOWculoarePAWNS(); //AFISEAZA culoarea pionului
	int GETculoarePAWNS();   //returneaza codul culorii ales de mine
};

class TABLE
{
  private:
	PIESE *piesa[8][8];

  public:
	TABLE(const char *i = "alb");
	~TABLE();

	void printtable();

	int returnez_culoare(int x, int y);
	int returnez_tip(int x, int y);

	int sah_mat(int cul);

	void mutare(int x, int y, int n, int m); //imi alege ce tip de mutare am nev + retin coordonatele piesei + n&m unde vreau sa ajunga
	int mutarepion(int x, int y, int n, int m);
	int mutarecal(int x, int y, int n, int m);
	int mutarenebun(int x, int y, int n, int m);
	int mutaretura(int x, int y, int n, int m);
	int mutareregina(int x, int y, int n, int m);
	int mutarerege(int x, int y, int n, int m);
};

#endif
