/**
 * @file
 * a quick and dirty implementation of a fire effect almost identitcal to the one found here http://fabiensanglard.net/doom_fire_psx/
 * @author Thibaut Van Goethem
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

int size=514;
sf::Image fire;

/**
 * this function creates the color buffer
 * this buffer contains 36 color going from black to white
 * @return a vector of sfml colors
 */
std::vector<sf::Color> getColorBuffer(){
    std::vector<sf::Color> buffer;
    buffer.emplace_back(7,7,7);
    buffer.emplace_back(31,7,7);
    buffer.emplace_back(47,15,7);
    buffer.emplace_back(71,15,7);
    buffer.emplace_back(87,23,7);
    buffer.emplace_back(103,31,7);
    buffer.emplace_back(119,31,7);
    buffer.emplace_back(143,39,7);
    buffer.emplace_back(159,47,7);
    buffer.emplace_back(175,63,7);
    buffer.emplace_back(191,71,7);
    buffer.emplace_back(199,71,7);
    buffer.emplace_back(223,79,7);
    buffer.emplace_back(223,87,7);
    buffer.emplace_back(223,87,7);
    buffer.emplace_back(215,95,7);
    buffer.emplace_back(215,95,7);
    buffer.emplace_back(215,103,15);
    buffer.emplace_back(207,111,15);
    buffer.emplace_back(207,119,15);
    buffer.emplace_back(207,127,15);
    buffer.emplace_back(207,135,23);
    buffer.emplace_back(199,135,23);
    buffer.emplace_back(199,143,23);
    buffer.emplace_back(199,151,31);
    buffer.emplace_back(191,159,31);
    buffer.emplace_back(191,159,31);
    buffer.emplace_back(191,167,39);
    buffer.emplace_back(191,167,39);
    buffer.emplace_back(191,175,47);
    buffer.emplace_back(183,175,47);
    buffer.emplace_back(183,183,47);
    buffer.emplace_back(183,183,55);
    buffer.emplace_back(207,207,111);
    buffer.emplace_back(223,223,159);
    buffer.emplace_back(239,239,199);
    buffer.emplace_back(255,255,255);
    return buffer;
}

/**
 * this function calculates the spread of the fire for a single pixel
 * @param pixelArray the array of fire pixels
 * @param x
 * @param y
 */
void advancePixel(std::vector<std::vector<int> > & pixelArray,int x,int y){
    //2 random variables are used one to randomise the amount of decay and one to randomize the movement of the fire going up
    int rand = std::rand()%3;
    int dst = static_cast<int>(round((std::rand() % 2)));

    int targetx=x+dst;
    if(targetx>size-1)targetx-=size;
    if(y<=0) return;
    pixelArray[y-1][x]=pixelArray[y][targetx]-rand;
}

/**
 * this function calls the advancepixel method on all pixeks
 * @param pixelArray the array of fire pixels
 */
void advanceFire(std::vector<std::vector<int> > & pixelArray){
    for (int i = 0; i <size ; ++i) {
        for (int j = 0; j <size ; ++j) {
            advancePixel(pixelArray,i,j);
        }
    }
}

/**
 * this function turns an array of pixels into a sfml image
 * @param pixelArray the array of pixels
 * @param colorbuffer a vector containing sfml colors
 * @return the output from this function is given to a global variable called fire
 *          the reason for this si bevause without it sometimes colors enter the image that dont belong there
 */
void makeImageFromArray(std::vector<std::vector<int> > & pixelArray, std::vector<sf::Color> &colorbuffer){
    for (int i = 0; i <size-1 ; ++i) {
        for (int j = 0; j <size-1 ; ++j) {
            int bufferint=pixelArray[i][j];
            bufferint/=size/128;
            if(bufferint>=0&&bufferint<=36) {
                fire.setPixel(static_cast<unsigned int>(j), static_cast<unsigned int>(i), colorbuffer[bufferint]);
            }else{
                fire.setPixel(static_cast<unsigned int>(j), static_cast<unsigned int>(i), sf::Color());
            }
        }
    }
}

/**
 * main function that holds all the sfml window functionality
 */
int main() {
    fire.create(size,size);
    sf::Clock gameclock;
    sf::RenderWindow window(sf::VideoMode(size, size), "embrace the fire");
    std::vector<sf::Color> colorbuffer=getColorBuffer();

    //making the pixelArray
    std::vector<std::vector<int> > pixelArray;
    for (int i = 0; i <size-1 ; ++i) {
        std::vector<int> temp;
        for (int j = 0; j <size-1 ; ++j) {
            temp.emplace_back(0);
        }
        pixelArray.emplace_back(temp);
    }
    std::vector<int> temp;
    for (int k = 0; k <size ; ++k) {
        temp.emplace_back(colorbuffer.size()*size/128-size/128);
    }
    pixelArray.emplace_back(temp);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(gameclock.getElapsedTime().asSeconds()>0.013) {
            advanceFire(pixelArray);
            window.clear();

            makeImageFromArray(pixelArray, colorbuffer);
            sf::Texture texture;
            texture.loadFromImage(fire);
            sf::Sprite sprite;
            sprite.setTexture(texture, true);
            window.draw(sprite);
            gameclock.restart();
            window.display();
        }


    }

    return 0;
}