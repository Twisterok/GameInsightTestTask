#ifndef __NODE_H__
#define __NODE_H__
#include <utils/Position.h>
#include <memory>

class node
{
public:
	std::shared_ptr<node>				m_parent;
	std::vector< std::weak_ptr<node> >	m_childs;	
	Position							m_pos;
	int									distance;
	node() : distance(0) {}		
};

#endif