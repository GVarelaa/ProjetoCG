#ifndef __TRIANGLE__
#define __TRIANGLE__


class Triangle { 
    private:   
        int indx;  
        int indy;  
        int indz;
    public:
        Triangle(int indx, int indy, int indz);
        int getIndX();
        int getIndY();
        int getIndZ();
};

#endif