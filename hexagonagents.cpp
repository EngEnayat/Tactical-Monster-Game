#include "hexagonagents.h"
#include <QDebug>

hexagonAgents* hexagonAgents::SelectedAgents = nullptr;
void hexagonAgents::HideAgents(bool isHide, QVector<hexagonAgents*> agents)
{
    bool isAgent = false;

    if (agents.contains(this)) {
        if (this == agents[6]) {
            for (auto it : agents) {
                it->setVisible(!isHide);
            }
        } else {
            isAgent = true;
        }
    }
    agents[6]->setVisible(true);

    if (isAgent) {
        if (SelectedAgents && SelectedAgents != this) {
            SelectedAgents->setScale(1.0);
        }
        if (SelectedAgents == this) {
            this->setScale(1.0);
            SelectedAgents = nullptr;
        } else {
            this->setScale(1.1);
            SelectedAgents = this;
        }
    }
}
