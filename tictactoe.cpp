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

void printGrid(vector<char> grid)
{
    int length = grid.size();
    int endPositions[3] = {2, 5, 8};

    for (int x = 0; x < length; x++)
    {
        bool isEndOfGrid = std::find(std::begin(endPositions), std::end(endPositions), x) != std::end(endPositions);
        if (isEndOfGrid)
        {
            cout << grid[x] << '\n';
        }
        else
        {
            cout << grid[x];
        }
    }
}

vector<char> buildGrid()
{
    int gridSize = 9;
    vector<char> grid = {};

    for (int x = 0; x < gridSize; x++)
    {
        char separator = '-';
        grid.push_back(separator);
    }

    return grid;
}

bool validatePlayerMove(vector<char> grid, int index)
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
        char stringAtIndex = grid[index];
        char empty = '-';

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

    // ignore non integers
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "(" + name + ")" + " Enter coordinate between 1-9 :\n";
    cin >> coordinate;
    
    // subtract one so it is more human friendly
    // as opposed to indexing the grid
    return coordinate - 1;
}

vector<char> addCharacterToGrid(vector<char> grid, int gridIndex, char character)
{
    vector<char> tempGrid = grid;
    int gridWidth = grid.size() / 3 - 1;
    int endPositions[3] = {2, 5, 8};
    bool isEndOfGrid = std::find(std::begin(endPositions), std::end(endPositions), gridIndex) != std::end(endPositions);

    tempGrid[gridIndex] = character;

    return tempGrid;
}

vector<char> applyUserInput(vector<char> grid, int gridIndex, Player player)
{
    char playerCharacter = player.character;
    vector<char> tempGrid = grid;

    if (validatePlayerMove(tempGrid, gridIndex))
    {
        tempGrid = addCharacterToGrid(tempGrid, gridIndex, playerCharacter);
        return tempGrid;
    }
    else
    {
        int newIndex = -1;
        do
        {
            cout << "Invalid move.\n";
            newIndex = getMove(player);
        } while (!validatePlayerMove(tempGrid, newIndex));

        tempGrid = addCharacterToGrid(tempGrid, newIndex, playerCharacter);

        return tempGrid;
    }
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
    vector<char> grid = buildGrid();
    int numMoves = 0;
    Player player1 = getPlayer1();
    Player player2 = getPlayer2();

    while (numMoves < 9)
    {
        Player currentPlayer = getCurrentPlayer(numMoves, player1, player2);
        int moveIndex = getMove(currentPlayer);

        vector<char> newGrid = applyUserInput(grid, moveIndex, currentPlayer);
        printGrid(newGrid);

        grid = newGrid;
        numMoves++;
    }

    return 0;
}