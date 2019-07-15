cmake_minimum_required(VERSION 2.8.12) 
project(test)
add_compile_options(-std=c++11) 
SET(CMAKE_CXX_FLAGS "-fPIC") 
SET(CMAKE_C_FLAGS "-fPIC")

include_directories(./)

file(GLOB native_srcs "*.cpp" "*.h") 
message("-----------------------src file----------------------") 
message(${native_srcs})
message("-----------------------src file----------------------")


add_library(# Sets the name of the library. 
	test 
	#Sets the library as a shared library.
	SHARED 
	${native_srcs} )


#add_executable(test_exe ${native_srcs}) 

