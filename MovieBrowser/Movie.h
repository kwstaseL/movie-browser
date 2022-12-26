#ifndef MOVIE_H
#define MOVIE_H

#include "sgg/graphics.h"
#include "constants.h"
#include <string>
#include <string_view>
#include <vector>


struct Box
{
private:

	float m_posX{};
	float m_posY{};

public:

	void setPosX(float x) { m_posX = x; }
	void setPosY(float y) { m_posY = y; }

	float getPosX() const { return m_posX; }
	float getPosY() const { return m_posY; }

};

class Movie
{
private:

	float m_pos[2];

	std::string m_name{};

	Box informationBox;

	const std::string m_description{};
	const std::string m_image{};
	const std::string m_production_year{};
	const std::string m_director{};

	std::vector<std::string> m_protagonists;

	float m_glow{};
	float m_highlight{};

	bool m_highlighted{ false };
	bool m_PlaySound{ true };

	bool hasFilteredGenre{ true };
	bool hasFilteredText{ true };

	int lastYearComparedfromTo{ 2020 };
	int lastYearComparedFrom{ 1950 };

	int m_genreCount{ 0 };

	bool m_active{ true };
	bool m_disabled{ false };
	bool m_clickTriggered{ false };

	bool contains(float x, float y) const;

	void DisplayInfo();

	class graphics::Brush brush_update1;
	class graphics::Brush brush_update2;
	class graphics::Brush br;

public:

	std::vector<std::string> genres;

	Movie(const std::string_view n, const std::string_view desc,
		const std::string_view image, const std::string_view year, const std::string_view dir,
		const std::vector<std::string>& prot, const std::vector<std::string>& genre);

	void draw();
	void update();

	void drawInformation();

	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

	int getGenreCount() const { return m_genreCount; }
	void resetGenreCount() { m_genreCount = 0; }
	void AddGenreCount(int g) { m_genreCount += g; }

	void setDisabled(bool d) { m_disabled = d; }
	bool isDisabled() const { return m_disabled; }

	bool isClickTriggered() const { return m_clickTriggered; }

	void setHighlight(bool h) { m_highlighted = h; }

	void setActive(bool a) { m_active = a; }
	bool isActive() const { return m_active; }

	// Control Variables

	void sethasFilteredGenre(bool g) { hasFilteredGenre = g; }
	bool gethasFilteredGenre() const { return hasFilteredGenre; }

	void setLastYearComparedfromTo(int y) { lastYearComparedfromTo = y; }
	int getLastYearComparedfromTo() const { return lastYearComparedfromTo; }

	void setLastYearComparedFrom(int y) { lastYearComparedFrom = y; }
	int getLastYearComparedFrom() const { return lastYearComparedFrom; }

	bool getHasFilteredText() const { return hasFilteredText; }
	void sethasFilteredText(bool t) { hasFilteredText = t; }

	//Info

	const std::string& getName() const;
	const std::string& getDesc() const;
	const std::string& getDate() const;
	const std::string& getDir() const;
};

#endif