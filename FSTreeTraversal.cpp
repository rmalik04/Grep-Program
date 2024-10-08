/*


*/


#include "FSTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;
void filePath(DirNode *dir, vector<DirNode*> &path);
string tracker(stringstream ss, DirNode *directory);

int main (int argc, char *argv[]) {
    if (argc != 2) {
        cout << "not enough files entered" << endl;
        return 0;
    }
    string directoryName = argv[1];
    FSTree directory(directoryName);

    vector<DirNode*> path;
    filePath(directory.getRoot(), path);
    return 0;
}

void filePath(DirNode *dir, vector<DirNode*> &path) {
    if (dir == nullptr) {
        return;
    }
    else {
        path.push_back(dir);
    }
    if (dir->hasSubDir()) {
        for (int i = 0; i < dir->numSubDirs(); i++) {
            filePath(dir->getSubDir(i), path);
        }
    }
    if (dir->hasFiles()) {
        for (int i = 0; i < dir->numFiles(); i++) {
            cout << path[0]->getName();
            for (int j = 1; j < int (path.size()); j++) {
                cout << "/" << path[j]->getName();
            }
            cout << "/" << dir->getFile(i) << endl;
        }
    }
    path.pop_back();
    
}

