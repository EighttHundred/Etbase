#ifndef ETBASE_TYPES_H
#define ETBASE_TYPES_H

#include <functional>
#include <queue>
#include <vector>
namespace Etbase
{   
    #define INPORTANT 2
    #define NORMAL 1
    #define PETTY 0
    typedef void(*funcp)(void*);
    typedef std::function<void()> evhandler;
    typedef std::pair<int,int> pair;    
    typedef std::priority_queue<pair,std::vector<pair>,std::greater<pair> > pri_queue; 
    
}
#endif // !ETBASE_TYPES_H