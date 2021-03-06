#include "sequential_program_main.h"

char *inputString(FILE* fp, size_t size, char ending_character);

int main() {
   char *root_path;     //...of the directory to process

  /*Catching input from the user*/

  printf("Welcone in Spire\n\n");

  printf("Insert directory path of the fasta files\n");
  root_path = inputString(stdin, 100, '\n');

  do {
    printf("Choose one of the following options\n");
    printf("1.CFL\n");
    printf("2.ICFL\n");
    printf("3.CFL first and ICFL then\n");
    printf("4.ICFL first and CFL then\n");
    printf("Answer:\n");
    scanf("%d", &fact_choice);
    if (fact_choice >= 1 && fact_choice <= 4)
      break;
    else
      printf("Sorry, invalid choice. Try again\n\n");
  } while (1);

  if (fact_choice > 2) {
    printf("Insert maximum factors' length\n");
    scanf("%d", &max_fact_length);
  }

  communicate_max_fact_length(max_fact_length);
  printf("Insert maximum number of elements for each k-fingerprint window\n");
  scanf("%d", &window_dimension);

  time_t m;
  time_t now = time(NULL);

  for_each_element_in(root_path, process_all_fasta_files);

  print_statistics();

  m = difftime(time(NULL), now);
  printf("Total processing time in seconds: %ld\n",m);

  if (log_file != NULL)
    fclose(log_file);
  return 0;
}

/*Used as scanf handling in the case in which the defined dimension is not enough.
  pre-condition fp: == stdio
  pre-condition size: > 0
  pre-condition ending_character: != '\0'
  return: input read from the start to the ending_character
*/
char *inputString(FILE* fp, size_t size, char ending_character){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}
