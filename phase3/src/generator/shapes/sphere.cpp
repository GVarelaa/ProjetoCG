#include "../../../include/generator/sphere.h"

pair<vector<Point>, vector<Triangle> > generateSphere(float radius, int slices, int stacks){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;

    int index = 0;
    for(int i = 0; i < slices; i++){
        //Ponto superior
        Point centralBottomPoint = Point(0, -radius, 0);
        vertices.push_back(centralBottomPoint);   

        Triangle baseTriangle = Triangle(index, index+2, index+1);
        triangles.push_back(baseTriangle);

        index++;

        for(int j = 1; j < stacks; j++){
            Point p1 = Point(radius * cos(j*beta-M_PI_2) * sin(i*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos(i*alpha));
            Point p2 = Point(radius * cos(j*beta-M_PI_2) * sin((i+1)*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos((i+1)*alpha));
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
        Point topCentralPoint = Point(0, radius, 0);
        vertices.push_back(topCentralPoint);

        Triangle topTriangle = Triangle(index, index+1, index+2);
        triangles.push_back(topTriangle);

        index+=3;
    }

    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}

