cmake_minimum_required(VERSION 3.2)
project(ANFIS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ANFIS ${SOURCE_FILES} neurofuzzy/Dataset.cpp neurofuzzy/Dataset.h neurofuzzy/Pair.cpp neurofuzzy/Pair.h neurofuzzy/Pair.h neurofuzzy/Pair.cpp neurofuzzy/ANFIS.cpp neurofuzzy/ANFIS.h neurofuzzy/Params.cpp neurofuzzy/Params.h neurofuzzy/Derivatives.cpp neurofuzzy/Derivatives.h)