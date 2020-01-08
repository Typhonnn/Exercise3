#include "Scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

Scene* createScene(char *fileName, ...) {
	Scene *scene = malloc(sizeof(Scene));
	if (scene == NULL) {
		printf("Failed To Allocate Memory For New Scene! ABORTING!");
		return NULL;
	}
	scene->header = malloc(sizeof(struct ObjectList));
	if (scene->header == NULL) {
		printf("Failed To Allocate Memory For New Object List! ABORTING!");
		return NULL;
	}
	ObjectList *objList = scene->header;
	ObjectList *preObjList = objList;
	va_list allFile;
	va_start(allFile, fileName);
	char *currentFile = fileName;
	while (currentFile != NULL) {
		objList->object = createObject(currentFile);
		objList->next = malloc(sizeof(struct ObjectList));
		if (objList->next == NULL) {
			printf("Failed To Allocate Memory For New Object List! ABORTING!");
			return NULL;
		}
		objList = objList->next;
		currentFile = va_arg(allFile, char*);
	}
	preObjList->next = NULL;
	return scene;
}

void perform(Scene *scene, void (*func)(Object*, void*), char *type,
		char *string) {
	ObjectList *objList = scene->header;
	while (objList != NULL) {
		if (strcmp(type, "INT") == 0) {
			int *sum = calloc(1, sizeof(int));
			func(objList->object, sum);
			printf("%s %d\n", string, *sum);
		} else if (strcmp(type, "DOUBLE") == 0) {
			double *sum = calloc(1, sizeof(double));
			func(objList->object, sum);
			printf("%s %lf\n", string, *sum);
		} else {
			printf("%s is not a valid type", type);
		}
		objList = objList->next;
	}
}

Scene* loadScene(char *fileName, enum FileType type) {
	FILE *file;
	if (type == TextFormat) {
		file = fopen(fileName, "r");
	} else if (type == BinaryFormat) {
		file = fopen(fileName, "rb");
	}
	if (file == NULL) {
		printf("File Open Failed! ABORTING!");
		return NULL;
	}
	Scene *scene = malloc(sizeof(Scene));
	if (scene == NULL) {
		printf("Failed To Allocate Memory For New Scene! ABORTING!");
		return NULL;
	}
	scene->header = malloc(sizeof(struct ObjectList));
	if (scene->header == NULL) {
		printf(
				"Failed To Allocate Memory For New Scene Object List! ABORTING!");
		return NULL;
	}
	ObjectList *objList = scene->header;
	while (!feof(file)) {
		objList->object = malloc(sizeof(Object));
		if (objList->object == NULL) {
			printf("Failed To Allocate Memory For New Object! ABORTING!");
			return NULL;
		}
		loadObject(file, objList->object);
		objList->next = malloc(sizeof(struct ObjectList));
		if (objList->next == NULL) {
			printf("Failed To Allocate Memory For New Object List! ABORTING!");
			return NULL;
		}
		objList = objList->next;
	}
	fclose(file);
	return scene;
}

void saveScene(Scene *scene, char *fileName, enum FileType type) {
	FILE *file;
	if (type == TextFormat) {
		file = fopen(fileName, "w");
	} else if (type == BinaryFormat) {
		file = fopen(fileName, "wb");
	}
	if (file == NULL) {
		printf("File Open Failed! ABORTING!");
		return;
	}
	fprintf(file, "# Tal Balelty Generated Scene File\n");
	ObjectList *objList = scene->header;
	while (objList != NULL) {
		saveObject(objList->object, file);
		objList = objList->next;
	}
	fclose(file);
}

void freeScene(Scene *scene) {
	int i, j;
	while (scene->header != NULL) {
		for (i = 0; i < scene->header->object->numberOfVertexes; ++i) {
			free(scene->header->object->vertexes);
		}
		for (i = 0; i < scene->header->object->numberOfFaces; ++i) {
			for (j = 0; j < scene->header->object->faces[i].size; ++j) {
				free(scene->header->object->faces[i].vertex);
			}
			free(scene->header->object->faces);
		}
		ObjectList *objList = scene->header;
		scene->header = scene->header->next;
		free(objList);
	}
	free(scene);
}
