#!/bin/bash
gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/student_test.c Sources/Course.c libmtm.a 
valgrind  --leak-check=full  --log-file="tmp.out" ./mtm > tmp.out 2>&1
grep " All heap blocks were freed -- no leaks are possible" tmp.out
echo student_test
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/course_test.c Sources/Course.c libmtm.a 
valgrind --leak-check=full --log-file="tmp.out" ./mtm > tmp.out 2>&1
grep  "All heap blocks were freed -- no leaks are possible" tmp.out
echo course_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/coursemanager_test.c Sources/Course.c libmtm.a 
valgrind --leak-check=full --log-file="tmp.out" ./mtm > tmp.out 2>&1
grep  "All heap blocks were freed -- no leaks are possible" tmp.out
echo coursemanager_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/friend_test.c Sources/Course.c libmtm.a 
valgrind --leak-check=full --log-file="tmp.out" ./mtm > tmp.out 2>&1
grep  "All heap blocks were freed -- no leaks are possible" tmp.out
echo friend_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/friendRequest_test.c Sources/Course.c libmtm.a 
valgrind --leak-check=full --log-file="tmp.out" ./mtm > tmp.out 2>&1
grep  "All heap blocks were freed -- no leaks are possible" tmp.out
echo friendRequest_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/grade_test.c Sources/Course.c libmtm.a 
valgrind --leak-check=full --log-file="tmp.out" ./mtm > tmp.out 2>&1
grep  "All heap blocks were freed -- no leaks are possible" tmp.out
echo grade_test
 
 gcc -std=c99 -o mtm  -Wall -pedantic-errors -Werror -L.  Sources/Student.c Sources/CourseManager.c Sources/Friend.c Sources/FriendRequest.c Sources/Grade.c Tests/list_mtm_test.c Sources/Course.c libmtm.a 
valgrind --leak-check=full --log-file="tmp.out" ./mtm > tmp.out 2>&1
grep  "All heap blocks were freed -- no leaks are possible" tmp.out
echo list_mtm_test
 
