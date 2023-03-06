#include "../../include/model.h"

Model::Model(vector<Point> newVertices, vector<Triangle> newTriangles){
    vertices = newVertices;
    triangles = newTriangles;
    nVertices = newVertices.size();
    nTriangles = newTriangles.size();
}

Model::Model(char* path){
    ifstream file(path);
    string line;
    getline(file, line);
    
    stringstream ss(line);
    string nVerticesStr, nTrianglesStr;
    ss >> nVerticesStr >> nTrianglesStr;

    int nVertices = stoi(nVerticesStr);
    int nTriangles = stoi(nTrianglesStr);
    
    for(int i = 0; i < nVertices; i++){
        getline(file, line);
        stringstream ss(line);
        string x, y, z;
        ss >> x >> y >> z;
        vertices.push_back(Point(stof(x), stof(y), stof(z)));
    }

    for(int i = 0; i < nTriangles; i++){
        getline(file, line);
        stringstream ss(line);
        string indP1, indP2, indP3;
        ss >> indP1 >> indP2 >> indP3;
        triangles.push_back(Triangle(stoi(indP1), stoi(indP2), stoi(indP3)));
    }

    file.close();
}

void Model::toFile(char* path){
    ofstream file; 
    file.open(path);
    char buffer[1024];
    
    //First line (nVertices e nTriangles)
    file << nVertices << " " << nTriangles << "\n";

    //Vertices
    for(int i = 0; i < nVertices; i++){
        sprintf(buffer, "%f %f %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
        file << buffer;
    }

    //Triangles
    for(int i = 0; i < nTriangles; i++){
        sprintf(buffer, "%d %d %d\n", triangles[i].indP1, triangles[i].indP2, triangles[i].indP3);
        file << buffer;
    }

    file.close();
}
