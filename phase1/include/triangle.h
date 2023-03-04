#ifndef __TRIANGLE__
#define __TRIANGLE__


class Triangle { 
    private:   
        int indP1;  
        int indP2;  
        int indP3;
    public:
        Triangle();
        Triangle(int indP1, int indP2, int indzP3);
        int getIndP1();
        int getIndP2();
        int getIndP3();
};

#endif