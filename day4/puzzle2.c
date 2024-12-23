#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#define LINE_LENGHT 140

off_t length = 0;

void print_file_with_highlight(int ul, int ur, int dl, int dr, int fd) {
    struct stat st;
    fstat(fd, &st);
    off_t length = st.st_size;

    char c;
    for (int i = 0; i < length; i++) {
        pread(fd, &c, 1, i);

        // Resaltar el valor de start_n y target en rojo
        if (i == ul || i == ur || i == dl || i == dr) {
            printf("\033[31m%c\033[0m", c);  // Código ANSI para rojo
        } else {
            printf("%c", c);
        }
    }

    printf("\n");
}

int check_line(int start_n, int fd) {
    char c;
    int target_ul = start_n - LINE_LENGHT - 2;
    int target_ur = start_n - LINE_LENGHT;
    int target_dl = start_n + LINE_LENGHT;
    int target_dr = start_n + LINE_LENGHT + 2;

    if (target_ul < 0 || target_ul > length) return 0;
    if (target_ur < 0 || target_ur > length) return 0;
    if (target_dl < 0 || target_dl > length) return 0;
    if (target_dr < 0 || target_dr > length) return 0;

    char char_ul;
    char char_ur;
    char char_dl;
    char char_dr;

    pread(fd, &char_ul, 1, target_ul);
    pread(fd, &char_ur, 1, target_ur);
    pread(fd, &char_dl, 1, target_dl);
    pread(fd, &char_dr, 1, target_dr);

    // diagonal 1
    if (((char_ul == 'M' && char_dr == 'S') ||
         (char_ul == 'S' && char_dr == 'M')) &&
        ((char_dl == 'S' && char_ur == 'M') ||
         (char_dl == 'M' && char_ur == 'S'))) {
        return 1;
    }

    return 0;
}

// XMAS
int main() {
    int fd = open("./input1.txt", O_RDONLY);

    if (fd < 0) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Obtener el tamaño del archivo usando fstat
    struct stat st;
    fstat(fd, &st);
    length = st.st_size;

    char c;
    int count = 0;

    int word_count = 0;

    while (count < length) {
        // Leer un byte en la posición count
        pread(fd, &c, 1, count);
        if (c == 'A') {
            word_count += check_line(count, fd);
        }

        count++;
    }

    printf("%i\n", word_count);

    close(fd);
    return 0;
}
