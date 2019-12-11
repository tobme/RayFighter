#ifndef LIB_H
#define LIB_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <random>

class Texture_lib
{
protected:
    sf::Texture& getTexture(std::string const &);
private:
    static std::map<std::string,sf::Texture> lib;
};


class The_font
{
protected:
    sf::Font& getFont();
private:
    static bool loaded;
    static sf::Font font;
};


class Sound_lib
{
public:
	static void Empty();
protected:
	void setVolume(int const & vol);
	int getVolume();
	void playSound(std::string const &,int const & vol = 50);
	void playSoundRP(std::string const &,int const & vol = 50);
private:
	static std::random_device r;
	static std::mt19937 mt;
	static int volume;
    static std::map<std::string,sf::SoundBuffer> lib;
	static std::map<std::string,sf::Sound> slib;
};

#endif
