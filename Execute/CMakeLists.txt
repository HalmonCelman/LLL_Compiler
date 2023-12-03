project(Execute)

set(Execute_Sources
process.cpp             process.hpp
execute.cpp             execute.hpp
commands.cpp            commands.hpp
command_processing.cpp  command_processing.hpp
directives.cpp          directives.hpp
)

add_library(${PROJECT_NAME} ${Execute_Sources})