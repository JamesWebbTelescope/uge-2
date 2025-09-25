#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <limits>

using namespace std;

vector<string> allowed_colours = {"red", "green", "yellow", "blue", "purple", "orange", "white", "black"}; //The list of colours the player can choose from
vector<string> colours_to_guess; //The list of colours chosen by the computer.
vector<string> player_colours; //The colours chosen by the player. This list is reset after eaach turn.
bool color_valid = 0; //Flag used to indicate whether the colors the player gives are valid or not.
int num_black_arrows = 0; //The number of places where the player gets both colour and placement right.
int num_white_arrows = 0; //The number of correct colours, but where the placement is wrong.

void set_colours() //This function is where the computer decides which colours to use.
{
    for(int i = 0; i<4; i++)
    {
        /* The function uses a random number generator going from index 0 to the highest possible index
        to pick four colours for the player to guess
         */
        int min = 0;
        int max = allowed_colours.size()-1;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(min, max);
        int rd_colour = distrib(gen);
        colours_to_guess.push_back(allowed_colours.at(rd_colour));
    }
}

void is_valid_colour(string input_colour)
{
    /*
    This function checks whether the colour inputted by the player is a valid colour.
    It uses the color_valid flag to indicate whether it is or isn't an allowed colour.
    If it is allowed, color_valid = 1.
    If it is not, color_valid = 0.
    */
    for(int i = 0; i < allowed_colours.size(); i++)
    {
        if (input_colour == allowed_colours.at(i))
        {
            color_valid = 1;
            break;
        }
        else
        {
            color_valid = 0;
        }
    }
}

void check_colours()
{
    /*
    This is where the game tries to match the player's inputs to the computer's chosen colours.
    First, it goes through the entire vector of player colors to see whether they match the computer's colours at the given index.
    If they do match, the number of black arrows is incremented by 1 and the player colour is removed.
    We remove it to avoid the same colour being matched more than once.
    Next, the game goes through the vector of player colours again, this time to see whether the colour matches any of the computer's colours,
    NOT at the same index.
    If there is a match, the number of white arrows is incremented by 1.
    Similarly, if there is a match, the player colour is removed to avoid it being matched more than once.
    */
    for(int i =0; i < player_colours.size(); i++)
    {
        for (int j = 0; j < colours_to_guess.size(); j++)
        {
            if((player_colours.at(i) == colours_to_guess.at(j)) && (i==j)) //If both the color and the placement is correct
            {
                num_black_arrows = num_black_arrows+1;
                player_colours.at(i) = "";
            }
        }
        
    }
    for (int i = 0; i < player_colours.size(); i++)
    {
        for (int j = 0; j < colours_to_guess.size(); j++)
        {
            if((player_colours.at(i) == colours_to_guess.at(j)) && (i!=j)) //If the color is correct, but the placement isn't
            {
                num_white_arrows = num_white_arrows + 1;
                player_colours.at(i) = "";
            }
        }
        
    }
}

void add_colour_to_player_list(string single_colours)
{
    /*
    This function is where the game takes single colours and check whether they're allowed colours.
    If not, it keeps prompting the player to give a valid colour until it gets a valid colour.
    */
    string new_colour;
    is_valid_colour(single_colours);
    if(color_valid == 1)
    {
        player_colours.push_back(single_colours);
    }
    else
    {
        while (color_valid == 0) //Keep prompting the user until he gives a valid colour
        {
            cout << single_colours << " is not a valid colour" << "\n";
            cout << "Please give valid color" << "\n";
            cin >> new_colour;
            is_valid_colour(new_colour);
            if(color_valid == 1)
            {
                player_colours.push_back(new_colour);
                break;
            }
        }
    }
}

void input_colours() //This function is for receiving the input colurs from the player
{
    /*
    What happens in this function is that first of all, it prints out the list of allowed colours for the game.
    It then prompts the user to give a set of four colours as a space-separated list.
    The string is received by the game and split into individual colours, that are then checked and added to the list of player colours.
    */
    string colour_string;
    string single_colours;
    cout << "List of possible colours: ";
    for (int i = 0; i < allowed_colours.size(); i++)
    {
        cout << allowed_colours.at(i) << " ";
    }
    cout << "\n";
    
    cout << "What colours do you think I have chosen?" << "\n";
    while(player_colours.size() < 4)
    {
        getline(cin, colour_string);
        string del = " "; 
        auto pos = colour_string.find(del);

        while(pos != string::npos)
        {
            single_colours = colour_string.substr(0, pos);
            add_colour_to_player_list(single_colours);
            colour_string.erase(0, pos + del.length());

            pos = colour_string.find(del);
        }
        single_colours = colour_string;
        add_colour_to_player_list(single_colours);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clear the input stream buffer after the colours have been given and verified.
    }
    
}

void display_results()
{
    /*
    This function simply displays the results of the player guesses.
    */
    cout << "Black arrows: " << num_black_arrows << "\n";
    cout << "White arrows: " << num_white_arrows << "\n";
}

void reset_game()
{
    /*
    This function resets the number of black and white arrows and clears the player's list of chosen colours,
    so that it is ready for the next turn.
    */
    num_black_arrows = 0;
    num_white_arrows = 0;
    while (player_colours.empty() == 0)
    {
        player_colours.pop_back();
    }
}

void play_game()
{
    /*
    This is the function that actually runs the game.
    First, the computer sets the colours to be guessed.
    Then, the player gets prompted to give a list of four space-separated colours.
    After that, the game checks how many colours are correct and in the correct place.
    For each correct colour and placement, the player gets one black arrow.
    Then the game checks for how many colours are correct, but in the wrong place. For each of these, the player gets one white arrow.
    If the player guesses all four colours and their placement, he wins the game.
    But if he spends more than 12 turns on it, he loses.
    At the end of each turn, the number of black and white arrows are reset, as well as the list of player colours
    */
    set_colours();
    int turns = 0;
    while ((turns < 12) && (num_black_arrows < 4))
    {
        turns = turns+1;
        input_colours();
        check_colours();
        display_results();
        if (num_black_arrows == 4)
        {
            cout << "Congratulations! You've guessed all the colours!" << "\n";
            break;
        }
        if (turns == 12)
        {
            cout << "Sorry! You've used up all your turns! Game over!" << "\n";
            break;
        }
        reset_game();
    }
}


void main()
{
    play_game();
}
