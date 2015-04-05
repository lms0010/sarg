#ifndef TYPES_H
#define TYPES_H

struct Vector3 {
    float x, y, z;

    Vector3(): x(0.0f), y(0.0f), z(0.0f) { }
};

class ObstacleDistance {
private:
    Vector3 _pos;
    Vector3 _vel;

public:
    const Vector3&  getPos() const { return _pos; }
    void            setPos(const Vector3& pos) { _pos = pos; }

    const Vector3&  getVel() const { return _vel; }
    void            setVel(const Vector3& vel) { _vel = vel; }

};

class Waypoint {
private:
    Vector3 _pos;
    bool    _relative;

public:

                    Waypoint(): _relative(false) {}

    bool            isRelative() const { return _relative; }
    void            setRelative(const bool rel) { _relative = rel; }

    const Vector3&  getPos() const { return _pos; }
    void            setPos(const Vector3& pos) { _pos = pos; }

};


#endif // TYPES_H
