#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <bits/stdc++.h>
using namespace std;

class TimeUtils{
public:
    static string getCurrentTime(){
        time_t now = time(0);
        char* dt = ctime(&now);
        return string (dt);
    }



};

#endif //TIME_UTILS_H