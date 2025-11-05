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
        printf("\n|  1> Inserir Audio                               | ");
        printf("\n|  2> Extrair trecho                              | ");
        printf("\n|  3> Volume                                      | ");
        printf("\n|  4> Inverter                                    | ");
        printf("\n|  5> Exit                                        | ");
        printf("\n|_________________________________________________| ");
        printf("\n Escolha o numero >>");
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
        O Sample Rate define a taxa na qual o áudio deve ser "tocado" (amostras/segundo).
        É o relógio mestre que dita a velocidade e, como consequência, o tom do áudio.

    ByteRate:
        O Byte Rate define a taxa na qual o hardware tem que mover o arquivo (Bytes/segundo) para acompanhar o áudio em tempo real.
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

void AUMENTAR_AMPLITUDE(char * nome_arq, float fator_volume) {
    FILE * LENDO;
    FILE * ESCREVENDO;

    LENDO = fopen(nome_arq, "rb");
    ESCREVENDO = fopen("saida_volume.wav", "wb"); // Novo arquivo de saída
    
    // Ler e copiar o cabeçalho
    wav_file header;
    fread(&header, sizeof(wav_file), 1, LENDO);
    fwrite(&header, sizeof(wav_file), 1, ESCREVENDO);

    // Processar e ajustar a amplitude sample por sample
    uint32_t bytes_restantes = header.Subchunk2Size; //Numero total de bytes que vou ter que lê
    uint16_t bytes_por_sample = header.BlackAlign; // Tamanho do frame (2 bytes para 16-bit mono, 4 para 16-bit stereo)
    
    int16_t sample; 
    
    // O valor máximo para um sample de 16 bits para não saturar.
    const int16_t MAX_SAMPLE = 32767; 
    const int16_t MIN_SAMPLE = -32768; 

    while (bytes_restantes > 0) {
        
        fread(&sample, sizeof(int16_t), 1, LENDO);

        float novo_valor_float = (float)sample * fator_volume; // A magica acontece aqui.

        if (novo_valor_float > MAX_SAMPLE) {
            sample = MAX_SAMPLE;
        } else if (novo_valor_float < MIN_SAMPLE) {
            sample = MIN_SAMPLE;
        } else {
            sample = (int16_t)novo_valor_float;
        }

        fwrite(&sample, sizeof(int16_t), 1, ESCREVENDO); // guarda o sample
        
        bytes_restantes -= sizeof(int16_t); //A cada leitura eu disconto um bloco de 2 bytes(16bits) quando for 0 ele vai parar por conta do if lá de cima.
    }

    // Fechamento e Sucesso
    fclose(LENDO);
    fclose(ESCREVENDO);

    printf("\nVolume ajustado com fator %.2fx. Salvo em saida_volume.wav\n", fator_volume);
}

void EXTRAIR_AUDIO(char * nome_arq, int t_inicio, int t_fim) {
    FILE * LENDO;
    FILE * ESCREVENDO;
    
    LENDO = fopen(nome_arq, "rb");
    ESCREVENDO = fopen("saida_extraida.wav", "wb");
    
    // Ler o cabeçalho
    wav_file original_header;

    fread(&original_header, sizeof(wav_file), 1, LENDO);

    uint32_t tempototal = original_header.Subchunk2Size/original_header.ByteRate;
    uint32_t bytes_por_segundo = original_header.ByteRate;
    uint32_t bytes_inicio = bytes_por_segundo * t_inicio; 
    
    // Duração do Trecho a Extrair
    int duracao = t_fim - t_inicio;

    if (t_inicio < 0 || t_fim <= t_inicio || t_fim > tempototal) {
        printf("Erro de limites: Valores fora do intervalo valido (0 a %u s) ou t_fim <= t_inicio.\n", tempototal);
        fclose(LENDO);
        fclose(ESCREVENDO);
        return;
    }
    
    // Bytes a Extrair (tamanho do novo áudio)
    uint32_t bytes_a_extrair = bytes_por_segundo * duracao; 
    
    //Atualizar o cabeçalho para o arquivo de saída
    wav_file new_header = original_header;
    
    new_header.Subchunk2Size = bytes_a_extrair; //Adiociona o novo tamanjo
    
    // O tamanho total do arquivo é o novo Subchunk2Size + 36 bytes do cabeçalho
    // (sizeof(wav_file) - 8) = 44 - 8 = 36
    new_header.ChunkSize = new_header.Subchunk2Size + (sizeof(wav_file) - 8); 

    // Escrever o novo cabeçalho no arquivo de saída
    fwrite(&new_header, sizeof(wav_file), 1, ESCREVENDO);

    //Manda pro inicio
    fseek(LENDO,sizeof(original_header) + bytes_inicio, SEEK_SET);
    // |......inicio.......|
    // |...........fim....................|
    //                     |....Duração...|
    //                     |..............| aí calcula o numero de bytes desta duração e guarda, recalcula tudo os tamanho.

    // Copiar o trecho
    uint32_t bytes_restantes = bytes_a_extrair;
    uint32_t tempo_decorrido = bytes_inicio;
    uint32_t bytes_fim = bytes_por_segundo * t_fim;
    
    int16_t sample;

    while (bytes_restantes > 0) {

        if (tempo_decorrido >= bytes_fim) {
             break;
        }
        // Leitura 
        fread(&sample, sizeof(int16_t), 1, LENDO);
        
        // Escrita
        fwrite(&sample, sizeof(int16_t), 1, ESCREVENDO);
        
        // Atualização dos contadores
        bytes_restantes -= sizeof(int16_t);
        tempo_decorrido += sizeof(int16_t);
    }
    
    fclose(LENDO);
    fclose(ESCREVENDO);

    printf("\nÁudio extraído com sucesso. Trecho de %d a %d segundos. Salvo em saida.wav\n", t_inicio, t_fim);
}

