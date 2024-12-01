#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 500

struct Node {
  int data;

  struct Node *next;
};

struct LinkedList {
  int lenght;

  struct Node *fist_node;
};

void get_line_data(char *line, struct Node *left_data,
                   struct Node *right_data) {
  char temp_buffer[6];

  strncpy(temp_buffer, line, 5);
  temp_buffer[5] = '\0';
  int left_value = atoi(temp_buffer);

  strncpy(temp_buffer, &line[8], 5);
  temp_buffer[5] = '\0';
  int right_value = atoi(temp_buffer);

  struct Node *tmp_node = left_data;
  while (tmp_node->next != NULL) {
    tmp_node = tmp_node->next;
  }

  tmp_node->data = left_value;
  tmp_node->next = malloc(sizeof(struct Node));

  tmp_node = right_data;
  while (tmp_node->next != NULL) {
    tmp_node = tmp_node->next;
  }

  tmp_node->data = right_value;
  tmp_node->next = malloc(sizeof(struct Node));
}

int main(int argc, char **argv) {
  FILE *file = fopen("./input1", "r");
  char line[LINE_LENGTH];

  struct Node *left_data = malloc(sizeof(struct Node));

  struct Node *right_data = malloc(sizeof(struct Node));

  while (fgets(line, LINE_LENGTH, file) != NULL) {
    get_line_data(line, left_data, right_data);
  }

  int count = 0;

  struct Node *tmp_node = left_data;
  while (tmp_node->next != NULL) {
    struct Node *tmp_node_right = right_data;
    int repeated_times = 0;
    while (tmp_node_right->next != NULL) {
        if (tmp_node->data == tmp_node_right->data){
            repeated_times++;
        }
        tmp_node_right = tmp_node_right->next;
    }

    count += repeated_times * tmp_node->data;

    tmp_node = tmp_node->next;
  }

  printf("%i\n", count);

  return 0;
}
