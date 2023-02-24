#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "script.h"


int CreateFile(char *imageName)
{
    char *call = malloc(sizeof(char[50]));
    strcat(call,"python3 pytess.py ");
    strcat(call,imageName);
    system(call);
    return 0;

}

void chomp(char *s)
{
    while (*s != '\n' && *s != '\0')
        ++s;

    *s = '\0';
}

void Add(char *chaine1,char *chaine2)
{
    int i = 0;
    while (chaine1[i]!='\0')
    {
        chaine2[i] = chaine1[i] ;
        i++;
    }
  
}

void liberer(char *ele)
{
    for (int i = 0; i < strlen(ele); i++)
    {
        ele[i] = ' ';
    }   
}


void space(FILE *flux, int dist)
{
    for (int i = 0; i < dist; i++)
    {
        fprintf(flux," ");
    }   
}



D_I recup_line1(char *ligne, char *sep1, char *sep2, char *sep3, char *sep4)
{
    D_I x;
    
    char *p = strtok(ligne, sep1);

    for (int i = 0; p != NULL; i++)
    {
        if (i+1==1)
        {
            x.element1 = p ;
            p = strtok(NULL, sep2);
        } 

        if (i+1==2)
        {
            x.element2 = p ;
            p = strtok(NULL, sep3);
        }

        if (i+1==3)
        {
            x.element3 = p ;
            p = strtok(NULL, sep4);
        }

        if (i+1==4)
        {
            x.element4 = p ;
        }

        if (i+1==5)
        {
            break;  
        }
    }
    return x ;
}



Infos recup_line2(char *ligne,char *sep1,char *sep2)
{
    Infos y ;

    char *p = strtok(ligne, sep1);

    for (int i = 0; p != NULL; i++)
    {
        if (i+1==1)
        {
            y.infos1 = p ;
            p = strtok(NULL, sep2);
        }

        if (i+1==2)
        {
            y.infos2 = p ;
        }

        if (i+1==3)
        {
            break;  
        }
    }
    return y;
}



int verification(char *nomfichier,char *ligne1,char *ligne2)
{
    char buf[200];

    char *pstr;

    FILE *fp = fopen(nomfichier,"r+"); 

    if (fp == NULL)
    {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert\n",nomfichier);
        return EXIT_FAILURE;
    }

    rewind(fp);  

    fgets(buf,200,fp);
    pstr = strstr(buf,ligne1);
    if (pstr==NULL)
    {
        fgets(buf,200,fp);
        pstr = strstr(buf,ligne1);
        if (pstr==NULL)
        {
            rewind(fp);
            fprintf(fp,"\t \t %s\n",ligne1);
            fprintf(fp,"\n");
            fprintf(fp,"%s\n",ligne2);
            fprintf(fp,"\n");

        }
        
    }

    fclose(fp);
}



int ecrire(char *nomfichier,Et etudiant)
{

    FILE *fp = fopen(nomfichier,"a");

    if (fp == NULL)
    {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert\n",nomfichier);
        return EXIT_FAILURE;
    }

    char ligne1[200] = "LISTES DES ETUDIANTS(ES) ABSENTS(ES)";
    char ligne2[200] = "DATE             ID        Prenom           Nom               Module                  Enseignants(es)";

    int tab_position[5] = {14,25,41,57,80} ;

    int pos = 0 ;
    
    verification(nomfichier,ligne1,ligne2);//Verifier la presence du fichier et de l'entete
    
    
    fprintf(fp,"%s",etudiant.DATE);
    pos = strlen(etudiant.DATE);
    space(fp,tab_position[0]-pos);// Se placer au niveau de l'id
    
    fprintf(fp,"-%s",etudiant.ID);
    pos = tab_position[0] + strlen(etudiant.ID) ;
    space(fp,tab_position[1]-pos);// Se palcer au niveau du prenom
    
    fprintf(fp,"-%s",etudiant.Prenom);
    pos = tab_position[1] + strlen(etudiant.Prenom) ;
    space(fp,tab_position[2]-pos);//Se placer au niveau du nom
    
    fprintf(fp,"-%s",etudiant.NOM);
    pos = tab_position[2] + strlen(etudiant.NOM) ;  
    space(fp,tab_position[3]-pos);// Se placer au niveau du MOdule 
    
    fprintf(fp,"-%s",etudiant.Module);
    pos = tab_position[3] + strlen(etudiant.Module) ;
    space(fp,tab_position[4]-pos);// Se placer au niveau du professeur
    
    fprintf(fp,"-%s",etudiant.Professeur);
    fprintf(fp,"\n");

    fclose(fp);
    return 0;
    
}





