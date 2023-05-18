#include "../../../include/generator/box.h"

void generateXZplane(Point initialPoint, float length, int divisions, int *index, bool isVisible, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals){
    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float x = initialX;
    float z = initialZ;

    for(int i = 0; i < divisions; i++){
        x = initialX;
        z = initialZ - i*squareLength;
        
        for(int j = 0; j < divisions; j++){
            x = initialX - j*squareLength;
            
            Point p1 = Point(x, initialY, z);
            Point p2 = Point(x, initialY, z-squareLength);
            Point p3 = Point(x-squareLength, initialY, z-squareLength);
            Point p4 = Point(x-squareLength, initialY, z);
            
            vertices->push_back(p1);
            vertices->push_back(p2);
            vertices->push_back(p3);
            vertices->push_back(p4);

            Triangle t1, t2;
            if(isVisible){
                for(int k = 0; k < 4; k++)
                    normals->push_back(Point(0, 1, 0));

                t1 = Triangle(*index, *index+1, *index+2);
                t2 = Triangle(*index, *index+2, *index+3);
            }
            else {
                for(int k = 0; k < 4; k++)
                    normals->push_back(Point(0, -1, 0));

                t1 = Triangle(*index+1, *index, *index+2);
                t2 = Triangle(*index+2, *index, *index+3);
            }

            triangles->push_back(t1);
            triangles->push_back(t2);

            *index+=4;
        }
    }
}


void generateYZplane(Point initialPoint, float length, int divisions, int *index, bool isVisible, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float y = initialY;
    float z = initialZ;

    for(int i = 0; i < divisions; i++){
        z = initialZ;
        y = initialY - i*squareLength;
        
        for(int j = 0; j < divisions; j++){
            z = initialZ - j*squareLength;

            Point p1 = Point(initialX, y, z);
            Point p2 = Point(initialX, y, z-squareLength);
            Point p3 = Point(initialX, y-squareLength, z-squareLength);
            Point p4 = Point(initialX, y-squareLength, z);
            
            vertices->push_back(p1);
            vertices->push_back(p2);
            vertices->push_back(p3);
            vertices->push_back(p4);

            Triangle t1, t2;
            if(isVisible){
                for(int k = 0; k < 4; k++)
                    normals->push_back(Point(1, 0, 0));

                t1 = Triangle(*index+1, *index, *index+2);
                t2 = Triangle(*index+2, *index, *index+3);
            }
            else {
                for(int k = 0; k < 4; k++)
                    normals->push_back(Point(-1, 0, 0));

                t1 = Triangle(*index, *index+1, *index+2);
                t2 = Triangle(*index, *index+2, *index+3);
            }

            triangles->push_back(t1);
            triangles->push_back(t2);

            *index+=4;
        }
    }
}


void generateXYplane(Point initialPoint, float length, int divisions, int *index, bool isVisible, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float x = initialX;
    float y = initialY;

    for(int i = 0; i < divisions; i++){
        y = initialY;
        x = initialX + i*squareLength;
        
        for(int j = 0; j < divisions; j++){
            y = initialY + j*squareLength;

            Point p1 = Point(x, y, initialZ);
            Point p2 = Point(x, y+squareLength, initialZ);
            Point p3 = Point(x+squareLength, y+squareLength, initialZ);
            Point p4 = Point(x+squareLength, y, initialZ);
            
            vertices->push_back(p1);
            vertices->push_back(p2);
            vertices->push_back(p3);
            vertices->push_back(p4);

            Triangle t1, t2;
            if(isVisible){
                for(int k = 0; k < 4; k++)
                    normals->push_back(Point(0, 0, 1));

                t1 = Triangle(*index+1, *index, *index+2);
                t2 = Triangle(*index+2, *index, *index+3);
            }
            else {
                for(int k = 0; k < 4; k++)
                    normals->push_back(Point(0, 0, -1));

                t1 = Triangle(*index, *index+1, *index+2);
                t2 = Triangle(*index, *index+2, *index+3);
            }

            triangles->push_back(t1);
            triangles->push_back(t2);
            
            *index+=4;
        }
    }
}


void generateBox(float length, int divisions, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals){
    int index = 0;
    float hl = length/2;

    generateXZplane(Point(hl, hl, hl), length, divisions, &index, true, vertices, triangles, normals);
    generateXZplane(Point(hl, -hl, hl), length, divisions, &index, false, vertices, triangles, normals);

    generateYZplane(Point(hl, hl, hl), length, divisions, &index, true, vertices, triangles, normals);
    generateYZplane(Point(-hl, hl, hl), length, divisions, &index, false, vertices, triangles, normals);

    generateXYplane(Point(-hl, -hl, hl), length, divisions, &index, true, vertices, triangles, normals);
    generateXYplane(Point(-hl, -hl, -hl), length, divisions, &index, false, vertices, triangles, normals);
}
