#include "Header.h"

PIESE::PIESE(int tip, int culoare)
{
	this->culoare = culoare;
	this->tip = tip;
}

PIESE::~PIESE()
{
}

void PIESE::SHOWculoarePAWNS()
{
	if (culoare == 11)
		cout << "ALB";
	else if (culoare == 12)
		cout << "NEGRU";
}
int PIESE::GETculoarePAWNS()
{
	return culoare;
}

void PIESE::SHOWtip()
{
	if (tip == 1)
		cout << "REGE";
	else if (tip == 2)
		cout << "REGINA";
	else if (tip == 3)
		cout << "TURA";
	else if (tip == 4)
		cout << "NEBUN";
	else if (tip == 5)
		cout << "CAL";
	else if (tip == 6)
		cout << "PION";
}
int PIESE::GETtip()
{
	return tip;
}

TABLE::TABLE(const char *i)
{
	if (strcmp("alb", i) == 0 || strcmp("ALB", i) == 0 || strcmp("Alb", i) == 0)
	{
		piesa[0][0] = new PIESE(TURA, ALB);
		piesa[0][1] = new PIESE(CAL, ALB);
		piesa[0][2] = new PIESE(NEBUN, ALB);
		piesa[0][3] = new PIESE(REGINA, ALB);
		piesa[0][4] = new PIESE(REGE, ALB);
		piesa[0][5] = new PIESE(NEBUN, ALB);
		piesa[0][6] = new PIESE(CAL, ALB);
		piesa[0][7] = new PIESE(TURA, ALB);
		for (int j = 0; j < 8; j++)
			piesa[1][j] = new PIESE(PION, ALB);

		for (int i = 2; i < 6; i++)
			for (int j = 0; j < 8; j++)
				piesa[i][j] = nullptr;

		for (int j = 0; j < 8; j++)
		piesa[6][j] = new PIESE(PION, NEGRU);
		piesa[7][0] = new PIESE(TURA, NEGRU);
		piesa[7][1] = new PIESE(CAL, NEGRU);
		piesa[7][2] = new PIESE(NEBUN, NEGRU);
		piesa[7][3] = new PIESE(REGINA, NEGRU);
		piesa[7][4] = new PIESE(REGE, NEGRU);
		piesa[7][5] = new PIESE(NEBUN, NEGRU);
		piesa[7][6] = new PIESE(CAL, NEGRU);
		piesa[7][7] = new PIESE(TURA, NEGRU);
	}

	if (strcmp("negru", i) == 0 || strcmp("Negru", i) == 0 || strcmp("NEGRU", i) == 0)
	//else
	{
		piesa[0][0] = new PIESE(TURA, NEGRU);
		piesa[0][1] = new PIESE(CAL, NEGRU);
		piesa[0][2] = new PIESE(NEBUN, NEGRU);
		piesa[0][3] = new PIESE(REGINA, NEGRU);
		piesa[0][4] = new PIESE(REGE, NEGRU);
		piesa[0][5] = new PIESE(NEBUN, NEGRU);
		piesa[0][6] = new PIESE(CAL, NEGRU);
		piesa[0][7] = new PIESE(TURA, NEGRU);
		for (int j = 0; j < 8; j++)
			piesa[1][j] = new PIESE(PION, NEGRU);

		for (int i = 2; i < 6; i++)
			for (int j = 0; j < 8; j++)
				piesa[i][j] = nullptr;

		for (int j = 0; j < 8; j++)
		piesa[6][j] = new PIESE(PION, ALB);
		piesa[7][0] = new PIESE(TURA, ALB);
		piesa[7][1] = new PIESE(CAL, ALB);
		piesa[7][2] = new PIESE(NEBUN, ALB);
		piesa[7][3] = new PIESE(REGINA, ALB);
		piesa[7][4] = new PIESE(REGE, ALB);
		piesa[7][5] = new PIESE(NEBUN, ALB);
		piesa[7][6] = new PIESE(CAL, ALB);
		piesa[7][7] = new PIESE(TURA, ALB);
	}
}

TABLE::~TABLE()
{
}

void TABLE::printtable()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			if (nullptr == piesa[i][j])
				cout << "-"
					 << "\t";
			else

				cout << piesa[i][j]->GETculoarePAWNS() << " " << piesa[i][j]->GETtip() << "\t";
		cout << endl;
	}
}

int TABLE::returnez_culoare(int x, int y)
{
	if (x < 0 || x >= 8 || y < 0 || y >= 8 || piesa[x][y] == nullptr)
	{
		printf("piesa invalida\n");
		return -1;
	}
	int b; //culoare piesei
	b = piesa[x][y]->GETculoarePAWNS();
	return b;
}
int TABLE::returnez_tip(int x, int y)
{
	if (x < 0 || x >= 8 || y < 0 || y >= 8 || piesa[x][y] == nullptr)
	{
		printf("piesa invalida\n");
		return -1;
	}
	int a; //tipul piesei
	a = piesa[x][y]->GETtip();
	return a;
}

