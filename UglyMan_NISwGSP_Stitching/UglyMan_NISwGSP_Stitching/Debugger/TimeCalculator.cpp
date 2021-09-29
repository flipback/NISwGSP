//
//  TimeCalculator.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#include "TimeCalculator.h"
#include "chrono"
void TimeCalculator::start() {
    begin_time = chrono::steady_clock::now().time_since_epoch().count();
}
double TimeCalculator::end(const string output) const {
    double result = chrono::steady_clock::now().time_since_epoch().count()- begin_time;
    if(output.empty() == false) {
        printf("[TIME] %.4fs : %s\n", result / 1'000'000'000, output.c_str());
    }
    return result;
}