#pragma once
#ifndef TVECTORNULLABLERESULT_H
#define TVECTORNULLABLERESULT_H

/* vector<NullableResult> */
#include "common.h"

class TVectorNullableResult {
    public:
    std::vector<NullableResult> val;

    TVectorNullableResult();

    TVectorNullableResult(std::vector<NullableResult> _val);

    std::vector<NullableResult>& get();

    bool operator==(const std::vector<NullableResult>& other) const;

    bool operator==(const TVectorNullableResult& other) const;

    bool tryParse(const std::string& input);

    friend std::ostream& operator<<(std::ostream& os, TVectorNullableResult& t);
};

#endif // TVECTORNULLABLERESULT_H
