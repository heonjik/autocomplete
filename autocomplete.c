#include "autocomplete.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int lexi(const void *p_a, const void *p_b)
{
    term *p_a_i = (struct term *)p_a;
    term *p_b_i = (struct term *)p_b;
    return strcmp(p_a_i -> term, p_b_i -> term);
}

void read_in_terms(term **terms, int *pnterms, char *filename)
{
    // PART 1: read the first line (number of terms)
    FILE *fp = fopen(filename, "r");

    char number[200];
    fgets(number, 200, fp);
    number[strlen(number) - 1] = '\0';
    *pnterms = atoi(number);

    *terms = (term *)malloc(*pnterms * sizeof(term));

    // PART 2: divide double and char, malloc
    for(int i = 0; i < *pnterms; i++){
        char line[200];
        fgets(line, 200, fp);
        line[strlen(line)-1] = '\0';

        double num;
        char temp[200];
        char str[200];

        int j = 0; int k = 0; int l = 0;
        while(line[j] != '\t'){
            temp[j] = line[j];
            j++;
            k = j;
        }
        num = atof(temp);
        while(line[k] != '\0'){
            k++;
            str[l] = line[k];
            l++;
        }

        strcpy((*terms)[i].term, str);
        (*terms)[i].weight = num;
    }

    qsort(*terms, *pnterms, sizeof(struct term), lexi);
}


int lowest_match(term *terms, int nterms, char *substr)
{
    int low = 0;
    int high = nterms - 1;
    int len = strlen(substr);

    while(low <= high){
        int mid = (low + high) / 2;
        if(strncmp(substr, terms[low].term, len) == 0){
            return low;
        }
        else if(low + 1 == high){
            return high;
        }
        else if(strncmp(substr, terms[mid].term, len) == 0){
            high = mid;
        }
        else if(strncmp(substr, terms[mid].term, len) < 0){
            high = mid - 1;
        }
        else if(strncmp(substr, terms[mid].term, len) > 0){
            low = mid + 1;
        }
    }
    return 0;
}


int highest_match(struct term *terms, int nterms, char *substr)
{
    int low = 0;
    int high = nterms - 1;
    int len = strlen(substr);

    while(low <= high){
        int mid = (low + high) / 2;
        if(strncmp(substr, terms[high].term, len) == 0){
            return high;
        }
        else if(low + 1 == high){
            return low;
        }
        else if(strncmp(substr, terms[mid].term, len) == 0){
            low = mid;
        }
        else if(strncmp(substr, terms[mid].term, len) > 0){
            low = mid + 1;
        }
        else if(strncmp(substr, terms[mid].term, len) < 0){
            high = mid - 1;
        }
    }
    return 0;
}


int q4(const void *p_a, const void *p_b)
{
    term *p_a_i = (struct term *)p_a;
    term *p_b_i = (struct term *)p_b;
    double x = p_a_i -> weight;
    double y = p_b_i -> weight;
    return (x < y) - (x > y);
}

void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr)
{
    int lowest = lowest_match(terms, nterms, substr);
    int highest = highest_match(terms, nterms, substr);
    *n_answer = highest - lowest + 1;

    *answer = (term *)malloc((*n_answer) * sizeof(term));
    
    for(int i = 0; (i+lowest) <= highest; i++){
        strcpy((*answer)[i].term, terms[lowest+i].term);
        (*answer)[i].weight = terms[lowest+i].weight;
    }

    qsort(*answer, *n_answer, sizeof(struct term), q4);
}

int main()
{
    term **terms;
    int *pnterms;

    read_in_terms(terms, pnterms, "wiktionary.txt");
    return 0;
}