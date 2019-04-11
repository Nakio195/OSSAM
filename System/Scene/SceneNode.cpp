#include "SceneNode.h"

SceneNode::SceneNode()
{
    Parent = nullptr;
}


void SceneNode::AttachChild(ScenePtr Child)
{
    Child->Parent = this;
    Children.push_back(std::move(Child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (NodePtr& p) -> bool { return p.get() == &node; });
    assert(found != mChildren.end());

    NodePtr result = std::move(*found);
    result->Parent = nullptr;

    Children.erase(found);

    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);

    for (const NodePtr& child : Children)
    {
        child->draw(target, states);
    }
}
