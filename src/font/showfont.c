#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* 字体 */
#define FNT_H 16 /* 字体高度 */
#define FNT_W 8 /* 半角宽度 */
#define FNT_Q 16 /* 全角宽度 */
#define FNT_S 32 /* 每个字形所占字节数 */
#define FNT_A 2097152 /* 字体文件大小 0x10000 * 32 */

int ishalf(const char* font)
{
    font += FNT_H;
    int i;
    for (i = 0; i < FNT_H; i++) {
        if (font[i] != 0) {
            return 0; /* 全角字符 */
        }
    }
    return 1; /* 半角字符 */
}

int main(int argc, char const* argv[])
{
    unsigned char* unifont = (unsigned char*)malloc(FNT_A);
    int fin = open("unifont.bin", O_RDONLY);
    read(fin, unifont, FNT_A);
    close(fin);

    char s[17], c = '*';
    int i, j, k;

    unsigned char* font = unifont + 0x4433 * 32;

    char *p, d /* data */;
    if (ishalf(font)) {
        for (i = 0; i < FNT_H; i += 1) {

            printf("%02x\t", font[i]);
            for (j = 0; j < 16; j++) {
                s[j] = ' ';
            }
            s[16] = 0;

            p = s;
            d = font[i];
            if ((d & 0x80) != 0) {
                p[0] = c;
            }
            if ((d & 0x40) != 0) {
                p[1] = c;
            }
            if ((d & 0x20) != 0) {
                p[2] = c;
            }
            if ((d & 0x10) != 0) {
                p[3] = c;
            }
            if ((d & 0x08) != 0) {
                p[4] = c;
            }
            if ((d & 0x04) != 0) {
                p[5] = c;
            }
            if ((d & 0x02) != 0) {
                p[6] = c;
            }
            if ((d & 0x01) != 0) {
                p[7] = c;
            }

            printf("%s\n", p);
        }
    }
    else {
        for (i = 0; i < FNT_S; i += 2) {

            printf("%02x %02x\t", font[i], font[i + 1]);
            for (j = 0; j < 16; j++) {
                s[j] = ' ';
            }
            s[16] = 0;

            p = s;
            d = font[i];
            if ((d & 0x80) != 0) {
                p[0] = c;
            }
            if ((d & 0x40) != 0) {
                p[1] = c;
            }
            if ((d & 0x20) != 0) {
                p[2] = c;
            }
            if ((d & 0x10) != 0) {
                p[3] = c;
            }
            if ((d & 0x08) != 0) {
                p[4] = c;
            }
            if ((d & 0x04) != 0) {
                p[5] = c;
            }
            if ((d & 0x02) != 0) {
                p[6] = c;
            }
            if ((d & 0x01) != 0) {
                p[7] = c;
            }
            d = font[i + 1];
            if ((d & 0x80) != 0) {
                p[8] = c;
            }
            if ((d & 0x40) != 0) {
                p[9] = c;
            }
            if ((d & 0x20) != 0) {
                p[10] = c;
            }
            if ((d & 0x10) != 0) {
                p[11] = c;
            }
            if ((d & 0x08) != 0) {
                p[12] = c;
            }
            if ((d & 0x04) != 0) {
                p[13] = c;
            }
            if ((d & 0x02) != 0) {
                p[14] = c;
            }
            if ((d & 0x01) != 0) {
                p[15] = c;
            }

            printf("%s\n", p);
        }
    }

    return 0;
}
