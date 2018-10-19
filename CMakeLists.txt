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



add_executable(course_test
        ${TESTS}/course_test.c
        ${SOURCES}/Grade.c
        ${SOURCES}/Course.c
        )


add_executable(list_test
        Tests/list_mtm_test.c
        Sources/list_mtm.c
        )
add_executable(cmd_handler_test
        Tests/cmd_handler_test.c
        Sources/cmdHandler.c
        Sources/cmd_api.c
        ${SOURCES}/Student.c
        ${SOURCES}/CourseManager.c
        ${SOURCES}/Friend.c
        ${SOURCES}/Grade.c
        ${SOURCES}/Course.c
        ${SOURCES}/FriendRequest.c
        )

link_directories(.)

target_link_libraries(list_test ${MAIN}/libmtm/win64/libmtm.a)
target_link_libraries(cmd_handler_test ${MAIN}/libmtm/win64/libmtm.a)
target_link_libraries(coursemanager_test ${MAIN}/libmtm/win64/libmtm.a)
target_link_libraries(student_test ${MAIN}/libmtm/win64/libmtm.a)
target_link_libraries(course_test ${MAIN}/libmtm/win64/libmtm.a)