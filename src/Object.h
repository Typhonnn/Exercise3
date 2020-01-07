#pragma once
#include <stdio.h>
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

void printFaces(Object *ptr, void *numberOfTriangularFaces);

void printVertexes(Object *ptr, void *numberOfVertexes);

void getTotalArea(Object *ptr, void *totalAreaOfTriangularFaces);

void saveObject(Object *object, FILE *file);

Object* loadObject(FILE *file);

void transformObject(char *originalObjectFileName, char *deformedObjectFileName);
