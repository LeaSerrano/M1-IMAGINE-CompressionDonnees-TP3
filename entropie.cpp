#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

   float tabProba[256], tabId[256];

    for (int elt=0; elt < 256; elt++)
    {
        tabId[elt] = 0;
        tabProba[elt] = 0;
    }

    for (int i=0; i < nH; i++)
    {
        for (int j=0; j < nW; j++)
        {
            tabId[ImgIn[i*nW+j]] += 1;
        }
    }

    for (int k = 0; k < 256; k++) 
    {
        tabProba[k] = float(tabId[k]/(nH*nW));
    }

    float entropie = 0; 

    for (int i = 0; i < 256; i++) {
        if (tabProba[i] > 0) {
            entropie += tabProba[i] * log2(tabProba[i]);
        }
    }

    entropie *= -1;

    std::cout << "L'entropie est de : " << entropie << std::endl;


   free(ImgIn);

   return 1;
}