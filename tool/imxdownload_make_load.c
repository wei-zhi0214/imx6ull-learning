#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "imxdownload.h"

#define BIN_OFFSET      (3072)

/*
 * Modified version:
 * - Only creates load.imx
 * - Does NOT write to SD card
 *
 * Usage:
 *   ./imxdownload_make_load -512m led.bin
 *   ./imxdownload_make_load -256m led.bin
 */

void message_print(void)
{
    printf("I.MX6ULL bin image maker\r\n");
    printf("Base: zuozhongkai imxdownload V1.1\r\n");
    printf("Modify: only generate load.imx, no dd to SD card\r\n");
}

int main(int argc, char *argv[])
{
    FILE *fp;
    unsigned char *buf;
    int nbytes, filelen;
    int ddrsize = 0; /* 0 = 512MB, 1 = 256MB */
    const char *source_bin = NULL;

    message_print();

    if (argc != 3) {
        printf("Error Usage! Reference Below:\r\n");
        printf("  ./%s <-512m or -256m> <source_bin>\r\n", argv[0]);
        printf("Example:\r\n");
        printf("  ./%s -512m led.bin\r\n", argv[0]);
        return -1;
    }

    if (strcmp(argv[1], "-256m") == 0) {
        ddrsize = 1;
    } else if (strcmp(argv[1], "-512m") == 0) {
        ddrsize = 0;
    } else {
        printf("Invalid DDR size: %s\r\n", argv[1]);
        printf("Use -512m or -256m\r\n");
        return -1;
    }

    source_bin = argv[2];

    fp = fopen(source_bin, "rb");
    if (fp == NULL) {
        printf("Can't Open file %s\r\n", source_bin);
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    filelen = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    printf("file %s size = %d Bytes\r\n", source_bin, filelen);

    buf = malloc(filelen + BIN_OFFSET);
    if (buf == NULL) {
        printf("Mem Malloc Failed!\r\n");
        fclose(fp);
        return -1;
    }
    memset(buf, 0, filelen + BIN_OFFSET);

    fread(buf + BIN_OFFSET, 1, filelen, fp);
    fclose(fp);

    if (ddrsize == 0) {
        printf("Board DDR SIZE: 512MB\r\n");
        memcpy(buf, imx6_512mb_ivtdcd_table, sizeof(imx6_512mb_ivtdcd_table));
    } else if (ddrsize == 1) {
        printf("Board DDR SIZE: 256MB\r\n");
        memcpy(buf, imx6_256mb_ivtdcd_table, sizeof(imx6_256mb_ivtdcd_table));
    }

    printf("Delete Old load.imx\r\n");
    remove("load.imx");

    printf("Create New load.imx\r\n");
    fp = fopen("load.imx", "wb");
    if (fp == NULL) {
        printf("Can't Open load.imx!!!\r\n");
        free(buf);
        return -1;
    }

    nbytes = fwrite(buf, 1, filelen + BIN_OFFSET, fp);
    if (nbytes != (filelen + BIN_OFFSET)) {
        printf("File Write Error!\r\n");
        free(buf);
        fclose(fp);
        return -1;
    }

    free(buf);
    fclose(fp);

    printf("Done. Generated load.imx only.\r\n");
    printf("No SD card was written.\r\n");
    printf("Original dd command would be:\r\n");
    printf("  sudo dd iflag=dsync oflag=dsync if=load.imx of=/dev/sdX bs=512 seek=2\r\n");

    return 0;
}
