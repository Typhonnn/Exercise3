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

Face* createFace(char *line) {
	Face *face = malloc(sizeof(Face));
	if (face == NULL) {
		printf("Failed To Allocate Memory For New Face! ABORTING!");
		return NULL;
	}
	face->size = 0;
	char *delimiters = "f ";
	char *splitLine = strtok(line, delimiters);
	while (splitLine != NULL) {
		face->vertex = realloc(face->vertex, (face->size + 1) * sizeof(int));
		face->vertex[face->size++] = (int) strtol(splitLine, NULL, 10);
		splitLine = strtok(NULL, delimiters);
	}
	return face;
}
