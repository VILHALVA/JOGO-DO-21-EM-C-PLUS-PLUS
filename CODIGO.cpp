#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int calcularValor(const vector<int>& cartas) {
    int valor = 0;
    int ases = 0;
    
    for (int carta : cartas) {
        if (carta >= 2 && carta <= 10) {
            valor += carta;
        } else {
            valor += 10;  
        }
        if (carta == 1) {
            ases++;
        }
    }
    
    while (ases-- > 0) {
        if (valor + 10 <= 21) {
            valor += 10;  
        }
    }
    
    return valor;
}

void exibirCartas(const vector<int>& cartas, bool revelarTodas = true) {
    for (size_t i = 0; i < cartas.size(); ++i) {
        if (i == 0 && !revelarTodas) {
            cout << "[?] ";
        } else {
            cout << "[" << cartas[i] << "] ";
        }
    }
    cout << endl;
}


int main() {
    srand(static_cast<unsigned>(time(0)));  
    vector<int> baralho = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};  
    vector<int> cartasJogador;
    vector<int> cartasBanca;
    
    auto retirarCarta = [&]() {
        int index = rand() % baralho.size();
        int carta = baralho[index];
        baralho.erase(baralho.begin() + index);
        return carta;
    };
    
    cartasJogador.push_back(retirarCarta());
    cartasJogador.push_back(retirarCarta());
    cartasBanca.push_back(retirarCarta());
    cartasBanca.push_back(retirarCarta());
    
    cout << "Cartas do jogador: ";
    exibirCartas(cartasJogador);
    cout << "Total do jogador: " << calcularValor(cartasJogador) << endl;
    
    bool jogadorContinua = true;
    while (jogadorContinua && calcularValor(cartasJogador) < 21) {
        cout << "Deseja 'bater' (1) ou 'ficar' (2)? ";
        int escolha;
        cin >> escolha;
        
        if (escolha == 1) {
            cartasJogador.push_back(retirarCarta());
            cout << "Cartas do jogador: ";
            exibirCartas(cartasJogador);
            cout << "Total do jogador: " << calcularValor(cartasJogador) << endl;
            
            if (calcularValor(cartasJogador) > 21) {
                cout << "Você estourou! Perdeu o jogo." << endl;
                return 0;
            }
        } else {
            jogadorContinua = false;
        }
    }
    
    cout << "Cartas da banca: ";
    exibirCartas(cartasBanca, false);
    while (calcularValor(cartasBanca) < 17) {
        cartasBanca.push_back(retirarCarta());
        cout << "Cartas da banca: ";
        exibirCartas(cartasBanca);
        cout << "Total da banca: " << calcularValor(cartasBanca) << endl;
    }
    
    int valorJogador = calcularValor(cartasJogador);
    int valorBanca = calcularValor(cartasBanca);
    
    cout << "Total do jogador: " << valorJogador << endl;
    cout << "Total da banca: " << valorBanca << endl;
    
    if (valorBanca > 21 || valorJogador > valorBanca) {
        cout << "Você ganhou!" << endl;
    } else if (valorJogador < valorBanca) {
        cout << "A banca ganhou!" << endl;
    } else {
        cout << "Empate!" << endl;
    }
    
    return 0;
}
