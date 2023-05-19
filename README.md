# StudentManagerment
My first university project

A Course Management System
There are 2 types of users in the system.
Academic staff members, for example, Ms. Le Thi Anh Thao, Ms. Nguyen Thi Minh Phuc, Ms.
Hoang Thanh Tu...
Students: in APCS, CLC, VP...
A user must log in to the system.
Then, he/she can view his/her own profile info, change the password, or log out of the system.
At the beginning of a school year (often in September), an academic
staff member will:
1. Create a school year (2020-2021, for example)
2. Create several classes for 1st-year students. For example: class 20APCS1, class 20APCS2,
class 20CLC1..., class 20CLC11, class 20VP...
3. Add new 1st year students to 1st-year classes.
4. For quick input, he/she can import a CSV file containing all students in a specific class to
the system, instead of adding one by one: No, Student ID, First name, Last name,
Gender, Date of Birth, and Social ID.
5. He/she does not need to add 2nd-year, 3rd-year, or 4th-year students, because these
students had been added in the previous years.
There are 3 semesters in a school year: Semester 1 (Fall), Semester 2 (Summer), and Semester 3
(Autumn).
At the beginning of a semester, an academic staff member will:
6. Create a semester: 1, 2, or 3, school year, start date, end date. Choose the school year
that the newly created semester belongs to. The created semester will be the current /
default semester for all the below actions.
7. Add a course to this semester: course id, course name, class name, teacher name,
number of credits, the maximum number of students in the course (default 50), day of
the week, and the session that the course will be performed (MON / TUE / WED / THU /
FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)). A course will be taught in
only one session in a week.
8. Then he/she will upload a CSV file, containing a list of students enrolled in the course.
9. View the list of courses.
10. Update course information.
11. Add a student to the course.

12. Remove a student from the course.
13. Delete a course.
In a semester, a student still can:
14. View a list of his/her courses. He/she will study these courses in this semester.
At any time, an academic staff member can:
15. View a list of classes.
16. View a list of students in a class (for example, 20APCS1...)
17. View a list of courses.
18. View a list of students in a course
At the end of a semester, an academic staff member can:
19. Export a list of students in a course to a CSV file
20. Import the scoreboard of a course. A scoreboard will have at least the following
columns: No, Student ID, Student Full Name, Total Mark, Final Mark, Midterm Mark, and
Other Mark. (An academic staff member will export the list of students in a course, and
send the CSV file to the teacher, the teacher will enter student results in this file, send it
back to the staff, and then the staff will import the scoreboard to the system)
21. View the scoreboard of a course.
22. Update a student's result.
23. View the scoreboard of a class, including final marks of all courses in the semester, GPA
in this semester, and the overall GPA.
When the scoreboard has been published (by the academic staff
member), a student can:
24. View his/her scoreboard.
Technical requirements
1. The text files and the binary files are ok. The databases are not allowed.
2. C++ language.
3. Only dynamic allocated arrays and linked lists are allowed.
4. char[], char*, and string are allowed.
5. Use Git to control your source code versions. Member(s) must have at least 20 commits
and must spread on at least 15 different days.
Submission

6. A report to describe data storage and structure of your source codes
7. Source code.
8. User manual videos, uploaded to Youtube as a playlist.
9. A list of tasks was made by each member of the group.
10. Presentation (later)
