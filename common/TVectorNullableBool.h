#pragma once
#ifndef TVECTORNULLABLEBOOL_H
#define TVECTORNULLABLEBOOL_H

/* vector<NullableBool> */
#include "common.h"

class TVectorNullableBool {
    public:
    std::vector<NullableBool> val;

    TVectorNullableBool();

    TVectorNullableBool(std::vector<NullableBool> _val);

    std::vector<NullableBool>& get();

    bool operator==(const std::vector<NullableBool>& other);

    bool operator==(const TVectorNullableBool& other);

    bool tryParse(const std::string& input);

    friend std::ostream& operator<<(std::ostream& os, TVectorNullableBool& t);
};

#endif // TVECTORNULLABLEBOOL_H
