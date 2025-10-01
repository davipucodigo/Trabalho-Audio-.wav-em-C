#include <stdio.h>

void MENU () {
        printf("\n___________________________________________________ ");
        printf("\n|                                                 | ");
        printf("\n|   █████╗ ██╗   ██╗██████╗ ██╗ ██████╗           | ");
        printf("\n|  ██╔══██╗██║   ██║██╔══██╗██║██╔═══██╗          | ");
        printf("\n|  ███████║██║   ██║██║  ██║██║██║   ██║          | ");
        printf("\n|  ██╔══██║██║   ██║██║  ██║██║██║   ██║          | ");
        printf("\n|  ██║  ██║╚██████╔╝██████╔╝██║╚██████╔╝          | ");
        printf("\n|  ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝ ╚═════╝           | ");
        printf("\n|                                                 | ");
        printf("\n|  ███████╗██████╗ ██╗████████╗ ██████╗ ██████╗   | ");
        printf("\n|  ██╔════╝██╔══██╗██║╚══██╔══╝██╔═══██╗██╔══██╗  | ");
        printf("\n|  █████╗  ██║  ██║██║   ██║   ██║   ██║██████╔╝  | ");
        printf("\n|  ██╔══╝  ██║  ██║██║   ██║   ██║   ██║██╔══██╗  | ");
        printf("\n|  ███████╗██████╔╝██║   ██║   ╚██████╔╝██║  ██║  | ");
        printf("\n|  ╚══════╝╚═════╝ ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝  | ");
        printf("\n|                                                 | ");
        printf("\n| DAVI SANT'ANNA VIEIRA  -  4324                  | ");
        printf("\n| - - - - - - - - - - - - - - - - - - - - - - - - | ");
        printf("\n|  1> Tocar                                       | ");
        printf("\n|  2> Extrair trecho                              | ");
        printf("\n|  3> Volume                                      | ");
        printf("\n|  4> Velocidade                                  | ");
        printf("\n|_________________________________________________| ");
        printf("\n Escolha o numero >>");
        printf("\n");
}

typedef struct
{
    /* data */
}wav_file;


MOSTRA_AUDIO(wav_file * p) {
    
}

int main () {

    wav_file audio;
    MOSTRA_AUDIO(&audio);
    MENU();
        // --------- Audio cut interface
    return 0;
}