#ifndef GLOBAL_H
#define GLOBAL_H
#include <QSemaphore>

const int BufferSize = 1024;
char g_szReadBuffer[BufferSize];

QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;

#endif // GLOBAL_H
