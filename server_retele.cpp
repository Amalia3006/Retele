#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Header.h"
#include <poll.h>

using namespace std;

struct trimise_de_client
{
	int index_tabla;
	int culoare;
	int tip;
	int cord_initiale_x;
	int cord_initiale_y;
	int cord_finale_x;
	int cord_finale_y;
} tdc;

int first;
int culoare_f;

TABLE *tabla[16];
int index_tabla;

int main()
{
	struct perechi_clienti
	{
		int player[2];
	} perechi_playeri[32];
	int numar_perechi_playeri = 0;

	//am creat soketul
	int skt;
	if (-1 == (skt = socket(AF_INET, SOCK_STREAM, 0)))
	{
		fprintf(stderr, "Eroare socket: %d\n", errno);
		exit(0);
	}

	{ // pt eroare 98 la bind ~> eroare 98 = Address already in use
		int value = 1;
		setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, (void *)&value, sizeof(value));
	}

	// atribui structul si familia pt soket
	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(9002);

	// asignez un struct sockaddr_in socketului care asculta conexiuni noi
	if (-1 == bind(skt, (struct sockaddr *)&client, sizeof(client)))
	{
		fprintf(stderr, "Eroare bind: %d\n", errno);
		exit(0);
	}

	//pot tine 5 conexiuni in coada pana le tratez
	if (-1 == listen(skt, 5))
	{
		fprintf(stderr, "Eroare listen: %d\n", errno);
		exit(0);
	}

	pollfd socketuri_deschise[32];
	int numar_sock_deschise = 0;

	socketuri_deschise[0].fd = skt;
	socketuri_deschise[0].events = POLLIN;
	numar_sock_deschise++;

	while (poll(socketuri_deschise, numar_sock_deschise, -1))
	{
		if (POLLIN & socketuri_deschise[0].revents)
		{ // client nou in coada
			int first = 0, culoare_f = 11;
			for (int i = 0; i < 2; i++)
			{ // conectez cate doi clienti
				// stabilesc: primul client = player1; clientul conectat al doilea = player 2;
				// iteratia 1: anunt clientul 1 ca e player 1
				// iteratia 2: anunt clientul 2 ca e player 2

				// fprintf(stderr, "astept client nou...\n");

				int temp = accept(socketuri_deschise[0].fd, NULL, NULL);
				if (temp == -1)
				{
					fprintf(stderr, "Eroare accept: %d\n", errno);
					continue; // continui cu urmatorul client
				}

				// fprintf(stderr, "client nou\n");

				socketuri_deschise[numar_sock_deschise].fd = temp;
				socketuri_deschise[numar_sock_deschise++].events = POLLIN;

				perechi_playeri[numar_perechi_playeri].player[i] = temp;

				if (0 > send(temp, &first, 4, 0))
				{
					fprintf(stderr, "Eroare send: %d\n", errno);
					exit(2);
				}
				if (0 > send(temp, &culoare_f, 4, 0))
				{
					fprintf(stderr, "Eroare send: %d\n", errno);
					exit(2);
				}
				if (0 > send(temp, &index_tabla, 4, 0))
				{
					fprintf(stderr, "Eroare send: %d\n", errno);
					exit(2);
				}

				first = 2;
				culoare_f = 12;
			}
			numar_perechi_playeri++;

			//initializez tabla abia dupa ce am 2 clienti conectati si o printez in terminalul serverului
			tabla[index_tabla] = new TABLE();
			tabla[index_tabla]->printtable();
			index_tabla++;
			cout << endl;
			cout << endl;
		}

		for (int i = 1; i < numar_sock_deschise; i++)
		{
			if (POLLIN & socketuri_deschise[i].revents)
			{
				int player1 = socketuri_deschise[i].fd;
				int res1 = recv(player1, &tdc, sizeof(tdc), 0);
				if (res1 == -1)
				{
					fprintf(stderr, "Eroare recv: %d\n", errno);
					close(player1);
					break;
				}
				else if (res1 == 0)
				{
					fprintf(stderr, "Client 1 s-a deconectat\n");
					close(player1);
					break;
				}
				// in server afisez mutarea primita
				cout << "index_tabla: " << tdc.index_tabla << endl;
				// cout << "culoare: " << tdc.culoare << endl;
				// cout << "tip: " << tdc.tip << endl;
				cout << "cord_initiale_x: " << tdc.cord_initiale_x << endl;
				cout << "cord_initiale_y: " << tdc.cord_initiale_y << endl;
				cout << "cord_finale_x: " << tdc.cord_finale_x << endl;
				cout << "cord_finale_y: " << tdc.cord_finale_y << endl;

				//verifica mutarea
				int index = tdc.index_tabla;
				if (tabla[index]->returnez_culoare(tdc.cord_initiale_x, tdc.cord_initiale_y) == culoare_f)
					//if (t.mutare(tdc.cord_initiale_x, tdc.cord_initiale_y, tdc.cord_finale_x,tdc.cord_finale_y)==1) mutare invalida
					tabla[index]->mutare(tdc.cord_initiale_x, tdc.cord_initiale_y, tdc.cord_finale_x, tdc.cord_finale_y);
				tabla[index]->printtable();
				cout << endl;
				cout << endl;

				// caut clientul doi
				int player2;
				for (int i = 0; i < numar_perechi_playeri; i++)
				{
					if (perechi_playeri[i].player[0] == player1)
						player2 = perechi_playeri[i].player[1];
					else if (perechi_playeri[i].player[1] == player1)
						player2 = perechi_playeri[i].player[0];
				}

				//fiind valida/invalida, trimit catre player 1 care aplica local pt vizualizarea tablei
				if (0 > send(player1, &tdc, sizeof(tdc), 0))
				{
					fprintf(stderr, "Eroare send: %d\n", errno);
					break;
				}
				//trimit catre player 2
				if (0 > send(player2, &tdc, sizeof(tdc), 0))
				{
					fprintf(stderr, "Eroare send: %d\n", errno);
					break;
				}

				if (tabla[index]->sah_mat(tdc.culoare))
				{
					printf("Castigator: %s\n", (tdc.culoare == ALB ? "client1" : "client2"));

					trimise_de_client temp = {-1, -1, -1, -1, -1, -1, -1};
					send(player1, &temp, sizeof(temp), 0);

					trimise_de_client temp2 = {-2, -2, -2, -2, -2, -2, -2};
					send(player2, &temp2, sizeof(temp2), 0);
				}
			}
		}
		// fprintf(stderr, "detalii: %d    %d\n", numar_sock_deschise, numar_perechi_playeri);
	}

	//inchidem soketul
	// close(sktc1);
	// close(sktc2);

	return 0;
}