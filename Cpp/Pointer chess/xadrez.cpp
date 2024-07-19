/*
Autores:
Andre L. Z.;
Henrique M.;
Leonardo Pereira;
Marcos A. F. J.;
*/

#include <iostream>
#include <stdlib.h>

using namespace std;


//Classe base - Peca
class Peca
{
protected:
    int x, y;
    //bool para identificar de qual lado do tabuleiro a peça pertence
	bool cor, primeira;

public:
    Peca(int = 0, int = 0, bool = true, bool = true);
    virtual bool mover(int, int) = 0;
    int get_X() const;
    int get_Y() const;
    bool get_Cor() const;

protected:
    void set_X(int);
    void set_Y(int);
    void set_Cor(bool);
    void set_primeira(bool);
};


/*
Construtor Peca
Parametros:
-vx - inteiro responsável pela  locação da peça no eixo x
-vy - inteiro responsável pela  locação da peça no eixo y
-b - booleano responsável pelo armazenamento de qual lado do tabuleiro a peça pertence
*/
Peca::Peca(int vx, int vy, bool b, bool pri) : x(0), y(0)
{
    set_X(vx);
    set_Y(vy);
    set_Cor(b);
    set_primeira(pri);
};

/*
set_X (classe Peca)
Setar a coordenada x, fazendo a verificação se a nova posição é positiva(unico caso considerado impossivel, coordenada negativas)
Parametro:
-vx - inteiro responsável pela posição x
retorno: vazio
*/
void Peca::set_X(int vx)
{
    if(x >= 0)
        x = vx;
}

/*
set_Y (classe Peca)
Setar a coordenada y, fazendo a verificação se a nova posição é positiva(unico caso considerado impossivel, coordenada negativas)
Parametro:
-vy - inteiro responsável pela posição y
retorno: vazio
*/
void Peca::set_Y(int vy)
{
    if(y >= 0)
        y = vy;
}

/*set_primeira (classe Peca)
Setar o bool primeira, devido ao peao
Parametro:
-pri - booleano que verifica primeira jogada
retorno: vazio
*/
void Peca::set_primeira(bool pri)
{
    primeira = pri;
}

/*
set_Cor (classe Peca)
Setar o estado bool da peça(TRUE ou FALSE)
Parametro:
-b - booleano
Retorno: vazio
*/
void Peca::set_Cor(bool b)
{
    cor = b;
}

/*
get_X (classe Peca)
Retorna a coordenada x atual da peça
Parametro: vazio
Retorno:
-x - inteiro contendo a coordenada x atual da peça
*/
int Peca::get_X() const
{
    return x;
}

/*
get_Y (classe Peca)
Retorna a coordenada y atual da peça
Parametro: vazio
Retorno:
-y - inteiro contendo a coordenada y atual da peça
*/
int Peca::get_Y() const
{
    return y;
}

/*
get_Cor (classe Peca)
Retorna a qual jogador a peça pertence
Parametro: vazio
Retorno:
-cor - booleano retornando TRUE ou FALSE, indicando em qual lado do tabuleiro a peça estava no inicio da partida
*/
bool Peca::get_Cor() const
{
    return cor;
}


//Classe base - Tabuleiro
class Tabuleiro
{
public:
	//Tabuleiro locado estaticamente - dimensões fixas
    Peca *tabu[8][8];

public:
    Tabuleiro();
    bool inserePeca(int, int, Peca*);
    bool removePeca(int, int);
    bool mover(int, int, int, int);
};

/*
Construtor Tabuleiro
Incia todos os ponteiros do tabuleiros, apontando para objetos nulos
Parametro: vazio
*/
Tabuleiro::Tabuleiro()
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            tabu[i][j] = NULL;
}

