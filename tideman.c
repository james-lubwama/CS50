#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

bool edges_away[MAX];
bool edges_towards[MAX];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_cycle(int a, int b);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }


    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // No need to perform on last place, hence candidate_count = - 1
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (j != i)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Initialise pair count
    pair_count = 0;

    for (int i = 0; i < candidate_count - 1; i++) //
    {
        for (int j = i; j < candidate_count; j++) // j =i ? or 0
        {
            if (preferences[i][j] - preferences[j][i] > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] - preferences[j][i] < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int margin[pair_count];

    for (int x = 0; x < pair_count; x++)
    {
        margin[x] = preferences[pairs[x].winner][pairs[x].loser] - preferences[pairs[x].loser][pairs[x].winner];
    }

    if (pair_count > 1)
    {
        int swaps;
        do
        {
            swaps = 0;
            for (int i = 0; i < pair_count - 1; i++)
            {
                for (int j = i + 1; j < pair_count; j++)
                {
                    if (margin[i] < margin[j])
                    {
                        pair temp = pairs[i];
                        pairs[i] = pairs[j];
                        pairs[j] = temp;
                        swaps++;

                        int temp_margin = margin[j];
                        margin[j] = margin[i];
                        margin[i] = temp_margin;
                    }
                }
            }
        }
        while (swaps != 0);
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    if (pair_count > 0)
    {
        locked[pairs[0].winner][pairs[0].loser] = true;
    }

    if (pair_count > 1)
    {
        // Starting at 2nd pair, as 1st is automatically locked in
        for (int i = 1; i < pair_count; i++)
        {
            if (check_cycle(pairs[i].winner, pairs[i].loser) == true)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }
    }

    return;
}


// Check whether adding a pair to 'locked' 2d bool array will render graph ciruitous
// a = the winner, b = the loser
bool check_cycle(int a, int b)
{
    // (Re)setting arrays with default false value
    for (int k = 0; k < MAX; k++)
    {
        edges_away[k] = false;
        edges_towards[k] = false;
    }

    // (Re)setting sources array to default false value
    bool sources[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        sources[i] = false;
    }

    int source_count = 0;

    for (int j = 0; j < candidate_count; j++)
    {
        // Edges going away/towards from node/candidate
        for (int l = 0; l < candidate_count; l++)
        {
            if (locked[j][l] == true)
            {
                edges_away[j] = true;
                edges_towards[l] = true;
            }
        }
    }

    // Increase source_count and add to sources[] if candidate has edges going away from it and none towards it
    for (int y = 0; y < candidate_count; y++)
    {
        if (edges_towards[y] == false && edges_away[y] == true)
        {
            source_count++;
            sources[y] = true;
        }
    }


    if (source_count > 1)
    {
        return true;
    }
    else if (source_count == 1 && sources[b] == true && edges_towards[a] == false)
    {
        return true;
    }
    else if (source_count == 1 && sources[b] == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Print the winner of the election
void print_winner(void)
{
    // Print the locked in 2d array
    // for (int j = 0; j < candidate_count; j++)
    // {
    //     for (int k = 0; k < candidate_count; k++)
    //     {
    //         printf("%d  ", locked[j][k]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    bool arrows_towards[candidate_count];

    for (int x = 0; x < candidate_count; x++)
    {
        arrows_towards[x] = false;
        // Record edges going towards node/candidate
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[x][i] == true)
            {
                arrows_towards[i] = true;
            }
        }
    }

    for (int y = 0; y < candidate_count; y++)
    {
        if (arrows_towards[y] == false)
        {
            printf("%s\n", candidates[y]);
        }
    }

    return;
}

