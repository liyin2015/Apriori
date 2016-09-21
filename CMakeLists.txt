cmake_minimum_required(VERSION 3.3)
project(Apriori)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES main.cpp apriori.cpp apriori.hpp io_manager.cpp io_manager.h fp-tree/FP_Tree.cxx
        #fp-tree/FP_Tree.hpp fp-tree/FP_Trie.hpp)


file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp" "*.hpp"fpgrowth
        )
add_executable(Apriori ${SOURCE_FILES})