// Ping_Pong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
bool gameOver;
const int width = 40;
const int height = 20;

int score = 0;
// + is down - is up

// player starting position
int plX = width / 2-2, //Player X axis position best to leave around 2-2
plY = height - 2, // Player Y axis position for best result leave around -2
pl = 0; // player in general

// ball starting position and velocity
int ballX = width / 2,
ballY = 8, 
speedX=0, speedY = 1;

bool is_in_range(int value, int lower, int upper)
{
	return (value >= lower && value <= upper);
}

void Draw()
{
	system("cls");
	
	// top border
	for (int i = 0; i < width + 2; i++)
	  std::cout<<"#";
	std::cout<<std::endl;
	
	// space between borders
	for (int i = 0; i < height; i++) // height is 20
	{
	   for (int j = 0; j < width; j++)  // width is 40
		{
		   // left side border
			if (j == 0)
				std::cout << "#";
			
			// Player model
			if (j == plX + pl && i == plY && pl != 4) 
			{
			     std::cout << "=";
				pl++; 
			}
			
			// Ball model
			else if (j == ballX && i == ballY)
				std::cout << "o";
		    
			// Playing Field
			else
		      std::cout <<" ";
		      
			// right side border
			if (j == width - 1)
				std::cout << "#";
		
		}
		
		std::cout << std::endl;
	
	}
	
	// bottom border
	for (int i = 0; i < width + 2; i++)
	        std::cout << "#";
	      std::cout << std::endl;
	
	pl = 0; // paddle size / position on x axis
	
	std::cout << "Score: " << score; // Score:

}
void Update() 
{
	
	// Player control input to move
	if (_kbhit())
	{
		switch (_getch())
		{
	    // Make paddle move left
		case 'a':
			plX--;
			break;
		// Make paddle move right
		case 'd':
			plX++;
			break;
		// Close game
		case 'x':
			gameOver = true;
			break;
		}
	}
	     // left collider radius?
	if (is_in_range(ballX, plX, plX + 2)
		&& ballY == plY - 1)
	{
		speedX = -1;
	}     // right collider radius?
	if (is_in_range(ballX, plX + 2, plX + 4)
		&& ballY == plY - 1)
	{
		speedX = 1; // ball speed on X Axis after it makes contact with player
	}
	    // Y collider radius
	if (is_in_range(ballX, plX, plX + 4)
		&& ballY == plY - 1)
	{
		speedY = -speedY; // the collider for the ball / player
	      score++;
	}

          // Game Over
		if(ballY <= 1)
			
			speedY = -speedY;
		
		if (ballX <= 1 || ballX >= width - 1)
		
			speedX = -speedX;
		
		if (ballY > plY)
		{
			score--;
			if (score < 0) score = 0;
			speedY = -speedY;
			//gameOver = true;
		}


		ballX += speedX;
		ballY += speedY;
}
int main()
{
	while(!gameOver){
		Draw();
		Update();
		Sleep(20);
	}
	return 0;
}

