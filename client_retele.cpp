#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Header.h"

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

int culoare_f;

void citesteMutarea(trimise_de_client &tdc)
{
    cout << "cord_initiale_x: ";
    cin >> tdc.cord_initiale_x;
    cout << "cord_initiale_y: ";
    cin >> tdc.cord_initiale_y;
    cout << "cord_finale_x: ";
    cin >> tdc.cord_finale_x;
    cout << "cord_finale_y: ";
    cin >> tdc.cord_finale_y;
};

int main()
{
    //vom crea socketul
    int skt = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;

    /* umplem structura folosita de server */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(9002);

    int status_conectare = connect(skt, (struct sockaddr *)&server, sizeof(server));
    //verificam daca conexiunea e ok
    if (status_conectare == -1)
    {
        fprintf(stderr, "Eroare la conectarea: %d\n", errno);
        exit(0);
    }

    trimise_de_client tdc;

    char i[10] = "alb";
    TABLE t(i);
    //verific daca e cel ce incepe jocul
    int first;

    int res3 = recv(skt, &first, sizeof(first), 0);
    if (res3 == -1)
    {
        fprintf(stderr, "Eroare recv: %d\n", errno);
        exit(5);
    }
    int res4 = recv(skt, &culoare_f, sizeof(first), 0);
    if (res4 == -1)
    {
        fprintf(stderr, "Eroare recv: %d\n", errno);
        exit(5);
    }
    int res5 = recv(skt, &tdc.index_tabla, sizeof(tdc.index_tabla), 0);
    if (res5 == -1)
    {
        fprintf(stderr, "Eroare recv: %d\n", errno);
        exit(5);
    }

    //initializez tabla de sah. playerul o poate vedea inainte sa aleaga mutarea
    t.printtable();
    cout << endl;
    cout << endl;

    if (first == 0)
    {

        citesteMutarea(tdc); //introduc mutarea

        if (0 > send(skt, &tdc, sizeof(tdc), 0))
        {
            fprintf(stderr, "Eroare send: %d\n", errno);
            exit(3);
        }
        //primesc mesaj de la server valid/invalid + printez tabla
        int res = recv(skt, &tdc, sizeof(tdc), 0);
        if (res == -1)
        {
            fprintf(stderr, "Eroare recv: %d\n", errno);
            exit(3);
        }
        if (t.returnez_culoare(tdc.cord_initiale_x, tdc.cord_initiale_y) == culoare_f)
            t.mutare(tdc.cord_initiale_x, tdc.cord_initiale_y, tdc.cord_finale_x, tdc.cord_finale_y);
        t.printtable();
        cout << endl;
        cout << endl;
    }

    while (1)
    {
        //primesc prima mutare de la server + printez tabla
        int res = recv(skt, &tdc, sizeof(tdc), 0);
        if (res == -1)
        {
            fprintf(stderr, "Eroare recv: %d\n", errno);
            break;
        }
        //actualizez tabla + afisez
        if (t.returnez_culoare(tdc.cord_initiale_x, tdc.cord_initiale_y) != culoare_f) // aplic doar mutarile de culoare opusa mie
            t.mutare(tdc.cord_initiale_x, tdc.cord_initiale_y, tdc.cord_finale_x, tdc.cord_finale_y);
        t.printtable();
        cout << endl;
        cout << endl;

        if (tdc.index_tabla == -1)
        {
            printf("Ai castigat!\n");
            getchar();
            exit(0);
        }
        else if (tdc.index_tabla == -2)
        {
            printf("Ai pierdut!\n");
            getchar();
            exit(0);
        }

        citesteMutarea(tdc);

        //primesc mesaj de la server valid/invalid + printez tabla
        if (0 > send(skt, &tdc, sizeof(tdc), 0))
        {
            fprintf(stderr, "Eroare send: %d\n", errno);
            exit(3);
        }
        //primesc mesaj de la server valid/invalid + printez tabla
        res = recv(skt, &tdc, sizeof(tdc), 0);
        if (res == -1)
        {
            fprintf(stderr, "Eroare recv: %d\n", errno);
            exit(3);
        }

        if (t.returnez_culoare(tdc.cord_initiale_x, tdc.cord_initiale_y) == culoare_f)
            t.mutare(tdc.cord_initiale_x, tdc.cord_initiale_y, tdc.cord_finale_x, tdc.cord_finale_y);
        t.printtable();
        cout << endl;
        cout << endl;
    }

    close(skt);

    return 0;
}