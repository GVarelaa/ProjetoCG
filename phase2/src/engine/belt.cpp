#include "../../include/engine/belt.h"


Belt::Belt(XMLElement *elem){
    char *path = strdup((char *)elem->Attribute("file"));
    int n = atoi((char *)elem->Attribute("n"));
    float radiusIn = atof((char *)elem->Attribute("radiusIn"));
    float radiusOut = atof((char *)elem->Attribute("radiusOut"));
    float verticalAngle = atof((char *)elem->Attribute("verticalAngle"));
    int seed = atoi((char *)elem->Attribute("seed"));
    pair<vector<float>, vector<int> > vectors = Model::readFile(path);
    Point *color = NULL;

    XMLElement *child = elem->FirstChildElement();
    if(child != NULL){
        string name(child->Name());
        if(name == "color"){
            float r = atof((char *)child->Attribute("R"));
            float g = atof((char *)child->Attribute("G"));
            float b = atof((char *)child->Attribute("B"));
            color = new Point(r, g, b);
        }
    }

    pair<vector<float>, vector<int> > vectors = Model::readFile(path);

    points = vectors.first;
    indexes = vectors.second;
    nVertices = points.size();
    nIndexes = indexes.size();
}


void Belt::load(){
    glGenBuffers(1, &vertices_buffer);
    glGenBuffers(1, &indexes_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertices, points.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * nIndexes, indexes.data(), GL_STATIC_DRAW);

    points.clear();
    indexes.clear();
}


void Belt::draw(){
    glPushAttrib(GL_CURRENT_BIT);

    if(color != NULL){
        glColor3f(color->x, color->y, color->z);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glDrawElements(GL_TRIANGLES, nIndexes, GL_UNSIGNED_INT, NULL);

    glPopAttrib();
}