#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "mouse.h"
#include <windows.h>   
#include <algorithm>

int minMove(BITBOARD myBoard, BITBOARD opponentBoard, int maxDepth, int currentDepth);
int maxMove(BITBOARD myBoard, BITBOARD opponentBoard, int maxDepth, int currentDepth);
int countPoints(BITBOARD board)
{
	BITBOARD shift = 0x0000000000000001;
	int points = 0;
	while (board != 0)
	{
		if((shift&board) != 0)
		{
			++points;
		}
		board = board >> 1;
	}
	return points;
}

BITBOARD flipPieces(BITBOARD boardA, BITBOARD boardB, BITBOARD moveOfA)
{
	
	BITBOARD all = boardA | boardB| moveOfA;
	BITBOARD empty = ~all;
	BITBOARD downMask = 0xFFFFFFFFFFFFFF;
	BITBOARD upMask = 0xFFFFFFFFFFFFFF00;
	BITBOARD rightMask = 0xFEFEFEFEFEFEFEFE;
	BITBOARD leftMask = 0x7F7F7F7F7F7F7F7F;
	BITBOARD allPotentialFlips1 = 0UL, allPotentialFlips2 = 0UL, allPotentialFlips3 = 0UL, allPotentialFlips4 = 0UL, allPotentialFlips5 = 0UL, allPotentialFlips6 = 0UL, allPotentialFlips7 = 0UL, allPotentialFlips8 = 0UL;
	BITBOARD validFlips1 = 0L, validFlips2 = 0L, validFlips3 = 0L, validFlips4 = 0L, validFlips5 = 0L, validFlips6 = 0L, validFlips7 = 0L, validFlips8 = 0L;
	BITBOARD validFlipsAll;
	//DOWN
	BITBOARD potentialFlip1 = (moveOfA >> 8) & downMask & boardB;
	while (potentialFlip1 != 0UL)
	{
		allPotentialFlips1 = allPotentialFlips1 | potentialFlip1;
		BITBOARD tmp = (potentialFlip1 >> 8) & downMask;
		if ((tmp&empty)!=0UL)
		{
			break;
		}
		if ((tmp&boardA) != 0UL)
		{
			validFlips1 = allPotentialFlips1;
			break;
		}
		potentialFlip1 = tmp;
	}
	//UP
	BITBOARD potentialFlip2 = (moveOfA << 8) & upMask & boardB;
	while (potentialFlip2 != 0UL)
	{
		allPotentialFlips2 = allPotentialFlips2 | potentialFlip2;
		BITBOARD tmp = (potentialFlip2 << 8) & upMask;
		if ((tmp&empty) != 0UL)
		{
			break;
		}
		if ((tmp&boardA) != 0UL)
		{
			validFlips2 = allPotentialFlips2;
			break;
		}
		potentialFlip2 = tmp;
	}
	//LEFT
	BITBOARD potentialFlip3 = (moveOfA >> 1) & leftMask & boardB;
	while (potentialFlip3 != 0UL)
	{
		allPotentialFlips3 = allPotentialFlips3 | potentialFlip3;
		BITBOARD tmp = (potentialFlip3 >> 1) & leftMask;
		if ((tmp&empty) != 0UL)
		{
			break;
		}
		if ((tmp&boardA) != 0UL)
		{
			validFlips3 = allPotentialFlips3;
			break;
		}
		potentialFlip3 = tmp;
	}
	//RIGHT
	BITBOARD potentialFlip4 = (moveOfA << 1) & rightMask & boardB;
	while (potentialFlip4 != 0UL)
	{
		allPotentialFlips4 = allPotentialFlips4 | potentialFlip4;
		BITBOARD tmp = (potentialFlip4 << 1) & rightMask;
		if ((tmp&empty) != 0UL)
		{
			break;
		}
		if ((tmp&boardA) != 0UL)
		{
			validFlips4 = allPotentialFlips4;
			break;
		}
		potentialFlip4 = tmp;
	}
	//UPRIGHT
	BITBOARD potentialFlip5 = (moveOfA << 9) & upMask & rightMask & boardB;
	while (potentialFlip5 != 0UL)
	{
		allPotentialFlips5 = allPotentialFlips5 | potentialFlip5;
		BITBOARD tmp = (potentialFlip5 << 9) & upMask & rightMask;
		if ((tmp&empty) != 0UL)
		{
			break;
		}
		if ((tmp&boardA) != 0UL)
		{
			validFlips5 = allPotentialFlips5;
			break;
		}
		potentialFlip5 = tmp;
	}
	//UPLEFT
	BITBOARD potentialFlip6 = (moveOfA << 7) & upMask & leftMask & boardB;
	while (potentialFlip6 != 0UL)
	{
		allPotentialFlips6 = allPotentialFlips6 | potentialFlip6;
		BITBOARD tmp = (potentialFlip6 << 7) & upMask & leftMask;
		if ((tmp&empty) != 0UL)
		{
			break;
		}
		if ((tmp&boardA) != 0UL)
		{
			validFlips6 = allPotentialFlips6;
			break;
		}
		potentialFlip6 = tmp;
	}
	//DOWNLEFT
	BITBOARD potentialFlip7 = (moveOfA >> 9) & downMask & leftMask & boardB;
	while (potentialFlip7 != 0UL)
	{
		allPotentialFlips7 = allPotentialFlips7 | potentialFlip7;
		BITBOARD tmp = (potentialFlip7 >> 9) & downMask & leftMask;
		if ((tmp&empty) != 0UL)
		{
			break;
		}
		if ((tmp&boardA) != 0UL)
		{
			validFlips7 = allPotentialFlips7;
			break;
		}
		potentialFlip7 = tmp;
	}
	//DOWNRIGHT
	BITBOARD potentialFlip8 = (moveOfA >> 7) & downMask & rightMask & boardB;
	while (potentialFlip8 != 0UL)
	{
		allPotentialFlips8 = allPotentialFlips8 | potentialFlip8;
		BITBOARD tmp = (potentialFlip8 >> 7) & downMask & rightMask;
		if ((tmp&empty) != 0UL)
		{
			break;
		}
		if ((tmp&boardA) != 0UL)
		{
			validFlips8 = allPotentialFlips8;
			break;
		}
		potentialFlip8 = tmp;
	}

	
	validFlipsAll= validFlips1 | validFlips2 | validFlips3 | validFlips4 | validFlips5 | validFlips6 | validFlips7 | validFlips8 ; 
	//return validFlipsAll;//only return positions of pieces to flip

	return (boardA | validFlipsAll | moveOfA); //returns the new board A
}
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
		BITBOARD tmp2 = (potentialMoves2 << 8) & upMask; 
		validMoves2 = validMoves2|(tmp2&empty);
		potentialMoves2 = tmp2&opponentBoard;
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

	//std::cout << "obliczam valid moves" << std::hex << allValidMoves << "\n";
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
	for(int x = 0; x<64 ;++x)
	{
		table[x] = new sf::Sprite;
	}
}

