#ifndef driver_h
#define driver_h

class Driver{
public:
        Driver(){};
        ~Driver(){};
        virtual int init() = 0;
        virtual int close() = 0;
        virtual int start() = 0;
        virtual int recv() = 0;
};

#endif
