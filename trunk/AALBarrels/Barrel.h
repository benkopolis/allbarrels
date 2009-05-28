/*
 * Barrel.h
 *
 *  Created on: 2009-03-13
 *      Author: zby
 */

#ifndef BARREL_H_
#define BARREL_H_


namespace AALBarrels // name space
{

class Barrel
{
public:

	enum Color
	{
		NONE=0, RED, BLUE, GREEN
	};

	Barrel();
	Barrel(Color c);
	Barrel(Color c, Barrel *p, Barrel *n);

	Barrel(const Barrel& another);

	virtual ~Barrel();

	Color getColor() const;
	void setColor(Color c);

	char printBarrel() const;
	static Barrel readBarrel(char c);

	/**
	 * zwraca -1 gdy it ma wiekszy priorytet od this, 0 gdy maja taki sam i
	 * 1 gdy it ma mniejszy priorytet od this
	 * -1 : true it > this
	 *  0 : true it == this
	 *  1 : true it < this
	 */
	int compareBarrels(const Barrel &it) const;

	/**
	 * @brief zwraca wskaznik do nastepnej beczki
	 * @return zwraca wskaznik next
	 */
	Barrel* next() const;

	/**
	 * @brief zwraca wskaznik do poprzedniej beczki
	 * @return zwraca wskaznik prev
	 */
	Barrel* prev() const;

	/**
	 * @brief ustawia nowy wskaznik na nastepna beczke
	 * @praram a - wskaznik na nowa nastepna beczke
	 */
	void setNext(Barrel *a);

	/**
	 * @brief ustawia nowy wskaznik na poprzednia beczke
	 * @param a - wskaznik na nowa nastepna beczke
	 */
	void setPrev(Barrel *a);

	/**
	 * @brief ustawia oba wskazniki beczki na nowe
	 * @param p - wskaznik do poprzedniej beczki
	 * @param n - wskaznik do nastepnej beczki
	 */
	void setPtr(Barrel *p, Barrel *n);

private:
	Color color;

	Barrel *_next;

	Barrel *_prev;
};


};


#endif /* BARREL_H_ */
