#include <stdio.h>
#include <stdint.h>

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
    //RIFF
    char ChunckID[4];
    uint32_t ChunkSize;
    char Format[4];
    //fmt
    char Subchunk1ID[4];
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlackAlign;
    uint16_t BitsPerSample;
    //data
    char Subchunk2ID[4];
    uint32_t Subchunk2Size; //Ler os dados apartir daqui.
    //...data
}wav_file;

MOSTRA_AUDIO(wav_file * p) {
    FILE * LEARQUIVO;

    LEARQUIVO = fopen("audio/smb_world_clear.wav","rb");

        if (!LEARQUIVO) printf("Não foi possivel abrir.");
        else {
            fread(p,sizeof(wav_file),1,LEARQUIVO);
            //Se usar %s para printar RIFF. A falta do '/0' fará com que a leitura seja incorreta, passando dos 4 bytes que há por conta do indicador de fim '0'.
            //Se usar uint32 para representar RIFF a arquitetura Intel/AMD registra os numeros ao contrario na memoria ficando FFIR que ao ler em hexa sai ao contrario.
            //Usar char e ler caracter por caracter.
            printf("\nChunckID: %c%c%c%c", p->ChunckID[0],p->ChunckID[1],p->ChunckID[2],p->ChunckID[3]);
            printf("\nChunckSize: %d ",p->ChunkSize);
            printf("\nFormat: %c%c%c%c", p->Format[0], p->Format[1], p->Format[2], p->Format[3]);
            printf("\nSubchunk1ID: %c%c%c%c", p->Subchunk1ID[0], p->Subchunk1ID[1], p->Subchunk1ID[2], p->Subchunk1ID[3]);
            printf("\nSubchunk1Size: %d", p->Subchunk1Size);
            printf("\nAudioFormat: %d ", p->AudioFormat);
            printf("\nNumChannels: %d ", p->NumChannels);
            printf("\nSampleRate: %d ", p->SampleRate);
            printf("\nByteRate: %d ", p->ByteRate);
            printf("\nBlackAlign: %d ", p->BlackAlign);
            printf("\nBitsPerSample: %d ", p->BitsPerSample);
            printf("\nSubchunk2ID: %c%c%c%c", p->Subchunk2ID[0], p->Subchunk2ID[1], p->Subchunk2ID[2], p->Subchunk2ID[3]);
            printf("\nSubchunk2Size: %d ", p->Subchunk2Size);
        }

    fclose(LEARQUIVO);
}

int main () {

    wav_file audio;
    MOSTRA_AUDIO(&audio);
    printf("\n\n");
    //MENU();
        // --------- Audio cut interface
    return 0;
}