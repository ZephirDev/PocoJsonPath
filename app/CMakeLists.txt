add_executable(jq++
        main.cpp
        JqApplication.cpp
        JqApplication.hpp)
target_link_libraries(jq++ PocoJsonPath Poco::Util)

#find_program (BASH_PROGRAM bash)
#if (BASH_PROGRAM)
#    message("-- Add shell test")
#    add_custom_command(TARGET jq++ POST_BUILD COMMAND ${BASH_PROGRAM} ${CMAKE_SOURCE_DIR}/test/main.sh ${CMAKE_CURRENT_BINARY_DIR}/jq++)
#endif (BASH_PROGRAM)
