#include "Scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

Scene* createScene(char *fileName, ...) {
	Scene *scene = malloc(sizeof(Scene));
	if (scene == NULL) {
		printf("Failed To Allocate Memory For New Scene! ABORTING!");
		return NULL;
	}
	ObjectList *objList = malloc(sizeof(ObjectList));
	scene->header = objList;
	va_list allFile;
	va_start(allFile, fileName);
	char *currentFile = fileName;
	if (currentFile != NULL) {
		objList->object = createObject(currentFile);
		objList->next = NULL;
		int counter = 0; // REMEMBER TO DELETE!
		while (currentFile != NULL && counter < 4) {
			objList = objList->next;
			objList->object = createObject(currentFile);
			objList->next = NULL;
			currentFile = va_arg(allFile, char*);
			counter++;
		}
	}
	return scene;
}

void saveScene(Scene *scene, char *fileName, enum FileType type) {
	//TODO need to continue the function.
}

Scene* loadScene(char *fileName, enum FileType type) {
	Scene *scene = malloc(sizeof(Scene));
	//TODO need to continue the function.
	return scene;
}

void freeScene(Scene *scene) {
	//TODO need to continue the function.
}
