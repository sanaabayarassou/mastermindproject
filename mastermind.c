#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int NUM_PAWNS = 5;
const int NUM_COLORS = 8;
const int NUM_ATTEMPTS = 10;

enum color_t { RED, GREEN, BLUE, YELLOW, BLACK, WHITE, GRAY, PURPLE };

/* Generate a random hidden combination */
void generate_hidden_combination(enum color_t hidden_combination[]) {
  srand(time(NULL));
  for (int i = 0; i < NUM_PAWNS; i++) {
    hidden_combination[i] = (enum color_t)rand() % NUM_COLORS;
  }
}

/* Retrieve the proposal of the codebreaker */
void read_proposed_combination(enum color_t proposed_combination[]) {
  printf("Enter your guess (5 colors, separated by spaces): ");
  for (int i = 0; i < NUM_PAWNS; i++) {
    scanf("%d", &proposed_combination[i]);
  }
}

/* Compare hidden and proposed combinations and count well-placed and misplaced pawns */
void evaluate_proposed_combination(
  enum color_t hidden_combination[],
  enum color_t proposed_combination[],
  int *num_well_placed_pawns,
  int *num_misplaced_pawns) {
  *num_well_placed_pawns = 0;
  *num_misplaced_pawns = 0;

  // Check for perfect match
  for (int i = 0; i < NUM_PAWNS; i++) {
    if (hidden_combination[i] == proposed_combination[i]) {
      (*num_well_placed_pawns)++;
    }
  }

  // Check for misplaced colors
  for (int i = 0; i < NUM_PAWNS; i++) {
    for (int j = 0; j < NUM_PAWNS; j++) {
      if (proposed_combination[i] == hidden_combination[j] && i != j) {
        (*num_misplaced_pawns)++;
        break; // only count each misplaced color once
      }
    }
  }
}

/* Run the game until the codebreaker guesses or reaches the limit */
void game() {
  enum color_t hidden_combination[NUM_PAWNS];
  int attempest ;
  generate_hidden_combination(hidden_combination);

  for (int attempt = 1; attempt <= NUM_ATTEMPTS; attempt++) {
    enum color_t proposed_combination[NUM_PAWNS];
    read_proposed_combination(proposed_combination);

    int num_well_placed_pawns, num_misplaced_pawns;
    evaluate_proposed_combination(hidden_combination, proposed_combination, &num_well_placed_pawns, &num_misplaced_pawns);

    printf("Feedback: %d well-placed, %d misplaced\n", num_well_placed_pawns, num_misplaced_pawns);

    if (num_well_placed_pawns == NUM_PAWNS) {
      printf("Congratulations! You cracked the code!\n");
      break;
    }
  }
int attempt;
  if (  attempt > NUM_ATTEMPTS) {
    printf("Sorry, you ran out of attempts. The hidden code was:\n");
    for (int i = 0; i < NUM_PAWNS; i++) {
      printf("%d ", hidden_combination[i]);
    }
    printf("\n");
  }
}

int main() {
  game();
  return 0;
}