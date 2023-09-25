#include "../../headers/materiais/BaseMaterial.h"

using namespace std;

BaseMaterial::BaseMaterial() : RUGOSIDADE(Vec3(1, 1, 1)), REFLETIVIDADE(Vec3(1, 1, 1)), M(1) {}

BaseMaterial::BaseMaterial(Vec3 RUGOSIDADE, Vec3 REFLETIVIDADE, double M) : RUGOSIDADE(RUGOSIDADE), REFLETIVIDADE(REFLETIVIDADE), M(M) {};

Vec3 BaseMaterial::getRugosidade() {
    return RUGOSIDADE;
}

Vec3 BaseMaterial::getRefletividade() {
    return REFLETIVIDADE;
}

double BaseMaterial::getM() {
    return M;
}