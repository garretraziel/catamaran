#ifndef OUTPUT_H
#define OUTPUT_H
#include <string>
#include <iostream>
//TODO: tady budu resit dvoji vystup - do souboru a do konzole
using namespace std;
class output: public ostream
{
    public:
        output(bool mode = 1);
        virtual ~output();
        //operator<<(string);
    protected:
    private:
};

#endif // OUTPUT_H
