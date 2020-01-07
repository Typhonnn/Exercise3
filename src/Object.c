#include "Object.h"

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define END_OBJECT "endObject"

Object* loadObject(FILE *file) {
	Object *object = malloc(sizeof(Object));
	if (object == NULL) {
		printf("Failed To Allocate Memory For New Object! ABORTING!");
		return NULL;
	}
	char *line = malloc(sizeof(char));
	size_t lineSize = 32;
	size_t bytesRead;
	bytesRead = getline(&line, &lineSize, file);
	while (bytesRead != -1 || strcmp(line, END_OBJECT) != 0) {
		if (line[0] == 'v' && line[1] == ' ') {
			object->vertexes = realloc(object->vertexes,
					(object->numberOfVertexes + 1) * sizeof(Vertex));
			object->vertexes[object->numberOfVertexes++] = *createVertex(line);
		} else if (line[0] == 'f' && line[1] == ' ') {
			object->faces = realloc(object->faces,
					(object->numberOfFaces + 1) * sizeof(Face));
			object->faces[object->numberOfFaces++] = *createFace(line);
		}
		bytesRead = getline(&line, &lineSize, file);
	}
	free(line);
	return object;
}

void saveObject(Object *object, FILE *file) {
	int i;
	int numOfVertexes = object->numberOfVertexes;
	fprintf(file, "\n# Number of Vertexes %d\n", numOfVertexes);
	for (i = 0; i < numOfVertexes; ++i) {
		saveVertex(&object->vertexes[i], file);
	}
	int numOfFaces = object->numberOfFaces;
	fprintf(file, "\n# Number of Faces %d\n", numOfFaces);
	for (i = 0; i < numOfFaces; ++i) {
		saveFace(&object->faces[i], file);
	}
	fprintf(file, END_OBJECT);
}

void getTotalArea(Object *ptr, void *totalAreaOfTriangularFaces) {
	int i;
	double s, a, b, c;
	*(double*) totalAreaOfTriangularFaces = 0;
	for (i = 0; i < ptr->numberOfFaces; ++i) {
		if (ptr->faces[i].size == 3) {
			a = pow(2, 2);
			a = ptr->vertexes[ptr->faces[i].vertex[0] - 1].x;
			a =
					pow(
							pow(
									(ptr->vertexes[ptr->faces[i].vertex[0] - 1].x
											- ptr->vertexes[ptr->faces[i].vertex[1]
													- 1].x), 2)
									+ pow(
											(ptr->vertexes[ptr->faces[i].vertex[0]
													- 1].y
													- ptr->vertexes[ptr->faces[i].vertex[1]
															- 1].y), 2)
									+ pow(
											(ptr->vertexes[ptr->faces[i].vertex[0]
													- 1].z
													- ptr->vertexes[ptr->faces[i].vertex[1]
															- 1].z), 2), 0.5);
			b =
					pow(
							pow(
									(ptr->vertexes[ptr->faces[i].vertex[0] - 1].x
											- ptr->vertexes[ptr->faces[i].vertex[2]
													- 1].x), 2)
									+ pow(
											(ptr->vertexes[ptr->faces[i].vertex[0]
													- 1].y
													- ptr->vertexes[ptr->faces[i].vertex[2]
															- 1].y), 2)
									+ pow(
											(ptr->vertexes[ptr->faces[i].vertex[0]
													- 1].z
													- ptr->vertexes[ptr->faces[i].vertex[2]
															- 1].z), 2), 0.5);
			c =
					pow(
							pow(
									(ptr->vertexes[ptr->faces[i].vertex[1] - 1].x
											- ptr->vertexes[ptr->faces[i].vertex[2]
													- 1].x), 2)
									+ pow(
											(ptr->vertexes[ptr->faces[i].vertex[1]
													- 1].y
													- ptr->vertexes[ptr->faces[i].vertex[2]
															- 1].y), 2)
									+ pow(
											(ptr->vertexes[ptr->faces[i].vertex[1]
													- 1].z
													- ptr->vertexes[ptr->faces[i].vertex[2]
															- 1].z), 2), 0.5);
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

Object* createObject(char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Failed Opening File %s! Aborting!", filename);
		return NULL;
	}
	Object *object = malloc(sizeof(Object));
	if (object == NULL) {
		printf("Failed To Allocate Memory For New Object! ABORTING!");
		return NULL;
	}
	object->numberOfFaces = 0;
	object->numberOfVertexes = 0;
	char *line = malloc(sizeof(char));
	size_t lineSize = 32;
	size_t bytesRead;
	bytesRead = getline(&line, &lineSize, file);
	while (bytesRead != -1) {
		if (line[0] == 'v' && line[1] == ' ') {
			object->vertexes = realloc(object->vertexes,
					(object->numberOfVertexes + 1) * sizeof(Vertex));
			object->vertexes[object->numberOfVertexes++] = *createVertex(line);
		} else if (line[0] == 'f' && line[1] == ' ') {
			object->faces = realloc(object->faces,
					(object->numberOfFaces + 1) * sizeof(Face));
			object->faces[object->numberOfFaces++] = *createFace(line);
		}
		bytesRead = getline(&line, &lineSize, file);
	}
	free(line);
	fclose(file);
	return object;
}

