#ifndef SUDOKO_H_INCLUDED
#define SUDOKO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#define LARGEUR_CONSOLE 80

time_t start,end,gameOver,save;
float tempsPasse;

typedef struct cases Cases;
struct cases
{
    int ligne;
    int colone;
    Cases* suivant;
};

typedef struct files Files;
struct files
{
    char nom[100];
    int index;
};


Cases* creerCases(int l,int c);//creation d'une case avec ces coordonnées ligne et colonne
int _casesEgeaux(Cases* c1,Cases* c2); // vérification si deux cases sont identiques
Cases * insertionCases(Cases * liste, Cases * c );//insertion d'une cases dans une liste
void affichageMenu(int i); // Affichage de menu
void affichageMenuControle(int *i,int *j); // le cotrole de Menu
void afficher_grilleJoue(char grilleC[9][9],Cases* list, int nbrAideR,Cases* listfaut);// affichage de la grille
void PositionnerCurseurF(char grilleF[9][9],int* a, int *b);// Positionner le curseur dans la grille
int grilleTousRemplis(char grilleC[9][9]);// verification si la grille est toute remplis
void jouer(char grilleC[9][9],int l,int c,Cases* niv,char username[100],char nivJeux[1],int nombreF,int aideR);// permettre au joueur à jouer
int _isNewElement(int l,int c,char niv);// vérification si une cases est à inserer par le joueur
void SetColor(int ForgC);//fonction qui permet d'afficher les coleurs
void affichagePrincipal();//fonction qui s'execute au debut qui contient l'affichage du menu et du lencement des grilles
Cases* resultatfinale(char grille[9][9],char username[100],int *faute,char niv[1],int nbrGr,Cases* casesFault);// correction de la grille entrée par l'utilisateur
void SauvegarderPartie(char grille[9][9],char username[100],Cases* list,char nivF[1],int nbrF,int aideR);//sauvegarde de la grille entrée par l'utilisateur
Cases* lirePartie(char grille[9][9],char username[100],char nivF[1],int *nbrF,char fileTitle[10],int *aideRes);//lire une grille sauvegardé d'un fichier
Cases* lireGrilleJeu(char grille[9][9],char niv[1],int nbrGr,Cases* listVides);//lire une griile jouable
int _isNewElementA(int l,int c,Cases* list);// vérification si une cases est nouvelle dans une liste des cases
void afficherliste(Cases * liste);//affichae de la liste
int nbrElementList(Cases * liste);//nombre element de la liste
void creerFilePlayer(char username[100]);//creeation d'un repertoir au nom du jour
int existRepre(char username[100]);//verifier si un repertoire existe deja
int lireRepertoire(char nom[100],Files *fichiers);// lire le contenue d'un repertoire
void currentTime(char dateTime[19]);//fonction qui retourne la date actuelle en parametre
int aide(int ligne,int colonne,char niv[1],int nbrGr);// fonction qui represente l'aide au joureur(remplir une case)
Cases * suprressionList(Cases* liste);//Suppression d'une liste donnée
Cases* supprimerElement(Cases* list, int l,int c);//Suppression d'un element dans une liste
void lireScore(char nom[100]);// lire les scores d'un joueur
#endif // SUDOKO_H_INCLUDED
