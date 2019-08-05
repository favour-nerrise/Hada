/*
Name: Favour Nerrise
UID: 114794437
Directory ID: fnerrise
*/
#include "document.h"
#include <stdio.h>
#include <string.h>

/*Initializes the document to be empty.*/
int init_document(Document *doc, const char *name) {
  if (!doc || !name || strlen(name) > MAX_STR_SIZE) {
    return FAILURE;
  }

  strcpy(doc->name, name);
  doc->number_of_paragraphs = 0;

  return SUCCESS;
}

/*Sets the number of paragraphs to 0.*/
int reset_document(Document *doc) {
  if (!doc) {
    return FAILURE;
  }
  doc->number_of_paragraphs = 0;

  return SUCCESS;
}
/*Prints the document’s name, number of paragraphs, followed by the paragraphs*/
int print_document(Document *doc) {
  Paragraph *p;
  int i, j;

  if (!doc) {
    return FAILURE;
  }

  printf("Document name: \"%s\"\n", doc->name);
  printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
  p = doc->paragraphs;

  for (i = 0; i < doc->number_of_paragraphs; i++) {
    for (j = 0; j < p[i].number_of_lines; j++) {
      if (p[i].lines[j] != '\0') {
        printf("%s\n", p[i].lines[j]);
      }
    }
    printf("\n");
  }

  return SUCCESS;
}

/*Adds a paragraph after the specified paragraph number. */
int add_paragraph_after(Document *doc, int paragraph_number) {
  Document tmpDoc;
  Paragraph *p;
  int i;

  if (!doc || doc->number_of_paragraphs == MAX_PARAGRAPHS ||
      paragraph_number > doc->number_of_paragraphs) {
    return FAILURE;
  }
  p = doc->paragraphs;
  tmpDoc = *doc;

  for (i = paragraph_number; i < doc->number_of_paragraphs; i++) {
    tmpDoc.paragraphs[i] = p[i];
  }

  *doc = tmpDoc;
  doc->number_of_paragraphs += 1;

  return SUCCESS;
}

/*Adds a new line after the line with the specified line number.*/
int add_line_after(Document *doc, int paragraph_number, int line_number,
                   const char *new_line) {
  int i;
  Paragraph *p, *tmpP;

  if (!doc || !new_line || doc->number_of_paragraphs < paragraph_number - 1 ||
      doc->paragraphs[paragraph_number - 1].number_of_lines ==
          MAX_PARAGRAPH_LINES ||
      line_number > doc->paragraphs[paragraph_number - 1].number_of_lines) {
    return FAILURE;
  }
  p = doc->paragraphs;
  tmpP = &p[paragraph_number - 1];

  /* New line added between 0 - MAX_PARAGRAPHS*/
  if (tmpP->number_of_lines > line_number) {
    for (i = tmpP->number_of_lines - 1; i >= line_number; i--) {
      strcpy(p[paragraph_number - 1].lines[i + 1],
             p[paragraph_number - 1].lines[i]);
    }
    strcpy(p[paragraph_number - 1].lines[line_number], new_line);
    p[paragraph_number - 1].number_of_lines += 1;
  }

  /* New line added after number_of_paragraphs*/
  strcpy(p[paragraph_number - 1].lines[line_number], new_line);
  p[paragraph_number - 1].number_of_lines += 1;

  return SUCCESS;
}

/*Returns the number of lines in a paragraph using the number of lines out
 * parameter. */
int get_number_lines_paragraph(Document *doc, int paragraph_number,
                               int *number_of_lines) {
  if (!doc || !number_of_lines ||
      paragraph_number > doc->number_of_paragraphs) {
    return FAILURE;
  }

  number_of_lines = &doc->paragraphs[paragraph_number].number_of_lines;
  return SUCCESS;
}

/*Appends a line to the specified paragraph. */
int append_line(Document *doc, int paragraph_number, const char *new_line) {
  int *num_lines;
  Paragraph *p;

  if (!doc || !new_line || doc->number_of_paragraphs < paragraph_number - 1 ||
      doc->paragraphs[paragraph_number - 1].number_of_lines ==
          MAX_PARAGRAPH_LINES) {
    return FAILURE;
  }
  p = doc->paragraphs;

  strcpy(doc->paragraphs[paragraph_number - 1]
             .lines[p[paragraph_number - 1].number_of_lines],
         new_line);
  doc->paragraphs[paragraph_number - 1].number_of_lines += 1;

  return SUCCESS;
}

/*Removes the specified line from the paragraph.*/
int remove_line(Document *doc, int paragraph_number, int line_number) {
  int i;
  Paragraph *p;

  if (!doc || paragraph_number > doc->number_of_paragraphs ||
      doc->paragraphs[paragraph_number].number_of_lines >=
          MAX_PARAGRAPH_LINES ||
      line_number > doc->paragraphs[paragraph_number - 1].number_of_lines) {
    return FAILURE;
  }
  p = doc->paragraphs;

  for (i = line_number - 1; i <= p[paragraph_number - 1].number_of_lines; i++) {
    strcpy(p[paragraph_number - 1].lines[i],
           p[paragraph_number - 1].lines[i + 1]);
  }

  p[paragraph_number - 1].number_of_lines -= 1;

  return SUCCESS;
}

/*add the first data lines number of lines from the data array to the
 * document.*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1],
                  int data_lines) {
  int i;
  int *num_p;

  if (!doc || !data || !data_lines) {
    return FAILURE;
  }

  num_p = &doc->number_of_paragraphs;

  add_paragraph_after(doc, *num_p);

  for (i = 0; i < data_lines; i++) {
    if (data[i][0] == '\0') {
      add_paragraph_after(doc, *num_p);
    } else {
      append_line(doc, *num_p, data[i]);
    }
  }
  return SUCCESS;
}

/*Replace text target with text replacement everywhere it appears in the doc*/
int replace_text(Document *doc, const char *target, const char *replacement) {
  int i, j, num_p, offset, trg_len;
  char *sub_str, result[MAX_STR_SIZE + 1];
  Paragraph *p;

  if (!doc || !target || !replacement) {
    return FAILURE;
  }

  p = doc->paragraphs;
  num_p = doc->number_of_paragraphs;
  trg_len = strlen(target);

  for (i = 0; i < num_p; i++) {
    for (j = 0; j < p[i].number_of_lines; j++) {
      sub_str = strstr(strcpy(result, p[i].lines[j]), target);

      if (sub_str) {
        offset = sub_str - result;
      }

      while (sub_str) {
        p[i].lines[j][offset] = '\0';
        strcat(p[i].lines[j], replacement);
        sub_str += trg_len;
        strcat(p[i].lines[j], sub_str);
        sub_str = strstr(sub_str, target);

        if (sub_str) {
          offset = strlen(p[i].lines[j]) - strlen(sub_str);
        }
      }
    }
  }

  return SUCCESS;
}

/*Highlight text with target everywhere it appears in the document */
int highlight_text(Document *doc, const char *target) {
  char empty[MAX_STR_SIZE + 1] = {'\0'};

  if (!doc || !target) {
    return FAILURE;
  }

  strcat(empty, HIGHLIGHT_START_STR);
  strcat(empty, target);
  strcat(empty, HIGHLIGHT_END_STR);

  replace_text(doc, target, empty);

  return SUCCESS;
}

/*Remove  text target everywhere it appears in the document.*/
int remove_text(Document *doc, const char *target) {
  if (!doc || !target) {
    return FAILURE;
  }

  replace_text(doc, target, "");
  return SUCCESS;
}
