#include "Vertex.h"
#include <stdio.h>

void saveVertex(Vertex *vertex, FILE *file) {
	fprintf(file, "v %f %f %f\n", vertex->x, vertex->y, vertex->z);
}

Vertex* createVertex(char *line) {
	Vertex *vertex = malloc(sizeof(Vertex));
	if (vertex == NULL) {
		printf("Failed To Allocate Memory For New Vertex! ABORTING!");
		return NULL;
	}
	sscanf(line, "%*c %f %f %f", &vertex->x, &vertex->y, &vertex->z);
	return vertex;
}
