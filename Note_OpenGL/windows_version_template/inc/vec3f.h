//**************************************************************************************
//  Copyright (C) 2017 - 2022, Min Tang
//  All rights reserved.
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//     1. Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//     2. Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//     3. The names of its contributors may not be used to endorse or promote
//        products derived from this software without specific prior written
//        permission.
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//**************************************************************************************

#pragma once

#include <ostream>
#include <math.h>

#include "forceline.h"
#define     GLH_ZERO                double(0.0)
#define     GLH_EPSILON          double(10e-6)
#define		GLH_EPSILON_2		double(10e-12)
#define     equivalent(a,b)             (((a < b + GLH_EPSILON) &&\
                                                      (a > b - GLH_EPSILON)) ? true : false)

inline double fmax(double a, double b) {
	return (a > b) ? a : b;
}

inline double fmin(double a, double b) {
	return (a < b) ? a : b;
}

inline bool isEqual( double a, double b, double tol=GLH_EPSILON )
{
    return fabs( a - b ) < tol;
}

/* This is approximately the smallest number that can be
* represented by a float, given its precision. */
#define ALMOST_ZERO		FLT_EPSILON



#ifndef M_PI
#define M_PI 3.14159f
#endif

#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

class vec2f {
	union {
		struct {
		double x, y;
		};
		struct {
		double v[2];
		};
	};
public:
	__host__ __device__  vec2f& operator=(vec2f& data)
	{
		this->x = data.x;
		this->y = data.y;
		this->v[0] = data.v[0];
		this->v[1] = data.v[1];
		return (*this);
	}

	__host__ __device__  vec2f ()
	{x=0; y=0;}

	__host__ __device__  vec2f(const vec2f &v)
	{
		x = v.x;
		y = v.y;
	}

	__host__ __device__  vec2f(const double *v)
	{
		x = v[0];
		y = v[1];
	}

	__host__ __device__  vec2f(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	__host__ __device__  double operator [] ( int i ) const {return v[i];}
	__host__ __device__  double &operator [] (int i) { return v[i]; }
};

class vec3f {
	
public:
union {
		struct {
		double x, y, z;
		};
		struct {
		double v[3];
		};
	};

	
	__host__ __device__  vec3f ()
	{x=0; y=0; z=0;}

	__host__ __device__ vec3f& operator =(const vec3f& data)
	{
		this->x = data.x;
		this->y = data.y;
		this->z = data.z;
		this->v[0] = data.v[0];
		this->v[1] = data.v[1];
		this->v[2] = data.v[2];
		return *this;
	}

	__host__ __device__  vec3f(const vec3f &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	__host__ __device__  vec3f(const double *v)
	{
		x = v[0];
		y = v[1];
		z = v[2];
	}

	__host__ __device__  vec3f(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	__host__ __device__  double operator [] ( int i ) const {return v[i];}
	__host__ __device__  double &operator [] (int i) { return v[i]; }

	__host__ __device__  vec3f &operator += (const vec3f &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	__host__ __device__  vec3f &operator -= (const vec3f &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	__host__ __device__  vec3f &operator *= (double t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	__host__ __device__  vec3f &operator /= (double t) {
		x /= t;
		y /= t;
		z /= t;
		return *this;
	}

	__host__ __device__  void negate() {
		x = -x;
		y = -y;
		z = -z;
	}

	__host__ __device__  vec3f operator - () const {
		return vec3f(-x, -y, -z);
	}

	__host__ __device__  vec3f operator+ (const vec3f &v) const
	{
		return vec3f(x+v.x, y+v.y, z+v.z);
	}

	__host__ __device__  vec3f operator- (const vec3f &v) const
	{
		return vec3f(x-v.x, y-v.y, z-v.z);
	}

	__host__ __device__  vec3f operator *(double t) const
	{
		return vec3f(x*t, y*t, z*t);
	}

	__host__ __device__  vec3f operator /(double t) const
	{
		return vec3f(x/t, y/t, z/t);
	}

     // cross product
     __host__ __device__  const vec3f cross(const vec3f &vec) const
     {
          return vec3f(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
     }

	 __host__ __device__  double dot(const vec3f &vec) const {
		 return x*vec.x+y*vec.y+z*vec.z;
	 }

	 __host__ __device__  void normalize() 
	 { 
		 double sum = x*x+y*y+z*z;
		 if (sum > GLH_EPSILON_2) {
			 double base = double(1.0/sqrt(sum));
			 x *= base;
			 y *= base;
			 z *= base;
		 }
	 }

	 __host__ __device__  double length() const {
		 return double(sqrt(x*x + y*y + z*z));
	 }

	 __host__ __device__  vec3f getUnit() const {
		 return (*this)/length();
	 }

	__host__ __device__  bool isUnit() const {
		return isEqual( squareLength(), 1.f );
	}

    //! max(|x|,|y|,|z|)
	__host__ __device__  double infinityNorm() const
	{
		return fmax(fmax( fabs(x), fabs(y) ), fabs(z));
	}

	__host__ __device__  vec3f & set_value( const double &vx, const double &vy, const double &vz)
	{ x = vx; y = vy; z = vz; return *this; }

	__host__ __device__  bool equal_abs(const vec3f &other) {
		return x == other.x && y == other.y && z == other.z;
	}

	__host__ __device__  double squareLength() const {
		return x*x+y*y+z*z;
	}

	static vec3f zero() {
		return vec3f(0.f, 0.f, 0.f);
	}

    //! Named constructor: retrieve vector for nth axis
	static vec3f axis( int n ) {
		assert( n < 3 );
		switch( n ) {
			case 0: {
				return xAxis();
			}
			case 1: {
				return yAxis();
			}
			case 2: {
				return zAxis();
			}
		}
		return vec3f();
	}

    //! Named constructor: retrieve vector for x axis
	static vec3f xAxis() { return vec3f(1.f, 0.f, 0.f); }
    //! Named constructor: retrieve vector for y axis
	static vec3f yAxis() { return vec3f(0.f, 1.f, 0.f); }
    //! Named constructor: retrieve vector for z axis
	static vec3f zAxis() { return vec3f(0.f, 0.f, 1.f); }

};

inline vec3f operator * (double t, const vec3f &v) {
	return vec3f(v.x*t, v.y*t, v.z*t);
}

inline vec3f interp(const vec3f &a, const vec3f &b, double t)
{
	return a*(1-t)+b*t;
}

inline vec3f vinterp(const vec3f &a, const vec3f &b, double t)
{
	return a*t+b*(1-t);
}

inline vec3f interp(const vec3f &a, const vec3f &b, const vec3f &c, double u, double v, double w)
{
	return a*u+b*v+c*w;
}

inline double clamp(double f, double a, double b)
{
	return fmax(a, fmin(f, b));
}

inline double vdistance(const vec3f &a, const vec3f &b)
{
	return (a-b).length();
}

inline std::ostream& operator<<( std::ostream&os, const vec3f &v ) {
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
	return os;
}

#define CLAMP(a, b, c)		if((a)<(b)) (a)=(b); else if((a)>(c)) (a)=(c)
