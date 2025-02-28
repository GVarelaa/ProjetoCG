#include "../../../include/generator/ellipsoid.h"

pair<vector<Point>, vector<Triangle> > generateEllipsoid(float a, float b, float c, int slices, int stacks){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;

    int index=0;
    for(int i = 0; i < slices; i++){
        //Ponto superior
        Point centralTopPoint = Point(0, b, 0);
        vertices.push_back(centralTopPoint);   

        Triangle topTriangle = Triangle(index, index+2, index+1);
        triangles.push_back(topTriangle);

        index++;

        for(int j = 1; j < stacks; j++){
            Point p1 = Point(a * cos(i*alpha) * sin(j*beta), b * cos(j*beta), c * sin(i*alpha) * sin(j*beta));
            Point p2 = Point(a * cos((i+1)*alpha) * sin(j*beta), b * cos(j*beta), c * sin((i+1)*alpha) * sin(j*beta));
            vertices.push_back(p1);
            vertices.push_back(p2);
            
            if(j!=stacks-1){
                Triangle t1 = Triangle(index, index+1, index+2);
                Triangle t2 = Triangle(index+1, index+3, index+2);

                triangles.push_back(t1);
                triangles.push_back(t2);

                index+=2;
            }
        }

        //Ponto superior
        Point centralBottomPoint = Point(0, -b, 0);
        vertices.push_back(centralBottomPoint);

        Triangle baseTriangle = Triangle(index, index+1, index+2);
        triangles.push_back(baseTriangle);

        index+=3;
    }

    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}