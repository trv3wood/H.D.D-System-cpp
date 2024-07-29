#include <QApplication>
#include <QDebug>
#include <QObject>
#include <cstddef>

#include "mainwindow.h"
struct MemoryManager {
    size_t totalAllocated = 0;
    size_t totalFreed = 0;
} memoryManager;

void* operator new(size_t size) {
    void* p = malloc(size);
    memoryManager.totalAllocated += size;
    qDebug() << "allocated at " << p;
    qDebug() << "total allocated " << memoryManager.totalAllocated << " bytes. Using "
             << memoryManager.totalAllocated - memoryManager.totalFreed
             << " bytes";
    // qDebug() << "Allocated " << size << " bytes";
    return p;
}

void operator delete(void* p, size_t size) noexcept {
    free(p);
    qDebug() << "Freed at " << p;
    memoryManager.totalFreed += size;
    qDebug() << "total freed " << memoryManager.totalFreed << " bytes. Using "
             << memoryManager.totalAllocated - memoryManager.totalFreed
             << " bytes";
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
