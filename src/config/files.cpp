#include "files.h"

namespace Files
{
    QString textureFilePath(const QString& path)
    {
        static const QDir textureFolder = QDir(TEXTURE_FOLDER);
        return textureFolder.filePath(path);
    }
}