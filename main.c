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

/*

1 byte = 8 bits;
.
    É a forma de organização da estrutura do .wav
    "chunks" (pedaços ou blocos de dados)

    Subchunk1Size:
        O tamanho do restante do sub-bloco de formato em bytes. 
        Para áudio PCM (não comprimido), o valor é sempre 16.

    AudioFormat:
    	Indica o tipo de formato de áudio.
        O valor 1 (um) significa PCM (Pulse Code Modulation),
        que é áudio não comprimido. Outros valores indicam
        formatos comprimidos.
    
    NumChannels:    
        O número de canais de áudio. 
        1 para Mono, 2 para Estéreo.

    SampleRate:
        Taxa com que se lê o arquivo.  
        O número de amostras (samples) de áudio gravadas
        por segundo (em Hz). 22050 Hz é uma taxa comum 
        (por exemplo, metade da qualidade de CD).

    ByteRate:
        O número de bytes que devem ser lidos por segundo (em B/s).
        Calculado como: SampleRate * NumChannels * (BitsPerSample / 8).
        Neste caso: 22050⋅1⋅(16/8)=22050⋅2=44100.

    BlockAlign:
        O número de bytes por bloco de amostra. É o tamanho de uma única amostra,
        incluindo todos os canais. Calculado como: NumChannels * (BitsPerSample / 8).
        Neste caso: 1⋅(16/8)=2 bytes.

    BitsPerSample:
        O número de bits usados para armazenar cada amostra de áudio por canal.
        16 bits é a qualidade de áudio de CD (valores inteiros de −32768 a 32767).

    Data:
        É uma constante (4 caracteres ASCII) que marca o início do sub-bloco onde os dados de áudio reais estão armazenados.
    
    Subchunk2Size:
        O tamanho em bytes dos dados de áudio brutos (as amostras reais).
.
*/

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

            int16_t byte; 
            int count = 0;

            for (int i = 0; i < p->Subchunk2Size; i++) {
                // Tenta ler o próximo byte
                /*
                    Cada sample, amplitude tem como informação que o compoem dada por um numero de bits
                    que é indicado em Subchunk1Size que neste caso é 16 bits, com 16bits ele consegue 
                    informar a amplitude.
                */
                if (fread(&byte, sizeof(int16_t), 1, LEARQUIVO) != 1) {
                    break;
                }
                count++;

                if(count % 1 == 0) {
                    fprintf(ESCREVENDO,"\n");
                }
                
                fprintf(ESCREVENDO,"%d ", byte); 
            }
            
            fprintf(ESCREVENDO,"\n\n--- Fim dos Dados de Audio ---\n");
        }
    fclose(LEARQUIVO);
    fclose(ESCREVENDO);
}

//                                              (Em segundos)
void EXTRAIR_AUDIO(wav_file * p, char * nome_arq, int tcorte) {
    FILE * LENDO;
    FILE * ESCREVENDO;
    LENDO = fopen(nome_arq,"rb");
    ESCREVENDO = fopen("saida.wav","wb");

    //Calculo tempo de corte
    int byte_que_ocorrerá_o_corte = p->BitsPerSample * tcorte; // Usar numeros inteiros no tcorte;
    printf("\n %d \n", byte_que_ocorrerá_o_corte);
    if ( byte_que_ocorrerá_o_corte >= p->Subchunk2Size) {
        printf("Erro: Tempo de corte (%d segundos) e maior ou igual ao audio total.\n", tcorte);
        fclose(LENDO);
        fclose(ESCREVENDO);
        return;
    }

    fclose(LENDO);
    fclose(ESCREVENDO);
}

int main () {

    wav_file audio;
    char endereço_arquivo[100] = "audio/smb_world_clear.wav";

    MOSTRA_AUDIO(&audio,endereço_arquivo);
    EXTRAIR_AUDIO(&audio,endereço_arquivo,3);
    printf("\n\n");
    //MENU();
        // --------- Audio cut interface
    return 0;
}