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

void MOSTRA_AUDIO(wav_file * p, char * nome_arq) {
    FILE * ESCREVENDO;
    FILE * LEARQUIVO;
        ESCREVENDO = fopen("analise_WAVE.txt","wt");
        LEARQUIVO = fopen(nome_arq,"rb");

        if (!LEARQUIVO) printf("Não foi possivel abrir.");
        else {
            fread(p,sizeof(wav_file),1,LEARQUIVO);
            //Se usar %s para printar RIFF. A falta do '/0' fará com que a leitura seja "incorreta", passando dos 4 bytes que há por conta do indicador de fim '/0' necessários não contidos na estrutura do arquivos.
            //Se usar uint32 para representar RIFF a arquitetura Intel/AMD registra os numeros ao contrario na memoria ficando FFIR que ao ler em hexa sai ao contrario.
            //Usar char e ler caracter por caracter.
            fprintf(ESCREVENDO,"\nChunckID: %c%c%c%c", p->ChunckID[0],p->ChunckID[1],p->ChunckID[2],p->ChunckID[3]);
            fprintf(ESCREVENDO,"\nChunckSize: %d ",p->ChunkSize);
            fprintf(ESCREVENDO,"\nFormat: %c%c%c%c", p->Format[0], p->Format[1], p->Format[2], p->Format[3]);
            fprintf(ESCREVENDO,"\nSubchunk1ID: %c%c%c%c", p->Subchunk1ID[0], p->Subchunk1ID[1], p->Subchunk1ID[2], p->Subchunk1ID[3]);
            fprintf(ESCREVENDO,"\nSubchunk1Size: %d", p->Subchunk1Size);
            fprintf(ESCREVENDO,"\nAudioFormat: %d ", p->AudioFormat);
            fprintf(ESCREVENDO,"\nNumChannels: %d ", p->NumChannels);
            fprintf(ESCREVENDO,"\nSampleRate: %d ", p->SampleRate);
            fprintf(ESCREVENDO,"\nByteRate: %d ", p->ByteRate);
            fprintf(ESCREVENDO,"\nBlackAlign: %d ", p->BlackAlign);
            fprintf(ESCREVENDO,"\nBitsPerSample: %d ", p->BitsPerSample);
            fprintf(ESCREVENDO,"\nSubchunk2ID: %c%c%c%c", p->Subchunk2ID[0], p->Subchunk2ID[1], p->Subchunk2ID[2], p->Subchunk2ID[3]);
            fprintf(ESCREVENDO,"\nSubchunk2Size: %d ", p->Subchunk2Size);
            fprintf(ESCREVENDO,"\n\n--- Dados de Audio (Samples) em Hexadecimal ---\n");

            // unsigned (0 a 225).
            // signed (-128 a 127) utiliza complemento de dois.
            unsigned char byte; 
            int count = 0;

            for (int i = 0; i < p->Subchunk2Size; i++) {
                // Tenta ler o próximo byte
                if (fread(&byte, 1, 1, LEARQUIVO) != 1) {
                    break; // Sai se não conseguir ler o próximo byte (Fim do arquivo)
                }
                count++;

                if(count % 16 == 0) {
                    fprintf(ESCREVENDO,"\n");
                }
                // %02X -> Imprime o byte em hexadecimal (X), com 2 dígitos, preenchidos com zero (0).
                fprintf(ESCREVENDO,"%02X ", byte); 
            }
            
            fprintf(ESCREVENDO,"\n\n--- Fim dos Dados de Audio ---\n");
        }
    fclose(LEARQUIVO);
    fclose(ESCREVENDO);
}

// void EXTRAIR_AUDIO(wav_file * p) {}

int main () {

    wav_file audio;
    char endereço_arquivo[100] = "audio/smb_world_clear.wav";

    MOSTRA_AUDIO(&audio,endereço_arquivo);
    //EXTRAIR_AUDIO(&audio);
    printf("\n\n");
    //MENU();
        // --------- Audio cut interface
    return 0;
}