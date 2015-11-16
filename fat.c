#include <stdio.h>
#include <stdint.h>

#define CLUSTER_SIZE    1024    // Tamanho do cluster em bytes
#define BOOT_DIR_SIZE   1       // numero de clusters da area de boot
#define ROOT_DIR_SIZE   1       // numero de clusters do doretorio de root
#define FAT_SIZE        8       // numero de clusters da FAT
#define DATA_SIZE       4086    // numero de clusters da area de dados     

#define PART_NAME       "fat.part"  //nome do arquivo da partição
/*
- 512 bytes por setor;
- cluster de 1024 bytes (2 setores por cluster);
- 4096 clusters;
*/

// Entrada de diretorio, 32 bytes cada
typedef struct 
{
    uint8_t filename[18];
    uint8_t attributes;
    uint8_t reserved[7];
    uint16_t firs_block;
    uint32_t size;
} dir_entry_t;

// Diretorios (incluindo ROOT), 32 entradas de diretorio
// com 32 bytes cada = 1024 bytes ou bloco de dados de 1024 bytes
union 
{
    dir_entry_t dir[CLUSTER_SIZE / sizeof(dir_entry_t)];
    uint8_t data[CLUSTER_SIZE];
} data_cluster;


// 8 clusters da tabela FAT, 
// 4096 entradas de 16 bits = 8192 bytes
uint16_t fat[4096];

#include "fat.h"

void fat_init(void)
{
    FILE *file;
    dir_entry_t dir;

   file = fopen(PART_NAME, "wb");
    if (!file)
    {
        printf("Unable to open file!");
    }

    //boot block
    const uint boot_block_size = BOOT_DIR_SIZE * CLUSTER_SIZE;
    for(int i = 0; i < boot_block_size; i++ )
    {
        fputc(0xbb, file);
    }

    //FAT
    const uint fat_size = FAT_SIZE * CLUSTER_SIZE;
    for(int i = 0; i < boot_block_size; i++ )
    {
        fputc(0xbb, file);
    }


    //root dir


    // Tests

    int i;
    for (i = 0; i < 4096 * 32; i++ ) {
        fwrite(&dir, sizeof(dir_entry_t), 1, file);
    }

    fclose(file);
}


