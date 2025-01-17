/*
 * Copyright 2024 Israel Owolabi
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for full license information.
 */


#include "Minesweeper3D.h"
#include "MinesweeperBoard.h"
#include "SplashScreen.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

SplashScreen::SplashScreen(std::shared_ptr<sf::RenderWindow> window) : window(window) {
	this->window = window;
	updateWindowSize();

	// Load resources and initialize variables here
	if (!logoTexture.loadFromFile("src/img/logo.png")) {
		std::cerr << "Failed to load logo.png" << std::endl;
		return;
	}

	//if (!font.loadFromFile("src/fonts/Minecrafter.Reg.ttf")) {
	if (!font.loadFromFile("src/fonts/PilotCommand-3zn93.otf")) {
		std::cerr << "Failed to load font" << std::endl;
		return;
	}

	if (!aboveLoadingBarTexture.loadFromFile("src/img/minesweeper_image.jpeg")) {
		std::cerr << "Failed to load minesweeper_image.jpeg" << std::endl;
		std::cerr << "Loading a placeholder image instead." << std::endl;
		sf::Image placeholderImage;
		placeholderImage.create(400, 300, sf::Color::Red); // Placeholder image size
		aboveLoadingBarTexture.loadFromImage(placeholderImage);
	}
}

void SplashScreen::setupUIElements() {
	// Set up your sprites and texts here based on the initial window size
	updateUIElements();
}

void SplashScreen::updateUIElements() {
	// Update positions and scales of your sprites and texts based on windowSize
	sf::Vector2u imageSize = aboveLoadingBarTexture.getSize();
	float scaleX = windowWidth / imageSize.x;
	float scaleY = windowHeight / imageSize.y;
	scaleFactor = std::min(scaleX * 1.5f, scaleY * 1.5f);
	aboveLoadingBarSprite.setScale(scaleFactor, scaleFactor);
	aboveLoadingBarSprite.setPosition((windowSize.x - aboveLoadingBarSprite.getLocalBounds().width) / 2 + 20, (windowSize.y - aboveLoadingBarSprite.getLocalBounds().height) / 2);

}

void SplashScreen::startGame(std::shared_ptr<sf::RenderWindow> window, int boardSize, GameMode selectedGameMode) {
	updateWindowSize();
	Minesweeper3D game(window, boardSize, selectedGameMode);
	game.run();
}
void SplashScreen::run() {
	// Display the logo
	displayLogo();
	loadAndDisplayAboveLoadingBarImage();
	// Display UI elements
	displayUI();
}

void SplashScreen::displayLogo() {
	sf::Sprite logoSprite(logoTexture);
	logoSprite.setPosition(windowWidth / 2 - logoTexture.getSize().x / 2,
		windowHeight / 2 - logoTexture.getSize().y / 2);
	window->draw(logoSprite);
	window->display();
	sf::sleep(sf::seconds(2)); // Wait for 2 seconds (adjust as needed)
}

sf::Sprite SplashScreen::loadAboveLoadingBarImage() {
	// Load the image to display above the loading bar
	if (!aboveLoadingBarTexture.loadFromFile("src/img/minesweeper_image.jpeg")) {
		updateUIElements(); // Call this to set initial positions and scales
		// If loading fails, display a placeholder message
		std::cerr << "Failed to load minesweeper_image.jpeg" << std::endl;
		std::cerr << "Loading a placeholder image instead." << std::endl;
		sf::Image placeholderImage;
		placeholderImage.create(400, 300, sf::Color::Red); // Placeholder image size
		aboveLoadingBarTexture.loadFromImage(placeholderImage);
	}

	// Define loading bar properties and other UI elements
	sf::Sprite aboveLoadingBarSprite(aboveLoadingBarTexture);

	// Get the size of the window
	sf::Vector2u windowSize = window->getSize();

	// Get the size of the loaded image
	sf::Vector2u imageSize = aboveLoadingBarTexture.getSize();

	// Calculate the scale factor to fit the image into the window
	float scaleX = windowWidth / imageSize.x;
	float scaleY = windowHeight / imageSize.y;
	float scaleFactor = std::min(scaleX * 1.5f, scaleY * 1.5f);

	// Set the scale of the sprite
	aboveLoadingBarSprite.setScale(scaleFactor, scaleFactor);

	// Center the sprite in the window
	aboveLoadingBarSprite.setPosition((windowSize.x - aboveLoadingBarSprite.getLocalBounds().width) / 2 + 20, (windowSize.y - aboveLoadingBarSprite.getLocalBounds().height) / 2);

	return aboveLoadingBarSprite;
}

