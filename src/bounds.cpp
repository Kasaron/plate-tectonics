#include "bounds.hpp"

Bounds::Bounds(const WorldDimension& worldDimension, const FloatPoint& position, 
       const Dimension& dimension)
    : _worldDimension(worldDimension), 
      _position(position), 
      _dimension(dimension) 
{
    if (_dimension.getWidth() >= _worldDimension.getWidth()) {
        throw runtime_error("(Bounds::Bounds) Plate is larger than the world containing it");
    }
    if (_dimension.getHeight() > _worldDimension.getHeight()) {
        throw runtime_error("(Bounds::Bounds) Plate is taller than the world containing it");
    }   
}

uint32_t Bounds::index(uint32_t x, uint32_t y) const 
{
    if (x >= _dimension.getWidth()) {
        throw runtime_error("Bounds::Index: unvalid x coordinate");
    }
    if (y >= _dimension.getHeight()) {
        throw runtime_error("Bounds::Index: unvalid y coordinate");
    }
    return y * _dimension.getWidth() + x;
}   

uint32_t Bounds::area() const
{
    return _dimension.getArea();
}

uint32_t Bounds::width() const 
{
    return _dimension.getWidth();
}

uint32_t Bounds::height() const 
{
    return _dimension.getHeight();
}

float Bounds::left() const 
{
    return _position.getX();
}

float Bounds::top() const 
{
    return _position.getY();
}   

float Bounds::right() const 
{
    return left() + width() - 1;
}

float Bounds::bottom() const 
{
    return top() + height() - 1;
}

bool Bounds::containsWorldPoint(uint32_t x, uint32_t y) const 
{
    uint32_t cleanX = _worldDimension.xMod(x);
    uint32_t cleanY = _worldDimension.yMod(y);
    return cleanX >= _position.getX() && cleanX<(_position.getX() + _dimension.getWidth()) 
        && cleanY >= _position.getY() && cleanY<(_position.getY() + _dimension.getHeight());
}

bool Bounds::isInLimits(float x, float y) const 
{
    if (x<0) return false;
    if (y<0) return false;
    return x<=_dimension.getWidth() && y<=_dimension.getHeight();
}

void Bounds::shift(float dx, float dy) {
    _position.shift(dx, dy, _worldDimension);
    p_assert(_worldDimension.contains(_position), "");
}

void Bounds::growWidth(int d)
{
    if (d<0) throw runtime_error("negative value");
    _dimension.growWidth(d);

    if (_dimension.getWidth() > _worldDimension.getWidth()) {
        throw runtime_error("(Bounds::growWidth) Plate is larger than the world containing it");
    }    
}

void Bounds::growHeight(int d)
{
    if (d<0) throw runtime_error("negative value");
    _dimension.growHeight(d);

    if (_dimension.getHeight() > _worldDimension.getHeight()) {
        string s("(Bounds::growHeight) Plate is taller than the world containing it:");
        s += " delta=" + Platec::to_string(d);
        s += " resulting plate height=" + Platec::to_string(_dimension.getHeight());
        s += " world height=" + Platec::to_string(_worldDimension.getHeight());
        throw runtime_error(s);
    } 
}   

Platec::Rectangle Bounds::asRect() const 
{
    p_assert(_position.getX() > 0.0f && _position.getY() >= 0.0f, "Left and top must be positive");  
    const uint32_t ilft = (uint32_t)_position.getX();
    const uint32_t itop = (uint32_t)_position.getY();
    const uint32_t irgt = ilft + _dimension.getWidth();
    const uint32_t ibtm = itop + _dimension.getHeight();

    return Platec::Rectangle(_worldDimension, ilft, irgt, itop, ibtm);     
}

uint32_t Bounds::getMapIndex(uint32_t* px, uint32_t* py) const
{
    return asRect().getMapIndex(px, py);       
}

uint32_t Bounds::getValidMapIndex(uint32_t* px, uint32_t* py) const
{
    uint32_t res = asRect().getMapIndex(px, py);
    if (res == BAD_INDEX) {
        throw runtime_error("BAD INDEX found");
    }
    return res;
}
