#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#define LINE_LENGHT 140 

off_t length = 0;

const char word[4] = {'X', 'M', 'A', 'S'};

int check_line(int iteration, int start_n, int math, int fd) {
    char c;
    int target = start_n + (math * iteration);
    if (target < 0 || target > length) return 0;

    if (pread(fd, &c, 1, target) == -1) return 0;

    if (c != word[iteration]) return 0;

    if (iteration == 3) {
        return 1;
    }

    return check_line(iteration + 1, start_n, math, fd);
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
        if (c == 'X') {
            word_count += check_line(1, count, -1 * (LINE_LENGHT + 2), fd); // arriba izquierda
            word_count += check_line(1, count, -1 * (LINE_LENGHT + 1), fd); // arriba
            word_count += check_line(1, count, -1 * LINE_LENGHT, fd); // arriba derecha
            word_count += check_line(1, count, -1, fd); // izquierda
            word_count += check_line(1, count, 1, fd); // derecha
            word_count += check_line(1, count, LINE_LENGHT, fd); // abajo izquierda
            word_count += check_line(1, count, LINE_LENGHT + 1, fd);  // abajo
            word_count += check_line(1, count, LINE_LENGHT + 2, fd); // abajo derecha
        }

        count++;
    }

    printf("%i\n", word_count);

    close(fd);
    return 0;
}
