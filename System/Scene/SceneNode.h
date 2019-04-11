#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> NodePtr;

    public:
        SceneNode();

        void AttachChild(NodePtr Child);
        ScenePtr DetachChild(const SceneNode& node);

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:


        std::vector<ScenePtr> Children;
        SceneNode* Parent;
};

#endif // SCENENODE_H
