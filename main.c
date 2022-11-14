
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* open_file(const char* filename) {
    FILE* file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    char* result = malloc(file_size + 1);
    fread(result, file_size, 1, file_ptr);
    fclose(file_ptr);

    return result;
}

static void save_to_file(const char* file, const char* filename) {
    FILE* file_ptr = fopen(filename, "w");
    fprintf(file_ptr, "%s\n", file);
    fclose(file_ptr);
}

static char* encrypt_file(const char* file, const char* key) {
    char* buffer = open_file(file);
    char* result = malloc(strlen(buffer) + 1);
    for (int i = 0; i < strlen(buffer); ++i) {
        result[i] = buffer[i] ^ key[i % strlen(key)];
    }
    free(buffer);
    return result;
}

static char* decrypt_file(const char* file, const char* key) {
    return encrypt_file(file, key);
}

int main(int argc, char** argv) {
    const char* usage = "Usage: hw5 <encrypt/decrypt> <input_file> <output_file> <key>\n";
    if (argc != 5) {
        printf(usage);
        exit(1);
    }

    if (strcmp(argv[1], "encrypt") == 0) {
        char* encrypted = encrypt_file(argv[2], argv[4]);
        save_to_file(encrypted, argv[3]);
    } else if (strcmp(argv[1], "decrypt") == 0) {
        char* decrypted = decrypt_file(argv[2], argv[4]);
        save_to_file(decrypted, argv[3]);
    } else {
        printf(usage);
        exit(1);
    }

    return 0;
}
