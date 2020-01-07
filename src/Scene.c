#include "Scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

Scene* loadScene(char *fileName, enum FileType type) {
	int counter = 0;
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
	ObjectList *objList = malloc(sizeof(ObjectList));
	if (objList == NULL) {
		printf("Failed To Allocate Memory For New Object List! ABORTING!");
		return NULL;
	}
	scene->header = objList;
	while (counter < 2) {
		objList->object = loadObject(file);
		objList->next = malloc(sizeof(ObjectList));
		if (objList->next == NULL) {
			printf("Failed To Allocate Memory For New Object List! ABORTING!");
			return NULL;
		}
		objList = objList->next;
		counter++;
	}
	return scene;
}

Scene* createScene(char *fileName, ...) {
	Scene *scene = malloc(sizeof(Scene));
	if (scene == NULL) {
		printf("Failed To Allocate Memory For New Scene! ABORTING!");
		return NULL;
	}
	ObjectList *objList = malloc(sizeof(ObjectList));
	if (objList == NULL) {
		printf("Failed To Allocate Memory For New Object List! ABORTING!");
		return NULL;
	}
	scene->header = objList;
	va_list allFile;
	va_start(allFile, fileName);
	char *currentFile = fileName;
	int counter = 0; // REMEMBER TO DELETE!
	while (currentFile != NULL && counter < 4) {
		objList->object = createObject(currentFile);
		objList->next = malloc(sizeof(ObjectList));
		if (objList->next == NULL) {
			printf("Failed To Allocate Memory For New Object List! ABORTING!");
			return NULL;
		}
		objList = objList->next;
		currentFile = va_arg(allFile, char*);
		counter++;
	}
	return scene;
}

void perform(Scene *scene, void (*func)(Object*, void*), char *type,
		char *string) {
	ObjectList *objList = scene->header;
	while (objList->object != NULL) {
		if (strcmp(type, "INT") == 0) {
			int *sum = malloc(sizeof(int));
			func(objList->object, sum);
			printf("%s %d\n", string, *sum);
			free(sum);
		} else if (strcmp(type, "DOUBLE") == 0) {
			double *sum = malloc(sizeof(double));
			func(objList->object, sum);
			printf("%s %lf\n", string, *sum);
			free(sum);
		} else if (strcmp(type, "STR") == 0) {
			printf("NO FUNCTION FOR STR");
			break;
			char *sum = malloc(sizeof(char*));
			func(objList->object, sum);
			printf("%s %s\n", string, sum);
			free(sum);
		} else if (strcmp(type, "CHAR") == 0) {
			printf("NO FUNCTION FOR CHAR");
			break;
			char *sum = malloc(sizeof(char));
			func(objList->object, sum);
			printf("%s %c\n", string, *sum);
			free(sum);
		} else {
			printf("%s is not a valid type", type);
		}
		objList = objList->next;
	}
}

void saveScene(Scene *scene, char *fileName, enum FileType type) {
	int counter = 0;
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
	while (objList != NULL && counter < 4) {
		saveObject(objList->object, file);
		objList = objList->next;
		counter++;
	}
	fclose(file);
}

void freeScene(Scene *scene) {
//TODO need to continue the function.
}
