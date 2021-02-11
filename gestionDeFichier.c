#include "sudoko.h"

void SauvegarderPartie(char grille[9][9],char username[100],Cases* list,char nivF[1],int nbrF,int aideR)
{
    //cette fonction permet de sauvegarder la partie joué et non complete par un joueur dans un fichier
    FILE* fichier = NULL;
    char dateTime[19];
    currentTime(dateTime); // stocker la valeur de la date et l'heure actuelle dans la variabke dateTime
    char title[150]="";//nous allons stocker le chemin du fichier dans ce tableau de caractère
    sprintf(title,"sauvegarde\\%s\\grille%c%d%s.txt",username,nivF[0],nbrF,dateTime);
   //le nom du nouveau fichier va être composer du niveau de la grille joué et son numéro et la date actuelle
   //le fichier va être stocker dans un dossier qui porte le nom du joueur
    system("cls");
    fichier = fopen(title, "w+");
    if (fichier != NULL)
    {
        // On peut lire et écrire dans le fichier
        int i,j;
        //écrire la grille jouée dans le fichier:
        for(i=0;i<9;i++)
        {
          for(j=0; j<9; j++)
            {
            fprintf(fichier,"|%c",grille[i][j]);
            }
            fprintf(fichier,"|\n");
        }
    Cases* dd=list;//écrire les coordonnées de chaque case remplie ou doit être remplis par l'utilisateur
    while(dd!=NULL)
    {
        fprintf(fichier,"|%d,%d",dd->ligne,dd->colone);
        dd=dd->suivant;
    }
    //le temps écoulé du début de la partie jusqu'à le sauvegarde
    time(&save);
    fprintf(fichier,"|%c%d",nivF[0],nbrF);//savegarde du niveau de la grille et son numèro
    fprintf(fichier,"\n%d",aideR); //sauvegarde du nombre d'aide restant
    fprintf(fichier,"\n%.2f",difftime(save,start)+tempsPasse);//sauvegarde du temps écoulé
    fclose(fichier);//fermeture du fichier
    }
    else
    {
        // On affiche un message d'erreur si on peut pas lire et écrire dans le fichier
        printf("Impossible de sauvegarde le fichier\n");
    }
}

Cases* lirePartie(char grille[9][9],char username[100],char nivF[1],int *nbrF,char fileTitle[10],int *aideRes)
{
    //cette fonction permet de lire une partie jouée par un utilisateur et qui retourne les cases à remplir par le joueur
    Cases* list=NULL;
    char niv;
    FILE* fichier = NULL;
    char title[250]="";
    //le titre du chemin va se composer du nom de dossier qui porte le nom du joueur, et la grille(son niveau et son numero) et la date
    sprintf(title,"sauvegarde\\%s\\%s.txt",username,fileTitle);
    fichier = fopen(title, "r");
    if (fichier != NULL)
    {
    int l=0,a=0,j=0,ligne=0,nb=0;
    int test;
    char ch[250],ch1[128];
    int position;
    int cmp=0;
    //lecture de la grille
    while(cmp!=9)
    {
        fgets(ch,sizeof(ch),fichier);
        if(ligne<9)
        {
            for(j=0; j<9; j++)
            {
                if(ch[2*j+1]=='_')
                grille[ligne][j]=' ';
                else
                grille[ligne][j]=ch[2*j+1];
            }
            ligne++;
        }
        cmp++;
    }
    //lecture des cases vides ou cases remplis par le joueur
    fgets(ch,sizeof(ch),fichier);
    j=0;
    while(ch[j+1]!='F' && ch[j+1]!='M' && ch[j+1]!='D')
    {
        list=insertionCases(list,creerCases(ch[j+1]-48,ch[j+3]-48));
        j+=4;
    }
    nivF[0]=ch[j+1];//lecture du niveau de la grille
    *nbrF=ch[j+2]-48;//lecture du numero de la grille
    fscanf(fichier,"%d",aideRes);//lecture du nombre d'aide restant
    fscanf(fichier,"%f",&tempsPasse);//lecture du temps passé avant le sauvegarde
    fclose(fichier);//fermeture du fichier
    return list;
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible de lire la partie");
    }
}
Cases* lireGrilleJeu(char grille[9][9],char niv[1],int nbrGr,Cases* listVides)
{
    //cette fonction permet de lire une nouvelle grille et qui retourne les cases à remplir par le joueur
    FILE* fichier = NULL;
    char title[150]="";
    sprintf(title, "grillesAresoudre\\grille%s%d.txt",niv,nbrGr);//le chemin va etre composer du niveau de la grille et son  numero
    fichier = fopen(title, "r");
     Cases* newCase=NULL;
    if (fichier != NULL)
    {
    int l=0,a=0,j=0,ligne=0,nb=0;
    int test;
    char ch[128],ch1[128];
    //lecture de la grille
    while(fgets(ch,sizeof(ch),fichier)!= NULL)
    {
            for(j=0; j<9; j++)
        {
            grille[ligne][j]=ch[2*j+1];
            if(grille[ligne][j]==' ')
            {
                newCase=creerCases(ligne,j);
                listVides = insertionCases(listVides,newCase);
            }

        }
        ligne++;
    }
    //fermeture du fichier
    fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }
    return listVides;
}


