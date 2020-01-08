#pragma once
#include <stdio.h>

typedef struct {
	float x;	// Coordinates of Vertex
	float y;
	float z;
} Vertex;

void saveVertex(Vertex *vertex, FILE *file);

void createVertex(char *line, Vertex *vertex);
