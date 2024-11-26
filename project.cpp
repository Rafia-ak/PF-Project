#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 100
#define PLAYER_COUNT 4

typedef struct {
    int position; 
    char *icon;
} Player;

int rollDice();
void printPositions(Player players[]);
int movePlayer(int position);
void resetPositions(Player players[]);

int main() {
    Player players[PLAYER_COUNT] = {
        {0, "\U0001F981"}, {0, "\U0001F43C"}, {0, "\U0001F422"}, {0, "\U0001F98A"}
    };
    
    char replay;

    srand(time(NULL));

    do {
        resetPositions(players);

        printf("Welcome to Snakes and Ladders!\n");
        printf("Snakes and Ladders Rules:\n");
        printf("1. Goal: Reach square 100 first to win. If you overshoot, you bounce back.\n");
        printf("2. Players: \U0001F981 (Lion), \U0001F43C (Panda), \U0001F422 (Turtle), \U0001F98A (Fox).\n");
        printf("3. Turns: Roll the dice (press Enter) and move forward by the dice value.\n");
        printf("4. Ladders: \U0001F973 Climb up when landing on:\n");
        printf("   - 3 ? 22, 5 ? 8, 11 ? 26, 20 ? 29, 27 ? 74, 21 ? 82.\n");
        printf("5. Snakes: \U0001F40D Slide down when landing on:\n");
        printf("   - 17 ? 4, 19 ? 7, 54 ? 34, 62 ? 18, 87 ? 24, 93 ? 73, 95 ? 75, 98 ? 79.\n");
        printf("6. Winning: First to exactly reach 100 wins \U0001F3C6\U0001F973.\n");
        printf("Have fun! \U0001F3B2\n");

        printf("Players:\n");
        for (int i = 0; i < PLAYER_COUNT; i++) {
            printf("Player %d: %s\n", i + 1, players[i].icon);
        }

        printf("\nPress Enter to start the game...");
        getchar();

        int currentPlayer = 0;
        int winner = -1;

        while (winner == -1) {
            printf("\nPlayer %d's (%s) turn. Press Enter to roll the dice...\n", currentPlayer + 1, players[currentPlayer].icon);
            getchar();

            int dice = rollDice();
            printf("Player %d rolled a %d!\n", currentPlayer + 1, dice);

            players[currentPlayer].position += dice;

            if (players[currentPlayer].position > BOARD_SIZE) {
                players[currentPlayer].position = BOARD_SIZE - (players[currentPlayer].position - BOARD_SIZE);
                printf("Overshot the board! Player %d bounces back to %d.\n", currentPlayer + 1, players[currentPlayer].position);
            }

            players[currentPlayer].position = movePlayer(players[currentPlayer].position);

            if (players[currentPlayer].position >= BOARD_SIZE) {
                winner = currentPlayer;
                players[currentPlayer].position = BOARD_SIZE;
            }

            printPositions(players);

            currentPlayer = (currentPlayer + 1) % PLAYER_COUNT;
        }

        printf("\n\U0001F3C6\U0001F973 Congratulations! Player %d (%s) wins the game! \U0001F3C6\U0001F973\n", winner + 1, players[winner].icon);

        printf("Would you like to play again? (y/n): ");
        scanf(" %c", &replay);
        getchar();
    } while (replay == 'y' || replay == 'Y');

    printf("Thanks for playing! Goodbye.\n");
    return 0;
}

int rollDice() {
    return (rand() % 6) + 1;
}

void printPositions(Player players[]) {
    for (int i = 0; i < PLAYER_COUNT; i++) {
        printf("Player %d (%s) is on square %d\n", i + 1, players[i].icon, players[i].position);
    }
}

int movePlayer(int position) {
    switch (position) {
        case 3:  printf("\U0001F973 Ladder! Climb up to 22! \U0001F973\n"); return 22;
        case 5:  printf("\U0001F973 Ladder! Climb up to 8! \U0001F973\n");  return 8;
        case 11: printf("\U0001F973 Ladder! Climb up to 26! \U0001F973\n"); return 26;
        case 20: printf("\U0001F973 Ladder! Climb up to 29! \U0001F973\n"); return 29;
        case 27: printf("\U0001F973 Ladder! Climb up to 74! \U0001F973\n"); return 74;
        case 21: printf("\U0001F973 Ladder! Climb up to 82! \U0001F973\n"); return 82;
    }

    switch (position) {
        case 17: printf("\U0001F40D Snake! Slide down to 4! \U0001F40D\n");  return 4;
        case 19: printf("\U0001F40D Snake! Slide down to 7! \U0001F40D\n");  return 7;
        case 54: printf("\U0001F40D Snake! Slide down to 34! \U0001F40D\n"); return 34;
        case 62: printf("\U0001F40D Snake! Slide down to 18! \U0001F40D\n"); return 18;
        case 87: printf("\U0001F40D Snake! Slide down to 24! \U0001F40D\n"); return 24;
        case 93: printf("\U0001F40D Snake! Slide down to 73! \U0001F40D\n"); return 73;
        case 95: printf("\U0001F40D Snake! Slide down to 75! \U0001F40D\n"); return 75;
        case 98: printf("\U0001F40D Snake! Slide down to 79! \U0001F40D\n"); return 79;
    }

    return position;
}

void resetPositions(Player players[]) {
    for (int i = 0; i < PLAYER_COUNT; i++) {
        players[i].position = 0;
    }
}                                    