#include "library.h"

sf::Texture& Texture_lib::getTexture(std::string const & s)
{
    auto search = lib.find(s);
    if(search == lib.end())
    {
        sf::Texture text;
        if(!text.loadFromFile("texture/" + s))throw std::logic_error(s + "texture missing ");
        Texture_lib::lib[s] = text;
    }
    return lib[s];
}
std::map<std::string,sf::Texture> Texture_lib::lib{};


sf::Font& The_font::getFont()
{
    if(!The_font::loaded)
    {
        font.loadFromFile("font/arial.ttf");
        The_font::loaded = true;
    }
    return font;
}
bool The_font::loaded{false};
sf::Font The_font::font{};


void Sound_lib::Empty()
{
	slib.clear();
	lib.clear();
}

void Sound_lib::setVolume(int const & vol)
{
	volume = vol;
}
int Sound_lib::getVolume()
{
    return volume;
}
void Sound_lib::playSoundRP(std::string const & s,int const & vol)
{
	std::uniform_int_distribution<> dis(0,20);
	float pitch = dis(mt);
	pitch = pitch / 10;

    auto search = lib.find(s);
    if(search == lib.end())
    {
        sf::SoundBuffer sound;
        if(!sound.loadFromFile("audio/" + s))throw std::logic_error(s + "sound missing ");
        Sound_lib::lib[s] = sound;
    }
    slib[s] = sf::Sound(lib[s]);
	float f = vol;
	f = (f/100) * volume;
	slib[s].setVolume(f);
	slib[s].setPitch(pitch);
	slib[s].play();
}
void Sound_lib::playSound(std::string const & s,int const & vol)
{
    auto search = lib.find(s);
    if(search == lib.end())
    {
        sf::SoundBuffer sound;
        if(!sound.loadFromFile("audio/" + s))throw std::logic_error(s + "sound missing ");
        Sound_lib::lib[s] = sound;
    }
    slib[s] = sf::Sound(lib[s]);
	float f = vol;
	f = (f/100) * volume;
	slib[s].setVolume(f);
	slib[s].play();
}
std::random_device Sound_lib::r{};
std::mt19937 Sound_lib::mt{r()};
int Sound_lib::volume{100};
std::map<std::string,sf::SoundBuffer> Sound_lib::lib{};
std::map<std::string,sf::Sound> Sound_lib::slib{};
