#include <stdlib.h>
#include <stdio.h>

int A = 0;
int B = 0;
int C = 1;
int D = 1;
int E = 1;
int F = 1;
int G = 1;
int H = 1;
int I = 0;
int J = 0;

struct komorka
{
    int wiersz;
    int kolumna;
    int sasiedzi;
};


struct KL	/// lista komorek znajdujacych sie w jednym wierszu
{
    struct komorka kom;
    struct KL *popL;
    struct KL *nastL;
};

struct WL	/// lista niepustych wierszy
{
    struct KL *lista;	/// wskaznik dzieki ktoremu bedziemy sie przemieszczac po liscie komorek w wierszu KL
    struct WL *nastLL;
    struct WL *popLL;
    struct KL *pierwsza; /// wskaznik na pierwszy element listy komorek w wierszu KL (ten element nie zawiera komorki, pierwsza->nastL zawiera)
    struct WL *poczatek; /// poczatek listy niepustych wierszy
};

void wczytaj();
void nowa_w_wierszu();
void nowa_kolumna();
void wypisz();
void zwolnij();
void pomoc();
void zmien_okno2();
void zmien_okno4();
void przedstaw_generacje();
void wczytaj_polecenie();
struct WL *licz_n_generacje();
struct WL *generuj();
struct WL *zostaw_zywe();
struct WL *czysc();

struct WL *Wiersze;

int main()
{
	///przygotowanie struktury do trzymania generacji
    Wiersze = malloc(sizeof(struct WL));
    Wiersze->nastLL = NULL;
    Wiersze->popLL = NULL;
    Wiersze->poczatek = Wiersze;
    struct KL *p;
    p = malloc(sizeof(struct KL));
    p->popL = NULL;
    p->nastL = NULL;
    Wiersze->lista = p;
    Wiersze->pierwsza = Wiersze->lista;
    
    	///wczytywanie generacji 0
    wczytaj(Wiersze->poczatek);
    
	/// wypisanie generacji 0
    wypisz(Wiersze->poczatek);
    
	/// wypisanie statusu generacji 0
    przedstaw_generacje();
    
	/// wykonanie polecen
    wczytaj_polecenie();
    
	/// zwolnienie struktury danych
    zwolnij(Wiersze->poczatek);

    return 0;
}

void wczytaj_polecenie()
{
    int a;
    int b;
    int c;
    int d;
    int czyt = getchar();
    while(czyt != EOF)
    {
        if(czyt == '\n')
        {
            Wiersze = licz_n_generacje(1, Wiersze->poczatek); /// Wiersze to zmienna globalna
            Wiersze->poczatek = Wiersze;
        }
        else
        {
            ungetc(czyt,stdin);
            scanf("%d", &a);
            czyt = getchar();
            if(czyt == '\n' || czyt == EOF)
            {
                Wiersze = licz_n_generacje(a, Wiersze->poczatek);
                Wiersze->poczatek = Wiersze;
            }
            else
            {
                scanf("%d", &b);
                czyt = getchar();
                if(czyt == '\n' || czyt == EOF)
                {
                    zmien_okno2(a, b);
                    wypisz(Wiersze->poczatek);
                    przedstaw_generacje();
                }
                else
                {
                    scanf("%d", &c);
                    czyt = getchar();
                    scanf("%d", &d);
                    czyt = getchar();
                    zmien_okno4(a, b, c, d);
                    wypisz(Wiersze->poczatek);
                    przedstaw_generacje();

                }
            }
        }
        czyt = getchar(); /// na koncu wczytujemy jeszcze jeden znak konca lini
    }

}

void przedstaw_generacje() /// wypisanie statusu
{
    printf("%d {%d} (%d:%d) (%d:%d) [%d:%d] [%d:%d]\n", A, B, C, D, E, F, G, H, I, J);
}

void zmien_okno4(int g, int h, int i, int j) /// zmiana okna gdy w poleceniu pojawia sie 4 liczby
{
    G = g;
    H = h;
    I = i;
    J = j;
}

void zmien_okno2(int g, int h) /// zmiana okna gdy w poleceniu pojawia sie 2 liczby
{
    I = I-G+g;
    J = J-H+h;
    G = g;
    H = h;
}

