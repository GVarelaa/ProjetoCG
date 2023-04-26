#include "../../include/engine/group.h"

Group::Group(){}

Group::Group(XMLElement *groupElement){
    color = NULL;
    label = NULL;

    if (groupElement->Attribute("label")) {
        label = strdup((char*)groupElement->Attribute("label"));
    }

    for(XMLElement *elem = groupElement->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "transform"){
            for(XMLElement *transformElem = elem->FirstChildElement(); transformElem; transformElem = transformElem->NextSiblingElement()){
                string transform(transformElem->Name());

                if(transform == "translate"){
                    if(transformElem->Attribute("x") && transformElem->Attribute("y") && transformElem->Attribute("z")){
                        transforms.push_back(new TranslateStatic(transformElem));
                    }
                    else if(transformElem->Attribute("time") && transformElem->Attribute("align")){
                        transforms.push_back(new TranslateDynamic(transformElem));
                    }
                    else cout << "ERROR: Invalid type of translation!" << endl;
                }
                
                else if(transform == "rotate"){
                    if(transformElem->Attribute("angle") && transformElem->Attribute("x") && transformElem->Attribute("y") && transformElem->Attribute("z")){
                        transforms.push_back(new RotateStatic(transformElem));
                    }
                    else if(transformElem->Attribute("time") && transformElem->Attribute("x") && transformElem->Attribute("y") && transformElem->Attribute("z")){
                        transforms.push_back(new RotateDynamic(transformElem));
                    }
                    else cout << "ERROR: Invalid type of rotation!" << endl;
                }
                else if(transform == "scale"){
                    transforms.push_back(new Scale(transformElem));
                }
            }
        }
        else if(name == "models"){
            for(XMLElement *modelElem = elem->FirstChildElement(); modelElem; modelElem = modelElem->NextSiblingElement()){
                string name(modelElem->Name());

                if(name == "model"){
                    models.push_back(Model(modelElem));
                }                
            }
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
        else if (name == "color") {
            color = new Point(atof((char*)elem->Attribute("R")), atof((char*)elem->Attribute("G")), atof((char*)elem->Attribute("B")));
        }
    }
}

void Group::loadModels(){
    for(int i = 0; i < models.size(); i++){
        models[i].load();
    }

    for(int i = 0; i < groups.size(); i++){
        groups[i].loadModels();
    }
}


void Group::drawModels(){
    glPushMatrix();

    if (color != NULL) {
        glColor3f(color->x / 255.0, color->y / 255.0, color->z / 255.0);
    }

    for(int i = 0; i < transforms.size(); i++){
        transforms[i]->transform();
    }
    
    for(int i = 0; i < models.size(); i++){
        models[i].draw();
    }    

    for(int i = 0; i < groups.size(); i++){
        groups[i].drawModels();
    }

    glPopMatrix();
}


void Group::getLabels(vector<char *> *labels) {
    labels->push_back(label); 

    for (int i = 0; i < groups.size(); i++) {
        groups[i].getLabels(labels);
    }
}


void multiplyMatrices(float m[4][4], float n[4][4], float res[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = 0.0f; 
            for (int k=0; k < 4; k++) {
                res[i][j] += m[i][k] * n[k][j];
            }
        }
    }
}


void Group::calculatePositions(float matrix[4][4]){
    for(int i=0; i<transforms.size(); i++){
        if(dynamic_cast<TranslateStatic*>(transforms[i])){
            float transf[4][4] = {
                {1, 0, 0, transforms[i]->x},
                {0, 1, 0, transforms[i]->y},
                {0, 0, 1, transforms[i]->z},
                {0, 0, 0, 1}
            };

            float aux[4][4];
            multiplyMatrices(matrix, transf, aux);
            memcpy(matrix, aux, sizeof(float) * 16);
        }
        else if(dynamic_cast<RotateStatic*>(transforms[i])){
            RotateStatic *rotate = dynamic_cast<RotateStatic*>(transforms[i]);
            float angle = 2 * M_PI * (rotate->angle/360.0);

            float transf[4][4] = {
                {(float)pow(rotate->x, 2) + (1 - (float)pow(rotate->x, 2)) * cos(angle), rotate->x * rotate->y * (1-cos(angle)) - rotate->z * sin(angle), rotate->x * rotate->z * (1-cos(angle)) + rotate->y*sin(angle), 0},
                {rotate->x*rotate->y*(1-cos(angle)) + rotate->z*sin(angle), (float)pow(rotate->y, 2) + (1 - (float)pow(rotate->y, 2))*cos(angle), rotate->y*rotate->z*(1-cos(angle)) - rotate->x*sin(angle), 0},
                {rotate->x*rotate->z*(1-cos(angle)) - rotate->y*sin(angle), rotate->y*rotate->z*(1-cos(angle)) + rotate->x*sin(angle), (float)pow(rotate->z, 2) + (1 - (float)pow(rotate->z, 2))*cos(angle), 0},
                {0, 0, 0, 1}
            };  

            float aux[4][4];
            multiplyMatrices(matrix, transf, aux);
            memcpy(matrix, aux, sizeof(float) * 16);  
        }
        else if(dynamic_cast<Scale*>(transforms[i])){
            float transf[4][4] = {
                {transforms[i]->x, 0, 0, 0},
                {0, transforms[i]->y, 0, 0},
                {0, 0, transforms[i]->z, 0},
                {0, 0, 0, 1}
            };
            
            float aux[4][4];
            multiplyMatrices(matrix, transf, aux);
            memcpy(matrix, aux, sizeof(float) * 16);
        }
    }

    position.x = matrix[0][3];
    position.y = matrix[1][3];
    position.z = matrix[2][3];

    for(int i=0; i<groups.size(); i++){
        float main[4][4];
        memcpy(main, matrix, sizeof(float) * 16);
        groups[i].calculatePositions(main);
    }     
}


Point* Group::getGroupPosition(int *i){
    if(*i == 0){
        return new Point(position.x, position.y, position.z);
    }
    
    (*i)--;

    for(int j=0; j<groups.size(); j++){
        Point *p = groups[j].getGroupPosition(i);

        if(p) return p;
    }

    return NULL;
}