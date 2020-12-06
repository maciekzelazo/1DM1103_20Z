all:
	gcc baza.c bazamain.c -o mydb -Wall --pedantic

test: all
	./mydb baza.csv list_students

test-dodstud: all
	./mydb baza.csv add_student Adam Malysz 420 email@email.com
  
test-dodprzedmiot: all
	./mydb baza.csv add_course 1DM1103 "Podstawy programowania" 2020Z
  
test-dodstuddoprzed: all
	./mydb baza.csv add_student_to_course 1DM1103 420

test-ile_studentow: all
	./mydb baza.csv count_students

