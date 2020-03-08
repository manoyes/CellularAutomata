#include <SFML/Graphics.hpp>
#include <array>

int main()
{
    const int HOR = 192;
    const int VERT = 108;
    const float PIXELS_PER_UNIT = 10.0f;    
    sf::RenderWindow window(sf::VideoMode(HOR * PIXELS_PER_UNIT, VERT * PIXELS_PER_UNIT), "Conway's Game of Life - https://github.com/manoyes");
    sf::RectangleShape* viewGrid[HOR][VERT];
    int neighborCounts[HOR][VERT];
    int grid[HOR][VERT];

    srand(time(NULL));

    // Initialize the grid
    for (int i = 0; i < HOR; i++)
    {
        for (int j = 0; j < VERT; j++)
        {
            grid[i][j] = rand() % 2;
            sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(10, 10));
            shape->setFillColor((grid[i][j] == 0 ? sf::Color::Black : sf::Color::White));
            shape->setPosition(i * PIXELS_PER_UNIT, j * PIXELS_PER_UNIT);
            viewGrid[i][j] = shape;
            neighborCounts[i][j] = 0;
        }
    }

    window.setFramerateLimit(30);

    //Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        // Draw the grid
        for (int i = 0; i < HOR; i++)
        {
            for (int j = 0; j < VERT; j++)
            {
                window.draw(*viewGrid[i][j]);
            }
        }

        window.display();

        // Tally the neighbors
        for (int i = 1; i < HOR - 1; i++)
        {
            for (int j = 1; j < VERT - 1; j++)
            {
                neighborCounts[i][j] = 0;

                for (int x = -1; x <= 1; x++)
                {                    
                    for (int y = -1; y <= 1; y++)
                    {
                        neighborCounts[i][j] += grid[i + x][j + y];
                    }
                }

                neighborCounts[i][j] -= grid[i][j];       
            }
        }

        // Update the grid
        for (int i = 0; i < HOR; i++)
        {
            for (int j = 0; j < VERT; j++)
            {
                if (grid[i][j] == 1 && (neighborCounts[i][j] < 2 || neighborCounts[i][j] > 3))
                {
                    grid[i][j] = 0;
                }
                else if (grid[i][j] == 0 && neighborCounts[i][j] == 3)
                {
                    grid[i][j] = 1;
                }

                viewGrid[i][j]->setFillColor((grid[i][j] == 0 ? sf::Color::Black : sf::Color::White));
                //viewGrid[i][j]->setFillColor((rand() % 2 == 0 ? sf::Color::Black : sf::Color::White));
            }
        }
    }

    return 0;
}