void setPieces(const char* filename, sf::Texture& tex,sf::Sprite** table)
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

BITBOARD minMax(BITBOARD computerBoard, BITBOARD playerBoard, int maxDepth)
{
	std::cout << "into MINMAX \n";
	BITBOARD movesBoard = showMyValidMoves(computerBoard, playerBoard); //ruchy dla kompa
	std::cout << std::hex << "Moves board (all possible moves)" << movesBoard << " \n";
	BITBOARD shift = 0x0000000000000001;
	std::vector<int> scoreList;
	std::vector<BITBOARD> selectedMovesList;
	std::vector<BITBOARD> movesList;
	std::cout << "movesList : \n";
	while (shift != 0)
	{
		if ((shift&movesBoard) != 0)
		{
			movesList.push_back(shift);
			std::cout << std::hex << shift << " \n";
		}
		shift = shift << 1;
	}
	std::cout << "zaraz bedzie petla \n";

	for(auto& elem : movesList)
	{
		selectedMovesList.push_back(elem);
		scoreList.push_back(minMove(flipPieces(computerBoard, playerBoard, elem), (playerBoard&~flipPieces(computerBoard, playerBoard, elem)), maxDepth, 1));
	}
	//for (int i = 0; i < movesList.size(); i++)
	//{
	//	std::cout << i <<"\n";
	//	std::cout << "w petli: \n";
	//	selectedMovesList.push_back(movesList[i]);
	//	std::cout << " ###### zaraz bedzie wywolany min dla :" << movesList[i] << "  ####### \n \n";
	//	scoreList.push_back(minMove(flipPieces(computerBoard, playerBoard, movesList[i]), (playerBoard&~flipPieces(computerBoard, playerBoard, movesList[i])), maxDepth, 1));
	//}
	std::cout << "koniec petli \n";
	int bestScore = 0;
	int position = 0;
	int wantedPosition = 0;
	//for(auto x = scoreList.begin(); ...)
	for (std::vector<int>::iterator it = scoreList.begin(); it != scoreList.end(); it++) {
		std::cout << *it << "\n";
		
		if (*it > bestScore)
		{	
			bestScore = *it;
			wantedPosition = position;
		}
		/* std::cout << *it; ... */
		position += 1;
	}
	/*
	for (int i : scoreList)
	{
		position++;
		if (i > bestScore)
		{

			bestScore = i;
			wantedPosition = position;
		}
	}
	*/
	//std::cout << selectedMovesList[wantedPosition] << " \n";
	return wantedPosition >= selectedMovesList.size() ? 0 : selectedMovesList[wantedPosition];
	//return 0x20000000;
}

