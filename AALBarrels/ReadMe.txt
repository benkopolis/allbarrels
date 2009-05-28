Autor: Zbigniew Manasterski

Zadania: Sortowanie beczek znajdujących się na równi pochyłej. Można podnosić beczki trójkami i przenosić je tylko na górę równi pochyłej. 
Beczki są w 3 kolorach (czerwone, niebieskie i zielone - w takiej kolejności mają być posortowane) i zawsze są minimum 3 zielone beczki.

Wszystkie informacje dla programu trzeba zawrzec w pliku inicjalizacyjnym, ktorego przyklad mozna znaleźć w pliku example.ini

Program można uruchomić bezargumentowo albo w argumencie podać nazwę pliku .ini. Gdy taka nazwa nie zostanie podana, program domyślnie otworzy plik
example.ini.


/**
 * Skladnia programu:
 *
 * ponizsze musza byc stosowane ZAMIENNIE
 * 		-g <ilosc beczek do generacji[def]> - korzysta z wewnetrzengo generatora losowego
 * 		-gout <ilosc beczek do generacji> <nazwa pliku> generuje dane losowe do podanego pliku
 * 		-in <nazwapliku> korzysta z danych wejsciowych zawartych w pliku
 * 		-cin - pobiera dane wejsciowe z konsoli
 *
 * -time  	- mierzy czasy dzialania, zapisuje w tabeli, na koniec drukuje do pliku
 * -show	- pokazuje przebieg algorytmu NIE POLECAM UZYWAC DLA DUZYCH ILOSC DANYCH
 * -seq <ilosc powtorzen[def: 10]> <krotnosc zmiany liczby danych - JEZELI 1 to dodaje ilosc danych do lacznej
 * 		sumy za kazdym powtorzeniem[def: 1]> <sposob wpisania danych[default:	-g 1000	]>
 * 	-table <filename>	- wygeneruje tabelke - automatycznie wlacza opcje time oraz defaultowa opcje seq,
 * 						  chyba ze seq bedzie podane.
 *
 * brak polecen uruchomi to:
 * 		./prog show -seq 10 1 -g 1000
 */