Cases* resultatfinale(char grille[9][9],char username[100],int *faute,char niv[1],int nbrGr,Cases* casesFault)
{

    //cette fonction permet de comparer le grille remplis par le joueur par la solution, et qui retourne les coordonées des cases fausse
    casesFault=suprressionList(casesFault);//vider la liste des cases fausses s'ils existent
    int l=0,a=0,j=0,ligne=0,nb=0;
    char title[150]="";
    sprintf(title, "Solutions\\grille%c%d.txt",niv[0],nbrGr);
    int test;
    char ch[128],ch1[128];
    FILE *g=fopen(title,"r");
    if(g!=NULL)
    {
        printf("\n");
    test=1;
    //comparaison des cases
    while(fgets(ch,sizeof(ch),g)!= NULL)
    {
        ligne++;
        for(j=0; j<9; j++)
        {
            if ((grille[ligne-1][j])!=((ch[2*j+1])))
            {
                //si les deux cases ne sont pas identiques on va ajouter une case à la liste des cases fausses
                test=0;
                a=j+1;
                 casesFault=insertionCases(casesFault,creerCases(ligne-1,a-1));
                nb++;
            }
        }
    }

     fclose(g);
     //affichage du nombre totales de fautes
    if (test==0)
        {
            printf("\nLenombre total de fautes est : %d",nb);
            printf("\nBouger si vous voulez continuer\n");
            printf("\nAppuyer sur 'C' si vous voulez quitter\n");
        }
    // s'il n'y a pas de faute on va dire congratulation au joueur
    else{
        printf("SUCCESS! CONGRATULATION\n");
        //sauvegarde du score
        putInFile(username,niv,nbrGr);
        *faute=0;
    }
    return casesFault;
    }

    else
    {
        printf("impossible d'ouvrire le fichier de solution\n");
    }

}
void putInFile(char username[100],char nivF[1],int nbrF)
{
    //cette fonction permet de sauvegarder le score du joueur qui a réussis de remplir une grille sans fautes
    float dureeOfPartie;
    time(&end);
    dureeOfPartie=difftime(end,start)+tempsPasse;// la duree de la partie
    FILE* fichier = NULL;
    char title[150]="";
    sprintf(title,"sauvegarde\\%s\\%s.txt",username,username);
    fichier = fopen(title, "a");
    if (fichier != NULL)
    {
    //convertir la duree en minutes
    int minute  = (int)dureeOfPartie / 60 % 60;
    int seconde = (int)dureeOfPartie % 60;
    //écrire la grille et le score dans le fichier
    fprintf(fichier,"\n\ngrille%c%d ========> %d minute(s), %d seconde(s)",nivF[0],nbrF,minute,seconde);
    fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible de sauvegardé le score\n");
    }
}
 void creerFilePlayer(char username[100])
 {
     // cette fonction permet d'écrire un dossier et un fichier au nom du joueur
     char newFile[100]="";
     char fileName[100]="";
     sprintf(newFile,"mkdir .\\sauvegarde\\%s",username);
     //écrire un dossier au nom du joueur
     system(newFile);
     sprintf(fileName,"sauvegarde\\%s\\%s.txt",username,username);
     FILE* fichier = NULL;
     //écrireun fichier au nom du joueur
    fichier = fopen(fileName, "w+");
    if(fichier!=NULL)
    {
        fclose(fichier);
    }
    if(fichier==NULL)
    {
        printf("impossible de jouer");
        exit(1);
    }
 }
 int existRepre(char username[100])
 {
     // cette fonction permet de savoir l'existance d'un dossier qui porte un nom donné
     char fileName[100]="";
     sprintf(fileName,"sauvegarde\\%s\\%s.txt",username,username);
     FILE* fichier = NULL;
    fichier = fopen(fileName, "r");
    if(fichier!=NULL)
    {
        // retourne 1 s'il existe
        return 1;
    }
    if(fichier==NULL)
    {
        //retourne 0 si non
        return 0;
    }
 }

 int lireRepertoire(char nom[100],Files *fichiers)
 {
     //cette fonction permet de lire le contenu d'un repertoire
     int fichierVide=1;
     char filee[100]="";
                 struct dirent *lecture;
                DIR *rep;
                sprintf(filee,"./sauvegarde/%s",nom);
                //ouverture du repertoire
                rep = opendir(filee);
                int cmp=0,cmp2=1,cmp3=1;
                //lecture du contenu
                while ((lecture = readdir(rep))) {
                    //depasse les deux valeurs parce qu'ils contiennent: . ..
                    if(cmp2==1 || cmp2==2)
                    {
                        cmp2++;
                        continue;
                    }
                    int j;
                    for(j=0;j<lecture->d_namlen-4;j++){
                        //savegarde des titres des fichiers du contenu dans une liste
                        fichiers[cmp].nom[j]=lecture->d_name[j];
                    }
                    fichiers[cmp].nom[j]='\0';
                    if(strcasecmp(fichiers[cmp].nom,nom)!=0){
                    //affichage des fichiers du contenu
                    printf("%d:%s\n",cmp3,fichiers[cmp].nom);
                    //donner un numero index à chaque fichier
                    fichiers[cmp].index=cmp3;
                    cmp3++;
                    }
                    cmp++;
                }
                closedir(rep);
                return fichierVide;
 }

