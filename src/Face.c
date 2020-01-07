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
	int *vertexes = malloc(sizeof(int));
	if (vertexes == NULL) {
		printf("Failed To Allocate Memory For New vertexes! ABORTING!");
		return NULL;
	}
	int *oldVertexes = vertexes;
	face->size = 0;
	char *delimiters = "f ";
	char *splitLine = strtok(line, delimiters);
	while (splitLine != NULL) {
		vertexes = realloc(oldVertexes, (face->size + 1) * sizeof(int));
		if (vertexes == NULL) {
			printf("Failed To Reallocate Memory For New vertexes! ABORTING!");
			return NULL;
		}
		vertexes[face->size++] = (int) strtol(splitLine, NULL, 10);
		splitLine = strtok(NULL, delimiters);
		oldVertexes = vertexes;
	}
	face->vertex = vertexes;
	return face;
}
