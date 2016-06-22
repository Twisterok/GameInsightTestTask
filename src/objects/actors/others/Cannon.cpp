#include <objects/actors/others/Cannon.h>

bool	Cannon::nextStateCheck()
{
	m_stepState += m_attackSpeed;
	if (abs(m_stepState - 1.0f) < m_attackSpeed)
	{
		m_stepState = 0.0f;
		return true;
	}	
	return false;
}