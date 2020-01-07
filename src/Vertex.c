#include "Vertex.h"
#include <stdio.h>
#include <stdlib.h>

void saveVertex(Vertex *vertex, FILE *file) {
	fprintf(file, "v  %f  %f  %f \n", vertex->x, vertex->y, vertex->z);
}

Vertex createVertex(char *line) {
	Vertex vertex;
	sscanf(line, " %*c %f %f %f ", &vertex.x, &vertex.y, &vertex.z);
	return vertex;
}
