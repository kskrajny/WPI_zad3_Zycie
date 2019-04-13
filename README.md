Życie
Wprowadzenie

Stworzona przez Johna Conwaya Gra w Życie to automat komórkowy, czyli symulacja świata komórek.

Symulacja jest prowadzona na planszy, składającej się z nieskończenie wielu wierszy i nieskończenie wielu kolumn.

Wiersze i kolumny planszy są numerowane liczbami całkowitymi ze znakiem.

Na każdym polu planszy jest komórka w jednym z dwóch stanów: żywa lub martwa.

Łączny stan wszystkich komórek nazywamy generacją.

Przyjmujemy, że komórka w wierszu w i kolumnie k sąsiaduje na planszy z ośmioma innymi komórkami, które mają numer wiersza od w - 1 do w + 1 a numer kolumny od k - 1 do k + 1.

Symulacja zaczyna się od pewnej generacji początkowej, na podstawie której liczymy następne.

W następnej generacji komórka jest żywa wtedy i tylko wtedy, gdy:

    w bieżącej generacji jest żywa i ma dwóch lub trzech żywych sąsiadów, albo

    w bieżącej generacji jest martwa i ma trzech żywych sąsiadów.

Polecenie

Napisz program symulujący Grę w Życie.

Program czyta z wejścia i pisze na wyjście opis generacji początkowej a następnie czyta i wykonuje polecenia użytkownika.

Polecenia sterują liczeniem i wypisywaniem kolejnych generacji.
Postać danych i wyniku

Na wejściu programu jest opis generacji początkowej i ciąg poleceń.

Wiersze wejścia, oraz znaki w wierszu, numerujemy od 1.

Opis generacji na wejściu programu jest ciągiem wierszy, z których wszystkie, z wyjątkiem ostatniego, są niepuste, a ostatni jest pusty.

W niepustych wierszach wejściowego opisu generacji znak 0 (zero) reprezentuje komórkę żywą a każdy inny znak reprezentuje komórkę martwą.

Niech W będzie liczbą niepustych wierszy opisu generacji początkowej a K będzie maksimum z długości tych wierszu lub 0, jeżeli W to 0.

W generacji początkowej komórka z wiersza planszy o numerze w i kolumny planszy o numerze k jest żywa wtedy i tylko wtedy, gdy w jest w przedziale od 1 do W, k jest w przedziale od 1 do K i k-tym znakiem w-tego wiersza wejścia jest 0.

Opis generacji na wyjściu programu jest ograniczony do prostokątnego okna, wyznaczonego przez cztery liczby całkowite A B C D, nazywane dalej współrzędnymi okna:

    A to numer pierwszego wypisywanego wiersza,

    B to numer pierwszej wypisywanej kolumny,

    C to numer ostatniego wypisywanego wiersza,

    D to numer ostatniej wypisywanej kolumny.

Początkowo okno ma współrzędne 1 1 W K.

Jeśli aktualnym oknem jest A B C D, to opis generacji na wyjściu programu składa się z C - A + 1 wierszy, w każdym po D - B + 1 znaków. Jeden znak odpowiada jednej komórce. Komórka żywa jest reprezentowana przez znak 0 (zero) a komórka martwa przez znak . (kropka).

Po każdej generacji program pisze wiersz ze statusem, czyli informacją o aktualnym stanie.

Status ma format:

A {B} (C:D) (E:F) [G:H] [I:J]

gdzie:

    A to numer generacji, dla generacji początkowej równy 0,

    B to liczba żywych komórek,

    C to numer pierwszego wiersza na planszy, w którym jest żywa komórka,

    D to numer pierwszej kolumny na planszy, w której jest żywa komórka,

    E to numer ostatniego wiersza na planszy, w którym jest żywa komórka,

    F to numer ostatniej kolumny na planszy, w której jest żywa komórka,

    G H I J to aktualne współrzędne okna.

Jeśli B jest zerem, to jako C, D, E, F piszemy zera.

Po opisie generacji początkowej, na wejściu programu jest ciąg jednowierszowych poleceń.

Polecenie składa się z ciągu liczb całkowitych, rozdzielonych pojedynczymi spacjami.

Rozpoznajemy polecenia postaci:

    polecenie puste,

    Oblicz i wypisz następną generację.

    jedna, nieujemna, liczba całkowita N,

    Oblicz i wypisz N-tą kolejną generację.

    Polecenie puste jest więc równoważne poleceniu 1.

    dwie liczby całkowite A B,

    Zmień dwie pierwsze współrzędne okna, czyli współrzędne lewego górnego rogu, na A B.

    Jednocześnie zaktualizuj dwie pozostałe współrzędne okna, czyli współrzędne prawego dolnego rogu tak, rozmiar okna się nie zmienił.

    Po zmianie okna, wypisz aktualną generację.

    cztery liczby całkowite A B C D.

    Zmień współrzędne okna na A B C D.

    Po zmianie okna, wypisz aktualną generację.

Polecenia zmiany okna nie powodują obliczenia kolejnej generacji.
