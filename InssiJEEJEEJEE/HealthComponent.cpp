#include "HealthComponent.h"
#include "InssiMath.h"
#include "DropComponent.h"
#include "World.h"
#include "GameplayScreen.h"
#include "soundManager.h"
#include "GameOverScreen.h"


void HealthComponent::addHitPoints(int amount) {
	maxHitPoints + amount;
	hitPoints += amount;
}
void HealthComponent::removeHitPoints(int amount) {
	maxHitPoints -= amount;
	hitPoints += amount;
}
void HealthComponent::resetToDefault() {
	int diff = maxHitPoints - defMaxHitPoints;

	hitPoints -= diff;
}

HealthComponent::HealthComponent(GameObject* owner, unsigned int maxHP)
: GameObjectComponent(owner), maxHitPoints(maxHP), hitPoints(maxHP)
{
	defMaxHitPoints = maxHP;
}


HealthComponent::~HealthComponent()
{
}

void HealthComponent::update(sf::Time& tpf) {
	if (getHp() <= 0) {
		// Jos vaikka lopetetaan peli jos pelaaja kuolee
		if (getOwner()->body == getOwner()->getWorld()->getPlayer()->body)
		{	
			// TODO: Niin t�st� pit�is jotenkin pysty� kutsumaan GAME OVERIA
			//getOwner()->getWorld()->getGame()->setGameRunning(false);
			GameObject* player = getOwner()->getWorld()->getPlayer();
			player->getWorld()->getGame()->doNextUpdate([player]() {
				player->getWorld()->getGame()->getStateManager()->push(new GameOverScreen(player->getWorld()->getGame()));
			});
				
				
		}
		else
		{
		DropComponent *dropComponent = (DropComponent*)getOwner()->getComponent<DropComponent>();

		if (dropComponent)
		{
			// TODO spawnaa itemi t�h�n positioon
			dropComponent->dropItem(getOwner()->getPosition().x, getOwner()->getPosition().y, getOwner()->getWorld());
			soundManager::getSound().playSmallMonsterDeath();
		}
		getOwner()->setRemoveOnNextUpdate(true);
	}
}
}

void HealthComponent::takeDamage(int amount) {
	this->hitPoints -= amount;
}

void HealthComponent::draw(sf::RenderWindow& window) {
 	/*sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(32.f * hitPoints/maxHitPoints, 4.f));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(Convert::box2dToWorld(getOwner()->body->GetPosition().x) + 16.f, Convert::box2dToWorld(getOwner()->body->GetPosition().y) - 8.f);
	window.draw(shape);*/
}