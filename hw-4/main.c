#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("%s <входной файл> <выходной файл>\n", argv[0]);
        exit(1);
    }

    int inputStream, outputStream;
    ssize_t bytesRead, bytesWritten;
    char buf[BUF_SIZE];

    // Открываем входной файл для чтения
    if ((inputStream = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    // Открываем выходной файл для записи
    if ((outputStream = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
        perror("open");
        exit(1);
    }

    // Читаем из входного файла и записываем в выходной файл
    while ((bytesRead = read(inputStream, buf, BUF_SIZE)) > 0) {
        bytesWritten = write(outputStream, buf, bytesRead);
        
        if (bytesWritten != bytesRead) {
            perror("write");
            exit(1);
        }
    }

    // ошибка при чтении файла
    if (bytesRead == -1) {
        perror("read");
        exit(1);
    }

    // Закрываем файлы
    if (close(inputStream) == -1 || close(outputStream) == -1) {
        perror("close");
        exit(1);
    }

    printf("Файл скопирован, все ок\n");
    return 0;
}