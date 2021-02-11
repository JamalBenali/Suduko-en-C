#include "sudoko.h"
Cases * suprressionList(Cases* list)
{
  if (list == NULL) // si la liste est NULL on s'arrete tout de suite
  return (list);
  Cases  *previous;
  previous = list;
  while(list!= NULL) // on supprime chaque element
{
    list=list->suivant;
    free(previous);
    previous=list;
}
return list;
}
Cases* supprimerElement(Cases* list, int l,int c)
{
Cases  *tmp;
Cases  *previous;

if (list == NULL) // si la liste est NULL on s'arrete tout de suite
  return (list);
previous = list;
if (previous->ligne == l && previous->colone==c) // Verifie la tete de liste, cas particulier
{
  list = previous->suivant;
  free(previous);
  return (list);
}
tmp = previous->suivant; // le cas n est gere on se place donc sur le cas n+1
while(tmp != NULL) // On Mouline est on supprime si on trouve l'element
{
  if (tmp->ligne == l && tmp->colone==c)
  {
    previous->suivant = tmp->suivant;
    free(tmp);
    return (list);
  }
  previous = tmp; // pour ce souvenir dans la prochaine iteration du precedent
  tmp = tmp->suivant;
}
return list;
}
Cases* creerCases(int l,int c)
{
    // location de la mémoire pour la nouvelle case
    Cases* nvCases=malloc(sizeof(Cases));
    // affectation des coordonnées
    nvCases->ligne=l;
    nvCases->colone=c;
    nvCases->suivant=NULL;
    return nvCases;
}

void afficherliste(Cases * liste)
{
    // affichage de chaque element de la liste donnée
    Cases* c=liste;
    while(c!=NULL)
    {
        printf("[%d,%d]",c->ligne,c->colone);
        c=c->suivant;
    }
}

int _casesEgeaux(Cases* c1,Cases* c2)
{
    //vérification d'égalité des deux cases donnés en paramètres
    if(c1->ligne==c2->ligne && c1->colone==c2->colone)
        return 1;//retourne 1 si vrai
    return 0;// retourne 0 si faux
}
Cases * insertionCases(Cases * liste, Cases * c )
{
    //insertion de la case C dans la liste liste
    if(liste==NULL)
        return c;// si la liste est vide, la case C va etre le premier élement
        c->suivant=liste;// si la liste n'est pas vide, la case C va etre ajouter au premier
        liste=c;
    return liste;
}

void affichageMenu(int i)
{
    //affichage du menu principale
    char nvPrt=' ',rprdPrt=' ',consultPrt=' ',cmntJouer=' ',info=' ',quitPrt=' ';
    //pour mettre un signe avant le choix selectionné selon le paramètre i
    switch(i)
    {
        case 0:nvPrt='>';break;
        case 1:rprdPrt='>';break;
        case 2:consultPrt='>';break;
        case 3:info='>';break;
        case 4:cmntJouer='>';break;
        case 5:quitPrt='>';break;
    }
    printf("\t\t\t========================================\n");
    printf("\t\t\t                 Suduko                \n");
    printf("\t\t\t========================================\n\n");
    printf("\t\t\t          %c- Nouvelle partie\n\n",nvPrt);
    printf("\t\t\t          %c- Reprendre une partie\n\n",rprdPrt);
    printf("\t\t\t          %c- Consulter mon score\n\n",consultPrt);
    printf("\t\t\t          %c- Informations\n\n",info);
    printf("\t\t\t          %c- Comment jouer\n\n",cmntJouer);
    printf("\t\t\t          %c- Quitter le jeu\n\n",quitPrt);
    printf("\t\t\t========================================\n\n");
}


void affichageMenuControle(int *i,int *j)
{
    //affichage du menu + controle
    system("cls");
    char caractere;
    affichageMenu(*i);
    caractere = getch();//lire un caractère
    switch(caractere)
    {
        //button pour descendre
        case 's':{
            //si nous avons arriver à la fin en va monter au premier choix
            if(*i==5)
            {
                *i=0;
                system("cls");
                affichageMenu(*i);
            }
            //si non, on va continuer à descendre
            else
            {
            *i=*i+1;
            system("cls");
            affichageMenu(*i);
            }
            break;
            }
            //button pour monter
          case 'z':{
            //si nous avons arriver au premier choix en va descendre au dernier choix
            if(*i==0)
            {
                *i=5;
                system("cls");
                affichageMenu(*i);
            }
            //si non, on va continuer à monter
            else
            {
            *i=*i-1;
            system("cls");
            affichageMenu(*i);
            }
            break;
            }
        case 13:
            {
            *j=1;
            }
    }
}

