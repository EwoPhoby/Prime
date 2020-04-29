#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int Fermat(mpz_t n, mpz_t k)
{
	gmp_randstate_t state; 
	gmp_randinit_mt(state);//Initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties. 
	gmp_randseed_ui(state, time(NULL));

	
	
	mpz_t i,n2,a,r,m;

	mpz_init(i);
	mpz_init(n2);
	mpz_init(a);
	mpz_init(r);
	mpz_init(m);

	mpz_set_si(i,1);

	mpz_sub_ui(n2,n,1);//
	mpz_sub_ui(m,n,3);//strictement plus petit que n-1

	char * h;

	while(mpz_cmp(i,k)<=0)
	{

		if (mpz_cmp_si(n,2)==0 || mpz_cmp_si(n,3)==0)break; //prime

		mpz_urandomm(a,state,m);
		mpz_add_ui(a,a,2);


		//**************************************************************
		//**************************************************************
		//*****************Square and Multiply**************************
		//**************************************************************
		//**************************************************************


		h=mpz_get_str(NULL,2,n2);  //decomposition binaire de l'exposant
    	mpz_set(r,a); // r=a
    	for(int i=1; i<strlen(h);i++)
   	 	{                  
			//r²mod n            
			mpz_mul(r,r,r);
			mpz_mod(r,r,n);

			if(h[i] == '1')
			{
				//r*a mod n
				mpz_mul(r,r,a);
				mpz_mod(r,r,n);
			}
		}

		//**************************************************************
		//**************************************************************
		//**************************************************************
		//**************************************************************
		//**************************************************************

		

		if(mpz_cmp_si(r,1)!=0)
		{
			
			mpz_clear(i);
			mpz_clear(n2);
			mpz_clear(a);
			mpz_clear(r);
			mpz_clear(m);
			
			gmp_randclear(state);

			return 0;
		}
		mpz_add_ui(i,i,1);
	}

	mpz_clear(i);
	mpz_clear(n2);
	mpz_clear(a);
	mpz_clear(r);
	mpz_clear(m);

	return 1;
	
	gmp_randclear(state);
}



int main()
{
	mpz_t n,k;

	int prime;

	mpz_init(n);
	mpz_init(k);

	    printf("Choisir n : ");
        gmp_scanf("%Zd", &n);
        if(mpz_cmp_ui(n,1)<=0)
        {	
			printf("\n Erreur nombre inférieur à 2");
		}
		else
		{
			printf("Choisir k : ");
			gmp_scanf("%Zd", &k);

			//flex();
			
			prime=Fermat(n,k);
			
			if (prime==1)gmp_printf("%Zd est premier \n",n);
			else gmp_printf("%Zd est composé \n",n);
			
		}	

	mpz_clear(n);	
	mpz_clear(k);

	return 0;
}
