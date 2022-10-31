#ifndef __SPACESHIPS__
#define __SPACESHIPS__

#include "Entidade.h"
#include "Shot.h"
#include "../parser.h"
#include <vector>
#include <GL/freeglut.h>
#include "Enemy.h"

// Tipos de inimigo
// 1 -> Runner
// 2 -> Kamikaze
// 3 -> Shooter

class Shooter : public Enemy
{
private:
    vec3f_t final_point;
    bool arrived;

public:
    // Constructors
    using Enemy::Enemy;

    Shooter(vec3f_t origin,
            float angle,
            float velocidade,
            vec3f_t final_point);

    void move() override;
    void move(vec3f_t *point) override;
};

class Kamikaze : public Enemy
{
private:
    float distance;

public:
    using Enemy::Enemy;
    Kamikaze(vec3f_t origin, float angle, float velocidade);
    void move(vec3f_t *point) override;
};

class Kamikaze2 : public Enemy
{
private:
    float distance;

public:
    using Enemy::Enemy;
    Kamikaze2(vec3f_t origin, float angle, float velocidade);
    void move(vec3f_t *point) override;
};

class Runner : public Enemy
{

public:
    using Enemy::Enemy;
    Runner(vec3f_t origin, float angle, float velocidade, int runner_type);
    void move(vec3f_t *point) override;
};

class PowerUp : public Enemy
{
private:
    float distance_angle;
    int type;
public:
    using Enemy::Enemy;
    PowerUp(vec3f_t origin, float angle, float velocidade,int type);
    void move() override;
    void draw();

    int getType();
};

#endif

//          By Camisa 09 >_<
//                    *     .--.
//                         / /  `
//        +               | |
//               '         \ \__,
//           *          +   '--'  *
//               +   /\
//  +              .'  '.   *
//         *      /======\      +
//               ;:.  _   ;
//               |:. (_)  |
//               |:.  _   |
//     +         |:. (_)  |          *
//               ;:.      ;
//             .' \:.    / `.
//            / .-'':._.'`-. \
        //            |/    /||\    \|
//      jgs _..--"""````"""--.._
//    _.-'``                    ``'-._
//  -'                                '-
// Font : https://textart.io/art/tag/rocket/1

//  Estamos todos na sarjeta, mas alguns de nós estão olhando para as estrelas...
// Oscar Wilde