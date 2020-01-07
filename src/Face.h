#pragma once
#include <stdio.h>

typedef struct {
	int size;		// Number of vertexes of the face
	int *vertex;	// Array of Ids of the vertexes
} Face;

void saveFace(Face *face, FILE *file);

Face createFace(char *line);