/*
InserePeca (classe Tabuleiro)
Insere uma Peca em uma dada posição
Parametro:
-x - inteiro representando a coordenada x onde a peça aparecera da primeira vez
-y - inteiro representando a coordenada y onde a peça aparecera da primeira vez
-P1 - Peca que será colocada na posição x, y dada
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel adicinar a peça na posição dada
*/
bool Tabuleiro::inserePeca(int x, int y,Peca* P1)
{
	if(x>=0 && x<=7 && y>=0 && y<=7)
	{
		tabu[x][y] = P1;
		return true;
	}

	else
		return false;
}

/*
removePeca (classe Tabuleiro)
Remove uma Peca que esta em uma dada posição
Parametro:
-x - inteiro representando a coordenada x onde a peça a ser retirada encontra-se
-y - inteiro representando a coordenada y onde a peça a ser retirada encontra-se
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel remover a peça da posição dada
*/
bool Tabuleiro::removePeca(int x, int y)
{
	if((x>=0 && x<=7) && (y>=0 && y<=7))
	{
		tabu[x][y] = NULL;
		return true;
	}
	else
		return false;
}

/*
mover (classe Tabuleiro)
Responsável por mover uma peça de uma posição xi, yi para uma posição xf, yf
Parametro:
-xi - inteiro representando a coordenada x onde a peça esta
-yi - inteiro representando a coordenada y onde a peça esta
-xf - inteiro representando a coordenada x onde a peça será enviada
-yf - inteiro representando a coordenada y onde a peça será enviada
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel mover a peça
*/
bool Tabuleiro::mover(int xi, int yi, int xf, int yf)
{
	if(xi >= 0 && xf <= 7&& yi >= 0 && yf <= 7)
		if(tabu[xi][yi]->mover(xf, yf) == true)
		{
				tabu[xf][yf] = tabu[xi][yi];
				tabu[xi][yi] = NULL;
				return true;
		}

	else
		return false;
}


//Classe derivada - Rei
class Rei : public Peca
{
public:
    Rei(int = 0, int = 0, bool = true, bool = true);
    virtual bool mover(int, int);
};

/*
Construtor Rei
Iniciar todas as especificidades da peça Rei
Parametro:
-vx - inteiro responsável pela locação da peça no eixo x
-vy - inteiro responsável pela locação da peça no eixo y
-b - booleano responsável pelo armazenamento de qual lado do tabuleiro a peça pertence
Retorno: vazio
*/
Rei::Rei(int vx, int vy, bool b, bool pri) : Peca(vx, vy, b, pri){};

/*
mover (classe Rei)
Responsável por mover uma peça de uma posição xi, yi para uma posição xf, yf
Parametro:
-x - inteiro representando a coordenada x onde a peça será enviada
-y - inteiro representando a coordenada y onde a peça será enviada
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel mover a peça
*/
bool Rei::mover(int x, int y)
{
    if((x == Rei::x + 1 && Rei::y == y) || (x == Rei::x && y == Rei::y + 1) ||
       (x == Rei::x - 1 && Rei::y == y) || (x == Rei::x && y == Rei::y - 1))
       {
          Rei::x = x;
          Rei::y = y;
          return true;
       }

    else
        return false;
}


//Classe derivada - Torre
class Torre : public Peca
{
public:
    Torre(int = 0, int = 0, bool = true, bool = true);
    virtual bool mover(int, int);
};

/*
Construtor Torre
Iniciar todas as especificidades da peça Rei
Parametro:
-vx - inteiro responsável pela locação da peça no eixo x
-vy - inteiro responsável pela locação da peça no eixo y
-b - booleano responsável pelo armazenamento de qual lado do tabuleiro a peça pertence
Retorno: vazio
*/
Torre::Torre(int vx, int vy, bool b, bool pri) : Peca(vx, vy, b, pri){};

/*
mover (classe Torre)
Responsável por mover uma peça de uma posição xi, yi para uma posição xf, yf
Parametro:
-x - inteiro representando a coordenada x onde a peça será enviada
-y - inteiro representando a coordenada y onde a peça será enviada
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel mover a peça
*/
bool Torre::mover(int x, int y)
{
    if(x == Torre::x || y == Torre::y)
    {
        Torre::x = x;
        Torre::y = y;
        return true;
    }
    else
        return false;
}


