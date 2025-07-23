#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC_HEADER "ORENC"
#define MAGIC_LEN 5
#define KEY_LEN 32

void stretch_password(const char* password, unsigned char* key_out) {
    size_t pass_len = strlen(password);
    for (int i = 0; i < KEY_LEN; i++) {
        key_out[i] = password[i % pass_len] ^ (i * 31);
    }
}

int encrypt_decrypt_file(const char* input_filename, const char* output_filename, const char* password, const char* mode) {
    FILE* in = fopen(input_filename, "rb");
    if (!in) {
        fprintf(stderr, "Error: Cannot open input file %s\n", input_filename);
        return 1;
    }

    FILE* out = fopen(output_filename, "wb");
    if (!out) {
        fprintf(stderr, "Error: Cannot create output file %s\n", output_filename);
        fclose(in);
        return 1;
    }

    unsigned char key[KEY_LEN];
    stretch_password(password, key);

    int i = 0;
    unsigned char byte;

    if (strcmp(mode, "encrypt") == 0) {
        fwrite(MAGIC_HEADER, 1, MAGIC_LEN, out);
    } else if (strcmp(mode, "decrypt") == 0) {
        char header[MAGIC_LEN];
        fread(header, 1, MAGIC_LEN, in);
        if (memcmp(header, MAGIC_HEADER, MAGIC_LEN) != 0) {
            fprintf(stderr, "Error: Invalid or unrecognized file format\n");
            fclose(in);
            fclose(out);
            remove(output_filename);
            return 1;
        }
    }

    while (fread(&byte, 1, 1, in) == 1) {
        byte ^= key[i % KEY_LEN];
        fwrite(&byte, 1, 1, out);
        i++;
    }

    fclose(in);
    fclose(out);
    return 0;
}

void print_usage(const char* prog_name) {
    printf("Usage: %s [encrypt|decrypt] <file1> [file2 ...] <password>\n", prog_name);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        print_usage(argv[0]);
        return 1;
    }

    const char* mode = argv[1];
    const char* password = argv[argc - 1];

    if (strcmp(mode, "encrypt") != 0 && strcmp(mode, "decrypt") != 0) {
        fprintf(stderr, "Error: Mode must be 'encrypt' or 'decrypt'\n");
        return 1;
    }

    for (int i = 2; i < argc - 1; i++) {
        const char* input_file = argv[i];
        char output_file[512];
        snprintf(output_file, sizeof(output_file), "%s.%s", input_file, strcmp(mode, "encrypt") == 0 ? "enc" : "dec");

        printf("[%s] %s -> %s\n", mode, input_file, output_file);

        if (encrypt_decrypt_file(input_file, output_file, password, mode) != 0) {
            fprintf(stderr, "Failed to process file: %s\n", input_file);
        } else {
            printf("Done: %s\n", output_file);
        }
    }

    return 0;
}

