#ifndef RESSOURCEHOLDER_H
#define RESSOURCEHOLDER_H

#include <map>




template <typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void load(Identifier id, const std::string & filename);
        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;

    private:
        std::map<Identifier, std::unique_ptr<Resource>> ResourceMap;
};

#include "RessourceHolder.inl"

#endif // RESSOURCEHOLDER_H