int TABLE::sah_mat(int cul)
{
	int regeI = -1, regeJ = -1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (piesa[i][j] != nullptr && piesa[i][j]->GETtip() == REGE && piesa[i][j]->GETculoarePAWNS() == cul)
			{
				regeI = i;
				regeJ = j;
			}
		}
	}
	if (regeI == -1 || regeJ == -1)
	{
		printf("Rege invalid\n");
		return -1;
	}

	int count_piese = 0;
	;
	const int cul_inamica = cul == ALB ? NEGRU : ALB;

	if (regeI - 1 >= 0 && piesa[regeI - 1][regeJ] != nullptr && piesa[regeI - 1][regeJ]->GETculoarePAWNS() == cul_inamica)
		count_piese++;

	if (regeI - 1 >= 0 && regeJ + 1 < 8 && piesa[regeI - 1][regeJ + 1] != nullptr && piesa[regeI - 1][regeJ]->GETculoarePAWNS() == cul_inamica)
		count_piese++;

	if (regeI + 1 < 8 && piesa[regeI][regeJ + 1] != nullptr && piesa[regeI - 1][regeJ]->GETculoarePAWNS() == cul_inamica)
		count_piese++;

	if (regeI + 1 < 8 && regeJ + 1 < 8 && piesa[regeI + 1][regeJ + 1] != nullptr && piesa[regeI - 1][regeJ]->GETculoarePAWNS() == cul_inamica)
		count_piese++;

	if (regeI + 1 < 8 && piesa[regeI + 1][regeJ] != nullptr && piesa[regeI - 1][regeJ]->GETculoarePAWNS() == cul_inamica)
		count_piese++;

	if (regeI + 1 < 8 && regeJ - 1 >= 0 && piesa[regeI + 1][regeJ - 1] != nullptr && piesa[regeI - 1][regeJ]->GETculoarePAWNS() == cul_inamica)
		count_piese++;

	if (regeJ - 1 >= 0 && piesa[regeI][regeJ - 1] != nullptr && piesa[regeI - 1][regeJ]->GETculoarePAWNS() == cul_inamica)
		count_piese++;

	if (regeI - 1 >= 0 && regeJ - 1 >= 0 && piesa[regeI - 1][regeJ - 1] != nullptr && piesa[regeI - 1][regeJ]->GETculoarePAWNS() == cul_inamica)
		count_piese++;

	return count_piese >= 4;
}

void TABLE::mutare(int x, int y, int n, int m) //a tipul pionulu si b culoarea, x&y coordonate
{
	if (x < 0 || x >= 8 || y < 0 || y >= 8 ||
		piesa[x][y] == nullptr || piesa[x][y] == nullptr)
	{
		cout << endl
			 << "mutare imposibila" << endl
			 << endl;
		return; // ??
	}
	int a; //tipul piesei
	a = piesa[x][y]->GETtip();
	int b; //culoare piesei
	b = piesa[x][y]->GETculoarePAWNS();
	if (!(piesa[n][m])) //ma asigur ca pot muta pe orice spatiu gol, unde n-am piese
	{					//cout << "true1" << endl << endl;

		if (a == PION)				  //piesa aleasa este pion
			mutarepion(x, y, n, m);   //x&y coordonate
		if (a == CAL)				  //piesa aleasa este cal
			mutarecal(x, y, n, m);	//x&y coordonate
		if (a == NEBUN)				  //piesa aleasa este nebun
			mutarenebun(x, y, n, m);  //x&y coordonate
		if (a == TURA)				  //piesa aleasa este tura
			mutaretura(x, y, n, m);   //x&y coordonate
		if (a == REGINA)			  //piesa aleasa este regina
			mutareregina(x, y, n, m); //x&y coordonate
		if (a == REGE)				  //piesa aleasa este rege
			mutarerege(x, y, n, m);   //x&y coordonate
	}
	else
	{
		int d;
		d = piesa[n][m]->GETculoarePAWNS();
		if (b != d) // ma asigur ca nu imi mananc piese de culoarea mea
		{
			if (a == PION)				  //piesa aleasa este pion
				mutarepion(x, y, n, m);   //x&y coordonate
			if (a == CAL)				  //piesa aleasa este cal
				mutarecal(x, y, n, m);	//x&y coordonate
			if (a == NEBUN)				  //piesa aleasa este nebun
				mutarenebun(x, y, n, m);  //x&y coordonate
			if (a == TURA)				  //piesa aleasa este tura
				mutaretura(x, y, n, m);   //x&y coordonate
			if (a == REGINA)			  //piesa aleasa este regina
				mutareregina(x, y, n, m); //x&y coordonate
			if (a == REGE)				  //piesa aleasa este rege
				mutarerege(x, y, n, m);   //x&y coordonate
		}
		else
			cout << endl
				 << "mutare imposibila" << endl
				 << endl;
	}
}

