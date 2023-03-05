#include "../../include/box.h"
#include <stdio.h>

vector<Triangle> generateSquareBox(int i, int j, int divisions, int *index, bool isVisible){
    vector<Triangle> triangles;

    int bottomLeftIndex = (divisions+1)*i + j + *index;
    int bottomRightIndex = (divisions+1)*(i+1) + j + *index;
    int topLeftIndex = (divisions+1)*i + (j+1) + *index;
    int topRightIndex = (divisions+1)*(i+1) + (j+1) + *index;

    Triangle t1, t2;
    if(isVisible){
        t1 = Triangle(bottomLeftIndex, bottomRightIndex, topRightIndex);
        t2 = Triangle(bottomLeftIndex, topRightIndex, topLeftIndex);
    }
    else{
        t1 = Triangle(topRightIndex, bottomRightIndex, bottomLeftIndex);
        t2 = Triangle(topLeftIndex, topRightIndex, bottomLeftIndex);
    }

    triangles.push_back(t1);
    triangles.push_back(t2);

    return triangles;
}


pair<vector<Point>, vector<Triangle> > generateXZplane(Point initialPoint, float length, int divisions, int *index, bool isVisible){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float x = initialX;
    float z = initialZ;

    for(int i = 0; i <= divisions; i++){
        x = initialX;
        z = initialZ - i*squareLength;
        
        for(int j = 0; j <= divisions; j++){
            x = initialX - j*squareLength;
            vertices.push_back(Point(x, initialY, z));
            
            if (i != divisions && j != divisions){
                vector<Triangle> squareTriangles = generateSquareBox(i, j, divisions, index, isVisible);
                triangles.insert(triangles.end(), squareTriangles.begin(), squareTriangles.end());
            }
        }
    }

    *index += vertices.size();
    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}


pair<vector<Point>, vector<Triangle> > generateYZplane(Point initialPoint, float length, int divisions, int *index, bool isVisible){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float y = initialY;
    float z = initialZ;

    for(int i = 0; i <= divisions; i++){
        z = initialZ;
        y = initialY - i*squareLength;
        
        for(int j = 0; j <= divisions; j++){
            z = initialZ - j*squareLength;
            vertices.push_back(Point(initialX, y, z));

            if (i != divisions && j != divisions){
                vector<Triangle> squareTriangles = generateSquareBox(i, j, divisions, index, isVisible);
                triangles.insert(triangles.end(), squareTriangles.begin(), squareTriangles.end());
            }
        }
    }

    *index += vertices.size();
    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}


pair<vector<Point>, vector<Triangle> > generateXYplane(Point initialPoint, float length, int divisions, int *index, bool isVisible){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float squareLength = length/divisions;
    float initialX = initialPoint.x;
    float initialY = initialPoint.y;
    float initialZ = initialPoint.z;

    float x = initialX;
    float y = initialY;

    for(int i = 0; i <= divisions; i++){
        y = initialY;
        x = initialX + i*squareLength;
        
        for(int j = 0; j <= divisions; j++){
            y = initialY + j*squareLength;
            vertices.push_back(Point(x, y, initialZ));
            
            if (i != divisions && j != divisions){
                vector<Triangle> squareTriangles = generateSquareBox(i, j, divisions, index, isVisible);
                triangles.insert(triangles.end(), squareTriangles.begin(), squareTriangles.end());
            } 
        }
    }

    *index += vertices.size();
    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}


Model generateBox(float length, int divisions){
    vector<Point> vertices;
    vector<Triangle> triangles;
    int index = 0;
    float hl = length/2;

    pair<vector<Point>, vector<Triangle> > xzPlane1  = generateXZplane(Point(hl, hl, hl), length, divisions, &index, true);
    pair<vector<Point>, vector<Triangle> > xzPlane2  = generateXZplane(Point(hl, -hl, hl), length, divisions, &index, false);

    pair<vector<Point>, vector<Triangle> > yzPlane1 = generateYZplane(Point(hl, hl, hl), length, divisions, &index, true);
    pair<vector<Point>, vector<Triangle> > yzPlane2 = generateYZplane(Point(-hl, hl, hl), length, divisions, &index, false);

    pair<vector<Point>, vector<Triangle> > xyPlane1 = generateXYplane(Point(-hl, -hl, hl), length, divisions, &index, true);
    pair<vector<Point>, vector<Triangle> > xyPlane2 = generateXYplane(Point(-hl, -hl, -hl), length, divisions, &index, false);

    vertices.insert(vertices.end(), xzPlane1.first.begin(), xzPlane1.first.end());
    vertices.insert(vertices.end(), xzPlane2.first.begin(), xzPlane2.first.end());
    vertices.insert(vertices.end(), yzPlane1.first.begin(), yzPlane1.first.end());
    vertices.insert(vertices.end(), yzPlane2.first.begin(), yzPlane2.first.end());
    vertices.insert(vertices.end(), xyPlane1.first.begin(), xyPlane1.first.end());
    vertices.insert(vertices.end(), xyPlane2.first.begin(), xyPlane2.first.end());

    triangles.insert(triangles.end(), xzPlane1.second.begin(), xzPlane1.second.end());
    triangles.insert(triangles.end(), xzPlane2.second.begin(), xzPlane2.second.end());
    triangles.insert(triangles.end(), yzPlane1.second.begin(), yzPlane1.second.end());
    triangles.insert(triangles.end(), yzPlane2.second.begin(), yzPlane2.second.end());
    triangles.insert(triangles.end(), xyPlane1.second.begin(), xyPlane1.second.end());
    triangles.insert(triangles.end(), xyPlane2.second.begin(), xyPlane2.second.end());

    return Model(vertices, triangles);
}