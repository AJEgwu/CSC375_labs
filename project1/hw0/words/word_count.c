/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utilities */

char *new_string(char *str) {
  return strcpy((char *)malloc(strlen(str) + 1), str);
}

void init_words(WordCount **wclist) {
  *wclist = NULL;
}

size_t len_words(WordCount *wchead) {
  size_t len = 0;
  for (WordCount *wc = wchead; wc; wc = wc->next) {
    len++;
  }
  return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
  for (WordCount *wc = wchead; wc; wc = wc->next) {
    if (strcmp(wc->word, word) == 0) {
      return wc;
    }
  }
  return NULL;
}

void add_word(WordCount **wclist, char *word) {
  WordCount *found = find_word(*wclist, word);
  if (found) {
    found->count++;
  } else {
    WordCount *new_wc = (WordCount *)malloc(sizeof(WordCount));
    new_wc->word = new_string(word);
    new_wc->count = 1;
    new_wc->next = *wclist;
    *wclist = new_wc;
  }
}

void fprint_words(WordCount *wchead, FILE *ofile) {
  for (WordCount *wc = wchead; wc; wc = wc->next) {
    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}

void wordcount_insert_ordered(WordCount **wclist, WordCount *elem,
                              bool less(const WordCount *, const WordCount *)) {
  if (*wclist == NULL || less(elem, *wclist)) {
    elem->next = *wclist;
    *wclist = elem;
    return;
  }

  WordCount *curr = *wclist;
  while (curr->next && !less(elem, curr->next)) {
    curr = curr->next;
  }
  elem->next = curr->next;
  curr->next = elem;
}

void wordcount_sort(WordCount **wclist,
                    bool less(const WordCount *, const WordCount *)) {
  WordCount *sorted = NULL;
  WordCount *curr = *wclist;
  while (curr) {
    WordCount *next = curr->next;
    curr->next = NULL;
    wordcount_insert_ordered(&sorted, curr, less);
    curr = next;
  }
  *wclist = sorted;
}
