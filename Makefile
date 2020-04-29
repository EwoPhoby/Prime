EXEC_NAME=Fermat Miller

fermat: Fermat.c
	gcc -o Fermat Fermat.c -lgmp
	./Fermat

miller: Miller_Rabin.c
	gcc -o Miller Miller_Rabin.c -lgmp
	./Miller

clean :
	rm $(EXEC_NAME) 

git:
	git add .
	git commit -a --allow-empty-message -m ''
	git push

