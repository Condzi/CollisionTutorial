#include <iostream>
#include <SFML/Graphics.hpp>

#include "SimpleEntity.hpp"
#include "CollisionChecker.hpp"

int main()
{
	sf::RenderWindow window( { 800u,600u }, "Collision Tutorial", sf::Style::Close );
	window.setFramerateLimit( 60u );
	sf::Event event;

	CollisionChecker checker;
	auto entityA = std::make_shared<SimpleEntity>();
	auto entityB = std::make_shared<SimpleEntity>();

	entityA->rectangle.width = 100;
	entityA->rectangle.height = 100;
	entityA->SetPosition( { 0,250 } );
	entityA->velocity = { 100.0f, 0.0f };

	entityB->rectangle = entityA->rectangle;
	entityB->SetPosition( { 700,250 } );
	entityB->velocity = { 0.0f,0.0f };

	checker.AddCollider( entityA );
	checker.AddCollider( entityB );

	entityA->Update( 1.0f / 60 );
	entityB->Update( 1.0f / 60 );

	while ( window.isOpen() )
	{
		while ( window.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed )
				window.close();
			if ( event.type == sf::Event::KeyReleased )
				if ( event.key.code == sf::Keyboard::Escape )
					window.close();
		}

		checker.Update( 1.0f / 60 );
		
		entityA->Update( 1.0f / 60 );
		entityB->Update( 1.0f / 60 );

		window.clear();
	
		entityA->Draw( window );
		entityB->Draw( window );

		window.display();
	}

	return 0;
}