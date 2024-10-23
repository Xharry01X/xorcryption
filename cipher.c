#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fi, *fo;
    char *cp;
    int c;

    // Check if we have the correct number of arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <key> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Check if key is not empty
    if ((cp = argv[1]) && *cp != '\0') {
        // Try to open input file
        if ((fi = fopen(argv[2], "rb")) == NULL) {
            fprintf(stderr, "Error: Cannot open input file '%s'\n", argv[2]);
            return 1;
        }

        // Try to open output file
        if ((fo = fopen(argv[3], "wb")) == NULL) {
            fprintf(stderr, "Error: Cannot open output file '%s'\n", argv[3]);
            fclose(fi);
            return 1;
        }

        // Process the file
        while ((c = getc(fi)) != EOF) {
            // Reset key pointer if we reached the end of the key
            if (!*cp) {
                cp = argv[1];
            }
            // XOR the current byte with the current key byte
            c ^= *(cp++);
            putc(c, fo);
        }

        // Close files
        fclose(fo);
        fclose(fi);
        return 0;
    }

    fprintf(stderr, "Error: Key cannot be empty\n");
    return 1;
}