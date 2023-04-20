#include<stdio.h>
#include<stdlib.h>

struct Cellule
{
	int info;
	struct Cellule *suivant;
};

typedef struct Cellule *Liste;

Liste initialise();
void insereFin(Liste *L,int info);
void SupprimerPos(Liste *L,int postion);
void affiche(Liste L);
void Union_Intersection(Liste *L1,Liste *L2);


int main(){
	Liste L1 = initialise();
	Liste L2 = initialise();
	// 
	insereFin(&L1,6);
	insereFin(&L1,4);
	insereFin(&L1,12);
	insereFin(&L1,8);
	insereFin(&L1,3);
	//
	// SupprimerPos(&L1,3);
	//
	insereFin(&L2,3);
	insereFin(&L2,7);
	insereFin(&L2,4);
	insereFin(&L2,5);
	// before
	puts("\nbefore");
	printf("Liste L1: ");
	affiche(L1);
	printf("Liste L2: ");
	affiche(L2);
	// 
	Union_Intersection(&L1,&L2);
	// 
	// after
	puts("\nafter");
	printf("Liste L1: ");
	affiche(L1);
	printf("Liste L2: ");
	affiche(L2);

	return 0;
}

Liste initialise(){
	return NULL;
}

int Taille(Liste L){
	int counter = 0;
	while (L != NULL)
	{
		counter++;
		L = L->suivant;
	}
	return counter;
}

void SupprimerPos(Liste *L, int position) {
    if (*L == NULL) return;

    if (position >= 0 && position < Taille(*L)) {
        Liste P = *L;
        Liste Q = NULL;

        // supprimer debut
        if (position == 0) {
            *L = P->suivant;
            free(P);
        }
        // supprimer fin
        else if (position == Taille(*L) - 1) {
            while (P->suivant != NULL) {
                Q = P;
                P = P->suivant;
            }
            Q->suivant = NULL;
            free(P);
        }
        // supprimer position
        else {
            Q = P;
            while (P->suivant != NULL && position > 0) {
                Q = P;
                P = P->suivant;
                position--;
            }
            Q->suivant = P->suivant;
            free(P);
        }
    }
}


void insereFin(Liste *L,int info){
	Liste new_liste = (Liste) malloc(sizeof(struct Cellule));
	// create the new list
	new_liste->info = info;
	new_liste->suivant = NULL;
	Liste P = *L;
	// if the list is empty we set it to the new list
	if (P == NULL)
	{
		*L = new_liste;
	}else{
		// else we search for the last element in the list
		// and we set it to the new list
		while (P->suivant != NULL)
		{
			P = P->suivant;
		}
		P->suivant = new_liste;
	}
}

void affiche(Liste L){
	printf("[ ");
	while (L != NULL)
	{
		printf("%d ",L->info);
		if (L->suivant)
		{
			printf(",");
		}
		
		L = L->suivant;
	}
	printf("]\n");
}


void Union_Intersection(Liste *L1, Liste *L2) {
    Liste P1 = *L1;
    Liste P2 = *L2;

    int index = 0;
    int value_exists = 0;
    
	// we loop all over the second list
	while (P2 != NULL)
    {
		// reassignment for the first list to its head
        P1 = *L1;
		// reset the boolean to false (value does not exists)
        value_exists = 0;
		// we loop over the second list
        while (P1 != NULL)
        {
			// if we find the value from the second list
			// inside the first list
            if (P2->info == P1->info)
            {
				// we set the boolean to true
                value_exists = 1;
				// and we break the loop because we
				// already found the value
				break;
            }
            P1 = P1->suivant;
        }
		// after we looped over the first list
		// with our value from the second list
		// we check if we found the value
        if( value_exists == 0){
			// if we did found the value
			// we insert it into the first list
            insereFin(L1,P2->info);
			// then move the second list a step further
			// because we need to delete the current list
			// if we didn't move "P2" will be 
			// a hanging Pointer(non allocated, dosnt have "suivant") 
        	P2 = P2->suivant;
			// then we delete the current value from the second list
            SupprimerPos(L2,index);
			// our index will decremnet for the deletion
			// and increment for the loop so we just didnt add it here
        }else{
			// otherwise if we didnt found the value then
			// we just move forward and increment the index
        index = index + 1 ;
        P2 = P2->suivant;
		}
    }
}
