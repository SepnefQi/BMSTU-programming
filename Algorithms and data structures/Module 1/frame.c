#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage: frame <height> <width> <text>");
        return 0;
    }
    int height = strtol(argv[1], NULL, 10);
    int width = strtol(argv[2], NULL, 10);
    char *text = argv[3];
    int len_text = strlen(text);
    if (width - len_text - 2 < 0 || height - 3 < 0) {
        printf("Error");
        return 0;
    }
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (i==0 || j==0 || i==height-1 || j==width-1) printf("*");
            else if (i==(height-1)/2 && (j >= ((width-1)/2 - len_text/2) && j <= ((width-1)/2 + len_text/2))) {
                printf("%c", text[j - ((width-1)/2 - len_text/2)]);
            }
            else printf(" ");
        }
        printf("\n");
    }
    return 0;
}