import random
"""
class that manages the ecosystem simulation
parameters usually the entity data
return none
"""
class Ecosystem:
    """
    constructor, creates the grid and the entity list
    parameters entity data
    return none
    """
    def __init__(self):
        self._area = [[None for _ in range(10)] for _ in range(10)]
        self._entities = []
        self._deathLog = {}
    """
    adds a plant or an animal on grind
    parameters entity data
    return none
    """
    def addEntity(self, entity):
        placed = False
        while not placed:
            x, y = random.randint(0, 9), random.randint(0, 9)
            if self._area[x][y] is None:
                entity._position = (x, y)
                self._area[x][y] = entity
                self._entities.append(entity)
                if isinstance(entity, Animal):
                    entity._ecosystem = self

                print(f"Added {entity}, current position: ({x}, {y}).")
                placed = True
    """
    removes an plant/animal if he dies
    parameters the plant/animal
    return none
    """
    def removeEntity(self, entity):
        if entity in self._entities:
            self._entities.remove(entity)
    """
    display the situation of the ecosystem every day
    parameters entity data
    return none
    """
    def display(self):
        print("\nEcosystem state:")
        for i, row in enumerate(self._area):
            for j, entity in enumerate(row):
                if entity:
                    print(f"{entity}")
    """
    displays the results at the end of the simulation
    parameters entity list
    return none
    """
    def simulationReport(self): 
        print("\nSimulation report:")
        for entity in sorted(self._entities + list(self._deathLog.keys()), key=lambda entity: entity.name):
            if entity.dead:
                print(f"{entity.name} is dead")
            else:
                print(f"{entity.name} is alive")
"""
main data for each entity
parameters none
return none
"""
class EntityEcosystem:
    """
    creates the entity (main data for plants)
    parameters name and entity (plant) data
    return none
    """
    def __init__(self, name, energy=20, survivalRate=70):
        self.name = name
        self._energy = energy
        self._survivalRate = survivalRate
        self._position = None
        self.dead = False 
    """
    function needed for adding energy to plants and animals
    parameters the entity data
    return the grow data
    """
    def grow(self):
        return
    """
    prints the entity data
    parameters the entity data
    return printing the entity data
    """
    def __str__(self):
        return f"{self.name}: Energy left: {self._energy}, Current position: {self._position}"
"""
main data and functions for animals
parameters the EntityEcosystem class
return none
"""
class Animal(EntityEcosystem):
    """
    creates the animal
    parameters name and animal data
    return none
    """
    def __init__(self, name, typePrey, energy=20, survivalRate=70, speed=3):
        super().__init__(name, energy, survivalRate)
        self._typePrey = typePrey
        self._speed = speed 
        self._ecosystem = None 
    """
    increases the energy each day
    parameters animal data
    return none
    """
    def grow(self): 
        if self._position:
            self._energy = min(self._energy + 1, 30)
    """
    makes (or not) a move in the grid
    parameters animal data
    return new probably position
    """
    def move(self):
        if not self._position:
            return

        x, y = self._position
        moveSteps = random.randint(0, self._speed)
        dx, dy = random.choice([(0, moveSteps), (0, -moveSteps), (moveSteps, 0), (-moveSteps, 0)])

        new_x = x + dx
        new_y = y + dy

        if new_x == 0 and new_y == 0:
            print(f"{self.name} is resting")
            return

        if 0 <= new_x < 10 and 0 <= new_y < 10:
            target = self._ecosystem._area[new_x][new_y]

            if target is None:  # Empty tile
                self._ecosystem._area[x][y] = None
                self._ecosystem._area[new_x][new_y] = self
                self._position = (new_x, new_y)
                self._energy -= moveSteps
                print(f"{self.name} is moving")

                if self._energy <= 0:
                    print(f"{self.name} hadn't eaten, so he died.")
                    self._position = None
                    self.dead = True
                    self._ecosystem.removeEntity(self)

            elif isinstance(target, tuple(self._typePrey)) and target != self:
                self._attack(target, self._ecosystem._area, self._ecosystem._deathLog)

            else:
                print(f"{self.name} is resting")
        else:
            print(f"{self.name} is resting")
    """
    attacks a plant or an animal and mark as dead
    parameters animal and subclass data
    return none
    """
    def _attack(self, target, area_, deathLog): 
        if isinstance(target, tuple(self._typePrey)):
            targetEnergy = target._energy
            self._energy = min(self._energy + targetEnergy, 30)
            print(f"{self.name} attacked and ate {target.name}")

            deathLog[target] = self.name

            x, y = target._position
            area_[x][y] = None
            target._position = None
            target.dead = True
            self._ecosystem.removeEntity(target)
"""
subclass of animals, creates an animal that can eat plants
parameters animal data
return none
"""
class Herbivore(Animal):
    def __init__(self, name):
        super().__init__(name, typePrey=(Plant,))
"""
subclass of animals, creates an animal that can eat animals
parameters animal data
return none
"""
class Carnivore(Animal):
    def __init__(self, name):
        super().__init__(name, typePrey=(Animal,))
"""
subclass of animals, creates an animal that can eat both plants and animals
parameters animal data
return none
"""
class Omnivore(Animal):
    def __init__(self, name):
        super().__init__(name, typePrey=(Plant, Animal))
"""
increases the energy every day
parameters plant data
return none
"""
class Plant(EntityEcosystem):
    def grow(self):
        if self._position:
            self._energy = min(self._energy + 1, 30)
            print(f"{self.name} grows")


ecosystem = Ecosystem()

plants = []
for i in range(6):
    plant = Plant(name=f"Plant{i+1}")
    ecosystem.addEntity(plant)
    plants.append(plant)

animals = []
for i in range(4):
    herbivore = Herbivore(name=f"Herbivore{i+1}")
    carnivore = Carnivore(name=f"Carnivore{i+1}")
    omnivore = Omnivore(name=f"Omnivore{i+1}")
    ecosystem.addEntity(herbivore)
    ecosystem.addEntity(carnivore)
    ecosystem.addEntity(omnivore)
    animals.extend([herbivore, carnivore, omnivore])

for step in range(15):
    print(f"\nDay {step+1}:")
    for entity in ecosystem._entities[:]:
        if entity._position:
            if isinstance(entity, Plant):
                entity.grow()
            elif isinstance(entity, Animal):
                entity.move()

    ecosystem.display()

ecosystem.simulationReport()
