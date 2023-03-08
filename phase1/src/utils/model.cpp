#include "../../include/model.h"

Model::Model(vector<Point> newVertices, vector<Triangle> newTriangles){
    vertices = newVertices;
    triangles = newTriangles;
    nVertices = newVertices.size();
    nTriangles = newTriangles.size();
}

Model::Model(char* path){
    glGenBuffers(1, &vertices_buffer);
    glGenBuffers(1, &indexes_buffer);

    vector<float> points;
    vector<int> indexes;

    ifstream file(path);
    string line;
    getline(file, line);
    
    stringstream ss(line);
    string nVerticesStr, nTrianglesStr;
    ss >> nVerticesStr >> nTrianglesStr;

    nVertices = stoi(nVerticesStr);
    nTriangles = stoi(nTrianglesStr);
    
    for(int i = 0; i < nVertices; i++){
        getline(file, line);
        stringstream ss(line);
        string x, y, z;
        ss >> x >> y >> z;
        points.push_back(stof(x));
        points.push_back(stof(y));
        points.push_back(stof(z));
    }

    for(int i = 0; i < nTriangles; i++){
        getline(file, line);
        stringstream ss(line);
        string indP1, indP2, indP3;
        ss >> indP1 >> indP2 >> indP3;
        indexes.push_back(stoi(indP1));
        indexes.push_back(stoi(indP2));
        indexes.push_back(stoi(indP3));
    }

    file.close();

    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

    nIndexes = indexes.size();
}

void Model::draw(){
    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glVertexPointer(3,GL_FLOAT,0,0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glDrawElements(GL_TRIANGLES, nIndexes, GL_UNSIGNED_INT, NULL);
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
