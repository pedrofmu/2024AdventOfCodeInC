#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGHT 500

struct Node {
  int data;

  struct Node *next;
};

void print_list(struct Node *list) {
  struct Node *tmp_node = list;
  while (tmp_node->next != NULL) {
    printf("%i ", tmp_node->data);
    tmp_node = tmp_node->next;
  }

  printf("\n");
}

struct Node *clone_list_removing_index(struct Node *list, int index_to_remove,
                                       int current_index) {
  if (list == NULL)
    return NULL;

  struct Node *result = malloc(sizeof(struct Node));

  if (index_to_remove == current_index) {
    if (list->next != NULL) {
      result->data = list->next->data;
      result->next = clone_list_removing_index(
          list->next->next, index_to_remove, current_index + 1);
    } else {
      return NULL;
    }
  } else {
    result->data = list->data;
    result->next = clone_list_removing_index(list->next, index_to_remove,
                                             current_index + 1);
  }

  return result;
}

int check_list(struct Node *list_head) {
  int isCorrect = 1;
  // Comprobar orden descendente
  struct Node *tmp_node = list_head;
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
  tmp_node = list_head;
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

int is_report_safe(char *line) {
  int line_lenght = strlen(line);

  int start_c = 0;

  char tmp_buffer[10];

  struct Node *number_list = malloc(sizeof(struct Node));

  int values_count = 0;
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
      values_count++;
    }
  }

  for (int i = 0; i < values_count; i++) {
    struct Node *iteration_list = clone_list_removing_index(number_list, i, 0);
    if (check_list(iteration_list) == 1) {
        return 1;
    }
  }

  return 0;
}

int main() {
  FILE *fd = fopen("./input1", "r");

  char line[LINE_LENGHT];
  int safe_report_count = 0;

  while (fgets(line, LINE_LENGHT, fd) != NULL) {
    safe_report_count += is_report_safe(line);
  }

  printf("%i\n", safe_report_count);
}
