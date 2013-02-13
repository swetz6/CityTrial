


#include "GameBuilding.h"
#include "GameRamp.h"


using glm::vec3;
using glm::mat4;

#include <vector>
using std::vector;

#include <stdio.h>



void  fprint3f(vec3 v, FILE *file) {
    fprintf(file, "%f %f %f\n", v.x, v.y, v.z);
}

void  read3f(vec3 &v, FILE *file) {
    fscanf(file, "%f %f %f ", &v.x, &v.y, &v.z);
}


void readMat4(mat4 &mat, FILE *file) {
    float tmp;
    for (int i=0; i<4; i++)
    for (int j=0; j<4; j++) {
        fscanf(file, "%f ", &tmp);
        mat[i][j] = tmp;
    };
}

bool loadMap(const char* filename, vector<GameDrawableObject* > &map) {

    FILE * file = fopen(filename, "r");

    if (NULL == file) {
        fprintf(stderr, "Couldn't open %s for reading the map\n", filename);
        return false;
    }

    int num_objs = 0;

    fscanf(file, "%d ", &num_objs); 

    GameDrawableObject *read_object;

    char name[100];
    int matnum;
    vec3 p, s, r;

    while (num_objs--) {
        fscanf(file, "%s %d\n", name, &matnum);

        read3f(p, file);
        printf("read p:\n");
        fprint3f(p, stdout);

        read3f(s, file);
        printf("read s:\n");
        fprint3f(s, stdout);

        read3f(r, file);
        printf("read r:\n");
        fprint3f(r, stdout);

        // TODO - put this info in a std::map
        if (strcmp(name, "building") == 0) {
           read_object = new GameBuilding();
        } else if (strcmp(name, "ramp") == 0) {
           read_object = new GameRamp();
        } else {
            // unknown
            read_object = new GameBuilding();
        }

        read_object->setPosition(p);
        read_object->setScale(s);
        read_object->setRotation(r);
        
        map.push_back(read_object);
    }



    fclose(file);
    
    return true;

}