//Classe derivada - Bispo
class Bispo : public Peca
{
public:
    Bispo(int = 0, int = 0, bool = true, bool = true);
    virtual bool mover(int, int);
};

/*
Construtor Bispo
Iniciar todas as especificidades da peça Rei
Parametro:
-vx - inteiro responsável pela locação da peça no eixo x
-vy - inteiro responsável pela locação da peça no eixo y
-b - booleano responsável pelo armazenamento de qual lado do tabuleiro a peça pertence
Retorno: vazio
*/
Bispo::Bispo(int vx, int vy, bool b, bool pri) : Peca(vx, vy, b, pri){};

/*
mover (classe Bispo)
Responsável por mover uma peça de uma posição xi, yi para uma posição xf, yf
Parametro:
-x - inteiro representando a coordenada x onde a peça será enviada
-y - inteiro representando a coordenada y onde a peça será enviada
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel mover a peça
*/
bool Bispo::mover(int x, int y)
{
    if(abs(x - Bispo::x )== abs(y - Bispo::y ))
    {
        Bispo::x = x;
        Bispo::y = y;
        return true;
    }

    else
        return false;
}


//Classe derivada - Peão
class Peao : public Peca
{

public:
    Peao(int = 0, int = 0, bool = true, bool  = true);
    virtual bool mover(int, int);

};

/*
Construtor Peão
Iniciar todas as especificidades da peça Rei
Parametro:
-vx - inteiro responsável pela locação da peça no eixo x
-vy - inteiro responsável pela locação da peça no eixo y
-b - booleano responsável pelo armazenamento de qual lado do tabuleiro a peça pertence
Retorno: vazio
*/
Peao::Peao(int vx, int vy, bool b, bool pri) : Peca(vx, vy, b, pri){}


/*
mover (classe Peao)
Responsável por mover uma peça de uma posição xi, yi para uma posição xf, yf
Parametro:
-x - inteiro representando a coordenada x onde a peça será enviada
-y - inteiro representando a coordenada y onde a peça será enviada
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel mover a peça
*/
bool Peao::mover(int x, int y)
{
    if((x == Peao::x + 1 && Peao::y == y) || (x == Peao::x && Peao::y == y + 1) ||
       (x == Peao::x - 1 && Peao::y == y) || (x == Peao::x && Peao::y == y - 1))
       {
          Peao::primeira = false;
          Peao::x = x;
          Peao::y = y;
          return true;
       }

    else if(((x == Peao::x + 2 && Peao::y == y) || (x == Peao::x && Peao::y == y + 2) || (x == Peao::x - 2 && Peao::y == y) || (x == Peao::x && Peao::y == y - 2)) && primeira == true)
       {
          Peao::primeira = false;
       	  Peao::x = x;
          Peao::y = y;
          return true;
	   }

        return false;
}


//Classe derivada - Rainha
class Rainha : public Peca
{
public:
    Rainha(int = 0, int = 0, bool = true, bool = true);
    virtual bool mover(int, int);
};

/*
Construtor Rainha
Iniciar todas as especificidades da peça Rei
Parametro:
-vx - inteiro responsável pela locação da peça no eixo x
-vy - inteiro responsável pela locação da peça no eixo y
-b - booleano responsável pelo armazenamento de qual lado do tabuleiro a peça pertence
Retorno: vazio
*/
Rainha::Rainha(int vx, int vy, bool b, bool pri) : Peca(vx, vy, b, pri){};

/*
mover (classe Rainha)
Responsável por mover uma peça de uma posição xi, yi para uma posição xf, yf
Parametro:
-x - inteiro representando a coordenada x onde a peça será enviada
-y - inteiro representando a coordenada y onde a peça será enviada
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel mover a peça
*/
bool Rainha::mover(int x, int y)
{
    if(x == Rainha::x || y == Rainha::y)
    {
        Rainha::x = x;
        Rainha::y = y;
        return true;
    }

    if(abs(x - Rainha::x) == abs(y - Rainha::y))
    {
        Rainha::x = x;
        Rainha::y = y;
        return true;
    }

	return false;
}


