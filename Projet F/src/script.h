#ifndef SCRIPT_H
#define SCRIPT_H

typedef struct double_information D_I ;

struct double_information
{
    char *element1;
    char *element2;
    char *element3;
    char *element4;

};


typedef struct information Infos ;

struct information
{
    char *infos1;
    char *infos2;
};


typedef struct etudiant Et ;

struct etudiant
{   
    //Constant
    char *departement;
    char *annee;
    char *classe;
    char *DATE;
    char *Professeur;
    char *Module;

    //Variables
    char *ID;
    char *NOM;
    char *Prenom;
    
};




int CreateFile(char *imageName);

void chomp(char *s);

void space(FILE *flux, int dist);

void Add(char *chaine1,char *chaine2);

void liberer(char *ele);

Infos recup_line2(char *ligne,char *sep1,char *sep2);

D_I recup_line1(char *ligne, char *sep1, char *sep2, char *sep3, char *sep4);

int verification(char *nomfichier,char *ligne1,char *ligne2);

int ecrire(char *nomfichier,Et etudiant);

int read_line( char *nomFichier);


#endif

