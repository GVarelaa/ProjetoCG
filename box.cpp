#include "headers/box.h"

vector<Point *> generate_xz_square(Point* point, float length, bool is_visible){
    vector<Point *> vetor;

    float x = point->getX();
    float y = point->getY();
    float z = point->getZ();

    Point *p1, *p2, *p3, *p4, *p5, *p6;

    if(is_visible){
        // primeiro triangulo
        Point* p1 = new Point(x, y, z);
        Point* p2 = new Point(x, y, z-length);
        Point* p3 = new Point(x-length, y, z);

        // segundo triangulo
        Point* p4 = new Point(x, y, z-length);
        Point* p5 = new Point(x-length, y, z-length);
        Point* p6 = new Point(x-length, y, z);
    }
    else{
        Point* p1 = new Point(x, y, z);
        Point* p2 = new Point(x-length, y, z);
        Point* p3 = new Point(x, y, z-length);

        // segundo triangulo
        Point* p4 = new Point(x, y, z-length);
        Point* p5 = new Point(x-length, y, z);
        Point* p6 = new Point(x-length, y, z-length);
    }

    vetor.push_back(p1);
    vetor.push_back(p2);
    vetor.push_back(p3);
    vetor.push_back(p4);
    vetor.push_back(p5);
    vetor.push_back(p6);

    return vetor;
}

vector<Point *> generate_yz_square(Point* point, float length, bool is_visible){
    vector<Point *> vetor;

    float x = point->getX();
    float y = point->getY();
    float z = point->getZ();

    Point *p1, *p2, *p3, *p4, *p5, *p6;

    if(is_visible){
        // primeiro triangulo
        Point* p1 = new Point(x, y, z-length);
        Point* p2 = new Point(x, y+length, z);
        Point* p3 = new Point(x, y, z);

        // segundo triangulo
        Point* p4 = new Point(x, y, z-length);
        Point* p5 = new Point(x, y+length, z-length);
        Point* p6 = new Point(x, y+length, z);
    }
    else{
        Point* p1 = new Point(x, y, z);
        Point* p2 = new Point(x, y+length, z);
        Point* p3 = new Point(x, y, z-length);

        // segundo triangulo
        Point* p4 = new Point(x, y, z-length);
        Point* p5 = new Point(x, y+length, z);
        Point* p6 = new Point(x, y+length, z-length);
    }

    vetor.push_back(p1);
    vetor.push_back(p2);
    vetor.push_back(p3);
    vetor.push_back(p4);
    vetor.push_back(p5);
    vetor.push_back(p6);

    return vetor;
}

vector<Point *> generate_xy_square(Point* point, float length, bool is_visible){
    vector<Point *> vetor;

    float x = point->getX();
    float y = point->getY();
    float z = point->getZ();
    
    Point *p1, *p2, *p3, *p4, *p5, *p6;

    if(is_visible){
      // primeiro triangulo
      Point* p1 = new Point(x, y, z);
      Point* p2 = new Point(x, y+length, z);
      Point* p3 = new Point(x-length, y, z);

      // segundo triangulo
      Point* p4 = new Point(x-length, y, z);
      Point* p5 = new Point(x, y+length, z);
      Point* p6 = new Point(x-length, y+length, z);
    }
    else{
      //primeiro triangulo
      Point* p1 = new Point(x, y, z);
      Point* p2 = new Point(x-length, y, z);
      Point* p3 = new Point(x, y+length, z);
      
      // segundo triangulo
      Point* p4 = new Point(x-length, y, z);
      Point* p5 = new Point(x-length, y+length, z);
      Point* p6 = new Point(x, y+length, z);
    }

    vetor.push_back(p1);
    vetor.push_back(p2);
    vetor.push_back(p3);
    vetor.push_back(p4);
    vetor.push_back(p5);
    vetor.push_back(p6);

    return vetor;
}

vector<Point *> generate_xz_plane(Point* initial_point, float length, int divisions, bool is_visible){
    vector<Point *> points;

    float square_length = length/divisions;
    float initial_x = initial_point->getX();
    float initial_y = initial_point->getY();
    float initial_z = initial_point->getZ();

    for(int i = 0; i < divisions; i++){
        float z_aux = initial_z;
        for(int j = 0; j < divisions; j++){
            vector<Point *> square_points = generate_xz_square(new Point(initial_x, initial_y, z_aux), square_length, is_visible);
            points.insert(points.end(), square_points.begin(), square_points.end());

            z_aux -= length/divisions;
        }

        initial_x -= length/divisions;
    }


    return points;
}


vector<Point *> generate_yz_plane(Point* initial_point, float length, int divisions, bool is_visible){
    vector<Point *> points;

    float square_length = length/divisions;
    float initial_x = initial_point->getX();
    float initial_y = initial_point->getY();
    float initial_z = initial_point->getZ();

    for(int i = 0; i < divisions; i++){
        float z_aux = initial_z;
        for(int j = 0; j < divisions; j++){
            vector<Point *> square_points = generate_yz_square(new Point(initial_x, initial_y, z_aux), square_length, is_visible);
            points.insert(points.end(), square_points.begin(), square_points.end());

            z_aux -= length/divisions;
        }

        initial_y -= length/divisions;
    }


    return points;
}

vector<Point *> generate_xy_plane(Point* initial_point, float length, int divisions, bool is_visible){
    vector<Point *> points;

    float square_length = length/divisions;
    float initial_x = initial_point->getX();
    float initial_y = initial_point->getY();
    float initial_z = initial_point->getZ();

    for(int i = 0; i < divisions; i++){
        float x_aux = initial_x;
        for(int j = 0; j < divisions; j++){
            vector<Point *> square_points = generate_yz_square(new Point(x_aux, initial_y, initial_z), square_length, is_visible);
            points.insert(points.end(), square_points.begin(), square_points.end());

            x_aux -= length/divisions;
        }

        initial_y -= length/divisions;
    }


    return points;
}

vector<Point *> generate_box(float length, int divisions){
    vector<Point *> points;

    Point* xz_p1 = new Point(length/2.0, -length/2.0, length/2.0);
    Point* xz_p2 = new Point(length/2.0, length/2.0, length/2.0);

    Point* yz_p1 = new Point(length/2.0, -length/2.0, length/2.0);
    Point* yz_p2 = new Point(-length/2.0, -length/2.0, length/2.0);

    Point* xy_p1 = new Point(length/2.0, -length/2.0, length/2.0);
    Point* xy_p2 = new Point(length/2.0, -length/2.0, -length/2.0);

    vector<Point *> xz_plane1 = generate_xz_plane(xz_p1, length, divisions, false);
    vector<Point *> xz_plane2 = generate_xz_plane(xz_p2, length, divisions, true);

    vector<Point *> yz_plane1 = generate_yz_plane(yz_p1, length, divisions, false);
    vector<Point *> yz_plane2 = generate_yz_plane(yz_p2, length, divisions, true);

    vector<Point *> xy_plane1 = generate_xy_plane(xy_p1, length, divisions, false);
    vector<Point *> xy_plane2 = generate_xy_plane(xy_p2, length, divisions, true);

    return points;
}