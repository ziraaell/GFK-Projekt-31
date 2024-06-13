#pragma once

/**
 * @struct Player
 * @brief Struktura reprezentująca gracza w grze.
 * 
 * Struktura Player przechowuje wszystkie kluczowe informacje dotyczące pozycji, orientacji, prędkości i stanu biegu gracza w symulacji lub grze.
 */
struct Player {
    float pos_x; ///< Pozycja gracza na osi X.
    float pos_y; ///< Pozycja gracza na osi Y.
    float angle; ///< Kąt orientacji gracza w radianach.
    float speed; ///< Aktualna prędkość liniowa gracza.
    float turnSpeed; ///< Prędkość obrotu gracza (zmiana kąta na jednostkę czasu).
    bool isRunning; ///< Flaga sprawdzajaca, czy gracz biegnie
};
