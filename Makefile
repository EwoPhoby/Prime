EXEC_NAME=Fermat MR

fermat: Fermat.c
	gcc -o Fermat Fermat.c -lgmp
	./Fermat

MR: Miller_Rabin.c
	gcc -o MR Miller_Rabin.c -lgmp

clean :
	rm $(EXEC_NAME) 

git:
	git add .
	git commit -a --allow-empty-message -m ''
	git push

