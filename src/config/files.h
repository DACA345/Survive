#pragma once
#include <QDir>

#define _PATH_JOIN(path1, path2) QDir::cleanPath(path1 + QDir::separator() + path2)

#define DIRECTORY_PATH QDir(QDir::current().filePath("..")).canonicalPath()

#define LEVEL_FOLDER _PATH_JOIN(DIRECTORY_PATH, "levels")
#define TEXTURE_FOLDER _PATH_JOIN(DIRECTORY_PATH, "textures")
#define SAVE_FOLDER _PATH_JOIN(DIRECTORY_PATH, "saves")

#define LEVEL_FILE(path) _PATH_JOIN(LEVEL_FOLDER, QDir::cleanPath(path))
#define TEXTURE_FILE(path) _PATH_JOIN(TEXTURE_FOLDER, QDir::cleanPath(path))
#define SAVE_FILE(path) _PATH_JOIN(SAVE_FOLDER, QDir::cleanPath(path))