void INVERTENDO_AUDIO(char * nome_arq) {
    FILE * LENDO;
    FILE * ESCREVENDO;
    
    LENDO = fopen(nome_arq, "rb");
    ESCREVENDO = fopen("saida_invertido.wav", "wb");
    
    wav_file header;
    fread(&header, sizeof(wav_file), 1, LENDO);
    fwrite(&header, sizeof(wav_file), 1, ESCREVENDO);

    int16_t sample;
    const long MARCHARE_SAMPLE = -(2 * sizeof(int16_t));
    long samples_restantes = header.Subchunk2Size / sizeof(int16_t); // Calcula o numero de blockAligns que tem.

    fseek(LENDO, sizeof(header) + header.Subchunk2Size - sizeof(int16_t), SEEK_SET); // Leva pro fim de dados
    fseek(ESCREVENDO, sizeof(header) , SEEK_SET); // Leva para o Incio de dados
    
    while (samples_restantes > 0) { 
        
        fread(&sample, sizeof(int16_t), 1, LENDO);

        fwrite(&sample, sizeof(int16_t), 1, ESCREVENDO);
        fseek(LENDO, MARCHARE_SAMPLE, SEEK_CUR); 
        samples_restantes--;
    }

    fclose(LENDO);
    fclose(ESCREVENDO);

    printf("\nÁudio invertido com sucesso. Salvo em saida_invertido.wav\n");
}

int main () {

    //Audio 
    wav_file audio;

    //Variaveis de Ajuste
    int op = 0;
    char endereço_arquivo[100] = "audio/smb_world_clear.wav";
    float volume;
    int inicio;
    int fim;
    int loop = 1;

    while(loop) {
        MENU();
        op = 0;
        MOSTRA_AUDIO(&audio,endereço_arquivo);
        scanf("%d", &op);
        fflush(stdin);
        switch (op)
            {
            case 1:
                //Escreve um novo endereço;
                printf("Trocar endereço, digite algo como pasta/arquivo.wav, use um wav 16bit de 1 canal: ");
                scanf("%s",endereço_arquivo);
                fflush(stdin);
                break;
            case 2:
                printf("\n Insira o inicio e termino do recorte em segundos: ");
                scanf("%d %d", &inicio, &fim);
                fflush(stdin);
                EXTRAIR_AUDIO(endereço_arquivo,inicio,fim);
                break;
            case 3:
                printf("\n Insira o volume desejado, use 1.x para acrescentar e 0.x decrementar o volume: ");
                scanf("%f",&volume);
                AUMENTAR_AMPLITUDE(endereço_arquivo,volume);
                break;
            case 4:
                INVERTENDO_AUDIO(endereço_arquivo);
                break;
            case 5:
                loop = 0;
                break;
        }
    }
    printf("\n\n");
    return 0;
}