int minMove(BITBOARD computerBoard, BITBOARD playerBoard, int maxDepth, int currentDepth)
{
	std::cout << "into MIN current depth " << currentDepth << "max depth" << maxDepth << " \n";
	if (maxDepth == currentDepth)
	{
		std::cout << "max depth in min! \n";
		std::cout << countPoints(playerBoard) << "\n";
		std::cout <<std::hex<<"player b " << playerBoard << "\n";
		std::cout << std::hex <<"computer b" << computerBoard << "\n";
		return countPoints(playerBoard);
	}
	int result = 100000;
	BITBOARD movesBoard = showMyValidMoves(playerBoard,computerBoard);
	//BITBOARD movesBoard = showMyValidMoves(computerBoard, playerBoard);
	BITBOARD shift = 0x0000000000000001;
	std::vector<BITBOARD> movesList;
	while (shift != 0)
	{
		if ((shift&movesBoard) != 0)
		{
			movesList.push_back(shift);
		}
		shift = shift << 1;
	}
	std::cout << "player board" << std::hex << playerBoard << "computer board " << std::hex << computerBoard << "\n ";
	std::cout << "moves list size " << movesList.size() << "moves" << std::hex << movesBoard <<"\n ";
	for (int i = 0; i < movesList.size(); i++)
	{
		std::cout << "for move" << std::hex << movesList[i] << "\n ";
		result = std::min(result, maxMove((computerBoard&~flipPieces(playerBoard, computerBoard, movesList[i])), flipPieces(playerBoard, computerBoard, movesList[i]), maxDepth, (currentDepth + 1)));
	}
	return result;
}
int maxMove(BITBOARD computerBoard, BITBOARD playerBoard, int maxDepth, int currentDepth)
{
	std::cout << "into MAX current depth " << currentDepth << "max depth" << maxDepth << " \n";
	
	if (maxDepth == currentDepth)
	{
		std::cout << "max depth in max! \n";
		std::cout << countPoints(computerBoard) << "\n";
		std::cout << std::hex << computerBoard << "\n";
		return countPoints(computerBoard);
	}
	int result = 0;
	BITBOARD movesBoard = showMyValidMoves(computerBoard, playerBoard);
	std::cout << "!!!!!1player b " << std::hex << playerBoard << "computer b: " << std::hex << computerBoard << "moves" << std::hex << showMyValidMoves(computerBoard,playerBoard)<<"\n ";
	
	BITBOARD shift = 0x0000000000000001;
	std::vector<BITBOARD> movesList;
	while (shift != 0)
	{
		if ((shift&movesBoard) != 0)
		{
			movesList.push_back(shift);
		}
		shift = shift << 1;
	}
	std::cout << "player board" << std::hex << playerBoard << "computer board " << std::hex << computerBoard << "\n ";
	std::cout << "moves list size " << movesList.size() << "moves" <<std::hex<< movesBoard << "\n ";
	for (int i = 0; i < movesList.size(); i++)
	{
		std::cout << "for move" << std::hex << movesList[i] << "\n ";
		result = std::max(result, minMove(flipPieces(computerBoard, playerBoard, movesList[i]), (playerBoard&~flipPieces(computerBoard, playerBoard, movesList[i])), maxDepth, (currentDepth + 1)));
	}
	return result;
}
/*
int minMove(BITBOARD myBoard, BITBOARD opponentBoard, int maxDepth, int currentDepth)
{
	if (maxDepth == currentDepth)
	{
		return countPoints(myBoard);
	}
	int result = 65;
	BITBOARD movesBoard = showMyValidMoves(myBoard, opponentBoard);
	BITBOARD shift = 0x0000000000000001;
	std::vector<BITBOARD> movesList;
	while (shift != 0)
	{
		if ((shift&movesBoard) != 0)
		{
			movesList.push_back(shift);
		}
		shift = shift << 1;
	}
	for (int i = 0; i < movesList.size(); i++)
	{
		result = std::min(result, maxMove(flipPieces(myBoard, opponentBoard, movesList[i]), opponentBoard, maxDepth, currentDepth + 1));
	}
	return result;
}
*/
/*
int maxMove(BITBOARD myBoard, BITBOARD opponentBoard,int maxDepth,int currentDepth)
{
	if (maxDepth == currentDepth)
	{
		return countPoints(myBoard);
	}
	int result = 0;
	BITBOARD movesBoard = showMyValidMoves(myBoard, opponentBoard);
	BITBOARD shift = 0x0000000000000001;
	std::vector<BITBOARD> movesList;
	while (shift != 0)
	{
		if ((shift&movesBoard) != 0)
		{
			movesList.push_back(shift);
		}
		shift = shift << 1;
	}
	for (int i = 0; i < movesList.size(); i++)
	{
		result = std::max(result, minMove(flipPieces(myBoard, opponentBoard, movesList[i]),opponentBoard,maxDepth,currentDepth+1));
	}
	return result;
}
*/



