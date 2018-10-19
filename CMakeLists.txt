cmake_minimum_required(VERSION 3.8)
project(mtm_ex3)

set(CMAKE_C_STANDARD 99)

set(GCC "-std=c99 -Wall -pedantic-errors -Werror ")
add_definitions(${GCC})
set(MAIN ${PROJECT_SOURCE_DIR})
set(HEADERS ${MAIN}/Headers)
set(SOURCES ${MAIN}/Sources)
set(TESTS ${MAIN}/Tests)

add_executable(coursemanager_test
        Tests/coursemanager_test.c
        Sources/Student.c
        Sources/CourseManager.c
        Sources/Course.c
        Sources/Friend.c
        Sources/Grade.c
        Sources/FriendRequest.c
        Headers/CourseManager.h
        Headers/Friend.h
        Headers/Grade.h
        Headers/FriendRequest.h)


add_executable(student_test
        Tests/student_test.c
        Sources/Student.c
        Sources/CourseManager.c
        Sources/Friend.c
        Sources/Grade.c
        Sources/Course.c
        Sources/FriendRequest.c
       Headers/Student.h)



#add_executable(course_test
#        ${TESTS}/course_test.c
#        ${SOURCES}/Grade.c
#        ${SOURCES}/Course.c
#        )


#add_executable(list_test
#        ready/list_mtm1_test.c
#        ready/list_mtm1.c
#        )

#add_executable(cmd_handler_test
#       Tests/cmdHandlerTest.c
#        ready/cmd_api1.c
#        ready/cmdHandler.c
#        ${SOURCES}/Student.c
#        ${SOURCES}/CourseManager.c
#        ${SOURCES}/Friend.c
#        ${SOURCES}/Grade.c
#        ${SOURCES}/Course.c
#        ${SOURCES}/FriendRequest.c
#        ${HEADERS}/CourseManager.h
#        ${HEADERS}/Friend.h
#        ${HEADERS}/Grade.h
#        ${HEADERS}/FriendRequest.h
#        ${HEADERS}/)

link_directories(.)

#target_link_libraries(list_test ${MAIN}/libmtm/win64/libmtm.a)
#target_link_libraries(cmd_handler_test ${MAIN}/libmtm/win64/libmtm.a)
target_link_libraries(coursemanager_test ${MAIN}/libmtm/win64/libmtm.a)
target_link_libraries(student_test ${MAIN}/libmtm/win64/libmtm.a)
#target_link_libraries(course_test ${MAIN}/libmtm/win64/libmtm.a)