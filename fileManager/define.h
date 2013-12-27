#ifndef DEFINE_H
#define DEFINE_H

// boost stuff
#include <boost/shared_ptr.hpp>

// std stuff

typedef unsigned long long uint64t;

namespace GANN_DEFINE {

    enum RESULT_EXEC_PROCESS {
         NO_ERROR = 0
        ,ERROR_NO_STARTED = 1
        ,ERROR_NO_FINISHED = 2
        ,IGNORE_COMMAND = 3
        ,ERROR_EXECUTE = 4
        ,DIRECTORY_NOT_EXIST
    };
}

#define DEBUG
//#undef DEBUG

#endif // DEFINE_H
