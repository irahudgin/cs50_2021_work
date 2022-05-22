#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Determines if name is matched
    int cvar = 0;
    int rankind;
    for (int i = 0; i < candidate_count; i++)
        {
            // If name is a valid candidate, cvar is non zero
            if (strcmp(name, candidates[i].name) == 0)
               {
                    cvar++;
                    rankind = i;
               }
        }

        // If cvar is zero, name doesnt correspond to a candidate and must be redone
        if (cvar == 0)
            {
                return false;
            }

    // Updating preference array for each voter with the rank index variable "rankind"
    preferences[voter][rank] = rankind;

    // Need to make sure that voter cant choose same person twice - maybe work into preferences updating?
    if (rank == 0)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < rank; i++)
        {
            if ((preferences[voter][i + 1]) == (preferences[voter][i]))
            {
                printf("Candidate already ranked\n");
                return false;
            }
        }
    }



    return true;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO

    // Adds top pick vote to candidates.vote
    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[preferences[i][0]].eliminated == true)
        {
            for (int j = 1; j < candidate_count; j++)
            {
                if (candidates[preferences[i][j]].eliminated == false)
                {
                    candidates[preferences[i][j]].votes++;
                    break;
                }
            }
        continue;
        }
        
        candidates[preferences[i][0]].votes++;
    }

}

// Print the winner of the election, if there is one
bool print_winner(void)
{

    // Find total votes
    // (Number of total votes / 2) + 1 is needed to win
    // If any candidate has this many votes or more they win
    // Else return false

    int votetowin = (voter_count / 2) + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= votetowin)
        {
            printf("%s\n", candidates[i].name);
            return true;
        
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Loop candidates struct
    // Sort through candidates.votes of which have not been eliminated to find smallest number
    // return that number
    
    int minvotes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            continue;
        }
        else if (candidates[i].votes <= minvotes )
        {
            minvotes = candidates[i].votes;
        }
    }

    return minvotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // if election is a tie, all candidates will have min votes
    // index through candidates.votes
    // for every i check if candidates.votes is equal to min
    // If it is, add counter to variable
    // if counter variable at the end = candidate_count then the election is a tie, and return true,
    // else return false
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            continue;
        }
        if (candidates[i].votes != min)
        {
            return false;
        }
    }
    
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Go through candidates
    // For every candidate compare candidate.vote with min
    // if candidate.vote == min, the candidate.eliminated is updated to true
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