BITBOARD easyAlg(BITBOARD myBoard, BITBOARD opponentBoard)
{

	std::cout << "jestem w easy alg" << "\n";
	std::cout << "black:" <<std::hex<< myBoard <<"\n";
	std::cout << "white:" << std::hex << opponentBoard << "\n";

	BITBOARD bestBoard = 0UL;
	int myScore = 0;
	int count = 0;
	BITBOARD shift = 0x0000000000000001;
	BITBOARD validMoves = showMyValidMoves(myBoard, opponentBoard);
	if (validMoves == 0UL)
		return 0UL;

	std::cout << "mozliwe ruchy ai:" << std::hex << validMoves << "\n";


	while (shift != 0)
	{
		std::cout << "jestem w petli, wart shift:" << std::hex<< shift << "\n";
		
		if ((shift&validMoves) != 0)
		{
			count = count + 1;
			if ((shift&validMoves) == (0x200 | 0x4000 | 0x2000000000000 | 0x40000000000000))
			{
				int score = 1;
				if (score > myScore)
				{
					myScore = score;
					bestBoard = shift&validMoves;
				}

			}
			else if ((shift&validMoves) == (0x8000000000000000 | 0x100000000000000 | 0x2000000000000 | 0x40000000000000))
			{
				int score = 64;
				if (score > myScore)
				{
					myScore = score;
					bestBoard = shift&validMoves;
				}

			}
			else
			{
				BITBOARD flipped = flipPieces(myBoard, opponentBoard, (shift&validMoves));
				int score = countPoints(flipped);
				if (score > myScore)
				{
					myScore = score;
					bestBoard = shift&validMoves;
				}

			}
		
		}
		shift = (shift << 1);
	}
	std::cout << "najlepszy ruch dla ai:" << std::hex << bestBoard << "\n";
	return bestBoard;


}