struct WL *licz_n_generacje(int n, struct WL *Wiersze) /// liczy n nastepnych generacji
{
    struct WL *pom;
    for(int i=0; i<n; i++)
    {
	/* tworzymy pomocnicza strukture danych w ktorej beda wszystkie komorki ktore byly zywe w popzredniej generacji 
	lub komorki posiadajace zywych sasiadow, w tej strukturze przeliczona jest ilosc sasiadow kazdej komorki */
        pom = generuj(Wiersze->poczatek); 
        pom->poczatek = pom;
        zwolnij(Wiersze->poczatek);
	/// tutaj tworzymy kolejna pomocnicza strukture, w ktorej bede tylko te komorki, ktore przezyly lub ozyly
        Wiersze = zostaw_zywe(pom->poczatek);
        Wiersze->poczatek = Wiersze;
        zwolnij(pom->poczatek);
    }
    wypisz(Wiersze->poczatek);
    przedstaw_generacje();
    return Wiersze->poczatek;
}

void pomoc(struct WL *W) /// funkcja pomocnicza, wypisuje zawartosc struktur
{
    while(W->pierwsza->nastL != NULL)
    {
        W->lista = W->pierwsza->nastL;
        while(W->lista != NULL)
        {
            printf("%d %d %d\n", W->lista->kom.kolumna, W->lista->kom.wiersz, W->lista->kom.sasiedzi);
            if(W->lista->nastL == NULL)
            {
                break;
            }
            W->lista = W->lista->nastL;
        }
        printf("\n");
        if(W->nastLL == NULL)
        {
            break;
        }
        W = W->nastLL;
    }
}
void nowa_w_wierszu(struct KL *aktualna, int kol, int w) /// dodaje nowa komorke 
{
    struct komorka nowa;
    nowa.wiersz = w;
    nowa.kolumna = kol;
    nowa.sasiedzi = 0;

    struct KL *pom;
    pom = malloc(sizeof(struct KL));
    pom->nastL = aktualna->nastL;
    pom->kom = nowa;
    aktualna->nastL = pom;
    aktualna->nastL->popL = aktualna;
}

void nowy_wiersz(struct WL *aktualny) /// dodaje nowy wiersz
{
    struct KL *pierwszy;
    pierwszy = malloc(sizeof(struct KL));
    pierwszy->popL = NULL;
    pierwszy->nastL = NULL;

    struct WL *pom;
    pom = malloc(sizeof(struct WL));
    pom->nastLL = aktualny->nastLL;
    aktualny->nastLL = pom;
    pom->popLL = aktualny;
    pom->poczatek = aktualny->poczatek;
    pom->lista = pierwszy;
    pom->pierwsza = pierwszy;

}

void wczytaj()	/// wczytuje generacje 0
{
    int w = 1; /// oznacza numer wiersza
    int k = 1; /// oznacza numer kolumny
    int a; /// sluzy do wczytywania znakow
    int ustal = 1; /// bool, mowi czy poczatkowe wartosci CDEF zostaly juz ustalony
    int tylko_linia = 1; 
    /* bool, mowi czy na wejsciu znajduje sie tylko jedna linia czy nie'	
    uzyte gdyz EOFy sa czasami dziwnie kodowane, bez tego nie dziala*/
    while(1)
    {
        int czy_pusty = 1;
        a = getchar();
        if(a == EOF)
        {
            return;
        }
        if(a == '\n') /// wtedy konczymy wczytywanie, gdyz pierwszym znakiem w lini jest znak konca lini
        {
            I = w-1; 
            if(B == 0)
            {
                C = 0;
                D = 0;
                E = 0;
                F = 0;
            }
            if(tylko_linia == 1)
            {
                getchar();
            }
            return;
        }
        tylko_linia = 0;
        ungetc(a, stdin);
        while(a != '\n')
        {
            if(k > J)
            {
                J = k-1;
            }
            a = getchar();
            if(a == '0')
            {
                E = w;
                czy_pusty = 0;
                if(ustal == 1)
                {
                    C = w;
                    F = k;
                    D = k;
                    ustal = 0;
                }
                if(k < D)
                {
                    D = k;
                }
                if(k > F)
                {
                    F = k;
                }
                nowa_w_wierszu(Wiersze->lista, k, w);
                B++;
                Wiersze->lista = Wiersze->lista->nastL;
            }
            k++;
        }
        k = 1;
        w++;
        if(czy_pusty == 0)
        {
            nowy_wiersz(Wiersze);
            Wiersze = Wiersze->nastLL;
        }
    }
}
void wypisz(struct WL *T) /// wypisujemy generacje
{

    struct WL *wiersze = T;
    int w;
    int k;
    if(wiersze == NULL)
    {
        for(int i=G; i<I+1; i++)
        {
            for (int j=H; j<J+1; j++)
            {
                printf(".");
            }
        }
        printf("\n");
    }
    else
    {
        for(int i=G; i<I+1; i++)
        {
            if(wiersze == NULL || wiersze->pierwsza->nastL == NULL)
            {
                for (int j=H; j<J+1; j++)
                {
                    printf(".");
                }
            }
            else
            {
                while(wiersze->pierwsza->nastL->kom.wiersz < i)
                {
                    if(wiersze->nastLL->pierwsza->nastL != NULL)
                    {
                        wiersze = wiersze->nastLL;
                    }
                }
                wiersze->lista = wiersze->pierwsza->nastL;
                for (int j=H; j<J+1; j++)
                {

                    if(wiersze->lista->kom.kolumna < j)
                    {
                        if(wiersze->lista->nastL != NULL)
                        {
                            wiersze->lista = wiersze->lista->nastL;
                        }
                    }
                    if(wiersze->lista != NULL)
                    {
                        w = wiersze->lista->kom.wiersz;
                        k = wiersze->lista->kom.kolumna;
                    }
                    if(w==i && k==j)
                    {
                        printf("0");
                        if(wiersze->lista->nastL != NULL)
                        {
                            wiersze->lista = wiersze->lista->nastL;
                        }
                    }
                    else
                    {
                        printf(".");
                    }
                }
                if(wiersze->pierwsza->nastL->kom.wiersz == i)
                {
                    wiersze = wiersze->nastLL;
                }
            }
            printf("\n");
        }
    }
}
void zwolnij(struct WL *T) /// zwalnia pamiec
{
    while(T != NULL)
    {
        int koniec = 0;
        T->lista = T->pierwsza;
        while(koniec == 0 && T->lista != NULL)
        {
            struct KL *a = T->lista;
            if(T->lista->nastL != NULL)
            {
                T->lista = T->lista->nastL;
            }
            else
            {
                koniec = 1;
            }
            free(a);
        }
        struct WL *b = T;
        T = T->nastLL;
        free(b);
    }
}

