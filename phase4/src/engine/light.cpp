#include "../../include/engine/light.h"

int Light::getLightN(int nLight){
    int CLight;
    switch (nLight) {
        case 0: CLight = GL_LIGHT0; break;
        case 1: CLight = GL_LIGHT1; break;
        case 2: CLight = GL_LIGHT2; break;
        case 3: CLight = GL_LIGHT3; break;
        case 4: CLight = GL_LIGHT4; break;
        case 5: CLight = GL_LIGHT5; break;
        case 6: CLight = GL_LIGHT6; break;
        case 7: CLight = GL_LIGHT7; break;
        default: exit(1);
    }
    return CLight;
}


//POINT
PointLight::PointLight(XMLElement *elem){
    elem->Attribute("posX") ? pos[0] = atof((char *)elem->Attribute("posX")) : pos[0] = atof((char *)elem->Attribute("posx"));
    elem->Attribute("posY") ? pos[1] = atof((char *)elem->Attribute("posY")) : pos[1] = atof((char *)elem->Attribute("posy"));
    elem->Attribute("posZ") ? pos[2] = atof((char *)elem->Attribute("posZ")) : pos[2] = atof((char *)elem->Attribute("posz"));
    pos[3] = 1;
}

void PointLight::apply(int ind){
    float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };
    float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    int CLight = getLightN(ind);

    // light colors
    glLightfv(CLight, GL_AMBIENT, dark);
    glLightfv(CLight, GL_DIFFUSE, white);
    glLightfv(CLight, GL_SPECULAR, white);

    // controls global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

    float quad_att = 1.0f;
    glLightfv(CLight, GL_POSITION, pos);
    glLightf(CLight, GL_QUADRATIC_ATTENUATION, quad_att);
}


//DIRECTIONAL
DirectionalLight::DirectionalLight(XMLElement *elem){
    elem->Attribute("dirX") ? dir[0] = atof((char *)elem->Attribute("dirX")) : dir[0] = atof((char *)elem->Attribute("dirx"));
    elem->Attribute("dirY") ? dir[1] = atof((char *)elem->Attribute("dirY")) : dir[1] = atof((char *)elem->Attribute("diry"));
    elem->Attribute("dirZ") ? dir[2] = atof((char *)elem->Attribute("dirZ")) : dir[2] = atof((char *)elem->Attribute("dirz"));
    dir[3] = 0;
}

void DirectionalLight::apply(int ind){
    float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };
    float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    int CLight = getLightN(ind);

    // light colors
    glLightfv(CLight, GL_AMBIENT, dark);
    glLightfv(CLight, GL_DIFFUSE, white);
    glLightfv(CLight, GL_SPECULAR, white);

    // controls global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

    glLightfv(CLight, GL_POSITION, dir);
}


//SPOTLIGHT
SpotLight::SpotLight(XMLElement* elem){
    elem->Attribute("posX") ? pos[0] = atof((char *)elem->Attribute("posX")) : pos[0] = atof((char *)elem->Attribute("posx"));
    elem->Attribute("posY") ? pos[1] = atof((char *)elem->Attribute("posY")) : pos[1] = atof((char *)elem->Attribute("posy"));
    elem->Attribute("posZ") ? pos[2] = atof((char *)elem->Attribute("posZ")) : pos[2] = atof((char *)elem->Attribute("posz"));
    pos[3] = 1;

    elem->Attribute("dirX") ? spotDir[0] = atof((char *)elem->Attribute("dirX")) : spotDir[0] = atof((char *)elem->Attribute("dirx"));
    elem->Attribute("dirY") ? spotDir[1] = atof((char *)elem->Attribute("dirY")) : spotDir[1] = atof((char *)elem->Attribute("diry"));
    elem->Attribute("dirZ") ? spotDir[2] = atof((char *)elem->Attribute("dirZ")) : spotDir[2] = atof((char *)elem->Attribute("dirz"));

    cutoff = atof((char *)elem->Attribute("cutoff"));
}

void SpotLight::apply(int ind){
    float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };
    float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    int CLight = getLightN(ind);

    // light colors
    glLightfv(CLight, GL_AMBIENT, dark);
    glLightfv(CLight, GL_DIFFUSE, white);
    glLightfv(CLight, GL_SPECULAR, white);

    // controls global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

    glLightfv(CLight, GL_POSITION, pos);
    glLightfv(CLight, GL_SPOT_DIRECTION, spotDir);
    glLightf(CLight, GL_SPOT_CUTOFF, cutoff);
    glLightf(CLight, GL_SPOT_EXPONENT, 0);  
}
