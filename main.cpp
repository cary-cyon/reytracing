#include <random>
#include <SFML/Graphics.hpp>

int main() {
	//размеры окна w - ширина h - высота
	int w = 1700, h = 1080;
	sf::Vector3f pos = sf::Vector3f(1.0f, 0.0f, 0.0f);
	//окно для рендера размена W на h
	sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Titlebar | sf::Style::Close);
	//установка количества кадров в секунду
	//window.setFramerateLimit(60);
	//включение вертикальной синхронизации 
	window.setVerticalSyncEnabled(true);
	//текстура размера w, h
	sf::RenderTexture firstTexture;
	firstTexture.create(w, h);
	//сплайн для текстуры
	sf::Sprite firstTextureSprite = sf::Sprite(firstTexture.getTexture());
	//выходная текстура 
	sf::RenderTexture outputTexture;
	outputTexture.create(w, h);
	//выходной сплайн для текстуры 
	sf::Sprite outputTextureSprite = sf::Sprite(outputTexture.getTexture());
	sf::Shader shader;
	//подключение шейдера 
	shader.loadFromFile("RayShаder.frag", sf::Shader::Fragment);
	//передача разрещения
	shader.setUniform("u_resolution", sf::Vector2f(w, h));
	//позиция камеры
	shader.setUniform("u_pos", pos);
	//главный цикл программы 
	while (window.isOpen())
	{
		//цикл обработки событий 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}
		//отрисовка нового кадра
		shader.setUniform("u_sample", firstTexture.getTexture());
		firstTexture.draw(firstTextureSprite, &shader);
		window.draw(firstTextureSprite);
		window.display();
	}
}