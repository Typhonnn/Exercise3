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

void createFace(Object *obj, char *line);

void createVertex(Object *obj, char *line);

void printFaces(Object *ptr, void *numberOfTriangularFaces);

void printVertexes(Object *ptr, void *numberOfVertexes);

void getTotalArea(Object *ptr, void *totalAreaOfTriangularFaces);
