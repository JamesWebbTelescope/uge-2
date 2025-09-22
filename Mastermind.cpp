#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

vector<string> allowed_colours = {"red", "green", "yellow", "blue", "purple", "orange", "white", "black"};
vector<string> colours_to_guess;

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

using namespace std;



void main()
{
    set_colours();
}