void SplashScreen::loadAndDisplayAboveLoadingBarImage() {
	// Load the image to display above the loading bar
	sf::Texture aboveLoadingBarTexture;
	if (!aboveLoadingBarTexture.loadFromFile("src/img/minesweeper_image.jpeg")) {
		// If loading fails, display a placeholder message
		std::cerr << "Failed to load minesweeper_image.jpeg" << std::endl;
		std::cerr << "Loading a placeholder image instead." << std::endl;
		sf::Image placeholderImage;
		placeholderImage.create(400, 300, sf::Color::Red); // Placeholder image size
		aboveLoadingBarTexture.loadFromImage(placeholderImage);
	}

	sf::Sprite aboveLoadingBarSprite(aboveLoadingBarTexture);

	// Get the size of the window
	windowSize = window->getSize();

	// Get the size of the loaded image
	sf::Vector2u imageSize = aboveLoadingBarTexture.getSize();

	// Calculate the scale factor to fit the image into the window
	float scaleX = windowWidth / imageSize.x;
	float scaleY = windowHeight / imageSize.y;
	float scaleFactor = std::min(scaleX * 1.5f, scaleY * 1.5f);

	// Set the scale of the sprite
	aboveLoadingBarSprite.setScale(scaleFactor, scaleFactor);

	// Center the sprite in the window
	aboveLoadingBarSprite.setPosition((windowWidth - aboveLoadingBarSprite.getLocalBounds().width) / 2 + 20,
		(windowHeight - aboveLoadingBarSprite.getLocalBounds().height) / 2);

	// Define loading bar properties
	sf::RectangleShape loadingBar(sf::Vector2f(400, 30));
	// Position the loading bar below the loading text
	loadingBar.setPosition(windowWidth / 2 - loadingBar.getSize().x / 2,
		windowHeight / 2 + logoTexture.getSize().y / 2 + 60);
	float cornerRadius = 35.0f;
	loadingBar.setOutlineThickness(2);
	loadingBar.setOutlineColor(sf::Color::Black);
	loadingBar.setFillColor(sf::Color::Transparent);

	// Create a gradient for rainbow colors
	sf::VertexArray gradient(sf::Quads, 4);
	gradient[0].color = sf::Color::Red;
	gradient[1].color = sf::Color::Yellow;
	gradient[2].color = sf::Color::Green;
	gradient[3].color = sf::Color::Blue;

	// Animation variables
	sf::Clock clock; // Declare the clock outside the loop to keep track of time continuously
	float elapsedTime = 0.0f;
	float animationDuration = 3.0f; // Duration of the animation in seconds
	float loadingProgress = 0.0f;

	// Define loading text properties
	sf::Text loadingText("Loading...", font, 30);
	loadingText.setFillColor(sf::Color::White);
	loadingText.setOutlineColor(sf::Color::Black);
	loadingText.setOutlineThickness(2);
	loadingText.setPosition(windowWidth / 2 - loadingText.getGlobalBounds().width / 2,
		windowHeight / 2 + logoTexture.getSize().y / 2 + 20); // Position the loading text below the logo

	// Define game text properties
	sf::Text gameText("Minesweeper 3D", font, 60);
	gameText.setFillColor(sf::Color::White);
	gameText.setOutlineColor(sf::Color::Black);
	gameText.setOutlineThickness(2);
	gameText.setPosition(windowWidth / 2 - gameText.getGlobalBounds().width / 2,
		windowHeight / 2 + logoTexture.getSize().y / 2 - 350); // Position the game text below the logo


	// Display the sprite, loading bar, and loading text together
	while (clock.getElapsedTime().asSeconds() < animationDuration) {
		// Clear the window
		window->clear();

		// Update the loading progress
		elapsedTime = clock.getElapsedTime().asSeconds();
		loadingProgress = elapsedTime / animationDuration;

		// Draw the sprite, loading bar, and loading text
		window->draw(aboveLoadingBarSprite);

		loadingBar.setSize(sf::Vector2f(400 * loadingProgress, 30));

		gradient[0].position = loadingBar.getPosition();
		gradient[1].position = sf::Vector2f(loadingBar.getPosition().x + loadingBar.getSize().x, loadingBar.getPosition().y);
		gradient[2].position = loadingBar.getPosition() + loadingBar.getSize();
		gradient[3].position = sf::Vector2f(loadingBar.getPosition().x, loadingBar.getPosition().y + loadingBar.getSize().y);

		window->draw(gradient);
		window->draw(loadingBar);
		window->draw(gameText);
		window->draw(loadingText);

		// Display the window
		window->display();
	}

	// Wait for a few seconds before closing
	sf::sleep(sf::seconds(2));
}
void SplashScreen::displayMainMenu() {
	bool exitClicked = false;
	updateWindowSize();
	sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));


	// Define UI elements
	sf::Text exitText("Exit", font, 30);
	exitText.setFillColor(sf::Color::White);
	exitText.setOutlineColor(sf::Color::Black);
	exitText.setOutlineThickness(2);
	exitText.setPosition(windowWidth / 2 - exitText.getGlobalBounds().width / 2,
		windowHeight / 2 + 50); // Adjust position as needed

	sf::Text startText("Start Game", font, 30);
	startText.setFillColor(sf::Color::White);
	startText.setOutlineColor(sf::Color::Black);
	startText.setOutlineThickness(2);
	startText.setPosition(windowWidth / 2 - startText.getGlobalBounds().width / 2,
		windowHeight / 2 - 150); // Adjust position as needed

	sf::Text levelchange("Difficulty Level", font, 30);
	levelchange.setFillColor(sf::Color::White);
	levelchange.setOutlineColor(sf::Color::Black);
	levelchange.setOutlineThickness(2);
	levelchange.setPosition(windowWidth / 2 - levelchange.getGlobalBounds().width / 2,
		windowHeight / 2 - 100); // Adjust position as needed

	// Define UI elements
	sf::Text difficultyText("Easy", font, 30);
	difficultyText.setFillColor(sf::Color::White);
	difficultyText.setOutlineColor(sf::Color::Black);
	difficultyText.setOutlineThickness(2);
	difficultyText.setPosition(windowWidth / 2 - difficultyText.getGlobalBounds().width / 2,
		windowHeight / 2 - 50); // Adjust position as needed


	sf::Text leftArrowText("<", font, 30);
	leftArrowText.setFillColor(sf::Color::White);
	leftArrowText.setOutlineColor(sf::Color::Black);
	leftArrowText.setOutlineThickness(2);
	leftArrowText.setPosition(windowWidth / 2 - startText.getGlobalBounds().width / 2 - 50,
		windowHeight / 2 - 50); // Adjust position as needed

	sf::Text rightArrowText(">", font, 30);
	rightArrowText.setFillColor(sf::Color::White);
	rightArrowText.setOutlineColor(sf::Color::Black);
	rightArrowText.setOutlineThickness(2);
	rightArrowText.setPosition(windowWidth / 2 + startText.getGlobalBounds().width / 2 + 10,
		windowHeight / 2 - 50); // Adjust position as needed

	sf::Text boardSizeText("Board Size: " + std::to_string(boardSize), font, 30);
	boardSizeText.setFillColor(sf::Color::White);
	boardSizeText.setOutlineColor(sf::Color::Black);
	boardSizeText.setOutlineThickness(2);
	boardSizeText.setPosition(windowWidth / 2 - boardSizeText.getGlobalBounds().width / 2,
		windowHeight / 2); // Adjust position as needed

	sf::Text leftBoardSizeArrowText("<", font, 30);
	leftBoardSizeArrowText.setFillColor(sf::Color::White);
	leftBoardSizeArrowText.setOutlineColor(sf::Color::Black);
	leftBoardSizeArrowText.setOutlineThickness(2);
	leftBoardSizeArrowText.setPosition(windowWidth / 2 - boardSizeText.getGlobalBounds().width / 2 - 50,
		windowHeight / 2); // Adjust position as needed

	sf::Text rightBoardSizeArrowText(">", font, 30);
	rightBoardSizeArrowText.setFillColor(sf::Color::White);
	rightBoardSizeArrowText.setOutlineColor(sf::Color::Black);
	rightBoardSizeArrowText.setOutlineThickness(2);
	rightBoardSizeArrowText.setPosition(windowWidth / 2 + boardSizeText.getGlobalBounds().width / 2 + 10,
		windowHeight / 2); // Adjust position as needed

	// Difficulty Logic
	GameMode selectedGameMode = GameMode::EASY;

	std::string selectedDifficulty = "Easy";

	while (window->isOpen() && !exitClicked) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				return; // Exit the method if the window is closed
			}
			else if (event.type == sf::Event::Resized)
			{
				sf::Vector2u newSize(event.size.width, event.size.height);
				if (newSize.x < MIN_WINDOW_WIDTH || newSize.y < MIN_WINDOW_HEIGHT) {
					newSize.x = std::max(newSize.x, MIN_WINDOW_WIDTH);
					newSize.y = std::max(newSize.y, MIN_WINDOW_HEIGHT);
					window->setSize(newSize);
				}
				windowWidth = static_cast<float>(newSize.x);
				windowHeight = static_cast<float>(newSize.y);

				// Window has been resized, recalculate the grid parameters
				updateWindowSize();
				view.setSize(windowWidth, windowHeight);
				window->setView(view);
				view.setSize(windowWidth, windowHeight);
				window->setView(view);
				updateUIElements();
				exitText.setCharacterSize(30);
				startText.setCharacterSize(30);
				levelchange.setCharacterSize(30);
				difficultyText.setCharacterSize(30);
				leftArrowText.setCharacterSize(30);
				rightArrowText.setCharacterSize(30);
				boardSizeText.setCharacterSize(30);
				leftBoardSizeArrowText.setCharacterSize(30);
				rightBoardSizeArrowText.setCharacterSize(30);

			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				// Check if the mouse click is within the bounds of the "Exit" text
				sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				if (exitText.getGlobalBounds().contains(mousePos)) {
					window->close(); // Close the window if "Exit" is clicked
					exitClicked = true; // Set the flag to exit the loop
				}

				// Check if the mouse click is within the bounds of the buttons
				if (leftArrowText.getGlobalBounds().contains(mousePos)) {

					// Cycle to the previous difficulty level
					switch (selectedGameMode) {
					case GameMode::EASY:
						selectedGameMode = GameMode::DEBUG;
						selectedDifficulty = "Debug";
						window->draw(difficultyText);
						break;
					case GameMode::NORMAL:
						selectedGameMode = GameMode::EASY;
						selectedDifficulty = "Easy";
						break;
					case GameMode::HARD:
						selectedGameMode = GameMode::NORMAL;
						selectedDifficulty = "Normal";
						break;
					case GameMode::DEBUG:
						selectedGameMode = GameMode::HARD;
						selectedDifficulty = "Hard";
						break;
					}
					difficultyText.setString(selectedDifficulty);
					difficultyText.setPosition(windowWidth / 2 - difficultyText.getGlobalBounds().width / 2, windowHeight / 2 - 50);
					// Adjust position as needed

				}
				else if (rightArrowText.getGlobalBounds().contains(mousePos)) {
					// Cycle to the next difficulty level
					switch (selectedGameMode) {
					case GameMode::EASY:
						selectedGameMode = GameMode::NORMAL;
						selectedDifficulty = "Normal";
						break;
					case GameMode::NORMAL:
						selectedGameMode = GameMode::HARD;
						selectedDifficulty = "Hard";
						break;
					case GameMode::HARD:
						selectedGameMode = GameMode::DEBUG;
						selectedDifficulty = "Debug";
						break;
					case GameMode::DEBUG:
						selectedGameMode = GameMode::EASY;
						selectedDifficulty = "Easy";
						break;
					}
					difficultyText.setString(selectedDifficulty);
					difficultyText.setPosition(windowWidth / 2 - difficultyText.getGlobalBounds().width / 2, windowHeight / 2 - 50);
					// Adjust position as needed


				}
				else  if (leftBoardSizeArrowText.getGlobalBounds().contains(mousePos)) {
					boardSize = std::max(boardSize - 1, 3); // Decrease board size, but not below 1
				}
				else if (rightBoardSizeArrowText.getGlobalBounds().contains(mousePos)) {
					boardSize = std::min(boardSize + 1, MAX_BOARD_SIZE); // Increase board size, but not above MAX_BOARD_SIZE
				}
				else if (startText.getGlobalBounds().contains(mousePos)) {
					// Start the game with the selected game mode
					startGame(window, boardSize, selectedGameMode);

				}

				boardSizeText.setString("Board Size: " + std::to_string(boardSize));
				boardSizeText.setPosition(windowWidth / 2 - boardSizeText.getGlobalBounds().width / 2,
					windowHeight / 2); // Adjust position as needed
			}

		}

		// Draw UI elements
		window->clear();
		window->draw(levelchange);
		window->draw(exitText);
		window->draw(difficultyText);
		window->draw(startText);
		window->draw(leftArrowText);
		window->draw(rightArrowText);
		window->draw(boardSizeText);
		window->draw(leftBoardSizeArrowText);
		window->draw(rightBoardSizeArrowText);
		window->display();
	}
}

void SplashScreen::displayUI() {

	//// Wait for a moment to show the Minesweeper 3D image
	sf::sleep(sf::seconds(2));

	// Clear the window before displaying the main menu
	window->clear();
	//window.reset();
	// Display the main menu
	displayMainMenu();

}
