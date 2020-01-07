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
	Vertex *vertexes = malloc(sizeof(Vertex));
	if (vertexes == NULL) {
		printf("Failed To Allocate Memory For New Vertexes! ABORTING!");
		return NULL;
	}
	Face *faces = malloc(sizeof(Face));
	if (faces == NULL) {
		printf("Failed To Allocate Memory For New Faces! ABORTING!");
		return NULL;
	}
	char *line = malloc(sizeof(char));
	if (line == NULL) {
		printf("Failed To Allocate Memory For New Line! ABORTING!");
		return NULL;
	}
	object->numberOfFaces = 0;
	object->numberOfVertexes = 0;
	size_t lineSize = 32;
	size_t bytesRead;
	bytesRead = getline(&line, &lineSize, file);
	while (bytesRead != -1) {
		if (line[0] == 'v' && line[1] == ' ') {
			vertexes = realloc(vertexes,
					(object->numberOfVertexes + 1) * sizeof(Vertex));
			if (vertexes == NULL) {
				printf(
						"Failed To Reallocate Memory For New Vertexes! ABORTING!");
				return NULL;
			}
			vertexes[object->numberOfVertexes++] = *createVertex(line);
		} else if (line[0] == 'f' && line[1] == ' ') {
			faces = realloc(faces, (object->numberOfFaces + 1) * sizeof(Face));
			if (faces == NULL) {
				printf("Failed To Reallocate Memory For New Faces! ABORTING!");
				return NULL;
			}
			faces[object->numberOfFaces++] = *createFace(line);
		}
		bytesRead = getline(&line, &lineSize, file);
	}
	object->vertexes = vertexes;
	object->faces = faces;
	free(line);
	fclose(file);
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
	return loadObject(file);
}
void transformObject(char *originalObjectFileName, char *deformedObjectFileName) {
	float x, y, z;
	FILE *orgFile = fopen(originalObjectFileName, "r");
	if (orgFile == NULL) {
		printf("Failed Opening File %s! Aborting!", originalObjectFileName);
		return;
	}
	FILE *defoFile = fopen(deformedObjectFileName, "w");
	if (defoFile == NULL) {
		printf("Failed Opening File %s! Aborting!", deformedObjectFileName);
		return;
	}
	char *line = malloc(sizeof(char));
	size_t lineSize = 32;
	size_t bytesRead;
	bytesRead = getline(&line, &lineSize, orgFile);
	while (bytesRead != -1) {
		if (line[0] == 'v' && line[1] == ' ') {
			sscanf(line, "%*c %f %f %f", &x, &y, &z);
			x = 0.3 * x;
			fprintf(defoFile, "v %f %f %f\n", x, y, z);
		} else {
			fprintf(defoFile, "%s", line);
		}
		bytesRead = getline(&line, &lineSize, orgFile);
	}
	free(line);
	fclose(orgFile);
	fclose(defoFile);
}

