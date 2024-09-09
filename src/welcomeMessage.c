#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define FRAME_DELAY 200000 
#define MAX_LINE_LENGTH 256 //Up to change, maybe not necessary

char* readFile(console_state_t state){
    FILE *file;
    int in_frame = 0; // Variable para saber si estamos dentro de un frame

    // Abre el archivo en modo lectura
    if (state == "CONSOLE_WELCOME"){
        file = fopen("welcome.txt", "r");
    } else if (state == "CONSOLE_EXIT"){
        file = fopen("exit.txt", "r");
    }
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        exit(_STATUS_ERR);
    }
    else{
        printMessage(file);
    }
    return "_STATUS_OK";
}
void printFile(FILE *file){
// Lee y muestra los frames
    char line[MAX_LINE_LENGTH];
    bool in_frame = false;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (strcmp(line, "START\n") == 0) {
            in_frame = true; // Comenzamos un nuevo frame
            system("clear"); // Limpiar pantalla
        } else if (strcmp(line, "END\n") == 0) {
            in_frame = false; // Terminamos el frame actual
            usleep(FRAME_DELAY); // Esperamos entre frames
        } else if (in_frame) {
            // Si estamos dentro de un frame, imprimimos las líneas
            printf("%s", line);
        }
    }
    // Cierra el archivo
    fclose(file);
}
