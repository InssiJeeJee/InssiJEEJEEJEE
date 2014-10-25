#include "AltarComponents.h"
#include "PlayerComponents.h"
SwitchComponent::SwitchComponent(GameObject* owner)
	: GameObjectComponent(owner) {

}
SwitchComponent::~SwitchComponent() {

}
void SwitchComponent::update(sf::Time& tpf) {

}
void SwitchComponent::draw(sf::RenderWindow& win) {

}

void SwitchComponent::interactWith(GameObject* gobject) {
	SoulComponent* souls = (SoulComponent*)gobject->getComponent<SoulComponent>();
	assert(souls != NULL);
	souls->setSouls(souls->getSouls() - 10);

	MoonComponent* moon = (MoonComponent*)gobject->getComponent<MoonComponent>();
	assert(moon != NULL);
	moon->setMoonState(moon->getMoonState() + 1);

}
