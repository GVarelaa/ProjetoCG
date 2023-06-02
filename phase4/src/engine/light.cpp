#include "../../include/engine/light.h"

//POINT
PointLight::PointLight(XMLElement *elem){
    const char *posX = elem->Attribute("posX");
    const char *posY = elem->Attribute("posY");
    const char *posZ = elem->Attribute("posZ");

    if (posX == NULL) posX = elem->Attribute("posx");
    if (posY == NULL) posY = elem->Attribute("posy");
    if (posZ == NULL) posZ = elem->Attribute("posz");

    pos[0] = stof(posX);
    pos[1] = stof(posY);
    pos[2] = stof(posZ);
    pos[3] = 1;
}

void PointLight::apply(){
    float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };
    float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    // light colors
    glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    // controls global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

    float quad_att = 1.0f;
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quad_att);
}


//DIRECTIONAL
DirectionalLight::DirectionalLight(XMLElement *elem){
    const char *dirX = elem->Attribute("dirX");
    const char *dirY = elem->Attribute("dirY");
    const char *dirZ = elem->Attribute("dirZ");

    if (dirX == NULL) dirX = elem->Attribute("dirx");
    if (dirY == NULL) dirY = elem->Attribute("diry");
    if (dirZ == NULL) dirZ = elem->Attribute("dirz");

    dir[0] = stof(dirX);
    dir[1] = stof(dirY);
    dir[2] = stof(dirZ);
    dir[3] = 0;
}

void DirectionalLight::apply(){
    float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };
    float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    // light colors
    glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    // controls global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

    glLightfv(GL_LIGHT0, GL_POSITION, dir);
}


//SPOTLIGHT
SpotLight::SpotLight(XMLElement* elem){
    const char *posX = elem->Attribute("posX");
    const char *posY = elem->Attribute("posY");
    const char *posZ = elem->Attribute("posZ");
    const char *dirX = elem->Attribute("dirX");
    const char *dirY = elem->Attribute("dirY");
    const char *dirZ = elem->Attribute("dirZ");

    if (posX == NULL) posX = elem->Attribute("posx");
    if (posY == NULL) posY = elem->Attribute("posy");
    if (posZ == NULL) posZ = elem->Attribute("posz");
    if (dirX == NULL) dirX = elem->Attribute("dirx");
    if (dirY == NULL) dirY = elem->Attribute("diry");
    if (dirZ == NULL) dirZ = elem->Attribute("dirz");

    pos[0] = stof(posX);
    pos[1] = stof(posY); 
    pos[2] = stof(posZ);
    pos[3] = 1;

    spotDir[0] = stof(dirX);
    spotDir[1] = stof(dirY);
    spotDir[2] = stof(dirZ);

    cutoff = atof((char *)elem->Attribute("cutoff"));
}

void SpotLight::apply(){
    float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };
    float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    // light colors
    glLightfv(GL_LIGHT0, GL_AMBIENT, dark);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    // controls global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0);  
}
