#include "../../include/box.h"
#include <stdio.h>

vector<Triangle> generate_square_box(int i, int j, int divisions, int *index, bool is_visible){
    vector<Triangle> triangles;

    int bottom_left_index = (divisions+1)*i + j + *index;
    int bottom_right_index = (divisions+1)*(i+1) + j + *index;
    int top_left_index = (divisions+1)*i + (j+1) + *index;
    int top_right_index = (divisions+1)*(i+1) + (j+1) + *index;

    Triangle t1, t2;
    if(is_visible){
        t1 = Triangle(bottom_left_index, bottom_right_index, top_left_index);
        t2 = Triangle(bottom_right_index, top_right_index, top_left_index);
    }
    else{
        t1 = Triangle(top_left_index, bottom_right_index, bottom_left_index);
        t2 = Triangle(top_left_index, top_right_index, bottom_right_index);
    }

    triangles.push_back(t1);
    triangles.push_back(t2);

    return triangles;
}


pair<vector<Point>, vector<Triangle> > generate_xz_plane(Point initial_point, float length, int divisions, int *index, bool is_visible){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float square_length = length/divisions;
    float initial_x = initial_point.x;
    float initial_y = initial_point.y;
    float initial_z = initial_point.z;

    float x = initial_x;
    float z = initial_z;

    // Primeiramente, calculamos os vértices do plano
    for(int i = 0; i <= divisions; i++){
        x = initial_x;
        z = initial_z - i*square_length;
        
        for(int j = 0; j <= divisions; j++){
            x = initial_x - j*square_length;
            vertices.push_back(Point(x, initial_y, z));
        }
    }

    // Segndamente, construímos os triangulos com os índices dos vértices
    for(int i = 0; i < divisions; i++){
        for(int j = 0; j < divisions; j++){
            vector<Triangle> square_triangles = generate_square_box(i, j, divisions, index, is_visible);
            triangles.insert(triangles.end(), square_triangles.begin(), square_triangles.end());
        }
    }

    *index += vertices.size();
    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}


pair<vector<Point>, vector<Triangle> > generate_yz_plane(Point initial_point, float length, int divisions, int *index, bool is_visible){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float square_length = length/divisions;
    float initial_x = initial_point.x;
    float initial_y = initial_point.y;
    float initial_z = initial_point.z;

    float y = initial_y;
    float z = initial_z;

    // Primeiramente, calculamos os vértices do plano
    for(int i = 0; i <= divisions; i++){
        y = initial_y;
        z = initial_z - i*square_length;
        
        for(int j = 0; j <= divisions; j++){
            y = initial_y + j*square_length;
            vertices.push_back(Point(initial_x, y, z));
        }
    }

    // Segndamente, construímos os triangulos com os índices dos vértices
    for(int i = 0; i < divisions; i++){
        for(int j = 0; j < divisions; j++){
            vector<Triangle> square_triangles = generate_square_box(i, j, divisions, index, is_visible);
            triangles.insert(triangles.end(), square_triangles.begin(), square_triangles.end());
        }
    }

    *index += vertices.size();
    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}


pair<vector<Point>, vector<Triangle> > generate_xy_plane(Point initial_point, float length, int divisions, int *index, bool is_visible){
    vector<Point> vertices;
    vector<Triangle> triangles;

    float square_length = length/divisions;
    float initial_x = initial_point.x;
    float initial_y = initial_point.y;
    float initial_z = initial_point.z;

    float x = initial_x;
    float y = initial_y;

    // Primeiramente, calculamos os vértices do plano
    for(int i = 0; i <= divisions; i++){
        y = initial_y;
        x = initial_x + i*square_length;
        
        for(int j = 0; j <= divisions; j++){
            y = initial_y + j*square_length;
            vertices.push_back(Point(x, y, initial_z));
        }
    }

    // Segndamente, construímos os triangulos com os índices dos vértices
    for(int i = 0; i < divisions; i++){
        for(int j = 0; j < divisions; j++){
            vector<Triangle> square_triangles = generate_square_box(i, j, divisions, index, is_visible);
            triangles.insert(triangles.end(), square_triangles.begin(), square_triangles.end());
        }
    }

    *index += vertices.size();
    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}


Model generate_box(float length, int divisions){
    vector<Point> vertices;
    vector<Triangle> triangles;
    int index = 0;
    float hl = length/2;

    pair<vector<Point>, vector<Triangle> > xz_plane1  = generate_xz_plane(Point(hl, hl, hl), length, divisions, &index, true);
    pair<vector<Point>, vector<Triangle> > xz_plane2  = generate_xz_plane(Point(hl, -hl, hl), length, divisions, &index, false);

    pair<vector<Point>, vector<Triangle> > yz_plane1 = generate_yz_plane(Point(hl, -hl, hl), length, divisions, &index, true);
    pair<vector<Point>, vector<Triangle> > yz_plane2 = generate_yz_plane(Point(-hl, -hl, hl), length, divisions, &index, false);

    pair<vector<Point>, vector<Triangle> > xy_plane1 = generate_xy_plane(Point(-hl, -hl, hl), length, divisions, &index, true);
    pair<vector<Point>, vector<Triangle> > xy_plane2 = generate_xy_plane(Point(-hl, -hl, -hl), length, divisions, &index, false);

    vertices.insert(vertices.end(), xz_plane1.first.begin(), xz_plane1.first.end());
    vertices.insert(vertices.end(), xz_plane2.first.begin(), xz_plane2.first.end());
    vertices.insert(vertices.end(), yz_plane1.first.begin(), yz_plane1.first.end());
    vertices.insert(vertices.end(), yz_plane2.first.begin(), yz_plane2.first.end());
    vertices.insert(vertices.end(), xy_plane1.first.begin(), xy_plane1.first.end());
    vertices.insert(vertices.end(), xy_plane2.first.begin(), xy_plane2.first.end());

    triangles.insert(triangles.end(), xz_plane1.second.begin(), xz_plane1.second.end());
    triangles.insert(triangles.end(), xz_plane2.second.begin(), xz_plane2.second.end());
    triangles.insert(triangles.end(), yz_plane1.second.begin(), yz_plane1.second.end());
    triangles.insert(triangles.end(), yz_plane2.second.begin(), yz_plane2.second.end());
    triangles.insert(triangles.end(), xy_plane1.second.begin(), xy_plane1.second.end());
    triangles.insert(triangles.end(), xy_plane2.second.begin(), xy_plane2.second.end());

    return Model(vertices, triangles);
}