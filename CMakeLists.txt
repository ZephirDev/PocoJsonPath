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
        src/PocoJsonPath/JsonPath.hpp src/PocoJsonPath/JsonPathScope.hpp src/PocoJsonPath/Helpers/JsonHelper.cpp src/PocoJsonPath/Helpers/JsonHelper.hpp src/PocoJsonPath/JsonPathScope.cpp src/PocoJsonPath/Types/IFilter.hpp)
target_link_libraries(PocoJsonPath Poco::Foundation Poco::JSON)

add_subdirectory(test)