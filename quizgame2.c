#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct question {
    char text[999];
    char opt[4][100];
    int ans;
};

struct player {
    char name[100];
    int score;
};

void show(struct question q) {
    printf("%s\n", q.text);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, q.opt[i]);
    }
}

int playQuiz(struct question base[], int total) {
    struct question q[50];
    for (int i = 0; i < total; i++) q[i] = base[i];

    int score = 0;
    int remain = total;

    for (int i = 0; i < total; i++) {
        int r = rand() % remain;
        struct question cur = q[r];
        show(cur);

        int user;
        printf("Enter your answer (1-4): ");
        scanf("%d", &user);

        if (user == cur.ans) {
            printf("Correct!\n\n");
            score++;
        } else if (user >= 1 && user <= 4) {
            printf("Wrong! Correct answer is %d. %s\n\n",
                   cur.ans, cur.opt[cur.ans - 1]);
        } else {
            printf("Invalid input. Please enter between 1-4.\n\n");
        }

        q[r] = q[remain - 1];
        remain--;
    }

    return score;
}

int main() {
    srand(time(NULL));

    struct question qs[5] = {
        {"In which year was thrustMIT founded or started?",
         {"2014", "2015", "2016", "2017"}, 3},
        {"What competition did thrustMIT participate in where their 2025 project reached an apogee of 29,432 ft?",
         {"Spaceport America Cup", "International Rocket Engineering Competition", "NASA Student Launch Challenge", "Rocketry India League"}, 2},
        {"Which of the following is not one of the listed subsystems of thrustMIT on their website?",
         {"Aerodynamics", "Avionics", "Structures", "Cryogenics"}, 4},
        {"Which project from thrustMIT in 2024 was the first Indian student-group built 30K ft-class sounding rocket?",
         {"VYOM", "PHOENIX", "AGNIASTRA", "ALTAIR"}, 3},
        {"Which of the following best describes thrustMIT's primary mission?",
         {"To promote satellite communication research in India",
          "To design and launch high-powered rockets and advance student rocketry in India",
          "To manufacture drones for defense applications",
          "To develop reusable spacecraft for commercial use"}, 2}
    };

    printf("Welcome to the Quiz Game!\n\n");

    int n;
    printf("How many players? ");
    scanf("%d", &n);  // user directly enters number of players

    struct player p[20];
    for (int i = 0; i < n; i++) {
        printf("Enter player %d name (no spaces): ", i + 1);
        scanf("%s", p[i].name);
        p[i].score = 0;
    }

    int total = 5;
    for (int i = 0; i < n; i++) {
        printf("\n--- %s's turn ---\n\n", p[i].name);
        p[i].score = playQuiz(qs, total);
        printf("%s scored %d/%d\n", p[i].name, p[i].score, total);
    }

    printf("\n=== Scoreboard ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d) %s : %d/%d\n", i + 1, p[i].name, p[i].score, total);
    }

    return 0;
}