#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED

#include "../stdafx.hpp"

namespace Mad
{
    struct Vector2f
    {
        float32 x,y; //As Meters

        //Default constructor does nothing for performance
        Vector2f() {}

        //Construct using coordinates
        Vector2f(float32 _x, float32 _y):
            x(_x), y(_y) {}

        //Set Vector to Zero
        void SetZero(){
            x   = 0;
            y   = 0;
        }

        //Set Vector Coordinates
        void Set(float32 _x, float32 _y){
            x   = _x;
            y   = _y;
        }

        //Negate this vector
        Vector2f operator -(){
            Vector2f v;
            v.Set(-x,-y);
            return v;
        }

        //Add Operator
        Vector2f operator+(const Vector2f& v){
            return Vector2f(x + v.x, y + v.y);
        }

        //Substract Operator
        Vector2f operator-(const Vector2f& v){
            return Vector2f(x - v.x, y - v.y);
        }

        //Add a vector to this vector
        void operator +=(const Vector2f& v){
            x+= v.x;
            y+= v.y;
        }

        //Substract a Vector from this vector
        void operator -=(const Vector2f& v){
            x-= v.x;
            y-= v.y;
        }

        //Multiply this vector by a scalar
        void operator*=(float32 a){
            x*=a;
            y*=a;
        }

        //Scalar Divede Operaotr
        void operator/=(float32 a){
            x/=a;
            y/=a;
        }

        //Get the length of this vector (norm)
        float32 Length() const
        {
            return sqrt( x * x + y * y);
        }

        //Convert Vector to unit vector and return the length
        float32 Normalize(){
            float32 length  = Length();
            if (length < FLT_EPSILON)
                return 0.0f;

            float32 invLength   = 1.f / length;
            x *= invLength;
            y *= invLength;

            return length;
        }

        //Third Party API Integration utility

        //Assingment Operator for SFML Vector
        Vector2f operator=(const sf::Vector2f& v){
            x = v.x * UNRATIO;
            y = v.y * UNRATIO;
            return *this;
        }

        //Assignment Operator for Box2D Vector
        Vector2f operator=(const b2Vec2& v){
            x = v.x;
            y = v.y;
            return *this;
        }

        //Casting to SFML Vector2f
        operator sf::Vector2f(){
            return sf::Vector2f(x * RATIO, y * RATIO);
        }

        //Casting to Box2D Vector
        operator b2Vec2(){
            return b2Vec2(x,y);
        }
    };
};

#endif // VECTOR2_H_INCLUDED
