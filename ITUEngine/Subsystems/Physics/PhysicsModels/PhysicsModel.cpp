#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>
#include <Game/Object.hpp>

void PhysicsModel::SetDirection(float x, float y)
{
	
}

void MovingObjectModel::SetDirection(float x, float y)
{
	m_Direction.X = x;
	m_Direction.Y = y;
}

void MovingObjectModel::calcDirection()
{
	if(m_Path != NULL && !m_Path->empty())
	{
		auto next = m_Path->at(0);

		auto pos = GetPosition();

		Point tempDirection = next - pos;

		//m_Direction = tempDirection.GetNormalizedPoint();
		tempDirection = tempDirection.GetNormalizedPoint(); 
		if(m_Owner != NULL)
		{
			m_Owner->setLookAt2D(tempDirection.X, tempDirection.Y);
		}
		else
		{
			SetDirection(tempDirection.X, tempDirection.Y);
		}
	}
}

