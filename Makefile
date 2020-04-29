EXEC_NAME=Fermat Miller

all:
	make fermat
	make miller

fermat: Fermat.c
	gcc -o Fermat Fermat.c -lgmp
	./Fermat
	rm Fermat

miller: Miller_Rabin.c
	gcc -o Miller Miller_Rabin.c -lgmp
	./Miller
	rm Miller

clean :
	rm $(EXEC_NAME) 

git:
	git add .
	git commit -a --allow-empty-message -m ''
	git push

