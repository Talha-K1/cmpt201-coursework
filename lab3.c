#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

int main(void) 
{
  char *history[HISTORY_SIZE] = {NULL};
  char *input = NULL;
  size_t buffer_size = 0;
  ssize_t input_length;
  int history_count = 0;

  while (1) {
    printf("Enter input: ");

    input_length = getline(&input, &buffer_size, stdin);

    if (input_length == -1) {
      break;
    }

    if (input_length > 0 && input[input_length - 1] == '\n') {
      input[input_length - 1] = '\0';
    }

    if (history_count == HISTORY_SIZE) {
      free(history[0]);

      for (int i = 0; i < HISTORY_SIZE - 1; i++) {
        history[i] = history[i + 1];
      }

      history_count--;
    }

    history[history_count] = malloc(strlen(input) + 1);

    if (history[history_count] == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      free(input);

      for (int i = 0; i < history_count; i++) {
        free(history[i]);
      }

      return 1;
    }

    strcpy(history[history_count], input);
    history_count++;

    
    if (strcmp(input, "print") == 0) {
      for (int i = 0; i < history_count; i++) {
        printf("%s\n", history[i]);
      }
    }
  }

  free(input);

  for (int i = 0; i < history_count; i++) {
    free(history[i]);
  }

  return 0;
}
