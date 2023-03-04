#include "../../include/model.h"

Model::Model(vector<Point> new_vertices, vector<Triangle> new_triangles){
    vertices = new_vertices;
    triangles = new_triangles;
    n_vertices = new_vertices.size();
    n_triangles = new_triangles.size();
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
        file << vertices[i].getX() << " " << vertices[i].getY() << " " << vertices[i].getZ() << "\n";
    }

    //Triangles
    for(int i = 0; i < n_triangles; i++){
        file << triangles[i].getIndP1() << " " << triangles[i].getIndP2() << " " << triangles[i].getIndP3() << "\n";
    }

    file.close();
}
