#include "OctSpatrialPartiton.h"


int OctNode::childNumber = 0;

OctNode::OctNode(glm::vec3 position_, float size_, OctNode* parent_) : octBounds(nullptr), parent(nullptr), children(), objectList(std::vector<GameObject*>())
{
	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;
	
	for(int i = 0; i < 8; i++)
	{
		children[i] = 0;
	}

	parent = parent_;
}


OctNode::~OctNode()
{
	OnDestroy();
}

void OctNode::OnDestroy()
{
	delete octBounds;
	octBounds = nullptr;

	if(objectList.size() > 0)
	{
		for(auto go : objectList)
		{
			 go = nullptr;
		}
		objectList.clear();
	}

	for(int i = 0; i < 8; i++)
	{
		if(children[i] != nullptr)
		{
			delete children[i];
			children[i] = nullptr;
		}
	}
}

void OctNode::Octify(int depth_)
{
	if(depth_ > 0 && this) 
	{
		float half = size / 2.0f;
		children[OCT_TLF] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_BLF] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half + half, octBounds->minVert.z + half), half, this);
		children[OCT_BRF] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half + half, octBounds->minVert.z + half), half, this);
		children[OCT_TRF] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_TLR] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half + half), half, this);
		children[OCT_BLR] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half + half, octBounds->minVert.z + half + half), half, this);
		children[OCT_BRR] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half + half, octBounds->minVert.z + half + half), half, this);
		children[OCT_TRR] = new OctNode(glm::vec3(octBounds->minVert.x + half + half, octBounds->minVert.y + half + half, octBounds->minVert.z + half + half), half, this);
		childNumber += 8;
	}

	if(depth_ > 0 && this)
	{
		for(int i = 0; i < 8; i++)
		{
			children[i]->Octify(depth_ - 1);
		}
	}

}

OctNode* OctNode::GetParent()
{
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos_)
{
	return  children[childPos_];
}

void OctNode::AddCollisonObject(GameObject* obj_)
{
	objectList.push_back(obj_);
}

int OctNode::GetObjectCount() const
{
	return objectList.size();
}

bool OctNode::IsLeaf()
{
	if(children[0] == nullptr)
	{
		return  true;
	}

	return false;
}

BoundingBox* OctNode::GetBoundBox() const
{
	return octBounds;
}

int OctNode::GetChildCount() const
{
	return childNumber;
}

OctSpatrialPartiton::OctSpatrialPartiton(float worldSize_)
{
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr);
	root->Octify(3);
	std::cout << "There are " << root->GetChildCount() << " child nodes" << std::endl;
}

OctSpatrialPartiton::~OctSpatrialPartiton()
{
	OnDestroy();
}

void OctSpatrialPartiton::OnDestroy()
{
	delete root;
	root = nullptr;

	if(rayIntersectionList.size() > 0)
	{
		for(auto cell : rayIntersectionList)
		{
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}
}

void OctSpatrialPartiton::AddObject(GameObject* obj_)
{
	AddObjectToCell(root, obj_);
}

GameObject* OctSpatrialPartiton::GetCollision(Ray ray_)
{
	rayIntersectionList.clear();
	PrepareCollisionQuery(root, ray_);
	// TODO: do this, is the same as collision handler

	GameObject* hitResult = nullptr;
	float shortestDist = FLT_MAX;
	for (auto go : rayIntersectionList)
	{
		for(auto go1 : go->objectList)
		{
			if (ray_.IsColliding(&go1->getBoundingBox()))
			{
				if (ray_.intersectionDistance < shortestDist)
				{
					hitResult = go1;
					shortestDist = ray_.intersectionDistance;
				}
			}
		}
	
	}

	return hitResult;
	
}

void OctSpatrialPartiton::AddObjectToCell(OctNode* cell_, GameObject* obj__)
{
	if(cell_)
	{
		BoundingBox nodeBox = *cell_->GetBoundBox();
		if(nodeBox.Intersects(&obj__->getBoundingBox()))
		{
			if(cell_->IsLeaf())
			{
				cell_->AddCollisonObject(obj__);
				std::cout << "Added " << obj__->getTag() << " to cell: " << glm::to_string(nodeBox.maxVert) << std::endl;
			}
			else
			{
				for(int i = 0; i < 8 ; i ++)
				{
					AddObjectToCell(cell_->GetChild(static_cast<OctNode::OctChildren>(i)), obj__);
				}
			}
		}
	}
}

void OctSpatrialPartiton::PrepareCollisionQuery(OctNode* cell_, Ray ray_)
{
	if(cell_)
	{
		if(ray_.IsColliding(cell_->GetBoundBox()))
		{
			if(cell_->IsLeaf())
			{
				rayIntersectionList.push_back(cell_);
			}
			else
			{
				for(int i = 0; i < 8; i++)
				{
					PrepareCollisionQuery(cell_->GetChild(static_cast<OctNode::OctChildren>(i)), ray_);
				}
			}
		}
	}

}
