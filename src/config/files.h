#pragma once
#include <QDir>

#define LEVEL_FOLDER DIRECTORY_PATH "/levels"
#define TEXTURE_FOLDER DIRECTORY_PATH "/textures"
#define SAVE_FOLDER DIRECTORY_PATH "/saves"

#define LEVEL_FILE(path) LEVEL_FOLDER "/" path
#define TEXTURE_FILE(path) TEXTURE_FOLDER "/" path
#define SAVE_FILE(path) SAVE_FOLDER "/" path

namespace Files
{
    QString textureFilePath(const QString& path);
}