#include "../../include/plane.h"

vector<Triangle> generate_square(int iter_x, int iter_z, int divisions){
    vector<Triangle> triangles;

    int bottom_left_index = (divisions+1)*iter_x + iter_z;
    int bottom_right_index = (divisions+1)*(iter_x+1) + iter_z;
    int top_left_index = (divisions+1)*iter_x + (iter_z+1);
    int top_right_index = (divisions+1)*(iter_x+1) + (iter_z+1);

    Triangle t1 = Triangle(bottom_left_index, bottom_right_index, top_left_index);
    Triangle t2 = Triangle(bottom_right_index, top_right_index, top_left_index);
    
    triangles.push_back(t1);
    triangles.push_back(t2);

    return triangles;
}

Model generate_plane(float length, int divisions){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float square_length = length/divisions;
    float initial_x = length/2.0;
    float initial_z = length/2.0;

    float x = initial_x;
    float z = initial_z;

    // Primeiramente, calculamos os vértices do plano
    for(int i = 0; i <= divisions; i++){
        x = initial_x;
        z = initial_z - i*square_length;
        
        for(int j = 0; j <= divisions; j++){
            x = initial_x - j*square_length;
            vertices.push_back(Point(x, 0, z));
        }
    }

    // Segndamente, construímos os trianguls com os índices dos vértices
    for(int i = 0; i < divisions; i++){
        for(int j = 0; j < divisions; j++){
            vector<Triangle> square_triangles = generate_square(i, j, divisions);
            triangles.insert(triangles.end(), square_triangles.begin(), square_triangles.end());
        }
    }

    return Model(vertices, triangles);
}
