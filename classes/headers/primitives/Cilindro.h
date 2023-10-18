#pragma once

#include <optional>
#include "../math/Vec3.h"
#include "./ObjetoComposto.h"
#include "../types/LPointGetType.h"
#include "../Ray.h"
#include "../materiais/BaseMaterial.h"
#include "./circulo.h"

class Cilindro : public ObjetoComposto {

    public:
    Vec3 Cb, Ct, d;
    double r, h;

    Circulo* circuloTopo;
    Circulo* circuloBase;
    
    Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r);
    Cilindro(int id, SDL_Color cor, Vec3 Cb, Vec3 Ct, double r, BaseMaterial material);
    
    Vec3 getW(Vec3 Pin);
    std::optional<LPointGetType> intersecta(Ray raycaster) override;
    std::optional<LPointGetType> intersectaFace(Ray raycaster);
};