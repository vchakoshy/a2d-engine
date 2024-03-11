#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <typeindex>
#include <unordered_map>
#include <set>

const unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
    static int nextId;
};

template <typename TComponent>
class Component : public IComponent
{
    static int GetId()
    {
        static auto id = nextId++;
        return id;
    }
};

class Entity
{
private:
    int id;

public:
    Entity(int id) : id(id)
    {
    }
    int GetId() const;

    Entity &operator=(const Entity &other) = default;
    bool operator==(const Entity &other) const { return id == other.id; };
    bool operator!=(const Entity &other) const { return id != other.id; };
    bool operator<(const Entity &other) const { return id < other.id; };
};

class System
{
private:
    Signature componentSignature;
    std::vector<Entity> entities;

public:
    System() = default;
    ~System() = default;

    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities() const;
    const Signature &GetComponentSignature() const;

    template <typename TComponent>
    void RequireComponent();
};

class IPool
{
public:
    virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool
{
private:
    std::vector<T> data;

public:
    Pool(int size = 100)
    {
        data.resize(size);
    }

    virtual ~Pool() = default;

    bool isEmpty() const
    {
        return data.empty();
    }

    int GetSize() const
    {
        return data.size();
    }

    void Resize(int n)
    {
        data.resize(n);
    }

    void Clear()
    {
        data.clear();
    }

    void Add(T object)
    {
        data.push_back(object);
    }

    void Set(int index, T object)
    {
        data[index] = object;
    }

    T &Get(int index)
    {
        return static_cast<T>(data[index]);
    }

    T &operator[](unsigned int index)
    {
        return data[index];
    }
};

class Registry
{
private:
    int numEntities = 0;
    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

    std::vector<IPool *> componentPools;

    std::vector<Signature> entityComponentSignatures;

    std::unordered_map<std::type_index, System *> systems;

public:
    Registry() = default;

    void Update();

    Entity CreateEntity();

    template <typename TComponent, typename... TArgs>
    void AddComponent(Entity entity, TArgs &&...args);
    template <typename TComponent>
    void RemoveComponent(Entity entity);
    template <typename TComponent>
    bool HasComponent(Entity entity) const;

    template <typename TSystem, typename... TArgs>
    void AddSystem(TArgs &&...args);
    template <typename TSystem>
    void RemoveSystem();
    template <typename TSystem>
    bool HasSystem() const;
    template <typename TSystem>
    TSystem &GetSystem() const;

    void AddEntityToSystems(Entity entity);
};

template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs &&...args)
{
    TSystem *newSystem(new TSystem(std::forward<TArgs>(args)...));
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem()
{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
};

template <typename TSystem>
bool Registry::HasSystem() const
{
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem>
TSystem &Registry::GetSystem() const
{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs &&...args)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    if (componentId >= componentPools.size())
    {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId])
    {
        Pool<TComponent> *newComponentPool = new Pool<TComponent>();
        componentPools[componentId] = newComponentPool;
    }

    Pool<TComponent> *componentPool = componentPools[componentId];
    if (entityId >= componentPool->GetSize())
    {
        componentPool->Resize(numEntities);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);

    entityComponentSignatures[entityId].set(componentId);
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity)
{
    const auto componentId = Component<TComponent>::GetID();
    const auto entityID = entity.GetId();
    entityComponentSignatures[entityID].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const
{
    const auto componentId = Component<TComponent>::GetID();
    const auto entityID = entity.GetId();
    return entityComponentSignatures[entityID].test(componentId);
}

#endif