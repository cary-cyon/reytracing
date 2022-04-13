#include <random>
#include <SFML/Graphics.hpp>

int main() {
	//������� ���� w - ������ h - ������
	int w = 1700, h = 1080;
	sf::Vector3f pos = sf::Vector3f(1.0f, 0.0f, 0.0f);
	//���� ��� ������� ������� W �� h
	sf::RenderWindow window(sf::VideoMode(w, h), "Ray tracing", sf::Style::Titlebar | sf::Style::Close);
	//��������� ���������� ������ � �������
	//window.setFramerateLimit(60);
	//��������� ������������ ������������� 
	window.setVerticalSyncEnabled(true);
	//�������� ������� w, h
	sf::RenderTexture firstTexture;
	firstTexture.create(w, h);
	//������ ��� ��������
	sf::Sprite firstTextureSprite = sf::Sprite(firstTexture.getTexture());
	//�������� �������� 
	sf::RenderTexture outputTexture;
	outputTexture.create(w, h);
	//�������� ������ ��� �������� 
	sf::Sprite outputTextureSprite = sf::Sprite(outputTexture.getTexture());
	sf::Shader shader;
	//����������� ������� 
	shader.loadFromFile("RaySh�der.frag", sf::Shader::Fragment);
	//�������� ����������
	shader.setUniform("u_resolution", sf::Vector2f(w, h));
	//������� ������
	shader.setUniform("u_pos", pos);
	//������� ���� ��������� 
	while (window.isOpen())
	{
		//���� ��������� ������� 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}
		//��������� ������ �����
		shader.setUniform("u_sample", firstTexture.getTexture());
		firstTexture.draw(firstTextureSprite, &shader);
		window.draw(firstTextureSprite);
		window.display();
	}
}