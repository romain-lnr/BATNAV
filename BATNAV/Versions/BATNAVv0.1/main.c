/**
 * Auteur:      R. Lenoir (CPNV)
 * Date:        02.03.2022
 * Titre:       BATNAV
 * Description: Ce projet, sous forme d'une bataille navale pur et dur, permet de tester le joueur dans un défi afin de trouver et de couler les bateaux de la grille choisit.
 */

//Les librairies
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//Les contents de grilles :
#define STLC 218 // ┌, Single Top Left Corner
#define STRC 191 // ┐, Single Top Right Corner
#define SBRC 217 // ┘, Single Bottom Right Corner
#define SVSB 179 // │, Single Vertical Simple Border
#define SVRB 180 // ┤, Single Vertical Right Border
#define SHSB 196 // ─, Single Horizontal Simple Border
#define SHBB 193 // ┴, Single Horizontal Bottom Border
#define SHTB 194 // ┬, Single Horizontal Top Border
#define SC   197 // ┼, Single Center
#define DTLC 201 // ╔, Double Top Left Corner
#define DTRC 187 // ╗, Double Top Right Corner
#define DBLC 200 // ╚, Double Bottom Left Corner
#define DBRC 188 // ╝, Double Bottom Right Corner
#define DVSB 186 // ║, Double Vertical Simple Border
#define DHSB 205 // ═, Double Horizontal Simple Border

