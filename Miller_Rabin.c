#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void S_M(mpz_t a, mpz_t n ,mpz_t h , mpz_t y)   //fonction square and multiply pour Miller_Rabin
{
    char * d = mpz_get_str(NULL,2,h);  
    int i;                               
    mpz_set(y,a); 
    for(i = 1; i < strlen(d);i++) 
    {                              
		mpz_mul(y,y,y);
		mpz_mod(y,y,n);
		if(d[i] == '1')
		{
			mpz_mul(y,y,a);
			mpz_mod(y,y,n);
		}
	}
}


int Miller_Rabin(mpz_t n, mpz_t k)
{
	if(mpz_get_ui(n) % 2 == 0)   		// On test si n pair et différent de 2
	{
		if(mpz_cmp_ui(n,2) == 0)
		{
			return 1;					
		}
        else
        {
            return 0;							
        }
	}

	int i = 1;
	mpz_t a,y,s,t,n1,n2,two,xts,tmp;
	
	gmp_randstate_t state;     			
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, time(NULL));

	mpz_init(a);
	mpz_init(y);
	mpz_init(s);
	mpz_init(two);
	mpz_init(t);
	mpz_init(n1);	
	mpz_init(n2);
	mpz_init(xts);
	mpz_init(tmp);

	mpz_set_ui(xts,0);
	mpz_set_ui(s,1);
	mpz_set_ui(two,2);
	mpz_sub_ui(n1,n,1);
	mpz_sub_ui(n2,n,2);
                                 
	while(mpz_cmp(xts,n1)!=0) 	// On efféctue la décomposition  
	{
        mpz_set_ui(t,1); 
        mpz_mul(xts,tmp,t);
        while(mpz_cmp(xts,n1) < 0)
        {                     
			mpz_add_ui(t,t,2); 
			int i = 0;
  			mpz_set_ui(tmp,1);

  			while(mpz_cmp_si(s,i) > 0 ) 
  			{
    			mpz_mul_ui(tmp,tmp,2);
    			i++;
  			}
			mpz_mul(xts,tmp,t);
        }
        mpz_add_ui(s,s,1); 
	}

	mpz_sub_ui(s,s,1);
	mpz_clear(xts);
	mpz_clear(tmp);

	mpz_sub_ui(s,s,1);
	while(mpz_cmp_ui(k,i)>=0)
	{
		mpz_urandomm(a,state,n1);
		mpz_add_ui(a,a,1);
		S_M(a,n,t,y);
		if(mpz_cmp_si(y,1) != 0)  
		{											
			if(mpz_cmp(y,n1) == 0)
			{
				break;
			}

			for(int j=1; mpz_cmp_ui(s,j)>=0; j++)
			{
				mpz_set(n2,y);
				S_M(y,n,two,y);
				if(mpz_cmp_si(y,1) == 0) 
				{
					//Le nombre est composé
					mpz_clear(a);
					mpz_clear(y);
					mpz_clear(s);
					mpz_clear(t);
					mpz_clear(n1);
					mpz_clear(n2);
					mpz_clear(two);
					gmp_randclear(state);
					return 0;
				}
				if(mpz_cmp(y,n1) == 0) 
				break;
			}
			if(mpz_cmp(y,n1) != 0)  
			{
				//Le nombre est composé
				mpz_clear(a);
				mpz_clear(y);
				mpz_clear(s);
				mpz_clear(t);
				mpz_clear(n1);
				mpz_clear(n2);
				mpz_clear(two);
				gmp_randclear(state);
				return 0;
			}

		}
		i++;
	}
	//Le nombre est premier
	
	mpz_clear(a);
	mpz_clear(y);
	mpz_clear(s);
	mpz_clear(t);
	mpz_clear(n1);
	mpz_clear(n2);
	mpz_clear(two);
	gmp_randclear(state);
	return 1;
}


int main()
{
	mpz_t n,k;

	mpz_init(n);
	mpz_init(k);

	int retour;

	
        printf("Choisir votre entier n à tester : ");
        gmp_scanf("%Zd", &n);
        if(mpz_cmp_ui(n,1)<=0)
        {	
			printf("\n Erreur nombre inférieur à 2");
		}
		else
		{
			printf("Choisir le nombre de répétitions k souhaité : ");
			gmp_scanf("%Zd", &k);
			retour = Miller_Rabin(n,k);		
			if (retour == 1)
			{
				printf("Le nombre est premier \n");
			}
			else
			{
				printf("Le nombre est composé \n");
			}
		}	
	mpz_clear(n);	
	mpz_clear(k);
	return 0;
}