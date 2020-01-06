#include "Object.h"
#include "Vertex.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void getTotalArea(Object *ptr, void *totalAreaOfTriangularFaces) {
	int i;
	double s, a, b, c;
	*(double*) totalAreaOfTriangularFaces = 0;
	for (i = 0; i < ptr->numberOfFaces; ++i) {
		if (ptr->faces[i].size == 3) {
			a = pow(2,2);
			a = ptr->vertexes[ptr->faces[i].vertex[0]-1].x;
			a =	pow(pow((ptr->vertexes[ptr->faces[i].vertex[0]-1].x - ptr->vertexes[ptr->faces[i].vertex[1]-1].x),2) +
					pow((ptr->vertexes[ptr->faces[i].vertex[0]-1].y - ptr->vertexes[ptr->faces[i].vertex[1]-1].y),2) +
					pow((ptr->vertexes[ptr->faces[i].vertex[0]-1].z - ptr->vertexes[ptr->faces[i].vertex[1]-1].z),2), 0.5);
			b =	pow(pow((ptr->vertexes[ptr->faces[i].vertex[0]-1].x - ptr->vertexes[ptr->faces[i].vertex[2]-1].x),2) +
					pow((ptr->vertexes[ptr->faces[i].vertex[0]-1].y - ptr->vertexes[ptr->faces[i].vertex[2]-1].y),2) +
					pow((ptr->vertexes[ptr->faces[i].vertex[0]-1].z - ptr->vertexes[ptr->faces[i].vertex[2]-1].z),2), 0.5);
			c =	pow(pow((ptr->vertexes[ptr->faces[i].vertex[1]-1].x - ptr->vertexes[ptr->faces[i].vertex[2]-1].x),2) +
					pow((ptr->vertexes[ptr->faces[i].vertex[1]-1].y - ptr->vertexes[ptr->faces[i].vertex[2]-1].y),2) +
					pow((ptr->vertexes[ptr->faces[i].vertex[1]-1].z - ptr->vertexes[ptr->faces[i].vertex[2]-1].z),2), 0.5);
			s = (a + b + c) / 2;
			*(double*) totalAreaOfTriangularFaces += pow(
					s * (s - a) * (s - b) * (s - c), 0.5);
		}
	}
}

void printVertexes(Object *ptr, void *numberOfVertexes) {
	*(int*) numberOfVertexes = ptr->numberOfVertexes;
}

void printFaces(Object *ptr, void *numberOfTriangularFaces) {
	int i, counter = 0;
	*(int*) numberOfTriangularFaces = 0;
	for (i = 0; i < ptr->numberOfFaces; i++) {
		if (ptr->faces->size == 3) {
			counter++;
		}
	}
	*(int*) numberOfTriangularFaces = counter;
}

void createFace(Object *obj, char *line) {
	obj->faces = realloc(obj->faces, (obj->numberOfFaces + 1) * sizeof(Face));
	obj->faces[obj->numberOfFaces].size = 0;
	char *delimiters = "f ";
	char *splitLine = strtok(line, delimiters);
	while (splitLine != NULL) {
		obj->faces->vertex[obj->faces->size++] = (int) strtol(splitLine, NULL,
				10);
		strtok(NULL, delimiters);
	}
	obj->numberOfFaces++;
}

void createVertex(Object *obj, char *line) {
	obj->vertexes = realloc(obj->vertexes,
			(obj->numberOfVertexes + 1) * sizeof(Vertex));
	sscanf(line, "%*c %f %f %f", &obj->vertexes[obj->numberOfVertexes].x,
			&obj->vertexes[obj->numberOfVertexes].y,
			&obj->vertexes[obj->numberOfVertexes].z);
	obj->numberOfVertexes++;
}

Object* createObject(char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Failed Opening File %s! Aborting!", filename);
		return NULL;
	}
	Object *obj = malloc(sizeof(Object));
	if (obj == NULL) {
		printf("Failed To Allocate Memory For New Object! ABORTING!");
		return NULL;
	}
	obj->numberOfFaces = 0;
	obj->numberOfVertexes = 0;
	char *line = malloc(sizeof(char));
	size_t lineSize = 32;
	size_t bytesRead;
	bytesRead = getline(&line, &lineSize, file);
	while (bytesRead != -1) {
		if (line[0] == 'v' && line[1] == ' ') {
			createVertex(obj, line);
		} else if (line[0] == 'f' && line[1] == ' ') {
			createFace(obj, line);
		}
		bytesRead = getline(&line, &lineSize, file);
	}
	free(line);
	fclose(file);
	return obj;
}