void currentTime(char dateTime[19])
{
  //cette fonction permet de stocker la valeur de la date et l'heure actuelle dans le tableau dateTime
  int h, min, s, day, mois, an;
  time_t now;
  // Renvoie l'heure actuelle
  time(&now);
  // Convertir au format heure locale
  struct tm *local = localtime(&now);
  h = local->tm_hour;
  min = local->tm_min;
  s = local->tm_sec;
  day = local->tm_mday;
  mois = local->tm_mon + 1;
  an = local->tm_year + 1900;
  sprintf(dateTime,"%02d_%02d_%d_%02d_%02d_%02d", day, mois, an, h, min, s);
}
int aide(int ligne,int colonne,char niv[1],int nbrGr)
{
    //cette fonction permet d'aider le joueur en remplissant une case de la grille pour lui
    int i=0;
    char ch[1500];
    int nb;
    char title[150]="";
    sprintf(title, "Solutions\\grille%s%d.txt",niv,nbrGr);
    // lire la grille de la solution
    FILE *f =fopen(title,"r");
    if(f!=NULL)
    {
            for(i=0;i<ligne;i++)
    {
        fflush(stdin);
        //lire les cases de la ligne demandé
        fgets(ch,sizeof(ch),f);
    }
    fclose(f);
    //retourne la valeur de la case demandé(correspond à la ligne et la colonne)
    return ch[2*colonne-1];
    }
    if(f==NULL)
    {
        printf("impossible d'ouvrire le fichier d'aide\n");
    }
    SEEK_CUR;
}
void lireScore(char nom[100])
{
    //cette fonction permet de lire les scores d'un joueur donné
    FILE* fichier = NULL;
    char title[150]="";
    sprintf(title, "sauvegarde\\%s\\%s.txt",nom,nom);//le chemin va etre composer du nom de joueur
    fichier = fopen(title, "r");
    if (fichier != NULL)
    {
    char ch[200];
    while(fgets(ch,sizeof(ch),fichier)!= NULL)
    {
           printf("%s",ch);
    }
    //fermeture du fichier
    fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier");
    }
}
