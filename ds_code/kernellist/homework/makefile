

# 目标:依赖文件
main:main.o student.o
	# 规则
	# gcc -o main main.o student.o
	gcc -o $@ $^

main.o:main.c
	gcc -c -o $@ $^

student.o:student.c
	gcc -c -o $@ $^ 

