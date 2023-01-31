#include <stdio.h>
#include "image_ppm.h"
#include <fstream>

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.dat\n"); 
       exit (1) ;
     }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite) ;

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    int tabId[256];

    for (int elt=0; elt < 256; elt++)
    {
        tabId[elt] = 0;
    }

    //Dans ce tableau, on va compter l'occurence des niveaux de gris de l'image
    for (int i=0; i < nW; i++)
    {
        for (int j=0; j < nW; j++)
        {
            tabId[ImgIn[i*nW+j]] += 1;
        }
    }

    //On va ensuite mettre toutes les valeurs dans le fichier "histo.dat"
    std::ofstream fichier(cNomImgEcrite);

    for (int k = 0; k < 256; k++) 
    {
        printf("%i %i\n", k, tabId[k]);
        fichier << k << " " << tabId[k] << "\n";
    }

    fichier.close();
}