project(Execute)

set(Prepare_Sources 
process.cpp     process.hpp
execute.cpp     execute.hpp
commands.cpp    commands.hpp
)

add_library(${PROJECT_NAME} ${Prepare_Sources})