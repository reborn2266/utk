all:
	gcc -o utk -g utk.c task.c context.c save.S restore.S

clean:
	rm -rf utk *.o
