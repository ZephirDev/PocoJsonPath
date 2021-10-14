cmake_minimum_required(VERSION 3.20)
project(PocoJsonPath)

set(CMAKE_CXX_STANDARD 17)

########################################################################################
###> package                                                                         ###
########################################################################################

###> package/poco ###
find_package(Poco REQUIRED Foundation JSON)
###< package/poco ###

########################################################################################
###> 3rd-party                                                                       ###
########################################################################################

###> 3rd-party/cpp-peglib ###
include_directories(3rd-party/cpp-peglib/include/)
###< 3rd-party/cpp-peglib ###

include_directories(src)
add_library(PocoJsonPath
        src/PocoJsonPath/JsonPath.cpp
        src/PocoJsonPath/JsonPath.hpp
        src/PocoJsonPath/JsonPathScope.hpp
        src/PocoJsonPath/JsonPathScope.cpp
        src/PocoJsonPath/Helpers/JsonHelper.cpp
        src/PocoJsonPath/Helpers/JsonHelper.hpp
        src/PocoJsonPath/Filters/IFilter.hpp
        src/PocoJsonPath/Operators/IOperator.hpp
        src/PocoJsonPath/Operators/AbstractOperator.cpp
        src/PocoJsonPath/Operators/AbstractOperator.hpp
        src/PocoJsonPath/Operators/AddOperator.cpp
        src/PocoJsonPath/Operators/AddOperator.hpp
        src/PocoJsonPath/Operators/SubstractOperator.cpp
        src/PocoJsonPath/Operators/SubstractOperator.hpp
        src/PocoJsonPath/Operators/MultOperator.cpp
        src/PocoJsonPath/Operators/MultOperator.hpp
        src/PocoJsonPath/Operators/DivOperator.cpp
        src/PocoJsonPath/Operators/DivOperator.hpp src/PocoJsonPath/Operators/EqualOperator.cpp src/PocoJsonPath/Operators/EqualOperator.hpp src/PocoJsonPath/Operators/NotEqualOperator.cpp src/PocoJsonPath/Operators/NotEqualOperator.hpp src/PocoJsonPath/Operators/GreaterThanOperator.cpp src/PocoJsonPath/Operators/GreaterThanOperator.hpp src/PocoJsonPath/Operators/GreaterThanOrEqualOperator.cpp src/PocoJsonPath/Operators/GreaterThanOrEqualOperator.hpp src/PocoJsonPath/Operators/LowerThanOperator.cpp src/PocoJsonPath/Operators/LowerThanOperator.hpp src/PocoJsonPath/Operators/LowerThanOrEqualOperator.cpp src/PocoJsonPath/Operators/LowerThanOrEqualOperator.hpp)
target_link_libraries(PocoJsonPath Poco::Foundation Poco::JSON)

add_subdirectory(test)