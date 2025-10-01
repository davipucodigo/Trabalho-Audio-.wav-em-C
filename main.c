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
    uint32_t ChunckID;
    uint32_t ChunkSize;
    uint32_t Format;
    //fmt
    uint32_t Subchunk1ID;
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlackAlign;
    uint16_t BitsPerSample;
    //data
    uint32_t Subchunk2ID;
    uint32_t Subchunk2Size; //Ler os dados apartir daqui.
    //...data
}wav_file;

MOSTRA_AUDIO(wav_file * p) {
    FILE * LEARQUIVO;

    LEARQUIVO = fopen("audio/smb_world_clear.wav","rb");

        if (!LEARQUIVO) printf("Não foi possivel abrir.");
        else {
            fread(p,sizeof(wav_file),1,LEARQUIVO);
            printf(
                "\nChunckID: %x"
                "\nChunkSize: %x"
                "\nFormat: %x"
                //fmt
                "\nSubchunk1ID: %x"
                "\nSubchunk1Size: %x"
                "\nAudioFormat: %x"
                "\nNumChannels: %x"
                "\nSampleRate: %x"
                "\nByteRate: %x"
                "\nBlackAlign: %x"
                "\nBitsPerSample: %x"
                //data
                "\nSubchunk2ID: %x"
                "\nSubchunk2Size: %x",
                p->ChunckID, p->ChunkSize, p->Format, 
                p->Subchunk1ID, p->Subchunk1Size, p->AudioFormat, p->NumChannels,
                p->SampleRate, p->ByteRate, p->BlackAlign, p->BitsPerSample,
                p->Subchunk2ID, p->Subchunk2Size
            );
        }

    fclose(LEARQUIVO);
}

int main () {

    wav_file audio;
    MOSTRA_AUDIO(&audio);
    //MENU();
        // --------- Audio cut interface
    return 0;
}