#include "../../include/engine/group.h"

Group::Group(){}

//Construção de um grupo para um único asteróide
Group::Group(char *path, float radiusIn, float radiusOut, int i, float anglePart){
    color = Point(255.0f, 255.0f, 255.0f); // Cor default -> branco
    models.push_back(Model(path));

    float randNumber = (float) rand() / RAND_MAX;
    printf("%f\n", randNumber);

    float scale = (float) rand() / RAND_MAX;
    scale = scale + 0.5;
    float angle = (randNumber * 2 * M_PI) + anglePart * i;
    float randomRadius = (float) rand() / RAND_MAX;
    randomRadius = randomRadius * radiusIn;

    transforms.push_back(new Translate((radiusOut + randomRadius*cos(angle))*cos(angle), randomRadius*sin(angle), (radiusOut + randomRadius*cos(angle))*sin(angle)));
    transforms.push_back(new Rotate((float) rand() / RAND_MAX, (float) rand() / RAND_MAX, (float) rand() / RAND_MAX, randNumber*360.0));
    transforms.push_back(new Scale((float) rand() / RAND_MAX, (float) rand() / RAND_MAX, (float) rand() / RAND_MAX));
}

Group::Group(XMLElement *groupElement){
    color = Point(255.0f, 255.0f, 255.0f); // Cor default -> branco

    for(XMLElement *elem = groupElement->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "transform"){
            for(XMLElement *transformElem = elem->FirstChildElement(); transformElem; transformElem = transformElem->NextSiblingElement()){
                string transform(transformElem->Name());

                if(transform == "translate"){
                    transforms.push_back(new Translate(transformElem));
                }
                else if(transform == "rotate"){
                    transforms.push_back(new Rotate(transformElem));
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
                else if(name == "belt"){
                    char *path = strdup((char *)modelElem->Attribute("file"));
                    int n = atoi((char *)modelElem->Attribute("n"));
                    float radiusIn = atof((char *)modelElem->Attribute("radiusIn"));
                    float radiusOut = atof((char *)modelElem->Attribute("radiusOut"));
                    int seed = atoi((char *)modelElem->Attribute("seed"));
                    printf("%d\n", seed);
                    //Point color;

                    /*XMLElement *child = elem->FirstChildElement();
                    if(child != NULL){
                        string name(child->Name());
                        if(name == "color"){
                            float r = atof((char *)child->Attribute("R"));
                            float g = atof((char *)child->Attribute("G"));
                            float b = atof((char *)child->Attribute("B"));
                            color = Point(r, g, b);
                        }
                    }*/
                    
                    srand(seed);
                    float anglePart = 2 * M_PI / (float)n;
                    for(int i = 0; i<n; i++){
                        groups.push_back(Group(path, radiusIn, radiusOut, i, anglePart));
                    }
                }
                
            }
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
        else if(name == "color"){
            color.x = atof((char *)elem->Attribute("R"));
            color.y = atof((char *)elem->Attribute("G"));
            color.z = atof((char *)elem->Attribute("B"));
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

    for(int i = 0; i < transforms.size(); i++){
        transforms[i]->transform();
    }
    
    for(int i = 0; i < models.size(); i++){
        glColor3f(color.x/255.0, color.y/255.0, color.z/255.0);
        models[i].draw();
    }    

    for(int i = 0; i < groups.size(); i++){
        groups[i].drawModels();
    }

    glPopMatrix();
}
