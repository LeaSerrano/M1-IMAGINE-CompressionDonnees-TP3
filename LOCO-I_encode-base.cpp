#include <stdio.h>
#include "image_ppm.h"
#include <fstream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgTemp, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
   allocation_tableau(ImgTemp, OCTET, nTaille);

  for (int i = 0; i < nH; i++) {
    for (int j = 0; j < nW; j++) {
        if (i > 0 && j > 0) {
            int a = ImgIn[i*nW+(j-1)];
            int b = ImgIn[(i-1)*nW+(j-1)];
            int c = ImgIn[(i-1)*nW+j];

            if (b >= std::max(a, c)) {
                ImgOut[i*nW+j] = std::min(a, c);
            }
            else if (b <= std::min(a, c)) {
                ImgOut[i*nW+j] = std::max(a, c);
            }
            else {
                ImgOut[i*nW+j] = a + c - b;
            }
        }
        else if (i == 0 && j != 0) {
            ImgOut[i*nW+j] = ImgIn[i*nW+(j-1)];
        }
        else if (j == 0 && i != 0) {
            ImgOut[i*nW+j] = ImgIn[(i-1)*nW+j];
        }
        else if (i == 0 && j == 0) {
          ImgOut[i*nW+j] = ImgIn[i*nW+j];
        }
    }
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}