void Aide() { // permet d'afficher l'aide dans l'option 5 du menu
    //Gestion des accents dans la console
    SetConsoleOutputCP(437);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",DTLC,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DTRC);
    printf("\n%c                                   %c",DVSB,DVSB);
    printf("\n%c          %s            %c",DVSB,"L'aide du jeu",DVSB);
    printf("\n%c                                   %c",DVSB,DVSB);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",DBLC,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DBRC);
    //Gestion des accents dans la console
    SetConsoleOutputCP(65001);
    printf("\nLa bataille navale à pour but de tester le joueur à travers une grille choisit aléatoirement\nPour gagner, il vous suffit donc de trouver et de détruire tous les bateaux qui s'opposeront à vous.\n");
    printf("\nDéroulement de la partie :\nLe joueur devra tirer à travers des cases prévu à cet effet en inscrivant des coordonnées (Ex:A2).\n");
    printf("\nLes joueurs ayant touché un bateau aura comme signe de case un 'X'.\nLes joueurs ayant raté un bateau aura comme signe de case un '0'.\nLes joueurs ayant coulé un bateau aura comme signe de case un 'C'.\n");
    printf("\nUne fois tous les bateaux coulés, le joueur revienda dans le menu principal.");
}
int CharToInt(char c) //Permet de changer la coordonnée "xy[0]" en entier
{
    switch (c)
    {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
        case 'I':
            return 8;
        case 'J':
            return 9;
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        case 'i':
            return 8;
        case 'j':
            return 9;
    }
}
char t(int n) //Permet de regrouper toutes les éventuels symboles en cours de partie
{
    if (n == 0) return ' ';
    if (n == 1) return 'O';
    if (n == 2) return 'X';
    if (n == 3) return 'C';
}
void clrscr() //Sert à actualiser l'écran en cours de partie
{
    system("@cls||clear");
}
void posShip(int ship[10][10], int nbrship, int shipsize[5]) //Sert à créer la table des bateaux afin de créer la grille de jeu
{
    /*int nbrship = 5;
    int shipsize[5] = {5,4,3,3,2};*/
    int vide, temp;

    for (int k = 0; k < nbrship; k++)
    {
        vide = 0;
        while (vide == 0)
        {
            int x = rand() % 10;
            int y = rand() % 10;
            int s = rand() % 2;

            if (s) {
                if (y + shipsize[k] < 10)
                {
                    temp = 1;
                    for (int i = y; i < y + shipsize[k]; i++) temp *= ship[x][i] + 1;
                    if (temp==1) vide = 1;
                    if (vide)  for (int i = y; i < y + shipsize[k]; i++) ship[x][i] = k+1;
                }

            }
            else
            {
                if (x + shipsize[k] < 10)
                {
                    temp = 1;
                    for (int i = x; i < x + shipsize[k]; i++) temp *= ship[i][y] + 1;
                    if (temp == 1) vide = 1;
                    if (vide)  for (int i = x; i < x + shipsize[k]; i++) ship[i][y] = k+1;
                }

            }
        }
    }

}
void TirTest(int *nbr_tir, int tirs[10][10], int ship[10][10], int shipsize[5], int line, int column, int *nbr_plouf, int *nbr_touched, int *nbr_sinked,int *nbr_remain,int *etat_tir) { //Permet de tester l'état de case de la table au point de tir du joueur
    (*nbr_tir)++;
    if (tirs[line][column] == 0) {
        if (ship[line][column] == 0) {
            tirs[line][column] = 1;
            (*nbr_plouf)++;
            *etat_tir=1;
        }
        if (ship[line][column] > 0) {
            (*nbr_touched)++;
            *etat_tir=2;
            tirs[line][column] = 2;
            int counttouched = 0;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (ship[i][j] == ship[line][column] && tirs[i][j] == 2) {
                        counttouched++;
                    }
                }
            }
            if (counttouched == shipsize[ship[line][column]-1]) {
                (*nbr_sinked)++;
                *etat_tir=3;
                (*nbr_remain)--;
                tirs[line][column] = 3;
            }
        }
    }
}
void AfficheGDJ(int tirs[10][10], int nbr_tir, int nbr_plouf, int nbr_touched, int nbr_sinked, int nbr_remain, int etat_tir) { //Permet d'afficher la table de jeu
    //Gestion des accents dans la console
    SetConsoleOutputCP(437);
    char alphabet[10]={'A','B','C','D','E','F','G','H','I','J'};
    printf("\n   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",STLC,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,STRC);
    printf("\n   %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c",SVSB,0,SVSB,1,SVSB,2,SVSB,3,SVSB,4,SVSB,5,SVSB,6,SVSB,7,SVSB,8,SVSB,9,SVSB);

    for (int i = 0; i<10; i++) {
        printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", SHSB, SHSB,
               SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB,
               SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC,
               SHSB, SHSB, SHSB, SVRB);
        printf("\n %c %c", alphabet[i], SVSB);
        for (int j = 0; j < 10; j++) {
            printf(" %c %c", t(tirs[i][j]), SVSB);
        }
        switch (i) {
            case 0:
                printf("   Nombre de tirs   : %d",nbr_tir);
                break;
            case 1:
                printf("   Nombre de ploufs : %d",nbr_plouf);
                break;
            case 2:
                //Gestion des accents dans la console
                SetConsoleOutputCP(65001);
                printf("   Nombre de touchés: %d",nbr_touched);
                //Gestion des accents dans la console
                SetConsoleOutputCP(437);
                break;
            case 3:
                //Gestion des accents dans la console
                SetConsoleOutputCP(65001);
                printf("   Bateaux coulés   : %d",nbr_sinked);
                //Gestion des accents dans la console
                SetConsoleOutputCP(437);
                break;
            case 4:
                printf("   Bateaux restants : %d",nbr_remain);
                break;
            case 7:
                printf("   O = plouf");
                break;
            case 8:
                //Gestion des accents dans la console
                SetConsoleOutputCP(65001);
                printf("   X = touché");
                //Gestion des accents dans la console
                SetConsoleOutputCP(437);
                break;
            case 9:
                //Gestion des accents dans la console
                SetConsoleOutputCP(65001);
                printf("   C = coulé");
                //Gestion des accents dans la console
                SetConsoleOutputCP(437);
                break;
        }
    }
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", SHSB, SHSB,
           SHSB, SHBB, SHSB, SHSB, SHSB, SHBB, SHSB, SHSB, SHSB, SHBB, SHSB, SHSB, SHSB, SHBB, SHSB, SHSB, SHSB, SHBB, SHSB,
           SHSB, SHSB, SHBB, SHSB, SHSB, SHSB,SHBB, SHSB, SHSB, SHSB, SHBB, SHSB, SHSB, SHSB, SHBB, SHSB, SHSB, SHSB, SHBB,
           SHSB, SHSB, SHSB, SBRC);
    //Gestion des accents dans la console
    SetConsoleOutputCP(65001);
    if (etat_tir==1) {
        printf("\nPlouf!");
    }
    if (etat_tir==2) {
        printf("\nVous avez touché le bateau");
    }
    if (etat_tir==3) {
        printf("\nVous avez coulé le bateau");
    }
}
int Validity(char *xy) { //Permet de valider les coordonnées durant la partie
    if (strlen(xy) == 2) {
        if (xy[0] == 'a' || xy[0] == 'A' || xy[0] == 'b' || xy[0] == 'B' || xy[0] == 'c' || xy[0] == 'C' || xy[0] == 'd' || xy[0] == 'D' || xy[0] == 'e' || xy[0] == 'E' || xy[0] == 'f' || xy[0] == 'F' || xy[0] == 'g' || xy[0] == 'G' || xy[0] == 'h' || xy[0] == 'H' || xy[0] == 'i' || xy[0] == 'I' || xy[0] == 'j' || xy[0] == 'J') {
            if (xy[1] == '0' || xy[1] == '1' || xy[1] == '2' || xy[1] == '3' || xy[1] == '4' || xy[1] == '5' || xy[1] == '6' || xy[1] == '7' || xy[1] == '8' || xy[1] == '9') {
                return 1;
            }
        }
    }
    return 0;
}

