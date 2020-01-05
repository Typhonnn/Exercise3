#pragma once

typedef struct
{
    int numOfObjects;

} Scene;

enum FileType
{
    TextFormat,
    BinaryFormat
};

Scene* createScene(char* fileName, ...);

void saveScene(Scene* scene, char* fileName, enum FileType type);

Scene* loadScene(char* fileName, enum FileType type);

void freeScene(Scene* scene);