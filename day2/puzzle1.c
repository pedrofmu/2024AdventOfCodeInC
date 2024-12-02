#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGHT 500

struct Node {
  int data;

  struct Node *next;
};

int is_report_safe(char *line) {
  int line_lenght = strlen(line);

  int start_c = 0;

  char tmp_buffer[10];

  struct Node *number_list = malloc(sizeof(struct Node));

  for (int i = 0; i < line_lenght; i++) {
    if (line[i] == ' ' || line[i] == '\n') {
      strncpy(tmp_buffer, &line[start_c], i - start_c);
      tmp_buffer[i - start_c] = '\0';
      start_c = i + 1;

      int number = atoi(tmp_buffer);

      struct Node *tmp_node = number_list;
      while (tmp_node->next != NULL) {
        tmp_node = tmp_node->next;
      }

      tmp_node->data = number;
      tmp_node->next = malloc(sizeof(struct Node));
    }
  }

  int isCorrect = 1;
  // Comprobar orden descendente
  struct Node *tmp_node = number_list;
  while (tmp_node->next->data != 0) {
    if (tmp_node->data >= tmp_node->next->data) {
      isCorrect = 0;
      break;
    }

    if (abs(tmp_node->data - tmp_node->next->data) > 3) {
      isCorrect = 0;
      break;
    }
    tmp_node = tmp_node->next;
  }

  if (isCorrect == 1) {
    return 1;
  }

  // Comprobar orden ascendente
  tmp_node = number_list;
  while (tmp_node->next->data != 0) {
    if (tmp_node->data <= tmp_node->next->data) {
      return 0;
    }

    if (abs(tmp_node->data - tmp_node->next->data) > 3) {
      return 0;
    }
    tmp_node = tmp_node->next;
  }

  return 1;
}

int main(int argc, char **argv) {
  FILE *fd = fopen("./input1", "r");

  char line[LINE_LENGHT];
  int safe_report_count = 0;

  while (fgets(line, LINE_LENGHT, fd) != NULL) {
    safe_report_count += is_report_safe(line);
  }

  printf("%i\n", safe_report_count);
}