int main() { //Fonction principale, fais le regroupement de toutes les fonctions et variables
    // Gestion des accents dans la console
    //SetConsoleOutputCP(65001);
    int nbrship = 5;
    int shipsize[5] = {5,4,3,3,2};
    int i,j,tirs[10][10], ship[10][10],nbr_tir, nbr_plouf, nbr_touched, nbr_sinked, nbr_remain, line, column, choice_int, etat_tir;
    char xy[3], choice[2];
    xy[2] = '\0';
    choice[1] = '\0';
    menu:
    clrscr();
    printf("---- Bataille navale ----\n");
    printf("1. Nouvelle partie\n2. Aide\n3. Quitter\nChoix :");
    scanf(" %s",&choice);
    while (strlen(choice) != 1) goto menu;
    choice_int = choice[0] - '0';
    switch (choice_int) {
        case 1:
            nbr_tir = 0;
            nbr_plouf = 0;
            nbr_touched = 0;
            nbr_sinked = 0;
            nbr_remain = nbrship;

            for ( i = 0; i<10; i++) {
                for (j = 0; j<10; j++) {
                    tirs[i][j] = 0;
                    ship[i][j] = 0;
                }
            }
            posShip(ship, nbrship, shipsize);
            while (nbr_remain > 0) {
                do {
                    clrscr();
                    AfficheGDJ(tirs, nbr_tir, nbr_plouf, nbr_touched, nbr_sinked, nbr_remain, etat_tir);
                    etat_tir = 0;
                    printf("\nCoordonnées de tir[ligne][colonne]:");
                    scanf("%s", &xy);
                } while (Validity(xy) == 0);
                line = CharToInt(xy[0]);
                column = xy[1] - '0';
                TirTest(&nbr_tir, tirs, ship, shipsize, line, column, &nbr_plouf, &nbr_touched, &nbr_sinked, &nbr_remain, &etat_tir);
            }
            goto menu;
        case 2:
            clrscr();
            Aide();
            printf("\nAppuyez sur une touche pour revenir au menu...");
            getch();
            goto menu;
        case 3:
            break;
        default:
            goto menu;
    }
    return 0;
}
