#include <Math/Matrix4x4f.hpp>
#include <cmath>
#include <iostream>

#define REVERSED 1

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
    //data[16]
    //|  0  1  2  3 |
    //|  4  5  6  7 |
    //|  8  9 10 11 |
    //| 12 13 14 15 |
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

#if REVERSED
	
	float f0 = t[0]*o[0] + t[4]*o[1] + t[8]*o[2]  + t[12]*o[3];
	float f1 = t[1]*o[0] + t[5]*o[1] + t[9]*o[2]  + t[13]*o[3];
	float f2 = t[2]*o[0] + t[6]*o[1] + t[10]*o[2] + t[14]*o[3];
	float f3 = t[3]*o[0] + t[7]*o[1] + t[11]*o[2] + t[15]*o[3];

	float f4 = t[0]*o[4] + t[4]*o[5] + t[8]*o[6]  + t[12]*o[7];
	float f5 = t[1]*o[4] + t[5]*o[5] + t[9]*o[6]  + t[13]*o[7];
	float f6 = t[2]*o[4] + t[6]*o[5] + t[10]*o[6] + t[14]*o[7];
	float f7 = t[3]*o[4] + t[7]*o[5] + t[11]*o[6] + t[15]*o[7];

	float f8 = t[0]*o[8] + t[4]*o[9] + t[8]*o[10]  + t[12]*o[11];
	float f9 = t[1]*o[8] + t[5]*o[9] + t[9]*o[10]  + t[13]*o[11];
	float f10 = t[2]*o[8] + t[6]*o[9] + t[10]*o[10] + t[14]*o[11];
	float f11 = t[3]*o[8] + t[7]*o[9] + t[11]*o[10] + t[15]*o[11];

	float f12 = t[0]*o[12] + t[4]*o[13] + t[8]*o[14]  + t[12]*o[15];
	float f13 = t[1]*o[12] + t[5]*o[13] + t[9]*o[14]  + t[13]*o[15];
	float f14 = t[2]*o[12] + t[6]*o[13] + t[10]*o[14] + t[14]*o[15];
	float f15 = t[3]*o[12] + t[7]*o[13] + t[11]*o[14] + t[15]*o[15];
	
	this->data[0] = f0;
	this->data[1] = f1;
	this->data[2] = f2;
	this->data[3] = f3;

	this->data[4] = f4;
	this->data[5] = f5;
	this->data[6] = f6;
	this->data[7] = f7;

	this->data[8]  = f8;
	this->data[9]  = f9;
	this->data[10] = f10;
	this->data[11] = f11;

	this->data[12] = f12;
	this->data[13] = f13;
	this->data[14] = f14;
	this->data[15] = f15;

#else

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
	this->data[1] = f21;
	this->data[2] = f31;
	this->data[3] = f41;

	this->data[4] = f12;
	this->data[5] = f22;
	this->data[6] = f32;
	this->data[7] = f42;

	this->data[8]  = f13;
	this->data[9]  = f23;
	this->data[10] = f33;
	this->data[11] = f43;

	this->data[12] = f14;
	this->data[13] = f24;
	this->data[14] = f34;
	this->data[15] = f44;

#endif
	
	return this;

    
    //data[16]
	//   1  2  3  4
	//.-------------. 
    //|  0  1  2  3 |
    //|  4  5  6  7 |
    //|  8  9 10 11 |
    //| 12 13 14 15 |
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
    temp->data[12] = x;
    temp->data[13] = y;
    temp->data[14] = z;
	return this->MultiplyWith(*temp);
}

Matrix4x4f* Matrix4x4f::Rotate(float degrees, float x, float y, float z)
{

    //data[16]
    //|  0  1  2  3 |
    //|  4  5  6  7 |
    //|  8  9 10 11 |
    //| 12 13 14 15 |

    float length = sqrt(x*x + y*y + z*z);
	if(length > 0)
	{
		x = x/length;
		y = y/length;
		z = z/length;
		// Rotate by <degrees> around (x, y, z)
		degrees = (degrees * 180)/PI;
		float c = cosf(degrees);
		float s = sinf(degrees);
		float t = 1 - c;

		Matrix4x4f temp;
#if REVERSED   
		temp.data[0] = t*x*x + c; temp.data[4] = t*x*y - s*z; temp.data[8] = t*x*z + s*y;
		temp.data[1] = t*x*y + s*z; temp.data[5] = t*y*y + c;  temp.data[9] = t*y*z - s*x;
		temp.data[2] = t*x*z - s*y; temp.data[6] = t*y*z + s*x; temp.data[10] = t*z*z + c;
		temp.data[12] = temp.data[13] = temp.data[14] = temp.data[3] = temp.data[7] = temp.data[11] = 0.0f;
		temp.data[15] = 1.0f;
#else
		temp.data[0] = t*x*x + c; temp.data[1] = t*x*y - s*z; temp.data[2] = t*x*z + s*y;
		temp.data[4] = t*x*y + s*z; temp.data[5] = t*y*y + c;  temp.data[6] = t*y*z - s*x;
		temp.data[8] = t*x*z - s*y; temp.data[9] = t*y*z + s*x; temp.data[10] = t*z*z + c;
		temp.data[12] = temp.data[13] = temp.data[14] = temp.data[3] = temp.data[7] = temp.data[11] = 0.0f;
		temp.data[15] = 1.0f;
#endif
	
		this->MultiplyWith(temp);
	}

	return this;
}

