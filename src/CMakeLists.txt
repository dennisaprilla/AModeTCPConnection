# CMakeList.txt : CMake project for AmodeTCPConnect, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp")

# Add my own library
add_library(AModeConnectionLib
	"AModeUSConnection.cpp"
)

# link the some other library to my own library
target_link_libraries(AModeConnectionLib
	Synch
	${OpenCV_LIBS}
	${Boost_LIBRARIES}
)

# finally, link my own full library to this project
target_link_libraries(${PROJECT_NAME}
	AModeConnectionLib
)