int main()
{

	BITBOARD w = 0x100818080000;
	BITBOARD b = 0x201000000000;
	BITBOARD m = showMyValidMoves(b , w);
	std::cout << std::hex << "White: " << w << "Black: " << b << "Mata: " << m << "\n";
	//std::exit;
    sf::RenderWindow window( sf::VideoMode( 400, 400 ), "REVERSI" );

	std::string filename_black = "black1.png";
	std::string filename_white = "white1.png";
	std::string filename_black_s = "black_s.png";
	std::string filename_white_s = "white_s.png";

	//std::string filename_black = "black2.png";
	//std::string filename_white = "white2.png";
	//std::string filename_black_s = "black_s2.png";
	//std::string filename_white_s = "white_s2.png";

	sf::Texture black_texture;
	sf::Texture white_texture;
	sf::Texture black_texture_s;
	sf::Texture white_texture_s;
	sf::Texture board_texture;
	sf::Texture game_over_texture;

	sf::Sprite ** black_table = new sf::Sprite*[64];
	sf::Sprite ** white_table = new sf::Sprite*[64];

	sf::Sprite ** black_table_s = new sf::Sprite*[64];
	sf::Sprite ** white_table_s = new sf::Sprite*[64];

	sf::Sprite boardImage;
	sf::Sprite boardGameOver;


	sf::Font font;
	sf::Text score_white;
	sf::Text score_black;
	sf::Text win_lost;

	if (!font.loadFromFile("HoboStd.otf"))
	{
		std::cout << "Unable to load font \n";
	}
	score_white.setFont(font);
	score_black.setFont(font);
	win_lost.setFont(font);
	score_white.setColor(sf::Color::White);
	score_black.setColor(sf::Color::Black);
	win_lost.setColor(sf::Color::Red);
	score_white.setPosition(105, 315);
	score_black.setPosition(250, 315);
	win_lost.setPosition(100, 200);

	if(!board_texture.loadFromFile("board1.png"))
		std::cout<<"Unable to load board_texture \n";
	boardImage.setTexture(board_texture);

	if (!game_over_texture.loadFromFile("board1go.png"))
		std::cout << "Unable to load game_over_texture \n";
	boardGameOver.setTexture(game_over_texture);
	
	//if (!board_texture.loadFromFile("board2.png"))
		//std::cout << "Unable to load board_texture \n";
	//boardImage.setTexture(board_texture);

	createPieces(black_table);
	createPieces(white_table);
	createPieces(black_table_s);
	createPieces(white_table_s);
	setPieces(filename_black.c_str(),black_texture,black_table);
	setPieces(filename_white.c_str(),white_texture,white_table);
	setPieces(filename_black_s.c_str(),black_texture_s,black_table_s);
	setPieces(filename_white_s.c_str(), white_texture_s, white_table_s);

	BITBOARD White = 0x810000000;
	BITBOARD Black = 0x1008000000;

	BITBOARD lolo = flipPieces(0x3E2222223E00,0x1C141C0000,0x8000000);
	bool gameOver = false;
	bool playerTurn = true;
	BITBOARD playerMove = 0UL;
	BITBOARD validPlayerMoves;
	BITBOARD potentialplayerMove = 0UL;
	BITBOARD potentialaiMove = 0UL;
	int whiteScore = 0;
	int blackScore = 0;

	bool AICanMove = true;
	bool playerCanMove = true;

    while( window.isOpen() )
    {
        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
			{
                 window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{

				std::cout << "mouse event"<<"\n";
				if (playerTurn == true)
				{
					int mouseX = sf::Mouse::getPosition(window).x;
					std::cout << "x:" << mouseX << "\n";
					int mouseY = sf::Mouse::getPosition(window).y;
					std::cout << "y:" << mouseY << "\n";
					potentialplayerMove = getBoardPosition(mouseX, mouseY);
					std::cout << "gracz chce postawic tu: " << std::hex << potentialplayerMove << "\n";

					validPlayerMoves = showMyValidMoves(White, Black);
					std::cout << "gracz moze postawic w tych miejscach" << std::hex << validPlayerMoves << "\n";
					if (validPlayerMoves != 0)
					{
						if ((validPlayerMoves&potentialplayerMove) != 0)
						{

							std::cout << "zaraz zamienie wart dla gracza" << "\n";
							playerMove = potentialplayerMove;

							std::cout << "white przed:" << std::hex << White << "\n";
							White = flipPieces(White, Black, playerMove);
							Black = (Black&~White);
							std::cout << "white po:" << std::hex << White << "\n";
							playerTurn = false;
							AICanMove = true;
						}
					}
					else
					{
						playerCanMove = false;
						playerTurn = false;
						if ((playerCanMove == false) && (AICanMove == false))
						{
						gameOver = true;
						std::cout << "GAME OVER!!!!!!!!!! \n";
						blackScore = countPoints(Black);
						whiteScore = countPoints(White);
						std::cout << "Punkty czarnego:" << std::dec << countPoints(Black) << "\n";
						std::cout << "Punkty bialego:" << std::dec << countPoints(White) << "\n";
						//system("pause");						//break;

						}


						
					}
					
				}
			}
           
        } 
        window.clear();
		window.draw(boardImage);

		drawBoard(White, white_table, window);
		drawBoard(Black, black_table, window);
		

		if (playerTurn == true)
		{
			drawBoard(showMyValidMoves(White, Black), white_table_s, window);
			if (showMyValidMoves(White, Black) == 0)
			{
				playerCanMove = false;

			}

		}
		window.display();
		if (playerTurn == false)
		{

			if (gameOver == false)
			{

				//potentialaiMove = easyAlg(Black, White);
				potentialaiMove = minMax(Black, White, 3); //black =computer
				std::cout << "potential move:" << std::hex << potentialaiMove << "\n";

				if (potentialaiMove != 0)
				{

					std::cout << "ai move:" << std::hex << potentialaiMove << "\n";

					drawBoard(potentialaiMove, black_table, window);
					//window.display();
					Sleep(500);

					Black = flipPieces(Black, White, potentialaiMove);
					White = (White&~Black);

					playerTurn = true;
					playerCanMove = true;


				}
				if (potentialaiMove == 0)
				{
					playerTurn = true;
					AICanMove = false;
					if ((AICanMove == false) && (playerCanMove == false))
					{
					gameOver = true;

					std::cout << "GAME OVER" << "\n";
					blackScore = countPoints(Black);
					whiteScore = countPoints(White);
					std::cout << "Punkty czarnego:" << std::dec<<countPoints(Black) << "\n";
					std::cout << "Punkty bialego:" << std::dec << countPoints(White) << "\n";
					//system("pause");

					}
					

				}
			}
			
			

		}
		if (playerTurn == true)
		{
			
			if (showMyValidMoves(White, Black) == 0)
			{
				playerCanMove = false;
				playerTurn = false;

			}

		}
		if (gameOver==true)
		{
			break;

		}

		
		

    } 

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
		window.draw(boardGameOver);

		window.draw(*white_table[9]);
		std::string strWhite = std::to_string(whiteScore);
		score_white.setString(strWhite);

		window.draw(*black_table[12]);
		std::string strBlack = std::to_string(blackScore);
		score_black.setString(strBlack);

		if (blackScore > whiteScore)
		{
			win_lost.setString("YOU LOST");
			window.draw(win_lost);

		}
		if (blackScore < whiteScore)
		{
			win_lost.setString("YOU WON");
			window.draw(win_lost);
		}

		//score_black.setString(strBlack);
		window.draw(score_black);
		window.draw(score_white);
		window.display();


	}



    return 0;
}