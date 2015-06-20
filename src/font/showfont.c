#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/* 字体 */
#define FNT_H 16 /* 字体高度 */
#define FNT_W  8 /* 半角宽度 */
#define FNT_Q 16 /* 全角宽度 */
#define FNT_S 32 /* 每个字形所占字节数 */
#define FNT_A 2097152 /* 字体文件大小 0x10000 * 32 */

void putfont8(char* vram, int xsize, int x, int y, char c, unsigned char* font)
{
    int i;
    char *p, d /* data */;
    for (i = 0; i < FNT_H; i++) {
        p = vram + (y + i) * xsize + x;
        printf("%4ld: ", p - vram);
        d = font[i];
        printf("%02x\n", d);
        if ((d & 0x80) != 0) { p[0] = c; }
        if ((d & 0x40) != 0) { p[1] = c; }
        if ((d & 0x20) != 0) { p[2] = c; }
        if ((d & 0x10) != 0) { p[3] = c; }
        if ((d & 0x08) != 0) { p[4] = c; }
        if ((d & 0x04) != 0) { p[5] = c; }
        if ((d & 0x02) != 0) { p[6] = c; }
        if ((d & 0x01) != 0) { p[7] = c; }
    }
    return;
}

void putfont16(char* vram, int xsize, int x, int y, char c, unsigned char* font)
{
    int i;
    char *p;
    unsigned char d;
    for (i = 0; i < FNT_H; i++) {
        p = vram + (y + i) * xsize + x;
        printf("%4ld: ", p - vram);
        d = font[i * 2];
        printf("%02x ", d);
        if ((d & 0x80) != 0) { p[0] = c; }
        if ((d & 0x40) != 0) { p[1] = c; }
        if ((d & 0x20) != 0) { p[2] = c; }
        if ((d & 0x10) != 0) { p[3] = c; }
        if ((d & 0x08) != 0) { p[4] = c; }
        if ((d & 0x04) != 0) { p[5] = c; }
        if ((d & 0x02) != 0) { p[6] = c; }
        if ((d & 0x01) != 0) { p[7] = c; }
        d = font[i * 2 + 1];
        printf("%02x\n", d);
        if ((d & 0x80) != 0) { p[8] = c; }
        if ((d & 0x40) != 0) { p[9] = c; }
        if ((d & 0x20) != 0) { p[10] = c; }
        if ((d & 0x10) != 0) { p[11] = c; }
        if ((d & 0x08) != 0) { p[12] = c; }
        if ((d & 0x04) != 0) { p[13] = c; }
        if ((d & 0x02) != 0) { p[14] = c; }
        if ((d & 0x01) != 0) { p[15] = c; }
    }
    return;
}

int ishalf(unsigned char *font)
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

char* utf8char(const char* s, int* code)
{
    int codepoint;
    int size = 0, index = 0;
    unsigned char *utf8 = (unsigned char*)s;
    unsigned char c;

    c = utf8[index++];
    while (c) {
        if ((c & 0x80) == 0) {
            codepoint = c;
        } else if ((c & 0xe0) == 0xe0) {
            codepoint = (c & 0x1F) << 12;
            c = utf8[index++];
            codepoint |= (c & 0x3F) << 6;
            c = utf8[index++];
            codepoint |= (c & 0x3F);
        } else {
            codepoint = (c & 0x3F) << 6;
            c = utf8[index++];
            codepoint |= (c & 0x3F);
        }
        c = utf8[index++];
        *code = codepoint;
        return &utf8[index - 1];
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    unsigned char* unifont = (unsigned char*)malloc(FNT_A);
    int fin = open("unifont.bin", O_RDONLY);
    read(fin, unifont, FNT_A);
    close(fin);

    int i, j, k;

    unsigned char *font;
    static char buf[20 * 20];

    char* s = "A你好!";
    char* p = s;
    int code;
    while (p = utf8char(p, &code)) {
        font = unifont + (code * FNT_S);
        memset(buf, 0, sizeof(buf));
        if (ishalf(font)) {
            putfont8(buf, 16, 0, 0, '*', font);
        } else {
            putfont16(buf, 16, 0, 0, '*', font);
        }
        for (i = 0; i < 16; i++) {
            for (j = 0; j < 16; j++) {
                printf("%c", buf[i * 16 + j] ? '*' : ' ');
            }
            printf("\n");
        }
    }

    return 0;
}
