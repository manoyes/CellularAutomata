#include <SFML/Graphics.hpp>

int main()
{
    const unsigned int HOR = 192;
    const unsigned int VERT = 108;
    const unsigned int PIXELS_PER_UNIT = 10;
    sf::RenderWindow* window = new sf::RenderWindow(
        sf::VideoMode(HOR * PIXELS_PER_UNIT, VERT * PIXELS_PER_UNIT),
        "Conway's Game of Life - https://github.com/manoyes");
    // template object for drawing a cell
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(10, 10));

    bool (*grid)[VERT] = new bool[HOR][VERT];
    bool(*nextGrid)[VERT] = new bool[HOR][VERT];

    // Seed our random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize the grid
    for (int i = 0; i < HOR; i++)
    {
        for (int j = 0; j < VERT; j++)
        {
            grid[i][j] = (bool)(rand() % 2);
        }
    }

    window->setFramerateLimit(30);

    //Main loop
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        // Draw the grid
        window->clear();
        for (int i = 0; i < HOR; i++)
        {
            for (int j = 0; j < VERT; j++)
            {
                shape->setPosition((float)i * PIXELS_PER_UNIT, 
                                   (float)j * PIXELS_PER_UNIT);
                window->draw(*shape);
            }
        }
        window->display();

        // Tally the neighbors
        for (int i = 1; i < HOR - 1; i++)
        {
            for (int j = 1; j < VERT - 1; j++)
            {
                int neighborCounts = 0;

                for (int x = -1; x <= 1; x++)
                {                    
                    for (int y = -1; y <= 1; y++)
                    {
                        neighborCounts += grid[i + x][j + y];
                    }
                }

                neighborCounts -= grid[i][j];

                // If cell is alive and has fewer than two or greater than 3 
                //neighbors, OR cell is dead and has exactly 3 neighbors, 
                //invert the state. Otherwise, the state continues.
                if ((grid[i][j] && (neighborCounts < 2 || neighborCounts > 3))
                    || (!grid[i][j] && neighborCounts == 3))
                {
                    nextGrid[i][j] = !grid[i][j];
                }
                else
                {
                    nextGrid[i][j] = grid[i][j];
                }
            }
        }

        // Update the grid
        for (int i = 0; i < HOR; i++)
        {
            for (int j = 0; j < VERT; j++)
            {                
                grid[i][j] = nextGrid[i][j];
            }
        }
    }

    return 0;
}