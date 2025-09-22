#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

vector<string> allowed_colours = {"red", "green", "yellow", "blue", "purple", "orange", "white", "black"};
vector<string> colours_to_guess;
vector<string> player_colours;
bool color_valid = 0;
int num_black_arrows = 0;
int num_white_arrows = 0;

void set_colours()
{
    for(int i = 0; i<4; i++)
    {
        // Find the random number in the range [min, max]
        int rd_colour = rand() % (allowed_colours.size() - 1);
        colours_to_guess.push_back(allowed_colours.at(rd_colour));
        cout << colours_to_guess.at(i) << "\n";
    }
}

void is_valid_colour(string input_colour)
{
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
    for(int i =0; i < colours_to_guess.size(); i++)
    {
        if(colours_to_guess.at(i) == player_colours.at(i))
        {
            num_black_arrows = num_black_arrows+1;
            cout << "Correct colour and placement: " << colours_to_guess.at(i) << " " << player_colours.at(i) << "\n";
            player_colours.at(i) = "";
        }
        
    }
    for (int i = 0; i < player_colours.size(); i++)
    {
        for (int j = 0; j < colours_to_guess.size(); j++)
        {
            if((player_colours.at(i) == colours_to_guess.at(j)) && (i!=j))
            {
                num_white_arrows = num_white_arrows + 1;
                cout << colours_to_guess.at(j) << " " << player_colours.at(i) << "\n";
                player_colours.at(i) = "";
            }
        }
        
    }
}

void add_colour_to_player_list(string single_colours)
{
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
    string colour_string;
    string single_colours;
    cout << "What colours do you think I have chosen?" << "\n";
    while(player_colours.size() < 4)
    {
        getline(cin, colour_string);
        //cout << "Colours: " << colour_string << "\n";
        string del = " "; 
        auto pos = colour_string.find(del);

        while(pos != string::npos)
        {
            single_colours = colour_string.substr(0, pos);
            add_colour_to_player_list(single_colours);
            //cout << single_colours << "\n";

            // Erase the extracted part from the
      	    // original string
            colour_string.erase(0, pos + del.length());

            // Find the next occurrence of the
      	    // delimiter
            pos = colour_string.find(del);
        }
        single_colours = colour_string;
        add_colour_to_player_list(single_colours);
    }
}

void display_results()
{
    cout << "Black arrows: " << num_black_arrows << "\n";
    cout << "White arrows: " << num_white_arrows << "\n";
}

void reset_game()
{
    num_black_arrows = 0;
    num_white_arrows = 0;
    for(int i = 0; i<player_colours.size(); i++)
    {
        player_colours.pop_back();
    }
}

void play_game()
{
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