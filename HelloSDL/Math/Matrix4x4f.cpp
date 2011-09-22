#include "Matrix4x4f.h"
#include <cmath>

Matrix4x4f::Matrix4x4f()
{
	this->Reset();
}

Matrix4x4f::~Matrix4x4f()
{
	// Destroy stuff
}

void Matrix4x4f::Reset()
{
    // Reset to I
    this->data[0] = this->data[5] = this->data[10] = this->data[15] = 1.0f;
    this->data[1] = this->data[2] = this->data[3] = this->data[4] = this->data[6] = this->data[7] =
    this->data[8] = this->data[9] = this->data[11] = this->data[12] = this->data[13] = this->data[14] = 0.0f;

	/*
		this->data[0][0] = this->data[1][1] = this->data[2][2] = this->data[3][3] = 1.0f;
	
	this->data[0][1] = this->data[0][2] = this->data[0][3] = 
	this->data[1][0] = this->data[1][2] = this->data[1][3] = 
	this->data[2][0] = this->data[2][1] = this->data[2][3] = 
	this->data[3][0] = this->data[3][1] = this->data[3][2] = 0.0f;
	*/
}

Matrix4x4f* Matrix4x4f::MultiplyWith(Matrix4x4f other)
{   
	float t[16] = {this->data[0], this->data[1], this->data[2], this->data[3],
                    this->data[4], this->data[5], this->data[6], this->data[7],
                    this->data[8], this->data[9], this->data[10], this->data[11],
                    this->data[12], this->data[13], this->data[14], this->data[15]};
	float o[16] = {other.data[0], other.data[1], other.data[2], other.data[3],
                    other.data[4], other.data[5], other.data[6], other.data[7],
                    other.data[8], other.data[9], other.data[10], other.data[11],
                    other.data[12], other.data[13], other.data[14], other.data[15]};

	float f11 = t[0]*o[0] + t[1]*o[4] + t[2]*o[8]  + t[3]*o[12];
	float f21 = t[0]*o[1] + t[1]*o[5] + t[2]*o[9]  + t[3]*o[13];
	float f31 = t[0]*o[2] + t[1]*o[6] + t[2]*o[10] + t[3]*o[14];
	float f41 = t[0]*o[3] + t[1]*o[7] + t[2]*o[11] + t[3]*o[15];

	float f12 = t[4]*o[0] + t[5]*o[4] + t[6]*o[8]  + t[7]*o[12];
	float f22 = t[4]*o[1] + t[5]*o[5] + t[6]*o[9]  + t[7]*o[13];
	float f32 = t[4]*o[2] + t[5]*o[6] + t[6]*o[10] + t[7]*o[14];
	float f42 = t[4]*o[3] + t[5]*o[7] + t[6]*o[11] + t[7]*o[15];

	float f13 = t[8]*o[0] + t[9]*o[4] + t[10]*o[8]  + t[11]*o[12];
	float f23 = t[8]*o[1] + t[9]*o[5] + t[10]*o[9]  + t[11]*o[13];
	float f33 = t[8]*o[2] + t[9]*o[6] + t[10]*o[10] + t[11]*o[14];
	float f43 = t[8]*o[3] + t[9]*o[7] + t[10]*o[11] + t[11]*o[15];

	float f14 = t[12]*o[0] + t[13]*o[4] + t[14]*o[8]  + t[15]*o[12];
	float f24 = t[12]*o[1] + t[13]*o[5] + t[14]*o[9]  + t[15]*o[13];
	float f34 = t[12]*o[2] + t[13]*o[6] + t[14]*o[10] + t[15]*o[14];
	float f44 = t[12]*o[3] + t[13]*o[7] + t[14]*o[11] + t[15]*o[15];
	
	this->data[0] = f11;
	this->data[1] = f12;
	this->data[2] = f13;
	this->data[3] = f14;

	this->data[4] = f21;
	this->data[5] = f22;
	this->data[6] = f23;
	this->data[7] = f24;

	this->data[8]  = f31;
	this->data[9]  = f32;
	this->data[10] = f33;
	this->data[11] = f34;

	this->data[12] = f41;
	this->data[13] = f42;
	this->data[14] = f43;
	this->data[15] = f44;

	return this;

    
    //data[16]
	//   1  2  3  4
	//.-------------. 
    //|  0  4  8 12 |
    //|  1  5  9 13 |
    //|  2  6 10 14 |
    //|  3  7 11 15 |
}

Matrix4x4f* Matrix4x4f::Scale(float x, float y, float z)
{
    
    Matrix4x4f temp;
    temp.data[0] = x;
    temp.data[5] = y;
    temp.data[10] = z;
    temp.data[15] = 1.0f;
    temp.data[1] = temp.data[2] = temp.data[3] = temp.data[4] = temp.data[6] = temp.data[7] = temp.data[8] = temp.data[9] =
    temp.data[11] = temp.data[12] = temp.data[13] = temp.data[14] = 0.0f;
    
    this->MultiplyWith(temp);

	return this;
}

Matrix4x4f* Matrix4x4f::Translate(float x, float y, float z)
{	
	// Translate by (x,y,z)
	auto temp = new Matrix4x4f();
	temp->Reset();

    temp->data[3] = x;
    temp->data[7] = y;
    temp->data[11] = z;
    
	return this->MultiplyWith(*temp);
}

Matrix4x4f* Matrix4x4f::Rotate(float degrees, float x, float y, float z)
{

    //data[16]
    //|  0  4  8 12 |
    //|  1  5  9 13 |
    //|  2  6 10 14 |
    //|  3  7 11 15 |
    
    
	// Rotate by <degrees> around (x, y, z)
    float c = cosf(degrees);
    float s = sinf(degrees);
    float t = 1 - c;
    
    Matrix4x4f temp;
    temp.data[0] = t*x*x + c; temp.data[4] = t*x*y - s*z; temp.data[8] = t*x*z + s*y;
    temp.data[1] = t*x*y + s*z; temp.data[5] = t*y*y + c;  temp.data[9] = t*y*z - s*x;
    temp.data[2] = t*x*z - s*y; temp.data[6] = t*y*z + s*x; temp.data[10] = t*z*z + c;
    temp.data[12] = temp.data[13] = temp.data[14] = temp.data[3] = temp.data[7] = temp.data[11] = 0.0f;
    temp.data[15] = 1.0f;
    
    this->MultiplyWith(temp);

	return this;
}