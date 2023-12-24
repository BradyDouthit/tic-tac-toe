#include <iostream>
#include <vector>
#include <string>

using namespace std;
using std::cin;
using std::cout;

class Player
{
public:
    char character;
    string nickname;
};

void printGrid(vector<string> grid)
{
    int length = grid.size();

    for (int x = 0; x < length; x++)
    {
        cout << grid[x];
    }
}

vector<string> buildGrid()
{
    const int gridSizeX = 3;
    const int gridSizeY = 3;

    vector<string> grid = {};

    for (int x = 0; x < gridSizeX; x++)
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            if (y == gridSizeY - 1)
            {
                string separator = "-\n";
                grid.push_back(separator);
            }
            else
            {
                string separator = "-";
                grid.push_back(separator);
            }
        }
    }

    return grid;
}

bool validatePlayerMove(vector<string> grid, int index)
{
    if (index > grid.size())
    {
        return false;
    }

    if (index < 0)
    {
        return false;
    }
    else
    {
        string stringAtIndex = grid[index];
        string empty = "-";

        // remove newlines from the grid at index position
        stringAtIndex.erase(remove(stringAtIndex.begin(), stringAtIndex.end(), '\n'), stringAtIndex.end());
        bool positionIsEmpty = stringAtIndex == empty;

        if (!positionIsEmpty)
        {
            return false;
        }
    }

    return true;
}

int getMove(Player currentPlayer)
{
    string name = currentPlayer.nickname;
    int coordinate;

    cout << "(" + name + ")" + " Enter coordinate between 1-9 :\n";
    cin >> coordinate;

    // subtract one so it is more human friendly
    // as opposed to indexing the grid
    return coordinate - 1;
}

vector<string> addCharacterToGrid(vector<string> grid, int gridIndex, char character)
{
    vector<string> tempGrid = grid;
    int gridWidth = grid.size() / 3 - 1;
    int endPositions[3] = {2, 5, 8};
    bool isEndOfGrid = std::find(std::begin(endPositions), std::end(endPositions), gridIndex) != std::end(endPositions);

    if (isEndOfGrid)
    {
        tempGrid[gridIndex] = character + "\n";
    }
    else
    {
        tempGrid[gridIndex] = character;
    }

    return tempGrid;
}

vector<string> applyUserInput(vector<string> grid, int gridIndex, Player player)
{
    char playerCharacter = player.character;
    vector<string> tempGrid = grid;

    if (validatePlayerMove(tempGrid, gridIndex))
    {
        tempGrid = addCharacterToGrid(tempGrid, gridIndex, playerCharacter);
    }
    else
    {
        int newIndex = -1;

        while (!validatePlayerMove(tempGrid, newIndex))
        {
            cout << "Invalid move. Enter a new number\n";
            newIndex = getMove(player);
        }

        tempGrid = addCharacterToGrid(tempGrid, newIndex, playerCharacter);
    }

    return tempGrid;
}

Player getPlayer1()
{
    string nickname;
    char character;

    Player player1;

    cout << "Enter a nickname for player 1:\n";
    cin >> nickname;

    cout << "Enter a character to represent player 1:\n";
    cin >> character;

    player1.nickname = nickname;
    player1.character = character;

    return player1;
}

Player getPlayer2()
{
    string nickname;
    char character;

    Player player2;

    cout << "Enter a nickname for player 2:\n";
    cin >> nickname;

    cout << "Enter a character to represent player 2:\n";
    cin >> character;

    player2.nickname = nickname;
    player2.character = character;

    return player2;
}

Player getCurrentPlayer(int numMoves, Player player1, Player player2)
{
    if (numMoves % 2 == 0)
    {
        return player1;
    }

    return player2;
}

int main()
{
    vector<string> grid = buildGrid();
    int numMoves = 0;
    Player player1 = getPlayer1();
    Player player2 = getPlayer2();

    while (numMoves < 9)
    {
        Player currentPlayer = getCurrentPlayer(numMoves, player1, player2);
        int moveIndex = getMove(currentPlayer);

        vector<string> newGrid = applyUserInput(grid, moveIndex, currentPlayer);
        printGrid(newGrid);

        grid = newGrid;
        numMoves++;
    }

    return 0;
}