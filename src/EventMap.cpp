// //
// // Created by eight on 1/17/20.
// //

// #include "../include/EventMap.h"
// using namespace Etbase;

// void EventMap::insert(EventPtr eventPtr) {
//     //lock whole map
//     // Guard guard(mutex);
//     if(eventPtr){
//         evmap[eventPtr->conf.in][eventPtr->fd]=eventPtr;
//     }
// }

// EventPtr EventMap::get(int fd, bool flag) {
//     // Guard guard(mutex);
//     auto iter=evmap[flag].find(fd);
//     if(iter!=evmap[flag].end()) return iter->second;
//     else return nullptr;
// }

// void HandlerMap::insert(int fd,bool in,Handler handler){
//     if(handler){
//         handlerMap[in][fd]=handler;
//     }
// }

// Handler HandlerMap::get(int fd,bool in){
//     auto iter=handlerMap[in].find(fd);
//     if(iter!=handlerMap[in].end()) return iter->second;
//     else return nullptr;
// }