void PositionnerCurseurF(char grilleF[9][9],int* a, int *b)
{
    //positionner le curseur dans la première case vide et qui retourne les cordonnées de la case en paramètres
    int m,n,k=0;
    for (m=0; m<9; m++)
    {
        if(k!=0) // pour sortir de la boucle après le premier positionnement
            break;
    for (n=0; n<9; n++)
    {
        if(grilleF[m][n]==' ')
        {
            *a=m;
            *b=n;
            grilleF[*a][*b]='_';//positionner le curseur
            k=1;
            break;
        }
    }
    }
}
////////////AfficherGrille String//////////////

void afficher_grilleJoue(char grilleC[9][9],Cases* list, int nbrAideR,Cases* listfaut)
{
//cette fonction permet d'afficher la grille de jeu
    int i ;
    int j ;
printf("\t\t\t");
puts("---------------Suduko----------------");
printf("\t\t\t");
puts("-------------------------------------");
if(listfaut!=NULL)//si la grille est dèja remplis par le joueur et il a commis des fautes
{
    for (i=0; i<9; i++)
{
printf("\t\t\t");
for (j=0; j<9; j++)
{
    if(grilleC[i][j]=='_')//affichage du curseur en bleu
    {
        SetColor(3);
        printf( ((j+1)%3) ? "[%c] " : "[%c]:", grilleC[i][j]);
    }
    else if(_isNewElementA(i,j,listfaut))//affichage des faux cases en rouge
    {
        SetColor(20);
        printf( ((j+1)%3) ? "[%c] " : "[%c]:", grilleC[i][j]);
    }
    else if(_isNewElementA(i,j,list)) // affichage des nouveau cases entrée par le joueur en blanc
    {
        SetColor(15);
        printf( ((j+1)%3) ? "[%c] " : "[%c]:", grilleC[i][j]);
    }
    else // afficher les autres cases de la grille en gris
    {
        SetColor(8);
        printf( ((j+1)%3) ? "[%c] " : "[%c]:", grilleC[i][j]);
   }

}
putchar('\n');
if (!((i+1)%3)){
SetColor(15);
printf("\t\t\t");
puts("------------------------------------");
}
}
}
else//si la grille est entrain d'être remplis par le joueur pour la première fois
{
    for (i=0; i<9; i++)
{
printf("\t\t\t");
for (j=0; j<9; j++)
{
    if(grilleC[i][j]=='_')//affichage du curseur en bleu
    {
        SetColor(3);
        printf( ((j+1)%3) ? "[%c] " : "[%c]:", grilleC[i][j]);
    }
    else if(_isNewElementA(i,j,list))// affichage des nouveau cases entrée par le joueur en blanc
    {
        SetColor(15);
        printf( ((j+1)%3) ? "[%c] " : "[%c]:", grilleC[i][j]);
    }
    else // afficher les autres cases de la grille en gris
    {
        SetColor(8);
        printf( ((j+1)%3) ? "[%c] " : "[%c]:", grilleC[i][j]);
   }

}
putchar('\n');
if (!((i+1)%3)){
SetColor(15);
printf("\t\t\t");
puts("------------------------------------");
}
}
}

puts("\n\n");
//afficher comment jouer
printf("\tZ\n");
printf("\t^\n");
printf("\t|\t\t\t-Appuyer sur X pour enregister votre partie\n");
printf("Q <--       --> D \t\t-Appuyer sur H pour presenter l'aide(%d)\n",nbrAideR);
printf("\t|\t  \t\t-Appuyer sur C pour quitter la partie\n");
printf("\tv\n");
printf("\tS\n");
}

