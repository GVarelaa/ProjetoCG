#include "../../include/model.h"

Model::Model(vector<Point> new_vertices, vector<Triangle> new_triangles){
    vertices = new_vertices;
    triangles = new_triangles;
    n_vertices = new_vertices.size();
    n_triangles = new_triangles.size();
}

Model::Model(char* path){
    ifstream file(path);
    string line;
    getline(file, line);
    
    stringstream ss(line);
    string n_vertices_str, n_triangles_str;
    ss >> n_vertices_str >> n_triangles_str;

    int n_vertices = stoi(n_vertices_str);
    int n_triangles = stoi(n_triangles_str);
    
    for(int i = 0; i < n_vertices; i++){
        getline(file, line);
        stringstream ss(line);
        string x, y, z;
        ss >> x >> y >> z;
        vertices.push_back(Point(stof(x), stof(y), stof(z)));
    }

    for(int i = 0; i < n_triangles; i++){
        getline(file, line);
        stringstream ss(line);
        string indp1, indp2, indp3;
        ss >> indp1 >> indp2 >> indp3;
        triangles.push_back(Triangle(stoi(indp1), stoi(indp2), stoi(indp3)));
    }

    file.close();
}

void Model::to_file(char* path){
    ofstream file; 
    file.open(path);
    char buffer[1024];
    
    //First line (n_vertices e n_triangles)
    file << n_vertices << " " << n_triangles << "\n";

    //Vertices
    for(int i = 0; i < n_vertices; i++){
        sprintf(buffer, "%f %f %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
        file << buffer;
    }

    //Triangles
    for(int i = 0; i < n_triangles; i++){
        sprintf(buffer, "%d %d %d\n", triangles[i].indP1, triangles[i].indP2, triangles[i].indP3);
        file << buffer;
    }

    file.close();
}
