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

Face createFace(char *line) {
	Face face;
	int *vertexes = malloc(sizeof(int));
	if (vertexes == NULL) {
		printf("Failed To Allocate Memory For New vertexes! ABORTING!");
		exit(1);
	}
	int size = 0;
	int *oldVertexes = vertexes;
	char *delimiters = "f ";
	char *splitLine = strtok(line, delimiters);
	while (splitLine != NULL) {
		vertexes = realloc(oldVertexes, (size + 1) * sizeof(int));
		if (vertexes == NULL) {
			printf("Failed To Reallocate Memory For New vertexes! ABORTING!");
			exit(1);
		}
		vertexes[size++] = strtol(splitLine, NULL, 10);
		splitLine = strtok(NULL, delimiters);
		oldVertexes = vertexes;
	}
	face.size = size;
	face.vertex = vertexes;
	return face;
}