//Classe derivada - Cavalo
class Cavalo : public Peca
{
public:
    Cavalo(int = 0, int = 0, bool = true, bool = true);
    virtual bool mover(int, int);
};

/*
Construtor Cavalo
Iniciar todas as especificidades da peça Rei
Parametro:
-vx - inteiro responsável pela locação da peça no eixo x
-vy - inteiro responsável pela locação da peça no eixo y
-b - booleano responsável pelo armazenamento de qual lado do tabuleiro a peça pertence
Retorno: vazio
*/
Cavalo::Cavalo(int vx, int vy, bool b, bool pri) : Peca(vx, vy, b, pri){};

/*
mover (classe Cavalo)
Responsável por mover uma peça de uma posição xi, yi para uma posição xf, yf
Parametro:
-x - inteiro representando a coordenada x onde a peça será enviada
-y - inteiro representando a coordenada y onde a peça será enviada
Retorno:
-bool - booleano retornando TRUE ou FALSE, indicando se foi possivel mover a peça
*/
bool Cavalo::mover(int x, int y)
{
	if((abs(Cavalo::x - x)==1 && abs(Cavalo::y - y)==3)||(abs(Cavalo::x - x)==3 && abs(Cavalo::y - y)==1))
	{
		Cavalo::x =x;
		Cavalo::y =y;
		return true;
	}
	return false;
}


//Programa principal
int main()
{
	//Cria um objeto tabuleiro
	Tabuleiro tabu;


	//Cria uma peça Rainha
	Peca *p1 = new Rainha(0,0,true, true);
	//Insere a Rainha criada
	tabu.inserePeca(0,0,p1);

	//Move a peça Rainha e emite uma mensagem se foi possivel ou não realizar o movimento
	if(tabu.mover(0,0,1,1) == true)
		cout << "Movimento bem sucedido" << endl;
	else
		cout <<"Impossivel realizar o movimento" << endl;

	//Move a peça Rainha e emite uma mensagem se foi possivel ou não realizar o movimento
	if(tabu.mover(1,1,7,7) == true)
		cout << "Movimento bem sucedido" << endl;
	else
		cout <<"Impossivel realizar o movimento" << endl;


	//Cria uma peça Bisbo
	Peca *p2 = new Bispo(1,1,true, true);
	//Insere o Bispo criada
	tabu.inserePeca(1,1,p2);

	//Move a peça Bispo e emite uma mensagem se foi possivel ou não realizar o movimento
	if(tabu.mover(1,1,2,2) == true)
		cout << "Movimento bem sucedido" << endl;
	else
		cout << "Impossivel realizar o movimento" << endl;

	//Move a peça Bispo e emite uma mensagem se foi possivel ou não realizar o movimento
	if(tabu.mover(2,2,7,6) == true )
		cout << "Movimento bem sucedido" << endl;
	else
		cout << "Impossivel realizar o movimento" << endl;


	//Cria uma peça Peão
	Peca *p3 = new Peao(2,2, true, true);
	//Insere o Peão criada
	tabu.inserePeca(2,2,p3);

	//Move a peça Peão e emite uma mensagem se foi possivel ou não realizar o movimento
	if(tabu.mover(2,2,4,2) == true)
		cout << "Movimento bem sucedido" << endl;
	else
		cout << "Impossivel realizar o movimento" << endl;

	//Move a peça Peão e emite uma mensagem se foi possivel ou não realizar o movimento
	if(tabu.mover(4,2,6,2) == true)
		cout << "Movimento bem sucedido" << endl;
	else
		cout << "Impossivel realizar o movimento" << endl;



    return 0;
}
