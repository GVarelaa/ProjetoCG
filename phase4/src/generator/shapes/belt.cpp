#include "../../../include/generator/belt.h"

pair<vector<Point>, vector<Triangle> > generateBelt(int n, float radiusIn, float radiusOut, float height, float lengthMin, float lengthMax, int seed) {
    vector<Point> vertices;
    vector<Triangle> triangles;

    /*srand(seed);
    int index=0;
    for (int k = 0; k < n; k++){
        float a = (((float)rand() / RAND_MAX) * (lengthMax - lengthMin)) + lengthMax;
        float b = (((float)rand() / RAND_MAX) * (lengthMax - lengthMin)) + lengthMax;
        float c = (((float)rand() / RAND_MAX) * (lengthMax - lengthMin)) + lengthMax;
        pair<vector<Point>, vector<Triangle> > pair = generateEllipsoid(a, b, c, 10, 10);
                
        float alphaRandom = ((float)rand() / RAND_MAX) * (2 * M_PI);
        float betaRandom = ((float)rand() / RAND_MAX) * (2 * M_PI);
        float radiusInRandom = ((float)rand() / RAND_MAX) * radiusIn;
        Point center = Point((radiusOut + radiusInRandom * cos(betaRandom)) * cos(alphaRandom), height * sin(betaRandom), (radiusOut + radiusInRandom * cos(betaRandom)) * sin(alphaRandom));

        for(int i=0; i<pair.first.size(); i++){
            Point p = pair.first[i];
            p.x += center.x;
            p.y += center.y;
            p.z += center.z;

            vertices.push_back(p);
        }

        for(int i=0; i<pair.second.size(); i++){
            Triangle t = pair.second[i];
            t.indP1 += index;
            t.indP2 += index;
            t.indP3 += index;

            triangles.push_back(t);
        }

        index += pair.first.size();
    }*/

    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}