int read_line( char *nomFichier)
{
    char *ligne = malloc(sizeof(char[250]));

    char *dep = "DEPARTEMENT" ;
    char *date = "DATE" ;
    char *Resp = "RESPONSABLE:" ;
    char *module = "NOM DU MODULE:" ;
    char *nomPr = "NOM DE L";
    char *abs = "Absent" ;
   
    char *sep1;
    char *sep2;
    char *sep3;
    char *sep4;
      
    D_I x1; 
    D_I x2 ; 
    D_I x3;
    D_I etd ;

    Infos y1 ;
    Infos y2 ;

    Et etudiant ;

    etudiant.departement = malloc(sizeof(char[20]));
    etudiant.annee = malloc(sizeof(char[20]));
    etudiant.classe = malloc(sizeof(char[20]));
    etudiant.classe = malloc(sizeof(char[20]));
    etudiant.ID = malloc(sizeof(char[20]));
    etudiant.Prenom = malloc(sizeof(char[30]));
    etudiant.NOM = malloc(sizeof(char[30]));
    etudiant.DATE = malloc(sizeof(char[20]));
    etudiant.Professeur = malloc(sizeof(char[30]));
    etudiant.Module = malloc(sizeof(char[30]));
   
    char *pLigne1 =NULL ;
    char *pLigne2 = NULL ;
    char *pLigne3 = NULL;
    char *pLigne4 = NULL;
    char *pLigne5 = NULL;
    char *pLis = NULL ;
    
    int kj =0 ;
    //int fc = 1 ;
    //int a = 0 ;

    FILE *fp = fopen(nomFichier,"r");

    if (fp == NULL)
    {
        fprintf(stderr, "Le fichier %s n'a pas pu être ouvert\n",nomFichier);
        return EXIT_FAILURE;
    }

    while (strstr(ligne,"LISTE DES ETUDIANTS")==NULL)
    {
        fgets(ligne,200,fp);

        pLigne5 = strstr(ligne,dep);

        if (pLigne5!=NULL) 
        {
            sep1 = ":";
            sep2 = " ";
            sep3 = ":";
            sep4 = " ";

            x3 = recup_line1(ligne,sep1,sep2,sep3,sep4);

            Add(x3.element4,etudiant.annee);
            
            Add(x3.element2,etudiant.departement);        
        }


        pLigne1 = strstr(ligne,date);

        if (pLigne1!=NULL) 
        {   
            sep1 = ":";
            sep2 = " ";
            sep3 = ":";
            sep4 = " ";
    
            x1 = recup_line1(ligne,sep1,sep2,sep3,sep4);

            Add(x1.element4,etudiant.classe);
            
            Add(x1.element2,etudiant.DATE);    
        }

        pLigne2 = strstr(ligne,Resp);
        
        if (pLigne2!=NULL) 
        {
            sep1 = ":";
            sep2 = "\n";

            y1 = recup_line2(ligne,sep1,sep2);
        }

        pLigne3 = strstr(ligne,module);

        if (pLigne3!=NULL) 
        {
            sep1 = ":";
            sep2 = " ";
            sep3 = " ";
            sep4 = "\n";

            x2 =  recup_line1(ligne,sep1,sep2,sep3,sep4);

            Add(x2.element2,etudiant.Module);
        }

        pLigne4 = strstr(ligne,nomPr);

        if (pLigne4!=NULL) 
        { 
            sep1 = ":" ;
            sep2 = "\n" ;

            y2 = recup_line2(ligne,sep1,sep2);

            chomp(y2.infos2);

            Add(y2.infos2,etudiant.Professeur) ;
        }

    }

    while ((ftell(fp)!=SEEK_END) && (kj<40))
    {
        if (fgets(ligne,200,fp)!=NULL)
        {
            kj++;
            pLis = strstr(ligne,abs);

            if (pLis!=NULL)
            {
                sep1 = " ";
                sep2 = " ";
                sep3 = " ";
                sep4 = " ";

                etd = recup_line1(ligne,sep1,sep2,sep3,sep4);

                chomp(etd.element1);
                chomp(etd.element2);
                chomp(etd.element3);
                chomp(etd.element4);

                Add(etd.element1,etudiant.ID);
                Add(etd.element2,etudiant.Prenom);
                Add(etd.element3,etudiant.NOM);

                char *nomFichier;
                nomFichier = etudiant.departement ;
                if (strstr(nomFichier,".txt")==NULL)
                {
                    chomp(nomFichier);
                    strcat( nomFichier,".txt");
                }                
                
                ecrire(nomFichier,etudiant);

                liberer(etudiant.ID);
                liberer(etudiant.Prenom);
                liberer(etudiant.NOM);
               
            }       
        }        
    }

    if (kj>37)
    {
        fclose(fp);
    }

}
