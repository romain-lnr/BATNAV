/**
 * Auteur:      R. Lenoir (CPNV)
 * Date:        02.03.2022
 * Titre:       BATNAV
 * Description: Ce projet, sous forme d'une bataille navale pur et dur, permet de tester le joueur dans un défi afin de trouver et de couler les bateaux de la grille choisit.
 */

//LIBRAIRIES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <sys/stat.h>

//CONTENANTS DE GRILLES
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

void Aide() { // permet d'afficher l'aide dans l'option 5 du menu principal
    //Gestion des accents dans la console
    SetConsoleOutputCP(437);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",DTLC,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DTRC);
    printf("\n%c                                   %c",DVSB,DVSB);
    printf("\n%c          %s            %c",DVSB,"L'aide du jeu",DVSB);
    printf("\n%c                                   %c",DVSB,DVSB);
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",DBLC,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DBRC);
    //Gestion des accents dans la console
    SetConsoleOutputCP(65001);
    printf("\nLa bataille navale a pour but de tester le joueur à travers une grille choisit aléatoirement\nPour gagner, il vous suffit donc de trouver et de détruire tous les bateaux qui s'opposeront à vous.\n");
    printf("\nDéroulement de la partie :\nLe joueur devra tirer à travers des cases prévu à cet effet en inscrivant des coordonnées (Ex:A2).\n");
    printf("\nLes joueurs ayant touché un bateau aura comme signe de case un 'X'.\nLes joueurs ayant raté un bateau aura comme signe de case un '0'.\nLes joueurs ayant coulé un bateau aura comme signe de case un 'C'.\n");
    printf("\nUne fois tous les bateaux coulés, le joueur reviendra dans le menu principal.\nA ce moment-là, le joueur pourra voir ses scores affichés dans l'option 'Mes meilleurs scores'.");
    printf("\nIl pourra également voir les scores des autres joueurs dans l'option 'Les meilleurs scores'.\n");
    printf("\nLe joueur a aussi à disposition une option de paramètres.\nLà-dedans, le joueur pourra charger un nouveau set de grilles de jeu et ajouter un nouveau joueur.");
    printf("\nCe joueur ajouté sera inscrit dans un fichier texte, inscrit dans le répertoire de l'exécutable.\n");
}
int CharToInt(char c) //Permet de changer la coordonnée 'xy[0]' en entier
{
    switch (c)
    {
        case 'A': //Si 'A', retourne 0
            return 0;
        case 'B': //Si 'B', retourne 1
            return 1;
        case 'C': //Si 'C', retourne 2
            return 2;
        case 'D': //Si 'D', retourne 3
            return 3;
        case 'E': //Si 'E', retourne 4
            return 4;
        case 'F': //Si 'F', retourne 5
            return 5;
        case 'G': //Si 'G', retourne 6
            return 6;
        case 'H': //Si 'H', retourne 7
            return 7;
        case 'I': //Si 'I', retourne 8
            return 8;
        case 'J': //Si 'J', retourne 9
            return 9;
        case 'a': //Si 'a', retourne 0
            return 0;
        case 'b': //Si 'b', retourne 1
            return 1;
        case 'c': //Si 'c', retourne 2
            return 2;
        case 'd': //Si 'd', retourne 3
            return 3;
        case 'e': //Si 'e', retourne 4
            return 4;
        case 'f': //Si 'f', retourne 5
            return 5;
        case 'g': //Si 'g', retourne 6
            return 6;
        case 'h': //Si 'h', retourne 7
            return 7;
        case 'i': //Si 'i', retourne 8
            return 8;
        case 'j': //Si 'j', retourne 9
            return 9;
    }
}
char t(int n) //Permet de regrouper toutes les éventuels symboles en cours de partie
{
    if (n == 0) return ' '; //Si tirs[][] équivaut à 0, retourne un ' ', la case reste vierge
    if (n == 1) { //Si tirs[][] équivaut à 1, retourne un '0'
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); // texte bleu (B) sur fond noir (0)
        return 'O';
    }
    if (n == 2) { //Si tirs[][] équivaut à 2, retourne un 'X'
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C); // texte rouge (C) sur fond noir (0)
        return 'X';
    }
    if (n == 3) { //Si tirs[][] équivaut à 3, retourne un 'C'
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A); // texte vert (A) sur fond noir (0)
        return 'C';
    }
}
void clrscr() //Sert à actualiser l'écran en cours de partie
{
    system("@cls||clear"); //Commande de windows pour clear l'image/l'exécutable
}
void posShip(int ship[10][10], int nbrship, const int shipsize[5]) //Sert à créer la table des bateaux afin de créer la grille de jeu
{
    int vide, temp;
    for (int k = 0; k < nbrship; k++) //Boucle afin de le faire pour chaque bateau
    {
        vide = 0;
        while (vide == 0) //tabt que le bateau est sur un champ libre
        {
            int x = rand() % 10; //Choisit un nombre entre 0 à 9
            int y = rand() % 10; //Choisit un nombre entre 0 à 9
            int s = rand() % 2; //Choisit un nombre entre 0 à 1

            if (s) { //Si 's' est vrai...
                if (y + shipsize[k] < 10) //Place un bateau verticalement
                {
                    temp = 1;
                    for (int i = y; i < y + shipsize[k]; i++) temp *= ship[x][i] + 1; //Pose le bateau verticalement
                    if (temp == 1) vide = 1;
                    if (vide)  for (int i = y; i < y + shipsize[k]; i++) ship[x][i] = k+1; //Si vide est vrai, replace le bateau
                }
            } else { //Sinon, si 's' n'est pas vrai
                if (x + shipsize[k] < 10) //Place un bateau horizontalement
                {
                    temp = 1;
                    for (int i = x; i < x + shipsize[k]; i++) temp *= ship[i][y] + 1; //Pose le bateau horizontal
                    if (temp == 1) vide = 1;
                    if (vide)  for (int i = x; i < x + shipsize[k]; i++) ship[i][y] = k+1; //Si vide est vrai, replace le bateau
                }
            }
        }
    }
}
int Authentify(char username[]) { //Fonction servant à s'identifier en tant que joueur, annexe : logs/users.txt
    const char *filename = "logs/users.txt";
    struct stat sb; //Crée une structure stat
    stat(filename,&sb);
    char *userfile = malloc(sb.st_size); //Attribue une allocation de mémoire
    FILE* fichier = NULL; //Crée le fichier
    fichier = fopen(filename, "r"); //Ouvre le fichier dans le répertoire 'filename' et crée une permission de lecture (r)
    if (fichier != NULL) { //Si fichier n'est pas null, s'il l'a ouvert correctement
        while (fscanf(fichier,"%[^\n] ",userfile) != EOF) { //Lit le fichier tant qu'il n'est pas à la fin du fichier
            if (strcmp(username,userfile) == 0) { //Si username et userfile sont égaux...
                return 1;
            }
        }
        fclose(fichier); //Ferme le fichier
    }
    return 0;
}
void Addnewuser(char *newuser) { //Permet d'ajouter un nouveau joueur dans le fichier txt, annexe : logs/users.txt
    FILE* fichier = NULL; //Crée le fichier
    fichier = fopen("logs/users.txt", "a"); //Ouvre le fichier dans le répertoire et crée une permission d'affichage (a)
    if (fichier != NULL) { //Si fichier n'est pas null, s'il l'a ouvert correctement
        fprintf(fichier,"%s\n",newuser); //Affiche le nouvel utilisateur dans le fichier
        fclose(fichier); //Ferme le fichier
    }
}
void MapWriter(int ship[10][10], char *filename) { //Ecrit les fichier .csv, annexe : maps
    FILE* fichier = NULL; //Crée le fichier
    fichier = fopen(filename, "w"); //Ouvre le fichier dans le répertoire 'filename' et crée une permission d'écriture (w)
    if (fichier != NULL) { //Si fichier n'est pas null, s'il l'a ouvert correctement
        //Boucle pour avoir la grille de bateau complet
        for (int m = 0; m < 10; m++) {
            for (int n = 0; n < 10; n++) {
                fprintf(fichier, " %d;", ship[m][n]); //Ecrit un chiffre qui déterminera les bateaux
            }
            fprintf(fichier, "\n"); //Effectue un retour à la ligne pour faire la grille de 10x10
        }
        fclose(fichier); //Ferme le fichier
    }
}
void MapReader(int ship[10][10]) { //Lire le fichier .csv, annexe : maps
    int i = rand() % 1000; //Choisit un nombre entre 0 à 999
    char filename[0];
    FILE* fichier = NULL; //Crée le fichier
    sprintf(filename,"maps/map%d.csv", i); //Choisit un fichier de map aléatoire
    fichier = fopen(filename, "r"); //Ouvre le fichier dans le répertoire 'filename' et crée une permission de lecture (r)

    if (fichier != NULL) { //Si fichier n'est pas null, s'il l'a ouvert correctement
        //Boucle pour avoir la grille de bateau complet
        for (int m = 0; m < 10; m++) {
            for (int n = 0; n < 10; n++) {
                fscanf(fichier, " %d;", &ship[m][n]); //Lit l'entièreté de la grille du fichier choisit aléatoirement
            }
            fscanf(fichier, "\n"); //Effectue un retour à la ligne pour faire la grille de 10x10
        }
        fclose(fichier); //Ferme le fichier
    }
}
void TirTest(int *nbr_tir, int tirs[10][10], int ship[10][10], const int shipsize[5], int line, int column, int *nbr_plouf, int *nbr_touched, int *nbr_sinked, int *nbr_remain, int *etat_tir) { //Permet de tester l'état de case de la table au point de tir du joueur
    (*nbr_tir)++;
    if (tirs[line][column] == 0) { //Si le joueur n'a pas déjà tiré par-là
        if (ship[line][column] == 0) { //S'il n'y a pas de bateau là où le joueur a tiré...
            tirs[line][column] = 1; //Le symbole de la case touchée sera '0'
            (*nbr_plouf)++;
            *etat_tir=1; //L'état du tir est un plouf
        }
        if (ship[line][column] > 0) { //S'il y a un bateau là où le joueur a tiré
            (*nbr_touched)++;
            *etat_tir=2; //L'état du tir est un touché
            tirs[line][column] = 2; //Le symbole de la case touchée sera 'X'
            int counttouched = 0;
            //Boucle pour avoir la grille de bateau complet
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (ship[i][j] == ship[line][column] && tirs[i][j] == 2) { //Si le bateau se fait attaquer...
                        counttouched++;
                    }
                }
            }
            if (counttouched == shipsize[ship[line][column]-1]) { //Si 'counttouched' est égale à la taille du bateau se faisant attaquer...
                (*nbr_sinked)++;
                *etat_tir=3; //L'état du tir est un touché-coulé
                (*nbr_remain)--;
                tirs[line][column] = 3; //Le symbole de la case touchée sera 'C'
            }
        }
    }
}
void AfficheGDJ(int tirs[10][10], int nbr_tir, int nbr_plouf, int nbr_touched, int nbr_sinked, int nbr_remain, int etat_tir) { //Permet d'afficher la table de jeu
    //Gestion des accents dans la console
    SetConsoleOutputCP(437);
    char alphabet[10]={'A','B','C','D','E','F','G','H','I','J'}; //Tableau servant à optimiser l'affichage de la grille en lui offrant moins de ligne
    //Affichage de la grille
    printf("\n   %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",STLC,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,SHTB,SHSB,SHSB,SHSB,STRC);
    printf("\n   %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c",SVSB,0,SVSB,1,SVSB,2,SVSB,3,SVSB,4,SVSB,5,SVSB,6,SVSB,7,SVSB,8,SVSB,9,SVSB);

    for (int i = 0; i<10; i++) {
        printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", SHSB, SHSB,
               SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB,
               SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC, SHSB, SHSB, SHSB, SC,
               SHSB, SHSB, SHSB, SVRB);
        printf("\n %c %c", alphabet[i], SVSB); //Affiche l'attribut de tableau 'alphabet' un par un
        for (int j = 0; j < 10; j++) {
            printf(" %c", t(tirs[i][j])); //Affiche l'émetteur de la case un par un
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F); // texte blanc (F) sur fond noir (0)
            printf(" %c", SVSB);
        }
        //---
        switch (i) { //Affiche les statistiques et les états de tirs
            case 0: //Ecrit après la première ligne, après la ligne 'A'
                printf("   Nombre de tirs   : %d",nbr_tir);
                break;
            case 1: //Ecrit après la deuxième ligne, après la ligne 'B'
                printf("   Nombre de ploufs : %d",nbr_plouf);
                break;
            case 2: //Ecrit après la troisième ligne, après la ligne 'C'
                //Gestion des accents dans la console
                SetConsoleOutputCP(65001);
                printf("   Nombre de touchés: %d",nbr_touched);
                //Gestion des accents dans la console
                SetConsoleOutputCP(437);
                break;
            case 3: //Ecrit après la Quatrième ligne, après la ligne 'D'
                //Gestion des accents dans la console
                SetConsoleOutputCP(65001);
                printf("   Bateaux coulés   : %d",nbr_sinked);
                //Gestion des accents dans la console
                SetConsoleOutputCP(437);
                break;
            case 4: //Ecrit après la cinquième ligne, après la ligne 'E'
                printf("   Bateaux restants : %d",nbr_remain);
                break;
            case 7: //Ecrit après la huitième ligne, après la ligne 'H'
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); // texte bleu (B) sur fond noir (0)
                printf("   O");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F); // texte blanc (F) sur fond noir (0)
                printf(" = Plouf");
                break;
            case 8: //Ecrit après la neuvième ligne, après la ligne 'I'
                //Gestion des accents dans la console
                SetConsoleOutputCP(65001);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C); // texte rouge (C) sur fond noir (0)
                printf("   X");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F); // texte blanc (F) sur fond noir (0)
                printf(" = touché");
                //Gestion des accents dans la console
                SetConsoleOutputCP(437);
                break;
            case 9: //Ecrit après la dixième ligne, après la ligne 'J'
                //Gestion des accents dans la console
                SetConsoleOutputCP(65001);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A); // texte vert (A) sur fond noir (0)
                printf("   C");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F); // texte blanc (F) sur fond noir (0)
                printf(" = coulé");
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
    if (etat_tir == 1) { //Si la case ne cache pas de bateau...
        printf("\nPlouf!");
    }
    if (etat_tir == 2) { //Si le bateau est touché...
        printf("\nTouché!");
    }
    if (etat_tir == 3) { //Si le bateau est coulé...
        printf("\nTouché-coulé!");
    }
}
int Validity(char *xy) { //Permet de valider les coordonnées durant la partie
    if (strlen(xy) == 2) { //Si le nombre de caractère de 'xy' équivauut à deux
        if (xy[0] == 'a' || xy[0] == 'A' || xy[0] == 'b' || xy[0] == 'B' || xy[0] == 'c' || xy[0] == 'C' || xy[0] == 'd' || xy[0] == 'D' || xy[0] == 'e' || xy[0] == 'E' || xy[0] == 'f' || xy[0] == 'F' || xy[0] == 'g' || xy[0] == 'G' || xy[0] == 'h' || xy[0] == 'H' || xy[0] == 'i' || xy[0] == 'I' || xy[0] == 'j' || xy[0] == 'J') {
            if (xy[1] == '0' || xy[1] == '1' || xy[1] == '2' || xy[1] == '3' || xy[1] == '4' || xy[1] == '5' || xy[1] == '6' || xy[1] == '7' || xy[1] == '8' || xy[1] == '9') {
                return 1; //Si tous ces conditions sont vraies, retourne la fonction de 1
            }
        }
    }
    return 0; //...Sinon, retourne 0
}
void Logs(char *username, char *date, int nbr_tir) { //Permet d'écrire le score dans un fichier txt afin de le conserver, annexe : logs/logs.txt
    FILE* fichier = NULL; //Crée le fichier
    fichier = fopen("logs/logs.txt", "a"); //Ouvre le fichier dans le répertoire et crée une permission d'affichage' (a)
    if (fichier != NULL) { //Si fichier n'est pas null, s'il l'a ouvert correctement
        fprintf(fichier,"%s; %s; %d\n",username,date,nbr_tir); //Affiche les scores détenus lors de la partie
        fclose(fichier); //Ferme le fichier
    }
}
void Printscore(char *username) { //Permet d'afficher le score dans l'options "Mes meilleurs scores" ou "Les meilleurs scores" en les filtrant et triant
    const char *filename = "logs/logs.txt";
    struct stat sb; //Crée une structure stat
    int nbr_line = 0;
    stat(filename,&sb);
    char *line = malloc(sb.st_size); //Crée une allocation de mémoire
    FILE* fichier = NULL; //Crée le fichier
    fichier = fopen(filename, "r"); //Ouvre le fichier dans le répertoire 'filename' et crée une permission de lecture (r)
    if (fichier != NULL) { //Si fichier n'est pas null, s'il l'a ouvert correctement
        while (fscanf(fichier, "%[^\n] ", line) != EOF) nbr_line++; //Tant qu'il n'a pas fini de lire l'entièreté du fichier, nbr_line augmente
        fclose(fichier); //Ferme le fichier
    }
    char user[nbr_line][16], timestamp[nbr_line][50];
    int nbr_tir[nbr_line], ranking[nbr_line], min_tir, max_tir, min_pos, temp;
    fichier = NULL; //Réintialise le fichier
    fichier = fopen(filename, "r"); //Ouvre le fichier dans le répertoire 'filename' et crée une permission de lecture (r)
    if (fichier != NULL) { //Si fichier n'est pas null, s'il l'a ouvert correctement
        for (int i = 0; i < nbr_line; i++) { //Boucle jusqu'à la valeur de nbr_line
            fscanf(fichier,"%[^;]; %[^;]; %d\n",user[i], timestamp[i], &nbr_tir[i]); //Lis le fichier dans son intégralité
        }
        fclose(fichier); //Ferme le fichier
    }
    max_tir = 0;
    for (int i = 0; i < nbr_line; i++) { //Boucle jusqu'à la valeur de nbr_line
        if (nbr_tir[i] > max_tir) { //Si le tir max est dépassé...
            max_tir = nbr_tir[i]+1; //Le tir max change
        }
        ranking[i] = i; //Remise du rang
    }
    for (int i = 0; i < nbr_line; i++) { //Boucle jusqu'à la valeur de nbr_line
        min_tir = max_tir;
        for (int j = i; j < nbr_line; j++) { //Boucle jusqu'à la valeur de nbr_line en commençant par i
            if (nbr_tir[ranking[j]] < min_tir) {
                min_tir = nbr_tir[ranking[j]];
                min_pos = j;
            }
        }
        //Inversion et conversation des variables
        temp = ranking[i];
        ranking[i] = ranking[min_pos];
        ranking[min_pos] = temp;
    }
    if (strcmp(username, "") == 0) { //Si le nom du joueur connecté équivaut à "", tous les joueurs compris...
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E); // texte jaune (E) sur fond noir (0)  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); // texte bleu (B) sur fond noir (0)
        for (int i = 0; i < min(nbr_line, 3); i++) { //Boucle les trois premiers stats qui minime le score
            if (strlen(user[ranking[i]]) < 7) printf("%s;\t\t %s;\t \\ %d /\n", user[ranking[i]], timestamp[ranking[i]], nbr_tir[ranking[i]]); //Si le nom du joueur avec un score a un nombre de caractère plus petit que 7, Il tabule deux fois
            else  printf("%s;\t %s;\t \\ %d /\n", user[ranking[i]], timestamp[ranking[i]], nbr_tir[ranking[i]]); //Sinon, Il tabule qu'ue seule fois
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F); // texte blanc (F) sur fond noir (0)
        printf("-----------------------------------------------\n");
        for (int i = 3; i < min(nbr_line, 20); i++) { //Boucle Le reste des stats
            if (strlen(user[ranking[i]]) < 7) printf("%s;\t\t %s;\t \\ %d /\n", user[ranking[i]], timestamp[ranking[i]], nbr_tir[ranking[i]]); //Si le nom du joueur avec un score a un nombre de caractère plus petit que 7, Il tabule deux fois
            else  printf("%s;\t %s;\t \\ %d /\n", user[ranking[i]], timestamp[ranking[i]], nbr_tir[ranking[i]]); //Sinon, Il tabule qu'ue seule fois
        }
    }
    else { //Sinon, Si le nom du joueur connecté équivaut autrement à "", tous les joueurs compris...
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0D); // texte violet (D) sur fond noir (0)  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); // texte bleu (B) sur fond noir (0)
        for (int i = 0; i < min(nbr_line, 20); i++) { //Boucle les 20 premier stats qui minime le score
            if (strcmp(user[ranking[i]], username) == 0) { //Si le nom du joueur connecté équivaut au score du joueur connecté...
                if (strlen(user[ranking[i]]) < 7) printf("%s;\t\t %s;\t \\ %d /\n", user[ranking[i]], timestamp[ranking[i]], nbr_tir[ranking[i]]); //Si le nom du joueur avec un score a un nombre de caractère plus petit que 7, Il tabule deux fois
                else  printf("%s;\t %s;\t \\ %d /\n", user[ranking[i]], timestamp[ranking[i]], nbr_tir[ranking[i]]); //Sinon, Il tabule qu'ue seule fois
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F); // texte blanc (F) sur fond noir (0)  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B); // texte bleu (B) sur fond noir (0)
    }
}
int main(void) { //Fonction principale, fais le regroupement de toutes les fonctions et variables
    srand(time(NULL)); //Pouvoir réutiliser les variables random et les réinscrire dans le code

    //VARIABLES
    int nbrship = 5;
    const int shipsize[5] = {5,4,3,3,2};
    int tirs[10][10], ship[10][10], nbr_tir, nbr_plouf, nbr_touched, nbr_sinked, nbr_remain, line, column, etat_tir = 0, choice_int, choice_opt_int;
    char filename[50], xy[3], username[21], newuser[21], temp[20], choice[2], choice_options[2];

    //Initialise la fin des tableaux afin de les utiliser pour la fonction 'strlen'
    xy[2] = '\0';
    choice[1] = '\0';
    choice_options[1] = '\0';
    username[20] = '\0';

    //COMMENCEMENT
   printf("\n                                                                 )___(\n");
   printf("                                                          _______/__/_\n");
   printf("                                                 ___     /===========|   ___\n");
   printf( "                                ____       __   [\\\\\\]___/____________|__[///]\n");
   printf("                                \\   \\_____[\\\\]__/___________________________\\__[//]___\n");
   printf("                                 \\40A                                                 |\n");
   printf("                                  \\                                                  /\n");
   printf("                             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   //Gestion des accents dans la console
    SetConsoleOutputCP(65001);
    printf("\n\n                                          /* Le nom choisit devra être inscrit\n");
    printf("                                          dans le fichier des utilisateurs */\n");
    //Gestion des accents dans la console
    SetConsoleOutputCP(437);
    printf("\n\n                                         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",DTLC,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DTRC);
    printf("\n                                         %c                                   %c",DVSB,DVSB);
    printf("\n                                         %c          %s          %c",DVSB,"Bataille navale",DVSB);
    printf("\n                                         %c                                   %c",DVSB,DVSB);
    printf("\n                                         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",DBLC,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DBRC);
    //Gestion des accents dans la console
    SetConsoleOutputCP(65001);
    printf("\n                                         Entrez votre nom :");
    scanf("%s",&username);
    if (Authentify(username) == 0) //Si les conditions de la fonction 'Validity' n'est pas respectée...
    {
        return 0;
    }
    menu:
    clrscr(); //Lis la fonction 'clrscr' pour effacer les éléments du code
    printf("Bataille navale :%c%c %s %c%c",126,125,username,123,126); //Affiche le nom du joueur dans l'en-tête
    printf("\n------------------------------\n1. Nouvelle partie            |\n------------------------------\n2. Mes meilleurs scores       |\n------------------------------\n3. Les meilleurs scores       |\n------------------------------\n4. Paramètres                 |\n------------------------------\n5. Aide                       |\n------------------------------\n6. Quitter                    |\n------------------------------\n");
    printf("{ Choix } :");
    scanf("%s",&choice);
    while (strlen(choice) != 1) goto menu; //Tant que le nombre de caractère de choice n'est pas égal à 1, reviens au menu principal
    choice_int = choice[0] - '0'; //Transforme le caractère choice en valeur pour ensuite l'imposer dans la variable choice_int
    switch (choice_int) {
        case 1: //Nouvelle partie
        //Initialisation des variables en début de nouvelle partie
            nbr_tir = 0;
            nbr_plouf = 0;
            nbr_touched = 0;
            nbr_sinked = 0;
            etat_tir = 0;
            nbr_remain = nbrship;

            //Initislisation des tableaux bidimensionnels
            for (int i = 0; i<10; i++) {
                for (int j = 0; j<10; j++) {
                    tirs[i][j] = 0;
                    ship[i][j] = 0;
                }
            }
            MapReader(ship);
            while (nbr_remain > 0) { //Tant qu'il reste encore des bateaux...
                do {
                    clrscr(); //Lis la fonction 'clrscr' pour effacer les éléments du code
                    printf("Bataille navale :%c%c %s %c%c\n",126,125,username,123,126); //Affiche le nom du joueur dans l'en-tête
                    AfficheGDJ(tirs, nbr_tir, nbr_plouf, nbr_touched, nbr_sinked, nbr_remain, etat_tir); //Lis la fonction 'AfficheGDJ' pour afficher le tableau avec les statistiques
                    etat_tir = 0;
                    printf("\nCoordonnées de tir[ligne][colonne]:");
                    scanf("%s", &xy);
                } while (Validity(xy) == 0); //Faire tant que la fonction 'Validity' est null
                line = CharToInt(xy[0]);
                column = xy[1] - '0'; //Transforme le caractère column en valeur
                TirTest(&nbr_tir, tirs, ship, shipsize, line, column, &nbr_plouf, &nbr_touched, &nbr_sinked, &nbr_remain,&etat_tir); //Lis la fonction 'TirTest' pour pouboir gérer et tester si un bateau est touché ou raté
            }
            time_t t = time(NULL);
            struct tm tm = *localtime(&t); //Crée une structure tm
            sprintf(temp,"%02d/%02d/%d %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
            Logs(username, temp, nbr_tir); //Lis la fonction 'Logs' pour écrire les scores détenus par l'utilisateur connecté
            goto menu; //Fais retourner au menu
        case 2: //Les meilleurs scores du joueur connecté
            clrscr(); //Lis la fonction 'clrscr' pour effacer les éléments du code
            printf("Bataille navale :%c%c %s %c%c",126,125,username,123,126); //Affiche le nom du joueur dans l'en-tête
            printf("\n------------------------------\n");
            printf("\n             {=====MES SCORES=====}");
            printf("\n-----------------------------------------------\n");
            Printscore(username); //Lis la fonction 'Printscore' pour afficher les scores du joueur connecté
            printf("-----------------------------------------------\n");
            printf("\nAppuyez sur une touche pour revenir au menu...");
            getch(); //Fonction intégrée à 'conio.h' qui l'a quitte dès qu'une touche est appuyée
            goto menu; //Fais retourner au menu principal
        case 3: //Les meilleurs scores en général
            clrscr(); //Lis la fonction 'clrscr' pour effacer les éléments du code
            printf("Bataille navale :%c%c %s %c%c",126,125,username,123,126); //Affiche le nom du joueur dans l'en-tête
            printf("\n------------------------------\n");
            printf("\n             {=====PODIUM=====}");
            printf("\n-----------------------------------------------\n");
            Printscore(""); //Lis la fonction 'Printscore' pour afficher les scores des joueurs inscrits dans les logs
            printf("-----------------------------------------------\n");
            printf("\nAppuyez sur une touche pour revenir au menu...");
            getch(); //Fonction intégrée à 'conio.h' qui l'a quitte dès qu'une touche est appuyée
            goto menu; //Fais retourner au menu principal
        case 4: //les options et paramètres du code
        options:
            clrscr(); //Lis la fonction 'clrscr' pour effacer les éléments du code
            printf("Bataille navale :%c%c %s %c%c",126,125,username,123,126); //Affiche le nom du joueur dans l'en-tête
            printf("\n------------------------------\n1. Générer un set de maps     |\n------------------------------\n2. Ajouter un joueur          |\n------------------------------\n3. Revenir au menu principal  |\n------------------------------\n");
            printf("{ Choix } :");
            scanf("%s",&choice_options);
            while (strlen(choice_options) != 1) goto options; //Tant que le nombre de caractères de choice_options n'est pas égal à 1, reviens au menu de paramètres
            choice_opt_int = choice_options[0] - '0';
            switch (choice_opt_int) {
                case 1: //Générer ou régénérer un set de maps dans le repértoire 'maps'
                //Boucle les fois où la fonction 'MapWriter' ira créer un fichier csv
                    for (int m = 0; m<1000; m++) {
                        for (int i = 0; i<10; i++) {
                            for (int j = 0; j<10; j++) {
                                ship[i][j] = 0;
                            }
                        }
                        posShip(ship, nbrship, shipsize); //Lis la fonction 'PosShip' pour pouvoir ensuite le lire dans 'MapWriter
                        sprintf(filename,"maps/map%d.csv", m);
                        MapWriter(ship, filename); //Lis la fonction 'MapWriter' pour réécrire les grilles de bateaux
                    }
                    break;
                case 2: //Ajouter un nouveau joueur et l'incrire dans les logs
                    do {
                        clrscr(); //Lis la fonction 'clrscr' pour effacer les éléments du code
                        printf("Bataille navale :%c%c %s %c%c",126,125,username,123,126); //Affiche le nom du joueur dans l'en-tête
                        printf("\n------------------------------\n");
                        printf("\n\n\n\n\n\n                                    /* Le nouveau joueur que vous allez transcrire");
                        printf("\n                                       ne devra pas dépasser les 20 caractères */");
                        //Gestion des accents dans la console
                        SetConsoleOutputCP(437);
                        printf("\n\n\n                                         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",DTLC,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DTRC);
                        printf("\n                                         %c                                   %c",DVSB,DVSB);
                        printf("\n                                         %c          %s           %c",DVSB,"Nouveau joueur",DVSB);
                        printf("\n                                         %c                                   %c",DVSB,DVSB);
                        printf("\n                                         %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",DBLC,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DHSB,DBRC);
                        //Gestion des accents dans la console
                        SetConsoleOutputCP(65001);
                        printf("\n                                         Nouveau joueur :");
                        scanf(" %s", &newuser);
                    } while (strlen(newuser) > 20); //Tant que le nommbre de caractère du nouvel utilisateur est plus grand que 20...
                    Addnewuser(newuser); //Lis la fonction 'Addnewuser' pour ajouter  un nouvel utilisateur dans les logs
                    break;
                case 3: //Revenir au menu principal
                    break;
                default: //Revenir dans le menu des paramètres par défaut
                    goto options; //Fais retourner au menu de paramètres
            }
            goto menu; //Fais retourner au menu principal
        case 5: //Affiche l'aide
            clrscr(); //Lis la fonction 'clrscr' pour effacer les éléments du code
            printf("Bataille navale :%c%c %s %c%c",126,125,username,123,126); //Affiche le nom du joueur dans l'en-tête
            printf("\n------------------------------\n");
            Aide(); //Lis la fonction 'Aide' pour l'aide du jeu
            printf("\nAppuyez sur une touche pour revenir au menu...");
            getch(); //Fonction intégrée à 'conio.h' qui l'a quitte dès qu'une touche est appuyée
            goto menu; //Fais retourner au menu principal
        case 6: //Quitte le programme
            break;
        default: //Revenir au menu principal par défaut
            goto menu; //Fais retourner au menu principal
    }
    return 0; //Quitte la fonction 'main', fin du code
}
