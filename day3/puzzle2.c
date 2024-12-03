#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGHT 8000

struct Node {
  int num1;
  int num2;

  struct Node *next;
};

void add_to_list(int num1, int num2, struct Node **list) {
  if (*list == NULL) {
    *list = malloc(sizeof(struct Node));
    (*list)->num1 = num1;
    (*list)->num2 = num2;
    (*list)->next = NULL;
    return;
  }

  struct Node *tmp_node = *list;
  while (tmp_node->next != NULL) {
    tmp_node = tmp_node->next;
  }

  tmp_node->next = malloc(sizeof(struct Node));
  tmp_node->next->num1 = num1;
  tmp_node->next->num2 = num2;
}

void print_list(struct Node *list) {
  struct Node *tmp_node = list;
  while (tmp_node != NULL) {
    printf(" [%i , %i] ", tmp_node->num1, tmp_node->num2);
    tmp_node = tmp_node->next;
  }

  printf("\n");
}

// valid expresion mul([0-9]1-3,[0-9]1-3)
int parse_line(char *line, struct Node **valid_operations, int default_enable) {
  int i = default_enable;
  // 0 disable | 1 enable
  int enabled = default_enable;
  while (line[i] != '\n') {
    // enable or disable
    if (line[i] == 'd') {
      char tmp_buff_do[5];
      strncpy(tmp_buff_do, &line[i], 4);
      tmp_buff_do[4] = '\0';
      if (strcmp(tmp_buff_do, "do()") == 0) {
        enabled = 1;
      }

      char tmp_buff_dont[8];
      strncpy(tmp_buff_dont, &line[i], 7);
      tmp_buff_dont[7] = '\0';

      if (strcmp(tmp_buff_dont, "don't()") == 0) {
        enabled = 0;
      }
    }
    if (line[i] == 'm') {
      char tmp_buff[4];
      strncpy(tmp_buff, &line[i], 3);
      tmp_buff[3] = '\0';

      if (strcmp(tmp_buff, "mul") == 0) {
        if (line[i + 3] == '(') {
          int j = i + 4;
          while (isdigit(line[j]) != 0) {
            j++;
          }

          char num1_buff[4];
          strncpy(num1_buff, &line[i + 4], j - (i + 4));
          num1_buff[j - (i + 4)] = '\0';

          int num1 = atoi(num1_buff);

          if (j - (i + 4) <= 3 && line[j] == ',') {
            int x = j + 1;
            while (isdigit(line[x]) != 0) {
              x++;
            }

            char num2_buff[4];
            strncpy(num2_buff, &line[j + 1], x - j - 1);
            num2_buff[x - j - 1] = '\0';

            int num2 = atoi(num2_buff);

            if (x - (j + 1) <= 3 && line[x] == ')') {
              //              char *valid_operation = malloc(sizeof(char) * x -
              //              i); strncpy(valid_operation, &line[i], x - i + 1);
              if (enabled == 1) {
                add_to_list(num1, num2, valid_operations);
              }
            }
          }
        }
      }
    }
    i++;
  }
  return enabled;
}

int multiply_values(struct Node *valid_values) {
  int sum = 0;
  struct Node *tmp_node = valid_values;
  while (tmp_node != NULL) {
    sum += tmp_node->num2 * tmp_node->num1;
    tmp_node = tmp_node->next;
  }
  return sum;
}

int main() {
  FILE *fd = fopen("./input1", "r");

  char line[LINE_LENGHT];
  struct Node *valid_operations;

  int enable = 1;

  while (fgets(line, LINE_LENGHT, fd) != NULL) {
    enable = parse_line(line, &valid_operations, enable);
  }

  print_list(valid_operations);

  int response = multiply_values(valid_operations);
  printf("%i \n", response);
}
