#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <list>

#define BITBOARD unsigned long long 

BITBOARD showMyValidMoves(BITBOARD myBoard, BITBOARD opponentBoard)
{
	
	BITBOARD all = myBoard | opponentBoard;
	BITBOARD empty = ~all;
	BITBOARD downMask = 0xFFFFFFFFFFFFFF;
	BITBOARD upMask = 0xFFFFFFFFFFFFFF00;
	BITBOARD rightMask = 0xFEFEFEFEFEFEFEFE;
	BITBOARD leftMask = 0x7F7F7F7F7F7F7F7F;

	BITBOARD validMoves1 = 0UL, validMoves2 = 0UL, validMoves3 = 0UL, validMoves4 = 0UL, validMoves5 = 0UL, validMoves6 = 0UL, validMoves7 = 0UL, validMoves8 = 0UL;
	
	// DOWN
	BITBOARD potentialMoves1 = (myBoard >> 8) & downMask & opponentBoard;
	while (potentialMoves1 != 0UL)
	{
		BITBOARD tmp1 = (potentialMoves1 >> 8) & downMask;
		validMoves1 = validMoves1| (tmp1&empty);
		potentialMoves1=tmp1&opponentBoard;	
	}
	//UP
	BITBOARD potentialMoves2 = (myBoard << 8) & upMask & opponentBoard ;
	while (potentialMoves2 != 0x0000000000000000)
	{	
		BITBOARD tmp = (potentialMoves2 << 8) & upMask; 
		validMoves2 = validMoves2|(tmp&empty);
		potentialMoves2 = tmp&opponentBoard;
	}
	//LEFT
	BITBOARD potentialMoves3 = (myBoard >> 1) & leftMask & opponentBoard;
	while (potentialMoves3 != 0x0000000000000000)
	{
		BITBOARD tmp = (potentialMoves3 >> 1) & leftMask;
		validMoves3 = validMoves3|(tmp&empty);
		potentialMoves3 = tmp & opponentBoard;
	}
	//RIGHT
	BITBOARD potentialMoves4 = (myBoard << 1) & rightMask & opponentBoard;
	while (potentialMoves4 != 0x0000000000000000)
	{
		BITBOARD tmp = (potentialMoves4 << 1) & rightMask ;
		validMoves4 = validMoves4 | (tmp&empty);
		potentialMoves4 = tmp & opponentBoard;
	}
	//UPRIGHT
	BITBOARD potentialMoves5 = (myBoard << 9) & rightMask & upMask & opponentBoard;
	while (potentialMoves5 != 0x0000000000000000)
	{
		BITBOARD tmp = (potentialMoves5 << 9) & rightMask & upMask;
		validMoves5 = validMoves5 | (tmp&empty);
		potentialMoves5 = tmp & opponentBoard;
	}
	//UPLEFT
	BITBOARD potentialMoves6 = (myBoard << 7) & leftMask & upMask & opponentBoard;
	while (potentialMoves6 != 0x0000000000000000)
	{
		BITBOARD tmp = (potentialMoves6 << 7) & leftMask & upMask;
		validMoves6 = validMoves6 | (tmp&empty);
		potentialMoves6 = tmp & opponentBoard;
	}
	//DOWNLEFT
	BITBOARD potentialMoves7 = (myBoard >> 9) & leftMask & downMask & opponentBoard;
	while (potentialMoves7 != 0x0000000000000000)
	{
		BITBOARD tmp = (potentialMoves7 >> 9) & leftMask&downMask;
		validMoves7 = validMoves7 | (tmp&empty);
		potentialMoves7 = tmp & opponentBoard;
	}
	//DOWNRIGHT
	BITBOARD potentialMoves8 = (myBoard >> 7) & rightMask & downMask & opponentBoard;
	while (potentialMoves8 != 0x0000000000000000)
	{
		BITBOARD tmp = (potentialMoves8 >> 7) & rightMask&downMask;
		validMoves8 = validMoves8 | (tmp&empty);
		potentialMoves8 = tmp & opponentBoard;
	}

	BITBOARD allValidMoves = validMoves1| validMoves2 | validMoves3 | validMoves4| validMoves5 | validMoves6 | validMoves7 | validMoves8;
	return allValidMoves;
}

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
	std::string filename_black_s = "black_s.png";
	std::string filename_white_s = "white_s.png";

	sf::Texture black_texture;
	sf::Texture white_texture;
	sf::Texture black_texture_s;
	sf::Texture white_texture_s;
	sf::Texture board_texture;

	sf::Sprite ** black_table = new sf::Sprite*[64];
	sf::Sprite ** white_table = new sf::Sprite*[64];

	sf::Sprite ** black_table_s = new sf::Sprite*[64];
	sf::Sprite ** white_table_s = new sf::Sprite*[64];

	sf::Sprite boardImage;

	if(!board_texture.loadFromFile("board1.png"))
		std::cout<<"Unable to load board_texture \n";
	boardImage.setTexture(board_texture);

	createPieces(black_table);
	createPieces(white_table);
	createPieces(black_table_s);
	createPieces(white_table_s);
	setPieces(filename_black.c_str(),black_texture,black_table);
	setPieces(filename_white.c_str(),white_texture,white_table);
	setPieces(filename_black_s.c_str(),black_texture_s,black_table_s);
	setPieces(filename_white_s.c_str(), white_texture_s, white_table_s);

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

	drawBoard(START_POSITION_black, black_table, window);
	drawBoard(START_POSITION_white, white_table, window);
	//drawBoard(0x830040000, white_table, window);
	BITBOARD test = showMyValidMoves(START_POSITION_black, START_POSITION_white);
	drawBoard(test, black_table_s, window);

		window.display();
		

    } 
    return 0;
}