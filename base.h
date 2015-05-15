#ifndef BASE
#define BASE

#include <cmath>
#include <QDebug>

//Refresh Rate :
#define _RATE   30
#define _COMMAND_INTERVAL 1000
#define _PLAYER_RESPONSE_TIME 100

enum RobotColor{
    Red = 1,
    Yellow = 2,
    Cyan = 3,
    Magenta = 0
};

enum Material{
    Rhodium = 1,
    Platinum = 2,
    Gold = 3,
    Neutral= 0
};

enum RobotModels{
    Explorer = 0,
    Ninja = 1,
    Terminator = 2,
    Predator = 3
};

/* Mathematical */
#define _PI         3.14159265358979323
#define	_RAD2DEG    (180.0/_PI)
#define _DEG2RAD    (_PI/180.0)

#define Property(type,name,local) \
        public: inline type& get##name() {return local;} \
        public: inline void set##name(type val) {local = val;} \
        protected: type local

#define PropertyGet(type,name,local) \
        public: inline type& get##name() {return local;} \
        protected: type local

#endif // BASE

