#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>

#define BITBOARD unsigned long long 

void drawBoard(BITBOARD board, sf::Sprite ** table, sf::RenderWindow &window)
{
	BITBOARD shift = 0x0000000000000001;
	int bitNbr = 0;
	while (board!=0)
	{
		if ((shift&board) != 0)
		{
			//if bit is set then:
			window.draw(*table[bitNbr]);
		}
		board = board >> 1;
		bitNbr += 1;
	}
	
}

void createPieces(sf::Sprite ** table)
{
	for(int x = 0; x<64 ;x++)
	{
	table[x] = new sf::Sprite;
	}
}

void setPieces(const char * filename, sf::Texture &tex,sf::Sprite ** table)
{
	if(!tex.loadFromFile(filename))
	{
		std::cout<<"Unable to load texture! \n";
	}

	for(int x = 0; x<64 ;x++)
	{
	table[x]->setTexture(tex);
	}
	
	int o = 0;
	int u = 350;
	for(int y = 0; y<64 ;y=y+8)
	{
		o=0;
		for(int x = y; x<y+8; x++)
		{
			
		table[x]->setPosition(o,u);
		o+=50;

		}
	u=u-50;
	}
}

int main()
{
    sf::RenderWindow window( sf::VideoMode( 400, 400 ), "REVERSI" );

	std::string filename_black = "black1.png";
	std::string filename_white = "white1.png";

	sf::Texture black_texture;
	sf::Texture white_texture;
	sf::Texture board_texture;

	sf::Sprite ** black_table = new sf::Sprite*[64];
	sf::Sprite ** white_table = new sf::Sprite*[64];
	sf::Sprite boardImage;

	if(!board_texture.loadFromFile("board1.png"))
		std::cout<<"Unable to load board_texture \n";
	boardImage.setTexture(board_texture);

	createPieces(black_table);
	createPieces(white_table);
	setPieces(filename_black.c_str(),black_texture, black_table);
	setPieces(filename_white.c_str(),white_texture, white_table);

	BITBOARD START_POSITION_white = 0x810000000;
	BITBOARD START_POSITION_black = 0x1008000000;


    while( window.isOpen() )
    {
        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
			{
                 window.close();
			}
           
        } 
        //window.clear();
		window.draw(boardImage);
		/*
		
		window.draw(*black_table[0]);
		window.draw(*black_table[1]);
		window.draw(*black_table[2]);
		window.draw(*black_table[3]);
		window.draw(*black_table[4]);
		window.draw(*black_table[5]);
		window.draw(*black_table[6]);
		window.draw(*black_table[7]);
		window.draw(*black_table[8]);
		window.draw(*black_table[9]);
		window.draw(*black_table[10]);
		window.draw(*black_table[11]);
		window.draw(*black_table[12]);
		window.draw(*black_table[13]);
		window.draw(*black_table[14]);
		window.draw(*black_table[15]);
		window.draw(*black_table[16]);
		window.draw(*black_table[17]);
		window.draw(*black_table[18]);
		window.draw(*black_table[19]);
		window.draw(*black_table[20]);
		window.draw(*black_table[21]);
		window.draw(*black_table[22]);
		window.draw(*black_table[23]);
		window.draw(*black_table[24]);
		window.draw(*black_table[25]);
		window.draw(*black_table[26]);
		window.draw(*black_table[27]);
		window.draw(*black_table[28]);
		window.draw(*black_table[29]);
		window.draw(*black_table[30]);
		window.draw(*black_table[31]);
		window.draw(*black_table[32]);
		window.draw(*black_table[33]);
		window.draw(*black_table[34]);
		window.draw(*black_table[35]);
		window.draw(*black_table[36]);
		window.draw(*black_table[37]);
		window.draw(*black_table[38]);
		window.draw(*black_table[39]);
		window.draw(*black_table[40]);
		window.draw(*black_table[41]);
		window.draw(*black_table[42]);
		window.draw(*black_table[43]);
		window.draw(*black_table[44]);
		window.draw(*black_table[45]);
		window.draw(*black_table[46]);
		window.draw(*black_table[47]);
		window.draw(*black_table[48]);
		window.draw(*black_table[49]);
		window.draw(*black_table[50]);
		window.draw(*black_table[51]);
		window.draw(*black_table[52]);
		window.draw(*black_table[53]);
		window.draw(*black_table[54]);
		window.draw(*black_table[55]);
		window.draw(*black_table[56]);
		window.draw(*black_table[57]);
		window.draw(*black_table[58]);
		window.draw(*black_table[59]);
		window.draw(*black_table[60]);
		window.draw(*black_table[61]);
		window.draw(*black_table[62]);
		window.draw(*black_table[63]);
		*/
		/*
		window.draw(*white_table[0]);
		window.draw(*white_table[1]);
		window.draw(*white_table[2]);
		window.draw(*white_table[3]);
		window.draw(*white_table[4]);
		window.draw(*white_table[5]);
		window.draw(*white_table[6]);
		window.draw(*white_table[7]);
		window.draw(*white_table[8]);
		window.draw(*white_table[9]);
		window.draw(*white_table[10]);
		window.draw(*white_table[11]);
		window.draw(*white_table[12]);
		window.draw(*white_table[13]);
		window.draw(*white_table[14]);
		window.draw(*white_table[15]);
		window.draw(*white_table[16]);
		window.draw(*white_table[17]);
		window.draw(*white_table[18]);
		window.draw(*white_table[19]);
		window.draw(*white_table[20]);
		window.draw(*white_table[21]);
		window.draw(*white_table[22]);
		window.draw(*white_table[23]);
		window.draw(*white_table[24]);
		window.draw(*white_table[25]);
		window.draw(*white_table[26]);
		window.draw(*white_table[27]);
		window.draw(*white_table[28]);
		window.draw(*white_table[29]);
		window.draw(*white_table[30]);
		window.draw(*white_table[31]);
		window.draw(*white_table[32]);
		window.draw(*white_table[33]);
		window.draw(*white_table[34]);
		window.draw(*white_table[35]);
		window.draw(*white_table[36]);
		window.draw(*white_table[37]);
		window.draw(*white_table[38]);
		window.draw(*white_table[39]);
		window.draw(*white_table[40]);
		window.draw(*white_table[41]);
		window.draw(*white_table[42]);
		window.draw(*white_table[43]);
		window.draw(*white_table[44]);
		window.draw(*white_table[45]);
		window.draw(*white_table[46]);
		window.draw(*white_table[47]);
		window.draw(*white_table[48]);
		window.draw(*white_table[49]);
		window.draw(*white_table[50]);
		window.draw(*white_table[51]);
		window.draw(*white_table[52]);
		window.draw(*white_table[53]);
		window.draw(*white_table[54]);
		window.draw(*white_table[55]);
		window.draw(*white_table[56]);
		window.draw(*white_table[57]);
		window.draw(*white_table[58]);
		window.draw(*white_table[59]);
		window.draw(*white_table[60]);
		window.draw(*white_table[61]);
		window.draw(*white_table[62]);
		window.draw(*white_table[63]);
		*/
		
	
	
	drawBoard(START_POSITION_black, black_table, window);
	drawBoard(START_POSITION_white, white_table, window);
	
		window.display();
		

    } 
    return 0;
}