int grilleTousRemplis(char grilleC[9][9])
{
    //vérifier si toutes les cases de la grille sont remplis
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(grilleC[i][j]==' ') //si il y a une case vide on sort de la boucle et on retourne 0
                return 0;
        }
    }
    return 1;//si toutes les cases de la grille sont remplis on retourne 1
}
int _isNewElementA(int l,int c,Cases* list)
{
    //verifier si nous qui vont remplis la case de ligne l et la colonne c
    Cases* maCase=creerCases(l,c);// création de la case
    //vérifier si la case appartient à la liste list qui contient les cordonnées de toutes les cases à remplir
    Cases* dd=list;
    while(dd!=NULL)
    {
        if(_casesEgeaux(maCase,dd)==1)
            return 1;//s'il appartient on retourne 1
        dd=dd->suivant;
    }
    return 0;// on retourne 0 si non
}

void affichageNiveau(int i)
{
    //affichage de niveau de difficulté jouable
    char facile=' ',moyen=' ',difficile=' ',retour=' ';
    switch(i)
    {
        //pour mettre le signe > avant le choix selectionné
        case 0:facile='>';break;
        case 1:moyen='>';break;
        case 2:difficile='>';break;
        case 3:retour='>';break;
    }
    printf("==================Menu==================\n\n");
    printf("          %c- Facile\n",facile);
    printf("          %c- Moyen\n",moyen);
    printf("          %c- Difficile\n",difficile);
     printf("          %c- retour\n",retour);
}

char afficherNiveauControle(int *i, int *j)
{
    system("cls");
    char caractere;
    affichageNiveau(*i);//affichage de niveau de difficulté jouable
    caractere = getch();//lire un caractère
    switch(caractere)
    {
        //si nous avons arriver à la fin en va monter au premier choix
        case 's':{
            if(*i==3)
            {
                *i=0;
                system("cls");
                affichageNiveau(*i);
            }
            //si non, on va continuer à descendre
            else
            {
            *i=*i+1;
            system("cls");
            affichageNiveau(*i);
            }
            break;
            }
            //si nous avons arriver à la fin en va descendre au dernier choix
          case 'z':{
            if(*i==0)
            {
                *i=3;
                system("cls");
                affichageNiveau(*i);
            }
            //si non, on va continuer à monter
            else
            {
            *i=*i-1;
            system("cls");
            affichageNiveau(*i);
            }
            break;
            }
            //si on clique sur la boutton entrer on accede au choix selectionné
        case 13:
            {
            *j=1;
            }
    }
}

