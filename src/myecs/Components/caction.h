#ifndef CACTION_H
#define CACTION_H
#include "../../ECS/component.h"
#include <map>
namespace ECS
{
class CAction : public Component
{
public:
    CAction(ecsint id, ecsint cid);
    std::map<std::string, bool> actions() const;
    const bool getAction(const std::string &index);
    void setActions(const std::string index, bool value);

private:
    std::map<std::string,bool> m_actions;
};
}
#endif // CACTION_H
