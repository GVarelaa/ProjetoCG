#include "../../../include/generator/sphere.h"

void generateSphere(float radius, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords){
    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;
    float xTexPart = 1.0 / (float) slices;
    float yTexPart = 1.0 / (float) stacks;

    int index = 0;
    for(int i = 0; i < slices; i++){
        //Ponto inferior
        vertices->push_back(Point(0, -radius, 0));   
        normals->push_back(Point(0, -1, 0));
        texCoords->push_back(Point(i*xTexPart, 0, 0));
        triangles->push_back(Triangle(index, index+2, index+1));

        index++;

        for(int j = 1; j < stacks; j++){
            Point p1 = Point(radius * cos(j*beta-M_PI_2) * sin(i*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos(i*alpha));
            Point p2 = Point(radius * cos(j*beta-M_PI_2) * sin((i+1)*alpha), radius * sin(j*beta-M_PI_2), radius * cos(j*beta-M_PI_2) * cos((i+1)*alpha));
            vertices->push_back(p1);
            vertices->push_back(p2);

            Point n1 = Point(cos(j*beta-M_PI_2) * sin(i*alpha), sin(j*beta-M_PI_2), cos(j*beta-M_PI_2) * cos(i*alpha));
            Point n2 = Point(cos(j*beta-M_PI_2) * sin((i+1)*alpha), sin(j*beta-M_PI_2), cos(j*beta-M_PI_2) * cos((i+1)*alpha));
            //n1.normalizeVector();
            //n2.normalizeVector();
            normals->push_back(n1);
            normals->push_back(n2);

            texCoords->push_back(Point(i*xTexPart, j*yTexPart, 0));
            texCoords->push_back(Point((i+1)*xTexPart, j*yTexPart, 0));
            
            if(j!=stacks-1){
                Triangle t1 = Triangle(index, index+1, index+2);
                Triangle t2 = Triangle(index+1, index+3, index+2);

                triangles->push_back(t1);
                triangles->push_back(t2);

                index+=2;
            }
        }

        //Ponto superior
        vertices->push_back(Point(0, radius, 0));
        normals->push_back(Point(0, 1 ,0));
        texCoords->push_back(Point(i*xTexPart, 1, 0));
        triangles->push_back(Triangle(index, index+1, index+2));

        index+=3;
    }
}

