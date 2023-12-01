project(Prepare)

set(Prepare_Sources 
convert.cpp     convert.hpp
help.cpp        help.hpp
)

add_library(${PROJECT_NAME} ${Prepare_Sources})