#include "Face.h"
#include <string.h>
#include <stdlib.h>

void saveFace(Face *face, FILE *file) {
	int i;
	fprintf(file, "f ");
	for (i = 0; i < face->size; ++i) {
		fprintf(file, "%d ", face->vertex[i]);
	}
	fprintf(file, "\n");
}

void createFace(char *line, Face *face) {
	int *vertexes = face->vertex;
	face->size = 0;
	char *delimiters = "f ";
	char *splitLine = strtok(line, delimiters);
	while (splitLine != NULL) {
		vertexes = realloc(face->vertex, (face->size + 1) * sizeof(int));
		if (vertexes == NULL) {
			printf("Failed To Reallocate Memory For New vertexes! ABORTING!");
			return;
		}
		vertexes[face->size++] = strtol(splitLine, NULL, 10);
		splitLine = strtok(NULL, delimiters);
	}
}