void jouer(char grilleC[9][9],int l,int c,Cases* niv,char username[100],char nivJeux[1],int nombreF,int aideR)
{
    char tmp=' ';
    int j=0;
    char caractere;
    int faute=1;
    Cases* listFaut=NULL;//vider la liste qui contient les cases fausses
    while(faute==1 && difftime(gameOver,start)+tempsPasse<=1000)
    {
        //tant que la partie n'est pas terminée et le joueur n'as pas dépasser 5 min
        time(&gameOver);//mesurer le temps jouer
        printf("vous avez fait: %f\n",difftime(gameOver,start)+tempsPasse);
        caractere = getch();//lire un caractere pour remplir une case
        if(caractere>='1' && caractere<='9')
        {
            //si l'entrée est un chiffre
            if(grilleTousRemplis(grilleC))
            {
                //vérifier s'il n'y a plus de cases à remplir
                grilleC[l][c]=caractere;//affecter le chiffre à la case
                listFaut=supprimerElement(listFaut,l,c);//supprimer l'element ajouté de la liste des cases fausses
                system("cls");//vider la console
                listFaut=resultatfinale(grilleC,username,&faute,nivJeux,nombreF,listFaut);//vérification des réponses des joueurs
                afficher_grilleJoue(grilleC,niv,aideR,listFaut);//affichage de la grille
            }
            else

            {
            grilleC[l][c]=caractere;//affecter le chiffre à la case
            listFaut=supprimerElement(listFaut,l,c);//supprimer l'element ajouté de la liste des cases fausses
            //placer le cursseur dans la case suivante
            c++;
                    if(c==9)
                    {
                        //si nous avons dépasser le nombre de colonnes  de la grille, retoure à la ligne
                        c=0;
                        l++;
                        if(l>8)
                            l=0;
                    }
                    while(grilleC[l][c]!=' ')
                        {
                            //incrementer l'index de la colonne jusqu'à trouver une case vide
                            c++;
                        if(c==9)
                        {
                            //si nous avons dépasser le nombre de colonnes  de la grille, retoure à la ligne
                            c=0;
                            l++;
                            if(l>8)
                                l=0;
                        }
                        }
                        tmp=' ';
                            grilleC[l][c]='_';//affecter le cursseur à cette case
                    system("cls");//vider la console
                        afficher_grilleJoue(grilleC,niv,aideR,listFaut);//affichage de la grille
        }
        }
        else{
       //si l'entrée n'est pas un chiffre
        switch(caractere)
        {
        case 'X':
            {
                //si X on sauvegarde la partie joué
                SauvegarderPartie(grilleC,username,niv,nivJeux,nombreF,aideR);
                printf("partie enregistre\n");
                 j=1;
                break;
            }
        case 'C':
            {
                //si C on retourne au menu principale
                j=1;
                affichagePrincipal();
                break;
            }
        case 'H':
            {
                //si H on présente l'aide(remplir une case pour le joueur)
                if(aideR>=1)
                {
                    //vérifier si le joueur n'a pas utilisé toutes les possibilité d'aide
                       char caractere1;
                caractere1=aide(l+1,c+1,nivJeux,nombreF);//lire la valeur de la case du fichier de solution
            if(grilleTousRemplis(grilleC))
            {
                //si la grille est toutes remplis
                grilleC[l][c]=caractere1;
                aideR--;//décrementer le nombre d'aide restant
                listFaut=supprimerElement(listFaut,l,c);//supprimer l'element ajouté de la liste des cases fausses
                //system("cls");
                listFaut=resultatfinale(grilleC,username,&faute,nivJeux,nombreF,listFaut);//vérification des réponses des joueurs
                afficher_grilleJoue(grilleC,niv,aideR,listFaut);//affichage de la grille
                //afficherliste(listFaut);
                j=1;
            }
            else
            {
            //si la grille n'est pas toutes remplis
            grilleC[l][c]=caractere1;//affecter le chiffre à la case
             //placer le cursseur dans la case suivante
            listFaut=supprimerElement(listFaut,l,c);
            aideR--;
            c++;
                    if(c==9)
                    {
                        c=0;
                        l++;
                        if(l>8)
                            l=0;
                    }
                    while(grilleC[l][c]!=' ')
                        {
                            c++;
                        if(c==9)
                        {
                            c=0;
                            l++;
                            if(l>8)
                                l=0;
                        }
                        }
                        tmp=' ';
                            grilleC[l][c]='_';
                    system("cls");
                        afficher_grilleJoue(grilleC,niv,aideR,listFaut);
        }
                }
                else
                {
                  printf("desole vous avez depasser le nombre d'aide possible\n");
                }
        break;
            }
            //si clique sur S
            case 'S':
                {
                //descendre le cursseur à la ligne suivante
                grilleC[l][c]=tmp;
                    l++;
                    if(l==9)
                    {
                        //si nous avons dépasser le nombre de lignes de la grille on incremante les colonnes est on se deplasse à la première ligne
                        l=0;
                        if(c!=8)
                        c++;
                        else c=0;
                    }
                    while(_isNewElementA(l,c,niv)==0)
                    {
                     //incrementer les lignes et les colonnes jusqu'à trouver une case vide à remplir
                        l++;
                    if(l==9)
                    {
                        l=0;
                        if(c!=8)
                        c++;
                        else c=0;
                    }
                    }
                    tmp=grilleC[l][c];//garder l'ancien contenu
                    grilleC[l][c]='_';//deplasser le cursseur dans la nouvelle case
                    system("cls");//vider la console
                    afficher_grilleJoue(grilleC,niv,aideR,listFaut);//affichage de la grille
                break;
                }
            case 'Z':
                {
                //monter le cursseur à la ligne suivante
                grilleC[l][c]=tmp;
                    l--;
                    //si nous avons dépasser le nombre de lignes de la grille on decremante les colonnes est on se deplasse à la dernière ligne
                    if(l<0)
                    {
                        l=8;
                        if(c!=0)
                        c--;
                        else c=8;
                    }
                    while(_isNewElementA(l,c,niv)==0)
                    {
                        //decrementer les lignes et les colonnes jusqu'à trouver une case vide à remplir
                        l--;
                    if(l<0)
                    {
                        l=8;
                        if(c!=0)
                        c--;
                        else c=8;
                    }
                    }
                    tmp=grilleC[l][c];//garder l'ancien contenu
                    grilleC[l][c]='_';//deplasser le cursseur dans la nouvelle case
                    system("cls");
                    afficher_grilleJoue(grilleC,niv,aideR,listFaut);//affichage de la grille
                break;
                }
            case 'D':
                {
                //bouger le cursseur vers la droite
                 grilleC[l][c]=tmp;
                 //grilleC[l][c]=' ';
                    c++;
                    //si nous avons dépasser le nombre de colonnes de la grille on incremante les lignes est on se deplasse à la première colonne
                    if(c==9)
                     {
                        c=0;
                        if(l!=8)
                        l++;
                        else l=0;
                      }
                    while(_isNewElementA(l,c,niv)==0)
                    {
                    //incrementer les colonnes et les lignes jusqu'à trouver une case vide à remplir
                        c++;
                    if(c==9)
                    {
                        c=0;
                        if(l!=8)
                        l++;
                        else l=0;
                    }
                    }
                    tmp=grilleC[l][c];//garder l'ancien contenu
                    grilleC[l][c]='_';//deplasser le cursseur dans la nouvelle case
                    system("cls");//vider la console
                    afficher_grilleJoue(grilleC,niv,aideR,listFaut);//affichage de la grille
                break;
                }
            case 'Q':
                {
                //bouger le cursseur vers la droite
                grilleC[l][c]=tmp;
                 //grilleC[l][c]=' ';
                    c--;
                     //si nous avons dépasser le nombre de colonnes de la grille on decremante les lignes est on se deplasse à la dernière colonne
                    if(c<0)
                    {
                        c=8;
                        if(l!=0)
                        l--;
                        else l=8;
                    }

                    while(_isNewElementA(l,c,niv)==0)
                    {
                        //decrementer les colonnes et les lignes jusqu'à trouver une case vide à remplir
                        c--;
                    if(c<0)
                    {
                        c=8;
                        if(l!=0)
                        l--;
                        else l=8;
                    }

                    }
                    tmp=grilleC[l][c];//garder l'ancien contenu
                    grilleC[l][c]='_';//deplasser le cursseur dans la nouvelle case
                    system("cls");//vider la console
                    afficher_grilleJoue(grilleC,niv,aideR,listFaut);//affichage de la grille
                break;
                }
        }
    }
    }
    printf("quitter");
    if(difftime(gameOver,start)>1000)
    {
        //si nous avant dépasser les 5 min on affiche un message de game over
        system("cls");
        printf("GAME OVER! Vous avez depasser 10 secondes");
    }
}

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void affichagePrincipal()
{
    char username[100];
    int grille[9][9];
    char grilleC[9][9];
    int aideR=10;
    char niv[1];
    Cases* listVides=NULL;
    int i=0,j=0,k=0,l=0,positionL,positionC;
     while(j!=1)
    affichageMenuControle(&i,&j); // affichage de menu principal
    switch(i)
    {
        //selen le choix de i
        case 0:{
        //nouvelle partie
        system("cls");
        printf("entrer votre Username\n");//demander le nom du joueur
        scanf("%s",username);
        if(existRepre(username)==0)
        creerFilePlayer(username);// creer un repertoire et un fichier qui porte son nom comme titre
        while(l!=1)
        afficherNiveauControle(&k,&l);//affichage les deffirentes difficultés jouable
        switch(k)
        {
            //selon le choix du niveau(k)
            case 0:
            {
            //niveau facile
            listVides=lireGrilleJeu(grilleC,"F",1,listVides);//lire une grille de jeu niveau facile
            system("cls");//vider la console
            PositionnerCurseurF(grilleC,&positionL,&positionC);// positionner le cursseur dans la première case vide de la grille
            time(&start);//commencer la mesure de temps de la partie
            time(&gameOver);
            afficher_grilleJoue(grilleC,listVides,aideR,NULL);//affichage de la grille
            jouer(grilleC,positionL,positionC,listVides,username,"F",1,aideR);//offre le joueur la possibilité de jouer
            break;
            }
            case 1:
            {
            //niveau moyen
            listVides=lireGrilleJeu(grilleC,"M",1,listVides);//lire une grille de jeu niveau moyen
            system("cls");//vider la console
            PositionnerCurseurF(grilleC,&positionL,&positionC);// positionner le cursseur dans la première case vide de la grille
            time(&start);//commencer la mesure de temps de la partie
            time(&gameOver);
            afficher_grilleJoue(grilleC,listVides,aideR,NULL);//affichage de la grille
            jouer(grilleC,positionL,positionC,listVides,username,"M",1,aideR);//offre le joueur la possibilité de jouer
            break;
            }
            case 2:
            {
            //niveau difficile
            listVides=lireGrilleJeu(grilleC,"D",1,listVides);//lire une grille de jeu niveau difficile
            system("cls");//vider la console
            PositionnerCurseurF(grilleC,&positionL,&positionC);// positionner le cursseur dans la première case vide de la grille
            time(&start);//commencer la mesure de temps de la partie
            time(&gameOver);
            afficher_grilleJoue(grilleC,listVides,aideR,NULL);//affichage de la grille
            jouer(grilleC,positionL,positionC,listVides,username,"D",1,aideR);//offre le joueur la possibilité de jouer
            break;
            }
            case 3:
            {
            //retour au menu principal
             j=0;
             i=0;
             affichagePrincipal();
            break;
            }
        }
        break;
        }
        case 1:{
            //reprendre une partie
            char nom[100];
            int choix,valide=1,i;
            Files fichiers[100];
            system("cls");
            int nbrf;
            printf("entrer votre nom d utilisateur\n");//demander le nom du joueur
            scanf("%s",nom);
            system("cls");
            if(existRepre(nom))
            {
                //si existe un repertoire qui porte son nom
                    lireRepertoire(nom,fichiers);// lire les fichiers du répertoire
                    if(fichiers[0].index==1)
                    {
                        //s'il existe des fichier dans son répertoire
                        printf("\n- entrer le numero de votre partie: \n");//demander le numero de la partie qu'il veut reprendre
                        printf("- entrer 0 pour retourner au menu principal\n");// demader de cliquer sur 0 pour retourner au menu principal
                        while(valide==1)
                        {
                        scanf("%d",&choix);
                        for(i=0;i<100;i++)
                        {
                            if(fichiers[i].index==choix)
                            {
                               valide=0;
                               listVides=lirePartie(grilleC,nom,niv,&nbrf,fichiers[i].nom,&aideR);//lire une grille de jeu demandé
                               system("cls");//vider la console
                               PositionnerCurseurF(grilleC,&positionL,&positionC);// positionner le cursseur dans la première case vide de la grille
                               time(&start);//commencer la mesure de temps de la partie
                               time(&gameOver);
                               afficher_grilleJoue(grilleC,listVides,aideR,NULL);//affichage de la grille
                               jouer(grilleC,positionL,positionC,listVides,nom,niv,nbrf,aideR);//offre le joueur la possibilité de jouer
                               break;
                            }
                            if(choix==0)
                            {
                                //si le choix égale à 0 retourner au menu principal
                                affichagePrincipal();
                            }
                        }
                            if(valide==1)
                            {
                                //si la partie choisis n'existe pas on affiche un message d'erreur
                                system("cls");
                                lireRepertoire(nom,fichiers);//affichage des parties à selectionées
                                printf("\n- la partie n'existe pas. Essayer a nouveau\n");
                                printf("- entrer 0 pour retourner au menu principal\n");
                            }
                        }
                    }
                    else
                    {
                        // si l'utilisateur n'a pas de partie sauvegardé
                         printf("Desole vous avez pas de partie sauvegarde\n");//demandé de taper 1 pour retourner au menu principal
                         printf("entrer 1 pour retourner au menu principal\n");//demandé de taper 0 pour quitter le jeu
                         printf("entrer 0 pour quitter\n");
                         int retour=0;
                         char charChoix;
                         while(retour==0)
                         {
                             charChoix=getch();
                             switch(charChoix)
                             {
                                 case '1':{affichagePrincipal();retour=1;break;}//retourner au menu principal
                                 case '0':{system("cls");exit(1);retour=1;break;}// quitter le jeu
                             }
                         }
                    }
            }
            else
            {
                // si l'utilisateur n'a pas de repertoire a son nom
                 printf("Desole votre nom n'est pas reconnu\n");//demandé de taper 1 pour retourner au menu principal
                 printf("entrer 1 pour retourner au menu principal\n");//demandé de taper 0 pour quitter le jeu
                 printf("entrer 0 pour quitter\n");
                 int retour=0;
                 char charChoix;
                 while(retour==0)
                 {
                     charChoix=getch();
                     switch(charChoix)
                     {
                         case '1':{affichagePrincipal();retour=1;break;}//retourner au menu principal
                         case '0':{system("cls");exit(1);retour=1;break;}// quitter le jeu
                     }
                 }
            }
            break;}

        case 2:{
         char nom[100];
            int choix,valide=1,i;
            Files fichiers[100];
            system("cls");
            int nbrf;
            printf("entrer votre nom d utilisateur\n");//demander le nom du joueur
            scanf("%s",nom);
            system("cls");
            if(existRepre(nom))
            {
                printf("votre scores est:");
                lireScore(nom);
                printf("\n\nentrer 1 pour retourner au menu principal\n");//demandé de taper 0 pour quitter le jeu
                 printf("entrer 0 pour quitter\n");
                 int retour=0;
                 char charChoix;
                 while(retour==0)
                 {
                     charChoix=getch();
                     switch(charChoix)
                     {
                         case '1':{affichagePrincipal();retour=1;break;}//retourner au menu principal
                         case '0':{system("cls");exit(1);retour=1;break;}// quitter le jeu
                     }
                 }
            }
            else
            {
                // si l'utilisateur n'a pas de repertoire a son nom
                 printf("Desole votre nom n'est pas reconnu\n");//demandé de taper 1 pour retourner au menu principal
                 printf("entrer 1 pour retourner au menu principal\n");//demandé de taper 0 pour quitter le jeu
                 printf("entrer 0 pour quitter\n");
                 int retour=0;
                 char charChoix;
                 while(retour==0)
                 {
                     charChoix=getch();
                     switch(charChoix)
                     {
                         case '1':{affichagePrincipal();retour=1;break;}//retourner au menu principal
                         case '0':{system("cls");exit(1);retour=1;break;}// quitter le jeu
                     }
                 }
            }
            break;
        }
        case 3:{
            system("cls");
            printf("Projet realise par :\n\t\t - BENALI Jamal\n\t\t - BEN JEMAA Oussama\n\t\t - BAYA HAYTAM");
            printf("\n\nentrer 1 pour retourner au menu principal\n");//demandé de taper 0 pour quitter le jeu
                 printf("entrer 0 pour quitter\n");
                 int retour=0;
                 char charChoix;
                 while(retour==0)
                 {
                     charChoix=getch();
                     switch(charChoix)
                     {
                         case '1':{affichagePrincipal();retour=1;break;}//retourner au menu principal
                         case '0':{system("cls");exit(1);retour=1;break;}// quitter le jeu
                     }
                 }
            break;}
        case 4:{
            system("cls");
            printf("Pour les mouvement: \n\n\n");
            printf("\tZ\n");
            printf("\t^\n");
            printf("\t|\t\t\t-Appuyer sur X pour enregister votre partie\n");
            printf("Q <--       --> D \t\t-Appuyer sur H pour presenter l'aide(Nombre d'aides restants)\n");
            printf("\t|\t  \t\t-Appuyer sur C pour quitter la partie\n");
            printf("\tv\n");
            printf("\tS\n");
            printf("\n\nentrer 1 pour retourner au menu principal\n");//demandé de taper 0 pour quitter le jeu
                 printf("entrer 0 pour quitter\n");
                 int retour=0;
                 char charChoix;
                 while(retour==0)
                 {
                     charChoix=getch();
                     switch(charChoix)
                     {
                         case '1':{affichagePrincipal();retour=1;break;}//retourner au menu principal
                         case '0':{system("cls");exit(1);retour=1;break;}// quitter le jeu
                     }
                 }
            break;}
        case 5:{exit(1);break;}
}
}
