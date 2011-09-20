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
}

Matrix4x4f* Matrix4x4f::MultiplyWith(Matrix4x4f other)
{   
	float temp[16] = {this->data[0], this->data[4], this->data[8], this->data[12],
                    this->data[1], this->data[5], this->data[9], this->data[13],
                    this->data[2], this->data[6], this->data[10], this->data[14],
                    this->data[3], this->data[7], this->data[11], this->data[15]};
    
    //data[16]
    //|  0  4  8 12 |
    //|  1  5  9 13 |
    //|  2  6 10 14 |
    //|  3  7 11 15 |
    
    this->data[0] = temp[0] * other.data[0] + temp[4] * other.data[1] + temp[8] * other.data[2] + temp[12] * other.data[3];
    this->data[1] = temp[1] * other.data[0] + temp[5] * other.data[1] + temp[9] * other.data[2] + temp[13] * other.data[3];
    this->data[2] = temp[2] * other.data[0] + temp[6] * other.data[1] + temp[10] * other.data[2] + temp[14] * other.data[3];
    this->data[3] = temp[3] * other.data[0] + temp[7] * other.data[1] + temp[11] * other.data[2] + temp[15] * other.data[3];
    
    this->data[4] = temp[0] * other.data[4] + temp[4] * other.data[5] + temp[8] * other.data[6] + temp[12] * other.data[7];
    this->data[5] = temp[1] * other.data[4] + temp[5] * other.data[5] + temp[9] * other.data[6] + temp[13] * other.data[7];
    this->data[6] = temp[2] * other.data[4] + temp[6] * other.data[5] + temp[10] * other.data[6] + temp[14] * other.data[7];
    this->data[7] = temp[3] * other.data[4] + temp[7] * other.data[5] + temp[11] * other.data[6] + temp[15] * other.data[7];
    
    this->data[8] = temp[0] * other.data[8] + temp[4] * other.data[9] + temp[8] * other.data[10] + temp[12] * other.data[11];
    this->data[9] = temp[1] * other.data[8] + temp[5] * other.data[9] + temp[9] * other.data[10] + temp[13] * other.data[11];
    this->data[10] = temp[2] * other.data[8] + temp[6] * other.data[9] + temp[10] * other.data[10] + temp[14] * other.data[11];
    this->data[11] = temp[3] * other.data[8] + temp[7] * other.data[9] + temp[11] * other.data[10] + temp[15] * other.data[11];

    this->data[12] = temp[0] * other.data[12] + temp[4] * other.data[13] + temp[8] * other.data[14] + temp[12] * other.data[15];
    this->data[13] = temp[1] * other.data[12] + temp[5] * other.data[13] + temp[9] * other.data[14] + temp[13] * other.data[15];
    this->data[14] = temp[2] * other.data[12] + temp[6] * other.data[13] + temp[10] * other.data[14] + temp[14] * other.data[15];
    this->data[12] = temp[3] * other.data[12] + temp[7] * other.data[13] + temp[11] * other.data[14] + temp[15] * other.data[15];

    return this;
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
    Matrix4x4f temp;
    temp.data[0] = temp.data[5] = temp.data[10] = temp.data[15] = 1.0f;
    temp.data[12] = x;
    temp.data[13] = y;
    temp.data[14] = z;
    temp.data[4] = temp.data[8] = temp.data[1] = temp.data[9] = temp.data[2] = temp.data[6] =
    temp.data[3] = temp.data[7] = temp.data[11] = 0.0f;
    
    this->MultiplyWith(temp);
    
	return this;
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