void generuj3(struct KL *a, struct KL *t, int i) /// zmienia liczbe sasiadow do 3 komorek w jednym wierszu
{
    int w = t->kom.wiersz;
    int k = t->kom.kolumna;
    for(int j=-1; j<2; j++)
    {
        int czy_robic = 1;
        while(a->nastL != NULL)
        {
            if(a->nastL->kom.kolumna < k+j)
            {
                a = a->nastL;
            }
            else
            {
                if(a->nastL->kom.kolumna == k+j)
                {
                    if(j != 0 || i != 0)
                    {
                        a->nastL->kom.sasiedzi++;
                    }
                    a = a->nastL;
                    if(j==0 && i ==0)
                    {
                        a->kom.sasiedzi += 10;/// dodajemy 10 jesli w poprzedniej generacji komorka byla zywa aby bylo latwiej
                    }
                }
                else
                {
                    nowa_w_wierszu(a, k+j, w+i);
                    B++;
                    if(j != 0 || i != 0)
                    {
                        a->nastL->kom.sasiedzi++;
                    }
                    a = a->nastL;
                    if(j==0 && i ==0)
                    {
                        a->kom.sasiedzi += 10;
                    }
                }
                czy_robic = 0;
            }
            if(czy_robic == 0)
            {
                break;
            }
        }
        if(a->nastL == NULL && czy_robic == 1)
        {
            nowa_w_wierszu(a, k+j, w+i);
            B++;
            if(j != 0 || i != 0)
            {
                a->nastL->kom.sasiedzi++;
            }
            a = a->nastL;
            if(j==0 && i==0)
            {
                a->kom.sasiedzi += 10;
            }
        }
    }
    a = a->popL->popL;
}

