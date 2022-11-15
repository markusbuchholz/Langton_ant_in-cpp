#include <iostream>
#include <thread>
#include <chrono>
#include <tuple>
#include <Eigen/Dense>

// (column, row)

std::tuple<int, int> direction(int xy)
{

    if (xy == 1)
    {
        return std::make_tuple(0, -1);
    }
    if (xy == 2)
    {
        return std::make_tuple(1, 0);
    }
    if (xy == 3)
    {
        return std::make_tuple(0, 1);
    }
    // xy == 4
    return std::make_tuple(-1, 0);
}

std::tuple<Eigen::Matrix<char, 50, 50>, int, int, int> applyAntRules(std::tuple<Eigen::Matrix<char, 50, 50>, int, int, int> &antGame)
{

    Eigen::Matrix<char, 50, 50> life = std::get<0>(antGame);
    int xX = std::get<1>(antGame);
    int yY = std::get<2>(antGame);
    int dirXY = std::get<3>(antGame);

    int antX = std::get<0>(direction(dirXY));
    int antY = std::get<1>(direction(dirXY));

    if (life(xX, yY) == ' ')
    {

        life(xX, yY) = '*';
        xX = xX + antX;
        yY = yY + antY;
        dirXY = dirXY % 4 + 1;
    }

    if (life(xX, yY) == '*')
    {

        life(xX, yY) = ' ';
        xX = xX + antX;
        yY = yY + antY;
        dirXY = dirXY % 4 - 1;
        if (dirXY == -1)
        {
            dirXY = 3;
        }
    }

    return std::make_tuple(life, xX, yY, dirXY);
}

int main()
{
    Eigen::Matrix<char, 50, 50> Game;
    int antX = 25;
    int antY = 25;
    int direction = 4;

    for (int ii = 0; ii < Game.rows(); ii++)
    {
        for (int jj = 0; jj < Game.cols(); jj++)
        {
            Game(ii, jj) = ' ';
        }
    }

    Game(antX, antY) = ' ';

    std::tuple<Eigen::Matrix<char, 50, 50>, int, int, int> antGame = std::make_tuple(Game, antX, antY, direction);

    for (int ii = 0; ii < 10000; ii++)
    {
        if (std::get<1>(antGame) <= 1 || std::get<1>(antGame) > 49 || std::get<2>(antGame) <= 1 || std::get<2>(antGame) > 49)
        {
            std::cout << "GAME OVER"
                      << "\n";
            return 0;
        }
        std::tuple<Eigen::Matrix<char, 50, 50>, int, int, int> next_antGame = applyAntRules(antGame);

        Eigen::Matrix<char, 50, 50> life = std::get<0>(next_antGame);

        system("clear");
        std::cout << life << "\n";
        antGame = next_antGame;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}