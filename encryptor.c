#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt_decrypt_file(const char* input_filename, const char* output_filename, const char* password) {
    FILE* in = fopen(input_filename, "rb");
    if (!in) {
        perror("Failed to open input file");
        exit(1);
    }

    FILE* out = fopen(output_filename, "wb");
    if (!out) {
        perror("Failed to create output file");
        fclose(in);
        exit(1);
    }

    int pass_len = strlen(password);
    int i = 0;
    unsigned char byte;

    while (fread(&byte, 1, 1, in)) {
        byte ^= password[i % pass_len];
        fwrite(&byte, 1, 1, out);
        i++;
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char* argv[])
{
    if (argc != 5) 
    {
        printf("Usage: %s [encrypt|decrypt] <input_file> <output_file> <password>\n", argv[0]);
        return 1;
    }

    const char* mode = argv[1];
    const char* input_file = argv[2];
    const char* output_file = argv[3];
    const char* password = argv[4];

    if (strcmp(mode, "encrypt") == 0 || strcmp(mode, "decrypt") == 0) {
        encrypt_decrypt_file(input_file, output_file, password);
        printf("Done: %s -> %s\n", input_file, output_file);
    }
    else {
        printf("Invalid mode. Use 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    return 0;
}
