# Autocomplete
* The autocomplete task is to quickly retrieve the top terms that match a query string.
  * For example, if the query string is "Eng", your matches might be "English", "Engineering", and "EngSci".
## Tasks
* Read in the entire file of terms, and sort the terms in lexicographic ordering. This sorted list will be reused for multiple queries.
* Use binary search to find the location of the first term in lexicographic ordering that matches the query string, as well as the last term in lexicographic ordering that matches the query string.
* Extract the terms that match the query string, and sort them by weight.
* Extract the top matching terms by weight.
## Functions
1. `void read_in_terms(term **terms, int *pnterms, char *filename);`
 1. The function reads in all the terms from filename, and allocates memory for all the terms in the file and stores a pointer to the block in `*terms`.
 2. The function stores the number of terms in `*pnterms`.
 3. The terms should be sorted in ascending lexicographic order.
2. `int lowest_match(term *terms, int nterms, char *substr);`
 1. The function returns the index in terms of the **first term** in lexicographic ordering that matches the string `substr`.
 2. This function must run in _O(log(nterms))_ time.
3. `int highest_match(struct term *terms, int nterms, char *substr);`
 1. The function returns the index in terms of the **last term** in lexicographic order that matches the string `substr`.
 2. This function must run in _O(log(nterms))_ time.
4. `void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr);`
 1. The function places the answers in `answer`, with `*n_answer` being the number of answers.
 2. The answers should be sorted by weight in non-increasing order.
 3. You must use **qsort** for this question.
