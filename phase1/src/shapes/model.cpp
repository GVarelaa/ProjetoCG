#include "../../include/model.h"

Model::Model(vector<Point> new_vertices, vector<Triangle> new_triangles){
    vertices = new_vertices;
    triangles = new_triangles;
    n_vertices = new_vertices.size();
    n_triangles = new_triangles.size();
}

Model::Model(char* path){
    vertices = vector<Point>();
    triangles = vector<Triangle>();
    n_vertices = 0;
    n_triangles = 0;
}

vector<Point> Model::getVertices(){
    return vertices;
}

vector<Triangle> Model::getTriangles(){
    return triangles;
}

void Model::to_file(char* path){
    ofstream file; 
    file.open(path);
    char buffer[1024];
    
    //First line (n_vertices e n_triangles)
    file << n_vertices << " " << n_triangles << "\n";

    //Vertices
    for(int i = 0; i < n_vertices; i++){
        sprintf(buffer, "%f %f %f\n", vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
        file << buffer;
    }

    //Triangles
    for(int i = 0; i < n_triangles; i++){
        sprintf(buffer, "%d %d %d\n", triangles[i].getIndP1(), triangles[i].getIndP2(), triangles[i].getIndP3());
        file << buffer;
    }

    file.close();
}
