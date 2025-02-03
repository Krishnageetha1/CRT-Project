#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct candidates {
    char cname[20];
    int vote;
};

struct candidates c[100];
int can;
int vot;

struct voters {
    char name[20];
    char id[20];
    char password[20];
    int voted;
};

struct voters v[100];

void addcandidates(int);
void viewcandidates();
void registervoters();
void viewvoters();
void castvoting();
int verifyvote(int);

void addcandidates(int a) {
    can = a;
    for (int i = 0; i < can; i++) {
        printf("Enter Candidate %d Name: ", i + 1);
        scanf("%s", c[i].cname);
        c[i].vote = 0;
    }
}

void viewcandidates() {
    for (int i = 0; i < can; i++) {
        printf("Candidate %d: %s\n", i + 1, c[i].cname);
    }
}

void registervoters() {
    char tid[20];
    printf("Enter the number of voters: ");
    scanf("%d", &vot);
    for (int i = 0; i < vot; i++) {
        printf("Enter name of voter %d: ", i + 1);
        scanf("%s", v[i].name);

        int uniqueID = 1;
        while (uniqueID) {
            printf("Enter ID of voter %d: ", i + 1);
            scanf("%s",tid);
            uniqueID = 0;
            for (int j = 0; j < vot; j++) {
                if (strcmp(v[j].id, tid) == 0) {
                    printf("This ID already exists, give a new unique ID\n");
                    uniqueID = 1;
                    break;
                }
            }
        }

        strcpy(v[i].id, tid);  // Store the unique ID
        printf("Enter password of voter %d: ", i + 1);
        scanf("%s", v[i].password);
        v[i].voted = 0;
    }
}

void viewvoters() {
    for (int i = 0; i < vot; i++) {
        printf("Voter %d - Name: %s, ID: %s\n", i + 1, v[i].name, v[i].id);
    }
}

int verifyvote(int q) {
    if (v[q].voted == 0) {
        v[q].voted = 1;
        return 0;  // Voter can vote
    }
    return 1;  // Voter already voted
}

void castvoting() {
    if (vot == 0) {
        printf("No registered voters. Please register first!\n");
        return;
    }

    char idd[20], p[20];
    int chk = -1;

    printf("Enter your ID: ");
    scanf("%s", idd);

    for (int i = 0; i < vot; i++) {
        if (strcmp(idd, v[i].id) == 0) {
            chk = i;
            break;
        }
    }

    if (chk == -1) {
        printf("Invalid voter ID!\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", p);

    if (strcmp(p, v[chk].password) != 0) {
        printf("Incorrect password!\n");
        return;
    }

    if (verifyvote(chk) == 1) {
        printf("Already voted! Cannot vote again.\n");
        return;
    }

    printf("Choose a candidate to vote for:\n");
    for (int i = 0; i < can; i++) {
        printf("%d. %s\n", i + 1, c[i].cname);
    }

    int cast;
    printf("Enter your choice: ");
    if (scanf("%d", &cast) != 1 || cast < 1 || cast > can) {
        printf("Invalid input! Please select a valid candidate.\n");
        return;
    }

    c[cast - 1].vote++;
    printf("Vote cast successfully!\n");
}

void displayResults() {
    printf("\nVoting Results:\n");
    int winnerIndex = 0;

    for (int i = 0; i < can; i++) {
        printf("%s - %d votes\n", c[i].cname, c[i].vote);
        if (c[i].vote > c[winnerIndex].vote) {
            winnerIndex = i;
        }
    }

    printf("\nThe winner is: %s with %d votes!\n", c[winnerIndex].cname, c[winnerIndex].vote);
}

int main() {
    int choice, mid;
    while (1) {
        printf("\nCandidate & Voter Management System:\n");
        printf("1. Manage Candidates\n2. Manage Voters\n3. Start Voting\n4. Display Results\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                while (1) {
                    printf("\n1. Add Candidates\n2. View Candidates\n3. Back\n");
                    printf("Enter your choice: ");
                    scanf("%d", &mid);
                    if (mid == 1) {
                        printf("Enter number of candidates: ");
                        scanf("%d", &can);
                        addcandidates(can);
                    } else if (mid == 2) {
                        viewcandidates();
                    } else {
                        break;
                    }
                }
                break;
            
            case 2:
                while (1) {
                    printf("\n1. Register Voters\n2. View Voters\n3. Back\n");
                    printf("Enter your choice: ");
                    scanf("%d", &mid);
                    if (mid == 1) {
                        registervoters();
                    } else if (mid == 2) {
                        viewvoters();
                    } else {
                        break;
                    }
                }
                break;

            case 3:
                castvoting();
                break;

            case 4:
                displayResults();
                break;

            case 5:
                printf("Thank you for using the system!\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
