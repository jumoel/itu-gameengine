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

void MovingObjectModel::RecalculatePath()
{
	//Only do stuff if the path contains elements.
	if(m_Path != NULL && !m_Path->empty())
	{
		auto next = m_Path->at(0);

		Point tempDirection = next - GetPosition();
		float distance = tempDirection.GetLength();
		tempDirection = tempDirection.GetNormalizedPoint();

		Point oppositDirection = m_Direction.GetNegatedPoint();
		oppositDirection = oppositDirection.GetNormalizedPoint();

		//If direction got negated, we overshot our target or if we have reached our next goal
		if(tempDirection == &oppositDirection || distance < 0.01f)
		{
			m_Path->erase(m_Path->begin());

			if(m_Path->empty())
			{
				m_MovementSpeed = 0;
			}
			else
			{
				next = m_Path->at(0);
				auto pos = GetPosition();

				Point newDirection = next - pos;
				newDirection = newDirection.GetNormalizedPoint();

				if(m_Owner != NULL)
				{
					m_Owner->setLookAt2D(newDirection.X, newDirection.Y);
				}
				else
				{
					SetDirection(newDirection.X, newDirection.Y);
				}
			}

		}
	}
}


