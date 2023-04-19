#include "../../../include/generator/belt.h"

pair<vector<Point>, vector<Triangle> > generateBelt(int n, float radiusIn, float radiusOut, float height, int seed) {
    vector<Point> vertices;
    vector<Triangle> triangles;
    int index = 0;

    int slices = 10;
    int stacks = 10;
    float radius = 0.15;

    float alpha = (2 * M_PI) / slices;
    float beta = M_PI / stacks;

    srand(seed);

    for (int k = 0; k < n; k++){
        float alphaRandom = ((float)rand() / RAND_MAX) * (2 * M_PI);
        float betaRandom = ((float)rand() / RAND_MAX) * (2 * M_PI);
        float radiusInRandom = ((float)rand() / RAND_MAX) * radiusIn;
        Point center = Point((radiusOut + radiusInRandom * cos(betaRandom)) * cos(alphaRandom), height * sin(betaRandom), (radiusOut + radiusInRandom * cos(betaRandom)) * sin(alphaRandom));


        for (int i = 0; i < slices; i++) {
            //Ponto superior
            Point centralBottomPoint = Point(center.x, center.y - radius, center.z);
            vertices.push_back(centralBottomPoint);

            Triangle baseTriangle = Triangle(index + i * (2 * stacks), index + i * (2 * stacks) + 2, index + i * (2 * stacks) + 1);
            triangles.push_back(baseTriangle);

            for (int j = 1; j < stacks; j++) {
                Point p1 = Point(center.x + radius * cos(j * beta - M_PI_2) * sin(i * alpha), center.y + radius * sin(j * beta - M_PI_2), center.z + radius * cos(j * beta - M_PI_2) * cos(i * alpha));
                Point p2 = Point(center.x + radius * cos(j * beta - M_PI_2) * sin((i + 1) * alpha), center.y + radius * sin(j * beta - M_PI_2), center.z + radius * cos(j * beta - M_PI_2) * cos((i + 1) * alpha));
                vertices.push_back(p1);
                vertices.push_back(p2);

                if (j != stacks - 1) {
                    Triangle t1 = Triangle(index + i * (2 * stacks) + j * 2 - 1, index + i * (2 * stacks) + j * 2, index + i * (2 * stacks) + j * 2 + 1);
                    Triangle t2 = Triangle(index + i * (2 * stacks) + j * 2, index + i * (2 * stacks) + j * 2 + 2, index + i * (2 * stacks) + j * 2 + 1);

                    triangles.push_back(t1);
                    triangles.push_back(t2);
                }
            }

            //Ponto superior
            Point topCentralPoint = Point(center.x, center.y + radius, center.z);
            vertices.push_back(topCentralPoint);

            Triangle topTriangle = Triangle(index + i * (2 * stacks) + stacks * 2 - 3, index + i * (2 * stacks) + stacks * 2 - 2, index + i * (2 * stacks) + stacks * 2 - 1);
            triangles.push_back(topTriangle);
        }
        index += 2 * slices + 2 * slices * (stacks - 1); // atualizar o índice
    }

    return pair<vector<Point>, vector<Triangle> >(vertices, triangles);
}