struct WL *generuj(struct WL *T) /// tworzenie nowej generacji
{
    A++;
    /// tworzymy nowa strukture
    struct WL *wiersze;
    wiersze = malloc(sizeof(struct WL));
    wiersze->nastLL = NULL;
    wiersze->popLL = NULL;
    wiersze->poczatek = wiersze;
    struct KL *p;
    p = malloc(sizeof(struct KL));
    p->popL = NULL;
    p->nastL = NULL;
    wiersze->lista = p;
    wiersze->pierwsza = wiersze->lista;
    /// poniewaz jedna komorka ma sasiadow w trzech roznych wierszach, tworzymy na poczatku trzy wiersze w nowej strukturze
    nowy_wiersz(wiersze);
    nowy_wiersz(wiersze->nastLL);
    int nast_w, ost_w; /* zmienne ktore mowia ile jest pustych wierszy pomiedzy zywymi komorkami,
    beda uzyte do okreslenia liczby nowych wierszy, ktore nalezy stworzyc w nowej strukturze*/
    if(T->pierwsza == NULL)
    {
        return wiersze->poczatek;
    }
    while(T->pierwsza->nastL != NULL)
    {
        T->lista = T->pierwsza->nastL;
        ost_w = T->lista->kom.wiersz;
	/// ustawiamy wskaniki na poczatki list(wierszy)
        wiersze->nastLL->nastLL->lista = wiersze->nastLL->nastLL->pierwsza;
        wiersze->nastLL->lista = wiersze->nastLL->pierwsza;
        wiersze->lista = wiersze->pierwsza;
        while(T->lista != NULL) /// modyfikujemy liczbe sasiadow w trzech wierszach 
        {
            generuj3(wiersze->lista, T->lista, -1);
            generuj3(wiersze->nastLL->lista, T->lista, 0);
            generuj3(wiersze->nastLL->nastLL->lista, T->lista, 1);
            if(T->lista->nastL == NULL)
            {
                break;
            }
            T->lista = T->lista->nastL;
        }
        if(T->nastLL->pierwsza->nastL == NULL)
        {
            nowy_wiersz(wiersze->nastLL->nastLL);
            return wiersze->poczatek;
        }
        T = T->nastLL;
        nast_w = T->pierwsza->nastL->kom.wiersz;
        int ile;	
	/// w zaleznosci od liczby pustych wierszy pomiedzy niepustymi tworzymy nowe wiersze w nowej strukturze
        if (nast_w-ost_w < 3)
        {
            ile = nast_w-ost_w ;
        }
        else
        {
            ile = 3;
        }
        for (int i=0; i<ile; i++)
        {
            nowy_wiersz(wiersze->nastLL->nastLL);
            wiersze = wiersze->nastLL;
        }
    }
    /// tworzymy ostatni pusty wiersz jako straznika
    nowy_wiersz(wiersze->nastLL->nastLL);
    return wiersze->poczatek;
}

struct WL *zostaw_zywe(struct WL *pom) /// tworzymy nowa strukture w ktorej beda tylko zywe komorki w tworzacej sie generacji
{
    B = 0;
    int ustal = 1; /// bool, zmienna pomoze ustalic wartosci CDEF
    /// tworzymy nowa strukture
    struct WL *T = pom;
    struct WL *wiersze;
    wiersze = malloc(sizeof(struct WL));
    wiersze->nastLL = NULL;
    wiersze->poczatek = wiersze;
    struct KL *p;
    p = malloc(sizeof(struct KL));
    p->popL = NULL;
    p->nastL = NULL;
    wiersze->lista = p;
    wiersze->pierwsza = wiersze->lista;
    while(T != NULL)
    {
	int czy_pusty = 1;
        T->lista = T->pierwsza->nastL;
        while(T->lista != NULL)
        {
            if(T->lista->kom.sasiedzi == 3 || T->lista->kom.sasiedzi == 12 || T->lista->kom.sasiedzi == 13)
            {
		czy_pusty = 0;
		if(ustal == 1)
                {
               	    C = T->lista->kom.wiersz;
                    D = T->lista->kom.kolumna;
		    F = T->lista->kom.kolumna;
		    ustal = 0;
            	}

		if (D > T->lista->kom.kolumna)
                {
                    D = T->lista->kom.kolumna;
            	}
		
		if(F < T->lista->kom.kolumna)
                {
                    F = T->lista->kom.kolumna;
                }
		
		E = T->pierwsza->nastL->kom.wiersz;
                nowa_w_wierszu(wiersze->lista, T->lista->kom.kolumna, T->lista->kom.wiersz);
		B++;
                wiersze->lista = wiersze->lista->nastL;
            }
            if(T->lista->nastL == NULL)
            {
                break;
            }
            T->lista = T->lista->nastL;
        }
	if(czy_pusty == 0)
	{
        nowy_wiersz(wiersze);
	wiersze = wiersze->nastLL;
	}        
	if(T->nastLL == NULL)
        {
	    if(B == 0)
            {
                C=0;
                D=0;
                E=0;
                F=0;
            }
            return wiersze->poczatek;
        }
        T = T->nastLL;
    }
    if(B == 0)
    {
     	C=0;
     	D=0;
    	E=0;
   	F=0;
    }
    return wiersze->poczatek;
}