int TABLE::mutarepion(int x, int y, int n, int m)
{
	int verificare = 1;
	if (((x - 1) == n) && (m == y))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if (((x + 1) == n) && (m == y))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if ((x == n) && ((m + 1) == y))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if ((x == n) && ((m - 1) == y))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if (((x - 2) == n) && ((y + 2) == m))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		piesa[x - 1][y + 1] = nullptr; //sterg piesa "mancata"
		verificare--;
	}
	else if (((x - 2) == n) && ((y - 2) == m))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		piesa[x - 1][y - 1] = nullptr;
		verificare--;
	}
	else if (((x + 2) == n) && ((y + 2) == m))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		piesa[x + 1][y + 1] = nullptr;
		verificare--;
	}
	else if (((x + 2) == n) && ((y - 2) == m))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		piesa[x + 1][y - 1] = nullptr;
		verificare--;
	}
	else if (verificare == 1)
		return verificare; //serverul foloseste variabila pt a verifica
	return 0;
}
int TABLE::mutarecal(int x, int y, int n, int m)
{
	int verificare = 1;
	if ((x + 2 >= 0) && (y + 1 >= 0) && (x + 2 < 8) && (y + 1 < 8) && (n == x + 2) && (m == y + 1))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if ((x + 2 >= 0) && (y - 1 >= 0) && (x + 2 < 8) && (y - 1 < 8) && (n == x + 2) && (m == y - 1))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if ((x - 2 >= 0) && (y - 1 >= 0) && (x - 2 < 8) && (y - 1 < 8) && (n == x - 2) && (m == y - 1))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if ((x - 2 >= 0) && (y + 1 >= 0) && (x - 2 < 8) && (y + 1 < 8) && (n == x - 2) && (m == y + 1))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if ((x + 1 >= 0) && (y + 2 >= 0) && (x + 1 < 8) && (y + 2 < 8) && (n == x + 1) && (m == y + 2))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else

		if ((x - 1 >= 0) && (y + 2 >= 0) && (x - 1 < 8) && (y + 2 < 8) && (n == x - 1) && (m == y + 2))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if ((x - 1 >= 0) && (y - 2 >= 0) && (x - 1 < 8) && (y - 2 < 8) && (n == x - 1) && (m == y - 2))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else

		if ((x + 1 >= 0) && (y - 2 >= 0) && (x + 1 < 8) && (y - 2 < 8) && (n == x + 1) && (m == y - 2))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		verificare--;
	}
	else if (verificare == 1)
		return verificare; //serverul foloseste variabila pt a verifica
	return 0;
}
int TABLE::mutarenebun(int x, int y, int n, int m)
{
	int c = 0;
	if ((n - x == m - y) && (n > x) && (m > y) && (0 <= x) && (0 <= y) && (8 > n) && (8 > m)) //(a,b) -> (a+n,b+n)
	{
		if (((x + 1) != n) && ((y + 1) != m))
		{
			for (int i = x + 1; i < n; i++)
				for (int j = y + 1; j < m; j++)
					if (piesa[i][j] != nullptr)
						c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((x - n == y - m) && (n < x) && (m < y) && (0 <= n) && (0 <= m) && (8 > x) && (8 > y)) //(a,b) -> (a-n,b-n)
	{
		if (((x - 1) != n) && ((y - 1) != m))
		{
			for (int i = x; i > n; i--)
				for (int j = y; j > m; j--)
					if (piesa[i][j] != nullptr)
						c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((x - n == m - y) && (n < x) && (m > y) && (0 <= n) && (0 <= y) && (8 > x) && (8 > m)) //(a,b) -> (a-n,b+n)
	{
		if (((x - 1) != n) && ((y + 1) != m))
		{
			for (int i = x; i > n; i--)
				for (int j = y; j < m; j++)
					if (piesa[i][j] != nullptr)
						c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((n - x == y - m) && (n > x) && (m < y) && (0 <= x) && (0 <= m) && (8 > n) && (8 > y)) //(a,b) -> (a+n,b-n)
	{
		if (((x - 1) != n) && ((y + 1) != m))
		{
			for (int i = x; i > n; i++)
				for (int j = y; j < m; j--)
					if (piesa[i][j] != nullptr)
						c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	return 0;
}
int TABLE::mutaretura(int x, int y, int n, int m)
{
	int c = 0;
	if ((0 <= x) && (x < n) && (n < 8) && (m == y)) // (a,b) -> (a+n,b)
	{
		if (((x + 1) != n))
		{
			for (int i = x + 1; i < n; i++)
				if (piesa[i][y] != nullptr)
					c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((0 <= n) && (x > n) && (x < 8) && (m == y)) // (a,b) -> (a-n,b)
	{
		if (((x - 1) != n))
		{
			for (int i = x + 1; i > n; i--)
				if (piesa[i][y] != nullptr)
					c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((0 <= y) && (y < m) && (m < 8) && (n == x)) // (a,b) -> (a,b+n)
	{
		if (((y + 1) != m))
		{
			for (int i = y + 1; i < m; i++)
				if (piesa[x][i] != nullptr)
					c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((0 <= m) && (m < y) && (y < 8) && (n == x)) // (a,b) -> (a,b-n)
	{
		if (((y - 1) != m))
		{
			for (int i = y + 1; i > m; i--)
				if (piesa[x][i] != nullptr)
					c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}

	return 0;
}
int TABLE::mutareregina(int x, int y, int n, int m)
{
	int c = 0;
	if ((0 <= x) && (x < n) && (n < 8) && (m == y)) // (a,b) -> (a+n,b)
	{
		if (((x + 1) != n))
		{
			for (int i = x + 1; i < n; i++)
				if (piesa[i][y] != nullptr)
					c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((0 <= n) && (x > n) && (x < 8) && (m == y)) // (a,b) -> (a-n,b)
	{
		if (((x - 1) != n))
		{
			for (int i = x + 1; i > n; i--)
				if (piesa[i][y] != nullptr)
					c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((0 <= y) && (y < m) && (m < 8) && (n == x)) // (a,b) -> (a,b+n)
	{
		if (((y + 1) != m))
		{
			for (int i = y + 1; i < m; i++)
				if (piesa[x][i] != nullptr)
					c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((0 <= m) && (m < y) && (y < 8) && (n == x)) // (a,b) -> (a,b-n)
	{
		if (((y - 1) != m))
		{
			for (int i = y + 1; i > m; i--)
				if (piesa[x][i] != nullptr)
					c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((n - x == m - y) && (n > x) && (m > y) && (0 <= x) && (0 <= y) && (8 > n) && (8 > m)) //(a,b) -> (a+n,b+n)
	{
		if (((x + 1) != n) && ((y + 1) != m))
		{
			for (int i = x + 1; i < n; i++)
				for (int j = y + 1; j < m; j++)
					if (piesa[i][j] != nullptr)
						c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((x - n == y - m) && (n < x) && (m < y) && (0 <= n) && (0 <= m) && (8 > x) && (8 > y)) //(a,b) -> (a-n,b-n)
	{
		if (((x - 1) != n) && ((y - 1) != m))
		{
			for (int i = x; i > n; i--)
				for (int j = y; j > m; j--)
					if (piesa[i][j] != nullptr)
						c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((x - n == m - y) && (n < x) && (m > y) && (0 <= n) && (0 <= y) && (8 > x) && (8 > m)) //(a,b) -> (a-n,b+n)
	{
		if (((x - 1) != n) && ((y + 1) != m))
		{
			for (int i = x; i > n; i--)
				for (int j = y; j < m; j++)
					if (piesa[i][j] != nullptr)
						c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	if ((n - x == y - m) && (n > x) && (m < y) && (0 <= x) && (0 <= m) && (8 > n) && (8 > y)) //(a,b) -> (a+n,b-n)
	{
		if (((x - 1) != n) && ((y + 1) != m))
		{
			for (int i = x; i > n; i++)
				for (int j = y; j < m; j--)
					if (piesa[i][j] != nullptr)
						c = 9; // "mutare care nu respecta regulile";
		}
		if (c == 0)
		{
			piesa[n][m] = piesa[x][y];
			piesa[x][y] = nullptr;
		}
		else
			cout << "mutare care nu respecta regulile" << endl;
	}
	return 0;
}
int TABLE::mutarerege(int x, int y, int n, int m)
{
	if (((x - 1) == n) && ((y + 1) == m))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		piesa[x - 1][y] = nullptr;
	}
	if (((x - 1) == n) && ((y - 1) == m))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		piesa[x - 1][y] = nullptr;
	}
	if (((x + 1) == n) && ((y + 1) == m))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		piesa[x + 1][y] = nullptr;
	}
	if (((x + 1) == n) && ((y - 1) == m))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
		piesa[x + 1][y] = nullptr;
	}
	if (((x - 1) == n) && (m == y))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
	}
	if (((x + 1) == n) && (m == y))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
	}
	if ((x == n) && ((m + 1) == y))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
	}
	if ((x == n) && ((m - 1) == y))
	{
		piesa[n][m] = piesa[x][y];
		piesa[x][y] = nullptr;
	}

	return 0;
}