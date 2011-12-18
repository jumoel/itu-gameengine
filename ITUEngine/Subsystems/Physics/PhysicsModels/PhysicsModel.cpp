#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>
#include <Game/Object.hpp>

void PhysicsModel::SetDirection(float x, float y)
{
	
}

void MovingObjectModel::SetDirection(float x, float y)
{
	m_Direction->X = x;
	m_Direction->Y = y;
}

void MovingObjectModel::calcDirection()
{
	if(m_Path != NULL && !m_Path->empty())
	{
		auto next = m_Path->at(0);

		auto pos = GetPosition();

		Point *tempDirection = new Point(next.X - pos->X, next.Y - pos->Y); // = next - pos;

		//m_Direction = tempDirection.GetNormalizedPoint();
		tempDirection = tempDirection->GetNormalizedPoint(); 
		if(m_Owner != NULL)
		{
			m_Owner->setLookAt2D(tempDirection->X, tempDirection->Y);
		}
		else
		{
			SetDirection(tempDirection->X, tempDirection->Y);
		}

		delete tempDirection;
	}
}

void MovingObjectModel::RecalculatePath()
{
	//Only do stuff if the path contains elements.
	if(m_Path != NULL && !m_Path->empty())
	{
		auto next = m_Path->at(0);

		Point *tempDirection = new Point(next.X - GetPosition()->X, next.Y - GetPosition()->Y);
		//tempDirection.X = next.X - GetPosition()->X;
		//tempDirection.Y = next.Y - GetPosition()->Y;
		float distance = tempDirection->GetLength();
		Point *tt = tempDirection->GetNormalizedPoint();
		delete tempDirection;
		tempDirection = tt;
		tt = nullptr;

		Point *oppositDirection = m_Direction->GetNegatedPoint();
		tt = oppositDirection->GetNormalizedPoint();
		delete oppositDirection;
		oppositDirection = tt;
		tt = nullptr;

		//If direction got negated, we overshot our target or if we have reached our next goal
		if((tempDirection->X == oppositDirection->X && tempDirection->Y == oppositDirection->Y) || distance < 0.01f)
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

				Point *newDirection = new Point(next.X - pos->X, next.Y - pos->Y);
				tt = newDirection->GetNormalizedPoint();
				delete newDirection;
				newDirection = tt;
				tt = nullptr;

				if(m_Owner != NULL)
				{
					m_Owner->setLookAt2D(newDirection->X, newDirection->Y);
				}
				else
				{
					SetDirection(newDirection->X, newDirection->Y);
				}
			}

		}
	}
}


