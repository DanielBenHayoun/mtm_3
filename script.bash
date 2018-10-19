#!bin/bash
gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/student_test.c Sources/Course.c libmtm.a 
valgrind ./mtm | grep  "All heap blocks were freed -- no leaks are possible"
echo student_test
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/course_test.c Sources/Course.c libmtm.a 
valgrind ./mtm | grep  "All heap blocks were freed -- no leaks are possible"
echo course_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/coursemanager_test.c Sources/Course.c libmtm.a 
valgrind ./mtm | grep  "All heap blocks were freed -- no leaks are possible"
echo coursemanager_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/friend_test.c Sources/Course.c libmtm.a 
valgrind ./mtm | grep  "All heap blocks were freed -- no leaks are possible"
echo friend_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/friendRequest_test.c Sources/Course.c libmtm.a 
valgrind ./mtm | grep  "All heap blocks were freed -- no leaks are possible"
echo friendRequest_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/grade_test.c Sources/Course.c libmtm.a 
valgrind ./mtm | grep  "All heap blocks were freed -- no leaks are possible"
echo grade_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/list_mtm_test.c Sources/Course.c libmtm.a 
valgrind ./mtm | grep  "All heap blocks were freed -- no leaks are possible"
echo list_mtm_test
 