Matrix4x4f* Matrix4x4f::createScale(float x, float y, float z)
{
	Matrix4x4f *temp = new Matrix4x4f();
   
    temp->data[0] = x;
    temp->data[5] = y;
    temp->data[10] = z;
    temp->data[15] = 1.0f;
    temp->data[1] = temp->data[2] = temp->data[3] = temp->data[4] = temp->data[6] = temp->data[7] = temp->data[8] = temp->data[9] =
    temp->data[11] = temp->data[12] = temp->data[13] = temp->data[14] = 0.0f;

	return temp;
}

Matrix4x4f* Matrix4x4f::createTranslate(float x, float y, float z)
{	
	// Translate by (x,y,z)
	auto temp = new Matrix4x4f();
	temp->Reset();
    temp->data[12] = x;
    temp->data[13] = y;
    temp->data[14] = z;
	return temp;
}

Matrix4x4f* Matrix4x4f::createRotate(float degrees, float x, float y, float z)
{

    //data[16]
    //|  0  1  2  3 |
    //|  4  5  6  7 |
    //|  8  9 10 11 |
    //| 12 13 14 15 |
    Matrix4x4f *temp = new Matrix4x4f();
    float length = sqrt(x*x + y*y + z*z);
	if(length > 0)
	{
		x = x/length;
		y = y/length;
		z = z/length;
		// Rotate by <degrees> around (x, y, z)
		degrees = (degrees/180.0f)*PI;
		float c = cosf(degrees);
		float s = sinf(degrees);
		float t = 1 - c;

		
#if REVERSED   
		temp->data[0] = t*x*x + c; temp->data[4] = t*x*y - s*z; temp->data[8] = t*x*z + s*y;
		temp->data[1] = t*x*y + s*z; temp->data[5] = t*y*y + c;  temp->data[9] = t*y*z - s*x;
		temp->data[2] = t*x*z - s*y; temp->data[6] = t*y*z + s*x; temp->data[10] = t*z*z + c;
		temp->data[12] = temp->data[13] = temp->data[14] = temp->data[3] = temp->data[7] = temp->data[11] = 0.0f;
		temp->data[15] = 1.0f;
#else
		temp->data[0] = t*x*x + c; temp->data[1] = t*x*y - s*z; temp->data[2] = t*x*z + s*y;
		temp->data[4] = t*x*y + s*z; temp->data[5] = t*y*y + c;  temp->data[6] = t*y*z - s*x;
		temp->data[8] = t*x*z - s*y; temp->data[9] = t*y*z + s*x; temp->data[10] = t*z*z + c;
		temp->data[12] = temp->data[13] = temp->data[14] = temp->data[3] = temp->data[7] = temp->data[11] = 0.0f;
		temp->data[15] = 1.0f;
#endif
	}
	else
	{
		temp->Reset();
	}

	return temp;
}



Vector3f Matrix4x4f::MultiplyWithVector(Vector3f inVector)
{
	
	float t[16] = {this->data[0], this->data[1], this->data[2], this->data[3],
                    this->data[4], this->data[5], this->data[6], this->data[7],
                    this->data[8], this->data[9], this->data[10], this->data[11],
                    this->data[12], this->data[13], this->data[14], this->data[15]};
	
	float o[4] = {inVector.x(),inVector.y(),inVector.z(), 1};

	float f1 = t[0]*o[0] + t[1]*o[1] + t[2]*o[2]  + t[3]*o[3];
	float f2 = t[4]*o[0] + t[5]*o[1] + t[6]*o[2]  + t[7]*o[3];
	float f3 = t[8]*o[0] + t[9]*o[1] + t[10]*o[2] + t[11]*o[3];
	//float f4 = t[12]*o[3] + t[13]*o[7] + t[14]*o[11] + t[15]*o[15];

	Vector3f outVector;
	outVector.SetX(f1);
	outVector.SetY(f2);
	outVector.SetZ(f3);

	return outVector;
}

void Matrix4x4f::Print()
{
std::cout << "Matrix Data " << std::endl;
std::cout << "|" << this->data[0] << "|" << this->data[1] << "|" << this->data[2] << "|" << this->data[3] << "|" << std::endl;
std::cout << "|" << this->data[4] << "|" << this->data[5] << "|" << this->data[6] << "|" << this->data[7] << "|" << std::endl;
std::cout << "|" << this->data[8] << "|" << this->data[9] << "|" << this->data[10] << "|" << this->data[11] << "|" << std::endl;
std::cout << "|" << this->data[12] << "|" << this->data[13] << "|" << this->data[14] << "|" << this->data[15] << "|" << std::endl;
}
