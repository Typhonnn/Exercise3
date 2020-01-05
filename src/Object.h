#pragma once
#include "Face.h"
#include "Vertex.h"

typedef struct {
	// Array of all Vertexes
	int numberOfVertexes;
	Vertex *vertexes;
	// Array of all Faces
	int numberOfFaces;
	Face *faces;
} Object;

Object* createObject(char *filename);
