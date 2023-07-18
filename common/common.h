#pragma once
#ifndef COMMON_H
#define COMMON_H

// for debugging one variable
#define DBVAR(x) std::cout << (#x) << " = " << (x) << std::endl;

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <cstdio>
#include <memory>
#include "TreeNode.h"
#include "ListNode.h"
// wrapper types for testcase parsing
#include "TVectorString.h"
// #include "TVector.h"
#include "TVectorInt.h"
#include "TVVInt.h"
#include "TVVString.h"
#include "TBool.h"
#include "TInt.h"
#include "TString.h"
#include "TTreeNode.h"
#include "TListNode.h"
#include "TVectorListNode.h"
#include "NullableResult.h"
#include "TVectorNullableResult.h"
using namespace std;
using linkedList::ListNode;

#endif // COMMON_H
