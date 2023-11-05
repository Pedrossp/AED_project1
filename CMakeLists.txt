cmake_minimum_required(VERSION 3.26)
project(AED_project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Classes)

add_executable(AED_project1
        Classes/Lesson.cpp
        Classes/Lesson.h
        Classes/Student.cpp
        Classes/Student.h
        Classes/UC_Class.cpp
        Classes/UC_Class.h
        Classes/DataManip.cpp
        Classes/DataManip.h
        Classes/main.cpp
        Classes/Consulting.cpp
        Classes/Consulting.h
        Classes/Menu.cpp
        Classes/Menu.h
        Classes/Menu.cpp
        Classes/Request.cpp
       )
